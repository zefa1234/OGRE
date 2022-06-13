#ifndef __BulletUnit_cpp_
#define __BulletUnit_cpp_



#include "BaseApplication.h"
#include "CollisionListener.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class BulletUnit:public CollisionListener
{
public:

	BulletUnit(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,int count,float dis,float spd) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		ID = count;
		disRange = dis;
		speed = spd;
		objectTag = "Bullet";

		BulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("KnifeNode" + std::to_string(ID));
		BulletEntity = mSceneMgr->createEntity("Knife" + std::to_string(ID), "Sword.mesh");
		colliderEntity = mSceneMgr->createEntity("testCollider" + std::to_string(ID), "Barrel.mesh");
		BulletNode->attachObject(BulletEntity);
		BulletNode->setOrientation(Origindirection);
		BulletNode->setPosition(OriginPos);
		

	}
	~BulletUnit(){

		

	}

	void update(const FrameEvent& evt, SceneManager*& mSceneMgr) {

		if (isOverRange == false) {

			BulletNode->translate(BulletNode->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);
			float tempScale = (BulletNode->getPosition().distance(OriginPos) >= 1 ? BulletNode->getPosition().distance(OriginPos)/10  : 1);
			//BulletNode->setScale(Vector3(1,1,1)*tempScale);
			if (BulletNode->getPosition().distance(OriginPos) > disRange) {
				isOverRange = true;

				mSceneMgr->destroySceneNode("KnifeNode" + std::to_string(ID));
				mSceneMgr->destroyEntity("Knife" + std::to_string(ID));
			}

		}
		
		nodeCurPos = BulletNode->getPosition();
	}

	virtual void OnCollision(CollisionListener* object)override {

		/*
		BulletNode->detachObject("Knife" + std::to_string(ID));
		BulletNode->attachObject(colliderEntity);
		*/
		if (object->objectTag == "OgreSin") {

			if (BulletNode->getAttachedObjects().size() != 0) {

				//BulletNode->detachAllObjects();

			}
			
			//BulletNode->attachObject(colliderEntity);
			//BulletNode->setScale(Vector3(2, 2, 2));

		}
		

	}

	bool collisionDetect(SceneNode* otherObject) {



		return true;

	}

	string type = "";
	int ID;
	bool isOverRange = false;

protected:

	Vector3 OriginPos;
	Quaternion Origindirection;
	SceneManager* currentmSceneMgr;
	SceneNode* BulletNode;
	Entity* BulletEntity;
	Entity* colliderEntity;
	float speed = 30;
	float disRange = 30;

};



#endif