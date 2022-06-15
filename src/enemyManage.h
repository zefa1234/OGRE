#ifndef ENEMYMANAGE_H
#define ENEMYMANAGE_H



#include "BaseApplication.h" 
#include "enemyUnit.cpp"
#include "Collision.h"
#include <vector>

using namespace std;
using namespace Ogre;
using namespace OgreBites;

class enemyManage
{
public:
	enemyManage(SceneManager*& mSceneMgr, Collision*& collisionManager);
	~enemyManage();
	void createEnemy(Vector3);
	void updateEnemy(const FrameEvent& evt, Vector3);

protected:
	int count = 0;
	SceneManager* CurSceneMgr;
	Collision* CollisionManager;

	vector<enemyUnit*> enemyUnitArr;
};
#endif // !ENEMYMANAGE_H
