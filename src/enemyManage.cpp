#include "enemyManage.h"


enemyManage::enemyManage(SceneManager*& mSceneMgr, Collision*& collisionManager)
{
	CurSceneMgr = mSceneMgr;
	CollisionManager = collisionManager;
}

enemyManage::~enemyManage()
{

}

void enemyManage::createEnemy(Vector3 initailPos)
{
	if (count < threshhold)
	{
		enemyUnit* temp = new enemyUnit(initailPos, CurSceneMgr, CollisionManager, count);
		count++;
		enemyUnitArr.push_back(temp);
	}
}

void enemyManage::updateEnemy(const FrameEvent& evt, Vector3 ogrePos)
{
	for (int a = 0; a < enemyUnitArr.size(); a++)
	{
		enemyUnit* temp = enemyUnitArr[a];
		temp->update(evt,  ogrePos);
	}

	vector<enemyUnit*>::iterator h;

	for (h = enemyUnitArr.begin(); h < enemyUnitArr.end(); h++) {

		enemyUnit* temp = *h;
		if (temp->isDead) {

			enemyUnitArr.erase(h);

			delete temp;
		}

	}
}