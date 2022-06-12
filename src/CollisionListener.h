#ifndef __CollisionListener_h_
#define __CollisionListener_h_



#include "BaseApplication.h"
#include "Collision.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;


class CollisionListener {

	public:

		/*
		CollisionListener(Vector3 nodePosition , string nameTag) {
		
			Collision().Instance.Register(*this);
			nodeCurPos = nodePosition;
			objectTag = nameTag;

			
		
		};
		*/

		CollisionListener() {}

		void Init(Vector3 nodePosition, string nameTag);
		//void AddToManager(Collision* manager);
		void UpdateCollision(CollisionListener* object);
		virtual void OnCollision(CollisionListener* object) = 0;
		string objectTag = "";
		
		Vector3 nodeCurPos;


	protected:




};

#endif
