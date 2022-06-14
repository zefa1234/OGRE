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

	BulletUnit(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,Collision*& CollisionManager,int count,float dis,float spd) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		collisionManager = CollisionManager;
		ID = count;
		disRange = dis;
		speed = spd;
		objectTag = "Bullet";

		collisionManager->Register(this);
		BulletNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("KnifeNode" + std::to_string(ID));
		BulletEntity = currentmSceneMgr->createEntity("Knife" + std::to_string(ID), "Sword.mesh");
		colliderEntity = currentmSceneMgr->createEntity("testCollider" + std::to_string(ID), "Barrel.mesh");
		BulletNode->attachObject(BulletEntity);
		BulletNode->setOrientation(Origindirection);
		BulletNode->setPosition(OriginPos);
		

	}
	~BulletUnit(){

		collisionManager->UnRegister(this);

	}

	void update(const FrameEvent& evt) {

		if (isOverRange == false) {

			BulletNode->translate(BulletNode->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);
			float tempScale = (BulletNode->getPosition().distance(OriginPos) >= 1 ? BulletNode->getPosition().distance(OriginPos)/10  : 1);
			//BulletNode->setScale(Vector3(1,1,1)*tempScale);
			if (BulletNode->getPosition().distance(OriginPos) > disRange) {
				isOverRange = true;

				currentmSceneMgr->destroySceneNode("KnifeNode" + std::to_string(ID));
				currentmSceneMgr->destroyEntity("Knife" + std::to_string(ID));
			}

		}
		
		nodeCurPos = BulletNode->getPosition();
	}

	virtual void OnCollision(CollisionListener* object)override {

		/*
		BulletNode->detachObject("Knife" + std::to_string(ID));
		BulletNode->attachObject(colliderEntity);
		*/
		if (object->objectTag == "enemy" || object->objectTag == "Speeditem") {

			if (BulletNode->getAttachedObjects().size() != 0) {

				//BulletNode->detachAllObjects();
				currentmSceneMgr->destroySceneNode("KnifeNode" + std::to_string(ID));

				currentmSceneMgr->destroyEntity("Knife" + std::to_string(ID));
			}
			isOverRange = true;
			//BulletNode->attachObject(colliderEntity);
			//BulletNode->setScale(Vector3(2, 2, 2));


		}
		else if (object->objectTag == "Speeditem") {



		}
		
		

	}


	string type = "";
	int ID;
	bool isOverRange = false;

protected:

	Vector3 OriginPos;
	Quaternion Origindirection;
	SceneManager* currentmSceneMgr;
	Collision* collisionManager;
	SceneNode* BulletNode;
	Entity* BulletEntity;
	Entity* colliderEntity;
	float speed = 30;
	float disRange = 30;

};



#endif