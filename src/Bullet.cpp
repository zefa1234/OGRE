#include "Bullet.h"

Bullet::Bullet(SceneManager*& mSceneMgr, Collision*& collisionManager) {

	CurSceneMgr = mSceneMgr;
	CollisionManager = collisionManager;

}

Bullet::~Bullet() {



}

void Bullet::createBullet(Vector3 initailPos, Quaternion direction, float shootspeed, float shootrange) {

	

	BulletUnit* temp = new BulletUnit(initailPos, direction, CurSceneMgr, CollisionManager, count, shootrange, shootspeed);
	
	BulletUnitArray.push_back(temp);

	count++;

	//AddCollision(manager, temp);
	
	
	Quaternion test = Quaternion(direction.getYaw() + Radian(Degree(20)), direction.yAxis());

	BulletUnit* temp2 = new BulletUnit(initailPos, test, CurSceneMgr, CollisionManager, count, shootrange, shootspeed);
	BulletUnitArray.push_back(temp2);


	count++;

	//AddCollision(manager, temp2);

	Quaternion test2 = Quaternion(direction.getYaw() - Radian(Degree(20)), direction.yAxis());

	BulletUnit* temp3 = new BulletUnit(initailPos, test2, CurSceneMgr, CollisionManager, count, shootrange, shootspeed);
	BulletUnitArray.push_back(temp3);


	count++;

	//AddCollision(manager, temp3);
	

}


void Bullet::updateBullet(const FrameEvent& evt) {

	/*
	for (int i = 0; i < bulletArray.size(); i++) {

		SceneNode* temp = bulletArray[i];
		temp->translate(temp->getOrientation().zAxis() * evt.timeSinceLastFrame * speed);

	}
	*/
	
	for (int i = 0; i < BulletUnitArray.size(); i++) {

		BulletUnit* temp = BulletUnitArray[i];
		temp->update(evt);
		
		
	}

	vector<BulletUnit*>::iterator h;
	

	for (h = BulletUnitArray.begin(); h < BulletUnitArray.end(); h++) {

		BulletUnit* temp = *h;
		if (temp->isOverRange) {

			//RemoveCollision(manager, temp);
			BulletUnitArray.erase(h);

			delete temp;
		}

	}


}