#ifndef ENEMYUNIT_H
#define ENEMYUNIT_H



#include "BaseApplication.h"
#include "CollisionListener.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class enemyUnit : public CollisionListener
{
public:
	enemyUnit(Vector3 initailPos, SceneManager*& mSceneMgr, Collision*& Colimanager, int count)
	{
		collisionManager = Colimanager;
		currentmSceneMgr = mSceneMgr;
		ID = count;
		objectTag = "Fish";
		enemyEntity = currentmSceneMgr->createEntity("Fish" + std::to_string(ID), "fish.mesh");
		enemyNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("FishNode" + std::to_string(ID), initailPos);
		enemyNode->attachObject(enemyEntity);
		colliderRange = 7;
		collisionManager->Register(this);

		//anotherEnt = mSceneMgr->createEntity("Barrel", "Barrel.mesh");

		nodeCurPos = enemyNode->getPosition();
	}
	~enemyUnit()
	{
		collisionManager->UnRegister(this);

		currentmSceneMgr->destroySceneNode("FishNode" + std::to_string(ID));
		currentmSceneMgr->destroyEntity("Fish" + std::to_string(ID));
	}
	void update(const FrameEvent& evt, Vector3 ogrePos)
	{
		if (isDead == false)
		{
			tempdis = enemyNode->getPosition().distance(ogrePos);
			tempV3 = Vector3((enemyNode->getPosition().x - ogrePos.x),
											(enemyNode->getPosition().y - ogrePos.y),
											(enemyNode->getPosition().z - ogrePos.z)) / tempdis * evt.timeSinceLastFrame * 8;
			enemyNode->setPosition(enemyNode->getPosition() - tempV3);
		}

	}

	virtual void OnCollision(CollisionListener* object)override
	{
		if (object->objectTag == "Bullet")
		{
			if (enemyNode->getAttachedObjects().size() != 0)
			{
				enemyNode->detachAllObjects();
				//enemyNode->attachObject(anotherEnt);
			}
			isDead = true;
		}
	}

	int ID;
	float tempdis;
	Vector3 tempV3, V3div;
	SceneNode* enemyNode;
	Entity* enemyEntity;
	Entity* anotherEnt;
	Collision* collisionManager;
	SceneManager* currentmSceneMgr;

	bool isDead = false;
};
#endif