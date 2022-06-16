#ifndef __Bullet_h_
#define __Bullet_h_



#include "BaseApplication.h"
#include "BulletUnit.cpp"
#include "Collision.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class Bullet
{
	public:

		Bullet(SceneManager*& mSceneMgr, Collision*& collisionManager);
		~Bullet();
		void createBullet(Vector3 initailPos, Quaternion direction,float shootspeed,float shootrange,int knifeNum);
		void updateBullet(const FrameEvent& evt);
	
	protected:

		SceneManager* CurSceneMgr;
		Collision* CollisionManager;

		float speed = 300;
		float fireRange = 40;
		int count = 0;
		Vector3 inpos;
		Vector3 direct;

		SceneNode* bulletNode;
		Entity* bulletEntity;
		vector<SceneNode*> bulletArray;
		vector<BulletUnit*> BulletUnitArray;
		

};



#endif