#include "enemyManage.h"
#include "Item.h"


enemyManage::enemyManage(SceneManager*& mSceneMgr, Collision*& collisionManager, Item*& itemManager)
{
	CurSceneMgr = mSceneMgr;
	CollisionManager = collisionManager;
	ItManager = itemManager;
	enemyResTimer.reset();
}

enemyManage::~enemyManage()
{

}

void enemyManage::createEnemy(Vector3 initailPos, Vector3 scale, string objectTag, string meshname, int colRange, int movSpd, int limit, int resTimer)
{//enemyUnit(Vector3 initailPos, SceneManager * &mSceneMgr, Collision * &Colimanager, Vector3 scale, string objTag, string meshname, int count, int colRange, int movSpd)ref

	threshhold = limit;
	if (resTimer == 0 && count < threshhold)
	{
		enemyUnit* temp = new enemyUnit(initailPos, CurSceneMgr, CollisionManager, scale, objectTag, meshname, count, colRange, movSpd, ItManager, drop);
		enemyUnitArr.push_back(temp);
		count++;
	}
	else if (count < threshhold && enemyResTimer.getMilliseconds() > resTimer)
	{
		if (count % 3 == 1)
			drop = true;
		else
			drop = false;
		enemyUnit* temp = new enemyUnit(initailPos, CurSceneMgr, CollisionManager, scale, objectTag, meshname, count, colRange, movSpd, ItManager, drop);
		enemyUnitArr.push_back(temp);
		count++;
		enemyResTimer.reset();
	}
}

void enemyManage::updateEnemy(const FrameEvent& evt, SceneNode* mSinbadNode)
{
	for (int a = 0; a < enemyUnitArr.size(); a++)
	{
		enemyUnit* temp = enemyUnitArr[a];
		temp->update(evt, mSinbadNode);
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