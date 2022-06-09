#include "Bullet.h"

Bullet::Bullet() {

	

}

Bullet::~Bullet() {



}
void Bullet::setup(void) {

	BaseApplication::setup();
	

}
void Bullet::createScene(void) {
	/*
	bulletEntity = mSceneMgr->createEntity("Bullet", "Sinbad.mesh");
	bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BulletNode", inpos);
	bulletNode->attachObject(bulletEntity);
	bulletNode->setDirection(direct);
	*/
}
void Bullet::createBullet(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr, float shootspeed, float shootrange) {

	/*
	SceneNode* tempNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("KnifeNode" + std::to_string(count));
	Entity* tempEntity = mSceneMgr->createEntity("Knife" + std::to_string(count), "Sword.mesh");
	tempNode->attachObject(tempEntity);
	tempNode->setOrientation(direction);
	tempNode->setPosition(initailPos);
	bulletArray.push_back(tempNode);
	*/

	BulletUnit* temp = new BulletUnit(initailPos, direction, mSceneMgr, count, shootrange, shootspeed);
	BulletUnitArray.push_back(temp);

	count++;

}
bool Bullet::frameRenderingQueued(const FrameEvent& evt) {
	if (!BaseApplication::frameRenderingQueued(evt)) return false;

	//bulletNode->translate(bulletNode->getOrientation().zAxis() * evt.timeSinceLastFrame * 10);
	
	for (int i = 0; i < bulletArray.size(); i++) {
	
		SceneNode* temp = bulletArray[i];
		temp->translate(temp->getOrientation().zAxis() * evt.timeSinceLastFrame * 10);

	}
	

	return true;
}

void Bullet::updateBullet(const FrameEvent& evt, SceneManager*& mSceneMgr) {

	/*
	for (int i = 0; i < bulletArray.size(); i++) {

		SceneNode* temp = bulletArray[i];
		temp->translate(temp->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);

	}
	*/
	
	for (int i = 0; i < BulletUnitArray.size(); i++) {

		BulletUnit* temp = BulletUnitArray[i];
		temp->update(evt, mSceneMgr);
		
		
	}

	vector<BulletUnit*>::iterator h;
	

	for (h = BulletUnitArray.begin(); h < BulletUnitArray.end(); h++) {

		BulletUnit* temp = *h;
		if (temp->isOverRange) {

			BulletUnitArray.erase(h);

			delete temp;
		}

	}


}