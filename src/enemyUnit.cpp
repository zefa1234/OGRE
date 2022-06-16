#ifndef ENEMYUNIT_H
#define ENEMYUNIT_H



#include "BaseApplication.h"
#include "CollisionListener.h"
#include "Item.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class enemyUnit : public CollisionListener
{
public:
	enemyUnit(Vector3 initailPos, SceneManager*& mSceneMgr, Collision*& Colimanager, Vector3 scale, string objTag, string meshname, int count, int colRange, int movSpd, Item*& itemManager)
	{
		currentmSceneMgr = mSceneMgr;
		collisionManager = Colimanager;
		itManager = itemManager;
		objectTag = objTag;
		ID = count;
		moveSpeed = movSpd;

		enemyEntity = currentmSceneMgr->createEntity("enemy" + std::to_string(ID), meshname);
		enemyNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("enemyNode" + std::to_string(ID), initailPos);
		enemyNode->attachObject(enemyEntity);
		enemyNode->setScale(scale);
		colliderRange = colRange;
		collisionManager->Register(this);

		//anotherEnt = mSceneMgr->createEntity("Barrel", "Barrel.mesh");

		nodeCurPos = enemyNode->getPosition();
	}
	~enemyUnit()
	{
		collisionManager->UnRegister(this);

		currentmSceneMgr->destroySceneNode("enemyNode" + std::to_string(ID));
		currentmSceneMgr->destroyEntity("enemy" + std::to_string(ID));
	}
	void update(const FrameEvent& evt, SceneNode* mSinbadNode)
	{
		if (isDead == false)
		{
			tempdis = enemyNode->getPosition().distance(mSinbadNode->getPosition());
			tempV3 = Vector3((enemyNode->getPosition().x - mSinbadNode->getPosition().x),
											(enemyNode->getPosition().y - mSinbadNode->getPosition().y),
											(enemyNode->getPosition().z - mSinbadNode->getPosition().z)) / tempdis * evt.timeSinceLastFrame * moveSpeed;
			enemyNode->setPosition(enemyNode->getPosition() - tempV3);
			if (objectTag == "fish")
				enemyNode->setAutoTracking(true, mSinbadNode, VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_X);
			else if (objectTag == "penguin")
				enemyNode->setAutoTracking(true, mSinbadNode, VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Y);

			nodeCurPos = enemyNode->getPosition();
		}


	}

	virtual void OnCollision(CollisionListener* object)override
	{
		if (object->objectTag == "Bullet")
		{
			itManager->createItem(nodeCurPos, Quaternion().IDENTITY, Vector3(1, 1, 1), "Speeditem", "Barrel.mesh", 3, 50);
			isDead = true;

		}
		else if (object->objectTag == "OgreSin")
		{
			isDead = true;
		}

	}

	int ID;
	int moveSpeed;
	float tempdis;
	Vector3 tempV3, V3div;
	SceneNode* enemyNode;
	Entity* enemyEntity;
	Entity* anotherEnt;
	Collision* collisionManager;
	SceneManager* currentmSceneMgr;
	Item* itManager;

	bool isDead = false;
};
#endif