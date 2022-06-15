#include "enemyManage.h"


enemyManage::enemyManage()
{

}

enemyManage::~enemyManage()
{

}

void enemyManage::setup(void)
{
	BaseApplication::setup();
}

void enemyManage::createScene(void)
{

}

bool enemyManage::frameRenderingQueued(const FrameEvent& evt)
{
	return true;
}

void enemyManage::createEnemy(Vector3 initailPos, SceneManager*& mSceneMgr, Collision*& Colimanager)
{
	enemyUnit* temp = new enemyUnit(initailPos, mSceneMgr, Colimanager);

	enemyUnitArr.push_back(temp);

	//AddCollision(Colimanager, temp);
}

void enemyManage::updateEnemy(const FrameEvent& evt, Vector3 ogrePos)
{
	for (int a = 0; a < enemyUnitArr.size(); a++)
	{
		enemyUnit* temp = enemyUnitArr[a];
		temp->update(evt,  ogrePos);
	}
}

void enemyManage::AddCollision(Collision* manager, CollisionListener* object)
{
	manager->Register(object);
}

void enemyManage::RemoveCollision(Collision* manager, CollisionListener* object)
{
	manager->UnRegister(object);
}