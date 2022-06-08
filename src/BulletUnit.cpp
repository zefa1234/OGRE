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

	BulletUnit(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,int count) {

		OriginPos = initailPos;
		Origindirection = direction;
		currentmSceneMgr = mSceneMgr;
		ID = count;

		BulletNode = currentmSceneMgr->getRootSceneNode()->createChildSceneNode("KnifeNode" + std::to_string(ID));
		BulletEntity = currentmSceneMgr->createEntity("Knife" + std::to_string(ID), "Sword.mesh");
		BulletNode->attachObject(BulletEntity);
		BulletNode->setOrientation(Origindirection);
		BulletNode->setPosition(OriginPos);

	}
	~BulletUnit(){

		BulletNode = nullptr;
		BulletEntity = nullptr;

	}

	void update(const FrameEvent& evt) {

		
		BulletNode->translate(BulletNode->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);

	}

	string type = "";
	int ID;

protected:

	Vector3 OriginPos;
	Quaternion Origindirection;
	SceneManager* currentmSceneMgr;
	SceneNode* BulletNode;
	Entity* BulletEntity;
	float speed = 30;

};



#endif