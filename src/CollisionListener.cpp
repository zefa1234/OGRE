
#include "CollisionListener.h"


void CollisionListener::Init(Vector3 nodePosition, string nameTag) {

	nodeCurPos = nodePosition;
	objectTag = nameTag;

}
void CollisionListener::UpdateCollision(CollisionListener* object) {


	OnCollision(object);

}
