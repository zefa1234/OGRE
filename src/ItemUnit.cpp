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

	ItemUnit(Vector3 initailPos, Quaternion direction,Vector3 scale ,string objTag, string meshName, float collidRange,float rotationSpeed, SceneManager*& mSceneMgr,Collision *&collisionManager, int count) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		CollisionManager = collisionManager;
		ID = count;
		objectTag = objTag;
		colliderRange = collidRange;
		speed = rotationSpeed;

		CollisionManager->Register(this);

		ItemNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("ItemNode" + std::to_string(ID));
		ItemtEntity = currentmSceneMgr->createEntity("Item" + std::to_string(ID), meshName);
		
		ItemNode->setScale(scale);
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

			

			ItemNode->setPosition(Vector3(ItemNode->getPosition().x, ItemNode->getPosition().y, ItemNode->getPosition().z));
			ItemNode->rotate(Quaternion().yAxis(), Radian(Degree(speed* evt.timeSinceLastFrame)));
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
	float curYfloatPos = 0;
	float upDownRange = 2;
	float upDownSpeed = 20;
	float speed = 50;

};



#endif