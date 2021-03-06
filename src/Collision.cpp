

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

		CollisionListener* temp1 = *h1;

		if (temp1->isTriggerOn == true) {


			h1++;
			if (h1 != collisionListener.end()) {

				h2 = h1;

			}
			else {

				h2 = collisionListener.end();
			}

			h1--;


			//BulletUnit* temp1 = dynamic_cast<BulletUnit*>(*h1);

			bool isCollide = false;

			for (h2; h2 != collisionListener.end(); h2++) {

				CollisionListener* temp2 = *h2;

				if (temp2->isTriggerOn == true) {

					float dis = temp1->nodeCurPos.distance(temp2->nodeCurPos);
					if (dis <= temp1->colliderRange || dis <= temp2->colliderRange) {

						temp1->UpdateCollision(temp2);
						temp2->UpdateCollision(temp1);
						isCollide = true;
					}
					else {

						temp1->NoCollision(temp2);
					}


				}

			}

			/*
			if (isCollide == false) {

				temp1->NoCollision();

			}
			*/

		}

		

	}

}





