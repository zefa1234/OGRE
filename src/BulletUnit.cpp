#ifndef __BulletUnit_cpp_
#define __BulletUnit_cpp_



#include "BaseApplication.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class BulletUnit
{
public:

	BulletUnit(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,int count,float dis,float spd) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		ID = count;
		disRange = dis;
		speed = spd;

		BulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("KnifeNode" + std::to_string(ID));
		BulletEntity = mSceneMgr->createEntity("Knife" + std::to_string(ID), "Sword.mesh");
		BulletNode->attachObject(BulletEntity);
		BulletNode->setOrientation(Origindirection);
		BulletNode->setPosition(OriginPos);
		

	}
	~BulletUnit(){

		

	}

	void update(const FrameEvent& evt, SceneManager*& mSceneMgr) {

		if (isOverRange == false) {

			BulletNode->translate(BulletNode->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);
			if (BulletNode->getPosition().distance(OriginPos) > disRange) {
				isOverRange = true;

				mSceneMgr->destroySceneNode("KnifeNode" + std::to_string(ID));
				mSceneMgr->destroyEntity("Knife" + std::to_string(ID));
			}

		}
		
		

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
	float speed = 30;
	float disRange = 30;

};



#endif