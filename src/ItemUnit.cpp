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

	ItemUnit(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,Collision *&collisionManager, int count) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		CollisionManager = collisionManager;
		ID = count;
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

		CollisionManager->UnRegister(this);
		currentmSceneMgr->destroySceneNode("ItemNode" + std::to_string(ID));

		currentmSceneMgr->destroyEntity("Item" + std::to_string(ID));

	}

	void update(const FrameEvent& evt) {

		if (isDestroy == false) {


			ItemNode->rotate(Quaternion().yAxis(), Radian(Degree(1)));
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
				

			
			}
			isDestroy = true;
			//BulletNode->attachObject(colliderEntity);
			//BulletNode->setScale(Vector3(2, 2, 2));
			
		}
		

	}


	string type = "";
	int ID;
	bool isDestroy = false;

protected:

	Vector3 OriginPos;
	Quaternion Origindirection;
	SceneManager* currentmSceneMgr;
	Collision* CollisionManager;
	SceneNode* ItemNode;
	Entity* ItemtEntity;
	float speed = 1;

};



#endif