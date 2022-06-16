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
	//跑速0  刀數1  回血23  無456789
	int randomItem = Math::RangeRandom(0, 9);
	if (randomItem == 0)//跑速
		dropItem = "Speeditem";
	else if (randomItem == 1)//刀數
		dropItem = "KnifeItem";
	else if (randomItem == 2 || randomItem == 3)//回血
		dropItem = "Healitem";
	else//無
		dropItem = "no";

		enemyUnit* temp = new enemyUnit(initailPos, CurSceneMgr, CollisionManager, scale, objectTag, meshname, totalCount, colRange, movSpd, ItManager, dropItem);
		totalCount++;
		enemyUnitArr.push_back(temp);
}

void enemyManage::updateEnemy(const FrameEvent& evt, SceneNode* mSinbadNode)
{
	if (fishCount < fishThrshd && enemyResTimer.getMilliseconds() > 1500)
	{
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(1, 1, 1), "fish", "fish.mesh", 2, 8);
		fishCount++;
		enemyResTimer.reset();
	}
	if (stageFishEnd == false && enemyUnitArr.size() == 0 && fishCount == 10)
	{
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(3, 3, 3), "fishKing", "fish.mesh", 5, 12);
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
		createEnemy(Vector3(Math::RangeRandom(-50, 50), 20, Math::RangeRandom(-50, 50)), Vector3(0.7, 0.7, 0.7), "penguinKing", "penguin.mesh", 10, 15);
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