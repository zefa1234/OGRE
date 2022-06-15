
#include "CollisionListener.h"


void CollisionListener::Init(Vector3 nodePosition, string nameTag) {

	nodeCurPos = nodePosition;
	objectTag = nameTag;

}
void CollisionListener::UpdateCollision(CollisionListener* object) {

	bool isOnCollision = false;

	list<CollisionListener*>::iterator h;

	for (h = collidList.begin(); h != collidList.end(); h++) {

		if (object == *h) {

			isOnCollision = true;
			break;
		}

	}

	if (isOnCollision == false) {
		
		collidList.push_back(object);

		OnCollision(object);
		triggerEnter = true;
	
	}

	/*
	if (triggerEnter == false) {

		OnCollision(object);
		triggerEnter = true;
	}
	*/
}

void CollisionListener::NoCollision(CollisionListener* object) {

	triggerEnter = false;


	list<CollisionListener*>::iterator h;

	for (h = collidList.begin(); h != collidList.end(); h++) {

		if (object == *h) {

			collidList.erase(h);
			break;
		}

	}
	
}