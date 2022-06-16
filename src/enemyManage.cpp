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

void enemyManage::createEnemy(Vector3 initailPos, Vector3 scale, string objectTag, string meshname, int colRange, int movSpd)
{//enemyUnit(Vector3 initailPos, SceneManager * &mSceneMgr, Collision * &Colimanager, Vector3 scale, string objTag, string meshname, int count, int colRange, int movSpd)ref

		if(totalCount % 3 == 1)
			drop = true;
		else
			drop = false;
		enemyUnit* temp = new enemyUnit(initailPos, CurSceneMgr, CollisionManager, scale, objectTag, meshname, totalCount, colRange, movSpd, ItManager, drop);
		totalCount++;
		enemyUnitArr.push_back(temp);
}

void enemyManage::updateEnemy(const FrameEvent& evt, SceneNode* mSinbadNode)
{
	if (fishCount < fishThrshd && enemyResTimer.getMilliseconds() > 1500)
	{
		/*if (Math::RangeRandom() % 3 == 1)
			drop = true;
		else
			drop = false;*/
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(1, 1, 1), "fish", "fish.mesh", 2, 8);
		fishCount++;
		enemyResTimer.reset();
	}
	if (stageFishEnd == false && enemyUnitArr.size() == 0 && fishCount == 10)
	{
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(3, 3, 3), "fish", "fish.mesh", 5, 12);
		fishCount++;
		stageFishEnd = true;
	}
	if (stageFishEnd == true && pengCount < pengThrshd && enemyResTimer.getMilliseconds() > 1000 && fishCount == 11)
	{
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(0.1, 0.1, 0.1), "penguin", "penguin.mesh",  2, 12);
		pengCount++;
		enemyResTimer.reset();
	}
	if (stagePengEnd == false && enemyUnitArr.size() == 0 && pengCount == 20)
	{
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(0.3, 0.3, 0.3), "penguin", "penguin.mesh", 5, 17);
		stagePengEnd = true;
	}


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