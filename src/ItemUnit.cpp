#ifndef __ItemUnit_cpp_
#define __ItemUnit_cpp_



#include "BaseApplication.h"
#include "CollisionListener.h"

#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class ItemUnit :public CollisionListener
{
public:

	ItemUnit(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,Collision *&collisionManager, int count, float dis, float spd) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		CollisionManager = collisionManager;
		ID = count;
		disRange = dis;
		speed = spd;
		objectTag = "Speeditem";
		colliderRange = 2;

		CollisionManager->Register(this);

		ItemNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("ItemNode" + std::to_string(ID));
		ItemtEntity = currentmSceneMgr->createEntity("Item" + std::to_string(ID), "Barrel.mesh");
		
		ItemNode->attachObject(ItemtEntity);
		ItemNode->setOrientation(Origindirection);
		ItemNode->setPosition(OriginPos);

		nodeCurPos = OriginPos;

	}
	~ItemUnit() {

		//CollisionManager->UnRegister(this);

	}

	void update(const FrameEvent& evt, SceneManager*& mSceneMgr) {

		if (isOverRange == false) {

			ItemNode->translate(ItemNode->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);
			float tempScale = (ItemNode->getPosition().distance(OriginPos) >= 1 ? ItemNode->getPosition().distance(OriginPos) / 10 : 1);
			//BulletNode->setScale(Vector3(1,1,1)*tempScale);
			if (ItemNode->getPosition().distance(OriginPos) > disRange) {
				isOverRange = true;

				currentmSceneMgr->destroySceneNode("KnifeNode" + std::to_string(ID));
				currentmSceneMgr->destroyEntity("Knife" + std::to_string(ID));
			}

		}

		nodeCurPos = ItemNode->getPosition();
	}

	virtual void OnCollision(CollisionListener* object)override {

		/*
		BulletNode->detachObject("Knife" + std::to_string(ID));
		BulletNode->attachObject(colliderEntity);
		*/
		if (object->objectTag == "OgreSin") {

			if (ItemNode->getAttachedObjects().size() != 0) {

				//BulletNode->detachAllObjects();
				//currentmSceneMgr->destroySceneNode("ItemNode" + std::to_string(ID));

				currentmSceneMgr->destroyEntity("Item" + std::to_string(ID));

			
			}
			isOverRange = true;
			//BulletNode->attachObject(colliderEntity);
			//BulletNode->setScale(Vector3(2, 2, 2));
			isTriggerOn = false;
		}
		

	}


	string type = "";
	int ID;
	bool isOverRange = false;

protected:

	Vector3 OriginPos;
	Quaternion Origindirection;
	SceneManager* currentmSceneMgr;
	Collision* CollisionManager;
	SceneNode* ItemNode;
	Entity* ItemtEntity;
	float speed = 30;
	float disRange = 30;

};



#endif