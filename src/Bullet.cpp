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
void Bullet::createBullet(Vector3 initailPos, Vector3 direction) {

	/*
	bulletEntity = mSceneMgr->createEntity("Bullet", "Sword.mesh");
	bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BulletNode");
	bulletNode->setPosition(initailPos);
	bulletNode->attachObject(bulletEntity);
	bulletNode->setDirection(direction);
	*/

}
bool Bullet::frameRenderingQueued(const FrameEvent& evt) {
	if (!BaseApplication::frameRenderingQueued(evt)) return false;



	return true;
}