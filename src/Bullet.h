#ifndef __Bullet_h_
#define __Bullet_h_



#include "BaseApplication.h"
#include "BulletUnit.cpp"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class Bullet : public BaseApplication
{
	public:

		Bullet();
		~Bullet();
		virtual void setup(void);
		virtual void createScene(void);
		virtual bool frameRenderingQueued(const FrameEvent& evt);
		void createBullet(Vector3 initailPos, Quaternion direction, SceneManager*& mSceneMgr,float shootspeed,float shootrange);
		void updateBullet(const FrameEvent& evt, SceneManager*& mSceneMgr);

	protected:

		float speed = 30;
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