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
	void createEnemy(Vector3 initailPos, Vector3 scale, string objectTag,  string meshname, int colRange, int movSpd);
	void updateEnemy(const FrameEvent& evt, SceneNode* mSinbadNode);

	vector<enemyUnit*> enemyUnitArr;
	bool stageFishEnd = false;
	bool stagePengEnd = false;
	
protected:
	int fishThrshd = 10;
	int pengThrshd = 20;
	int fishCount = 0;
	int pengCount = 0;
	int totalCount = 0;
	bool drop = false;
	SceneManager* CurSceneMgr;
	Collision* CollisionManager;
	Item* ItManager;
	Timer enemyResTimer;

};
#endif // !ENEMYMANAGE_H
