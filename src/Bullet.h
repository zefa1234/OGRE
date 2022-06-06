#ifndef __Bullet_h_
#define __Bullet_h_



#include "BaseApplication.h"


using namespace Ogre;
using namespace OgreBites;

class Bullet : public BaseApplication
{
	public:

		Bullet();
		~Bullet();
		virtual void setup(void);
		virtual void createScene(void);
		virtual bool frameRenderingQueued(const FrameEvent& evt);
		void createBullet(Vector3 initailPos, Vector3 direction);

	protected:

		float speed = 1;
		Vector3 inpos;
		Vector3 direct;

		SceneNode* bulletNode;
		Entity* bulletEntity;

};



#endif