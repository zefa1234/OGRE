#ifndef ENEMYMANAGE_H
#define ENEMYMANAGE_H



#include "BaseApplication.h" 
#include "enemyUnit.cpp"
#include "Collision.h"
#include <vector>

using namespace std;
using namespace Ogre;
using namespace OgreBites;

class enemyManage : public BaseApplication
{
public:
	enemyManage();
	~enemyManage();
	virtual void setup(void);
	virtual void createScene(void);
	virtual bool frameRenderingQueued(const FrameEvent& evt);
	void createEnemy(Vector3, SceneManager*&, Collision*&);
	void updateEnemy(const FrameEvent& evt, Vector3);
	void AddCollision(Collision* manager, CollisionListener* object);
	void RemoveCollision(Collision* manager, CollisionListener* object);

protected:
	vector<enemyUnit*> enemyUnitArr;
};
#endif // !ENEMYMANAGE_H