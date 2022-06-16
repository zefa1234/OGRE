#ifndef ENEMYUNIT_H
#define ENEMYUNIT_H



#include "BaseApplication.h"
#include "CollisionListener.h"
#include "Bullet.h"
#include "Item.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class enemyUnit : public CollisionListener
{
public:
	enemyUnit(Vector3 initailPos, SceneManager*& mSceneMgr, Collision*& Colimanager,Bullet*& BulletManager, Vector3 scale, string objTag, string meshname, int count, int colRange, int movSpd, Item*& itemManager, string dropItem)
	{
		currentmSceneMgr = mSceneMgr;
		collisionManager = Colimanager;
		itManager = itemManager;
		bulletManager = BulletManager;
		objectTag = objTag;
		ID = count;
		moveSpeed = movSpd;
		dropIt = dropItem;
		shootTimer.reset();

		enemyEntity = currentmSceneMgr->createEntity("enemy" + std::to_string(ID), meshname);
		enemyNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("enemyNode" + std::to_string(ID), initailPos);
		enemyNode->attachObject(enemyEntity);
		enemyNode->setScale(scale);
		colliderRange = colRange;
		collisionManager->Register(this);

		nodeCurPos = enemyNode->getPosition();
		if (objectTag == "fish")
			health = 15; 
		else if (objectTag == "fishKing")
			health = 150;
		else if (objectTag == "penguin")
			health = 20;
		else if (objectTag == "penguinKing")
			health = 250;


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
			if (objectTag == "fish" || objectTag == "fishKing") {

				enemyNode->setAutoTracking(true, mSinbadNode, VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_X);

				if (objectTag == "fishKing" && shootTimer.getMilliseconds() > 600) {

					bulletManager->createBullet(enemyNode->getPosition(), Quaternion(enemyNode->getOrientation().getYaw() + Radian(Degree(-90)), enemyNode->getOrientation().yAxis()), "fishKingBullet", "Sword.mesh", 20, 108, 1);
					shootTimer.reset();
				}

				
			}
				
			else if (objectTag == "penguin" || objectTag == "penguinKing") {

				enemyNode->setAutoTracking(true, mSinbadNode, -VectorBase<3, Ogre::Real>::NEGATIVE_UNIT_Z);

				if (objectTag == "penguinKing" && shootTimer.getMilliseconds() > 3000) {

					bulletManager->createBullet(enemyNode->getPosition(), enemyNode->getOrientation(), "penguinKingBullet", "Barrel.mesh", 20, 108, 3);
					shootTimer.reset();
				}

				
			}
				

			nodeCurPos = enemyNode->getPosition();
		}


	}

	virtual void OnCollision(CollisionListener* object)override
	{
		if (object->objectTag == "Bullet")
		{
			health--;
			if (health <= 0)
			{
				if (dropIt != "no")
				{
					if(dropIt == "Speeditem")
						itManager->createItem(nodeCurPos, Quaternion().IDENTITY, Vector3(0.05, 0.05, 0.05), dropIt, "ninja.mesh", 3, 50);
					else if (dropIt == "KnifeItem")
						itManager->createItem(nodeCurPos, Quaternion().IDENTITY, Vector3(0.1, 0.1, 0.1), dropIt, "athene.mesh", 3, 50);
					else if (dropIt == "Healitem")
						itManager->createItem(nodeCurPos, Quaternion().IDENTITY, Vector3(0.03, 0.03, 0.03), dropIt, "knot.mesh", 3, 50);
				}
				isDead = true;

				if (objectTag == "penguinKing") {
					bulletManager->isGameOver = true;
				}

			}

		}
		else if (object->objectTag == "OgreSin")
		{
			isDead = true;
		}

	}

	int health = 1;
	int ID;
	int moveSpeed;
	float tempdis;
	string dropIt;
	Vector3 tempV3, V3div;
	SceneNode* enemyNode;
	Entity* enemyEntity;
	Entity* anotherEnt;
	Collision* collisionManager;
	SceneManager* currentmSceneMgr;
	Item* itManager;
	Bullet* bulletManager;
	Timer shootTimer;

	bool isDead = false;
};
#endif