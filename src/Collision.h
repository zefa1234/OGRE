#ifndef __Collision_h_
#define __Collision_h_


#include "BaseApplication.h"
#include <vector>
#include <List>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class CollisionListener;

class Collision {

public:

	Collision() {

	}
		
		
	void Register(CollisionListener* collision);
	void UnRegister(CollisionListener* collision);
	string listnum() {

		return std::to_string(collisionListener.size());

	}
	

	void CheckCollision();
	list<CollisionListener*> collisionListener;

private:
	
	/*
	Collision(Collision const&);
	void operator=(Collision const&);
	*/
	


public:

	/*
	Collision(Collision const&) = delete;
	void operator=(Collision const&) = delete;
	*/


};




#endif

