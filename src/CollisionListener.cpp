
#include "CollisionListener.h"


void CollisionListener::Init(Vector3 nodePosition, string nameTag) {

	nodeCurPos = nodePosition;
	objectTag = nameTag;

}
void CollisionListener::UpdateCollision(CollisionListener* object) {

	if (triggerEnter == false) {

		OnCollision(object);
		triggerEnter = true;
	}

}

void CollisionListener::NoCollision() {

	triggerEnter = false;
	
}