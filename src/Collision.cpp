

#include "CollisionListener.h"
#include "BulletUnit.cpp"


void Collision::Register(CollisionListener* collision) {

	collisionListener.push_back(collision);

}

void Collision::UnRegister(CollisionListener* collision) {

	collisionListener.remove(collision);

}


void Collision::CheckCollision() {
	list<CollisionListener*>::iterator h1;
	list<CollisionListener*>::iterator h2;


	for (h1 = collisionListener.begin(); h1 != collisionListener.end(); h1++) {

		h1++;
		if (h1 != collisionListener.end()) {

			h2 = h1;

		}
		else {

			h2 = collisionListener.end();
		}
		
		h1--;

		CollisionListener* temp1 = *h1;
		//BulletUnit* temp1 = dynamic_cast<BulletUnit*>(*h1);

		for (h2; h2 != collisionListener.end(); h2++) {

			CollisionListener* temp2 = *h2;

			if (temp1->nodeCurPos.distance(temp2->nodeCurPos) < 1) {

				temp1->UpdateCollision(temp2);
				temp2->UpdateCollision(temp1);

			}

		}

	}

}





