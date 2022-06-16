#ifndef ENEMYMANAGE_H
#define ENEMYMANAGE_H



#include "BaseApplication.h" 
#include "enemyUnit.cpp"
#include "Collision.h"
#include "Item.h"
#include <vector>

using namespace std;
using namespace Ogre;
using namespace OgreBites;

class enemyManage
{
public:
	enemyManage(SceneManager*& mSceneMgr, Collision*& collisionManager, Item*& itemManager);
	~enemyManage();
	void createEnemy(Vector3 initailPos, Vector3 scale, string objectTag,  string meshname, int colRange, int movSpd, int limit, int resTimer);
	void updateEnemy(const FrameEvent& evt, SceneNode* mSinbadNode);

protected:
	int count = 0;
	int threshhold;
	SceneManager* CurSceneMgr;
	Collision* CollisionManager;
	Item* ItManager;
	Timer enemyResTimer;

	vector<enemyUnit*> enemyUnitArr;
};
#endif // !ENEMYMANAGE_H
