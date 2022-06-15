#ifndef __Item_h_
#define __Item_h_



#include "BaseApplication.h"
#include "ItemUnit.cpp"
#include "Collision.h"
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class Item
{
public:

	Item(SceneManager*& mSceneMgr, Collision*& collisionManager) {

		CurSceneMgr = mSceneMgr;
		CollisionManager = collisionManager;

	};
	~Item(){};
	void createItem(Vector3 initailPos, Quaternion direction) {

		ItemUnit* temp = new ItemUnit(initailPos,direction,CurSceneMgr,CollisionManager,count);
		ItemUnitArray.push_back(temp);
		count++;


	};
	void updateItem(const FrameEvent& evt) {

		for (int i = 0; i < ItemUnitArray.size(); i++) {

			ItemUnit* temp = ItemUnitArray[i];
			temp->update(evt);


		}

		vector<ItemUnit*>::iterator h;


		for (h = ItemUnitArray.begin(); h < ItemUnitArray.end(); h++) {

			ItemUnit* temp = *h;
			if (temp->isDestroy) {

				//RemoveCollision(manager, temp);
				ItemUnitArray.erase(h);

				delete temp;
			}

		}

	};

protected:

	SceneManager* CurSceneMgr;
	Collision* CollisionManager;

	float speed = 30;
	float fireRange = 40;
	int count = 0;
	Vector3 inpos;
	Vector3 direct;

	vector<ItemUnit*> ItemUnitArray;


};



#endif