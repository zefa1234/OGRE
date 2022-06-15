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
		ID = count;
		objectTag = "Fish";
		enemyEntity = mSceneMgr->createEntity("Fish" + std::to_string(ID), "fish.mesh");
		enemyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemy" + std::to_string(ID), initailPos);
		enemyNode->attachObject(enemyEntity);
		Colimanager->Register(this);

		//anotherEnt = mSceneMgr->createEntity("Barrel", "Barrel.mesh");

		nodeCurPos = enemyNode->getPosition();
	}

	void update(const FrameEvent& evt, Vector3 ogrePos)
	{
		tempdis = enemyNode->getPosition().distance(ogrePos);
		tempV3 = Vector3((enemyNode->getPosition().x - ogrePos.x),
										(enemyNode->getPosition().y - ogrePos.y),
										(enemyNode->getPosition().z - ogrePos.z)) / tempdis * evt.timeSinceLastFrame * 8;
		enemyNode->setPosition(enemyNode->getPosition() - tempV3);


		/*tempdis = enemyNode->getPosition().distance(mSinbadNode->getPosition());
		tempV3 = Vector3((enemyNode->getPosition().x - mSinbadNode->getPosition().x),
			(enemyNode->getPosition().y - mSinbadNode->getPosition().y),
			(enemyNode->getPosition().z - mSinbadNode->getPosition().z)) / tempdis * evt.timeSinceLastFrame * 8;
		enemyNode->setPosition(enemyNode->getPosition() - tempV3);*/
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
		}
	}

	int ID;
	float tempdis;
	Vector3 tempV3, V3div;
	SceneNode* enemyNode;
	Entity* enemyEntity;
	Entity* anotherEnt;
};
#endif