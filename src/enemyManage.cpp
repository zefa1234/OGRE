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
	enemyUnit* temp = new enemyUnit(initailPos, CurSceneMgr, CollisionManager, count);

	enemyUnitArr.push_back(temp);
}

void enemyManage::updateEnemy(const FrameEvent& evt, Vector3 ogrePos)
{
	for (int a = 0; a < enemyUnitArr.size(); a++)
	{
		enemyUnit* temp = enemyUnitArr[a];
		temp->update(evt,  ogrePos);
	}
}