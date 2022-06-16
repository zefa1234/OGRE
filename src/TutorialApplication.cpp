/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/


Copyright (c) 2000-2013 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/

#include "TutorialApplication.h"


//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication() : mSinbadNode(nullptr),
	floor(nullptr),
	floorNode(nullptr),
	mSinbad(nullptr),
	mSwordL(nullptr),
	mSwordR(nullptr),
	mSwordAtHand(false),
	mRunBaseState(nullptr),
	mRunTopState(nullptr),
	mSwordState(nullptr),
	mJumpStart(nullptr),
	mJumpLoop(nullptr),
	mJumpEnd(nullptr),
	mSwordsVertical(nullptr),
	mSwordsHorizon(nullptr)
{
	Knife_timer.reset();
	st1FishTimer.reset();
	st2PengTimer.reset();
}


//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
	mPressKeySet.clear();
	mPressMouseSet.clear();
	MoveSpeed.clear();
	JumpHeight.clear();

}

void TutorialApplication::setup(void)
{
	
	BaseApplication::setup();

	// Show the cursor
	mTrayMgr->showCursor();

	// Create slider labels
	//MoveSpeed.push_back(mTrayMgr->createLabel(TL_NONE, "MoveSpeedLabel", "MoveSpeed"));
	//JumpHeight.push_back(mTrayMgr->createLabel(TL_NONE, "JumpHeightLabel", "JumpHeight"));


	//MoveSpeed.push_back(mTrayMgr->createLongSlider(TL_RIGHT, "MoveSpeed", "MoveSpeed", 250, 80, 44, 0, 1, 11));
	Move = mTrayMgr->createLongSlider(TrayLocation::TL_TOPRIGHT, "MoveSpeed", "MoveSpeed", 250, 80, 44, 0, 20, 11);
	Height = mTrayMgr->createLongSlider(TrayLocation::TL_TOPRIGHT, "JumpHeight", "JumpHeight", 250, 80, 44, 0, 100, 11);
	ShootRange = mTrayMgr->createLongSlider(TrayLocation::TL_TOPRIGHT, "ShootRange", "ShootRange", 250, 80, 44, 0, 120, 11);
	ShootPower = mTrayMgr->createLongSlider(TrayLocation::TL_TOPRIGHT, "ShootPower", "ShootPower", 250, 80, 44, 0, 150, 11);
	ShootSpeedPerSec = mTrayMgr->createLongSlider(TrayLocation::TL_TOPRIGHT, "ShootSpeed", "ShootSpeed", 250, 80, 44, 0, 500, 11);
	OgreCamDis = mTrayMgr->createLongSlider(TrayLocation::TL_TOPRIGHT, "OgreCamDis", "OgreCamDis", 250, 80, 44, 10, 50, 11);
	CamMovement = mTrayMgr->createCheckBox(TrayLocation::TL_TOPRIGHT, "CamMovement", "CamMovement", 250 );
	testLifeBar = mTrayMgr->createProgressBar(TrayLocation::TL_TOPLEFT, "OgreLifeBar", "Ogre", 250, 50);
	monsterLifeBar = mTrayMgr->createProgressBar(TrayLocation::TL_BOTTOM, "monsterLifeBar", "monster", 500, 50);

	StringVector items;
	items.push_back("debug");
	DebugDetailsPanel = mTrayMgr->createParamsPanel(TrayLocation::TL_BOTTOM,"debug",250,items);
	DebugDetailsPanel->setParamValue(0, "test");


	monsterLifeBar->setProgress(0.7);
	
	monsterLifeBar->setComment("Life");

	testLifeBar->setProgress(0.6);
	testLifeBar->setComment("Life");
	
	Move->setValue(15);
	Height->setValue(50);
	ShootRange->setValue(108);
	ShootPower->setValue(60);
	ShootSpeedPerSec->setValue(100);
	OgreCamDis->setValue(50);
	CamMovement->setChecked(false);
}


//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{

	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a Light and set its position
	Light* light = mSceneMgr->createLight("MainLight");
	SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
	lightNode->attachObject(light);
	lightNode->setPosition(200, 600, 500);


	Plane plane(Vector3::UNIT_Y, 0);

	MeshManager::getSingleton().createPlane(
		"ground", RGN_DEFAULT,
		plane,
		150, 150, 20, 20,
		true,
		1, 5, 5,
		Vector3::UNIT_Z);

	Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

	groundEntity->setCastShadows(false);

	groundEntity->setMaterialName("Examples/Rockwall");

	createOgreCamera();
	


	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 3, 8);
	
	CollisionManager = new Collision();
	bulletManager = new Bullet(mSceneMgr, CollisionManager);
	ItemManager = new Item(mSceneMgr, CollisionManager);

	enemyManager = new enemyManage(mSceneMgr, CollisionManager, ItemManager);
	//ItemManager->createItem(Vector3(10, 5, 10), Quaternion().IDENTITY,Vector3(1,1,1),"Speeditem","Barrel.mesh",3, 50);
	/*ItemManager->createItem(Vector3(30, 5, 10), Quaternion().IDENTITY, Vector3(1, 1, 1), "SpeeditemAndDamage", "Barrel.mesh", 3, 50);
	ItemManager->createItem(Vector3(20, 2, -10), Quaternion().IDENTITY, Vector3(0.1, 0.1, 0.1), "Healitem", "cube.mesh", 3,50);
	ItemManager->createItem(Vector3(10, 2, -10), Quaternion().IDENTITY, Vector3(0.1, 0.1, 0.1), "upgradeKnife", "spine.mesh", 3,50);*/
	/*ItemManager->createItem(Vector3(0, 5, -10), Quaternion().IDENTITY, Vector3(0.1, 0.1, 0.1), "jaiqua", "jaiqua.mesh", 3, 50);
	ItemManager->createItem(Vector3(-10, 5, -10), Quaternion().IDENTITY, Vector3(0.1, 0.1, 0.1), "penguin", "penguin.mesh", 3, 50);
	ItemManager->createItem(Vector3(-20, 5, -10), Quaternion().IDENTITY, Vector3(0.1, 0.1, 0.1), "razor", "razor.mesh", 3, 50);*/

	ogreSin = new OgreSin(mSceneMgr,CollisionManager,bulletManager,mTrayMgr);
	
	//create enemy
		//enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, 50));

		//enemyCount++;
		//enemyMovTimer.reset();
}


void TutorialApplication::createOgreCamera() {

	testYawNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("testYawNode");
	rollNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("testRollNode");

	yawNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("pitchNode");

	
	mCameraNode->detachObject("myCam");
	sinCameraNode = yawNode->createChildSceneNode("sinCameraNode");
	sinCameraNode->attachObject(mCamera);
	sinCameraNode->setPosition(0, 50, 50);
	sinCameraNode->rotate(sinCameraNode->getOrientation().xAxis(),Radian(Degree(-45)));
	//sinCameraNode->setAutoTracking(true, yawNode);
	sinCameraNode->setFixedYawAxis(true);

	mCameraNode->setAutoTracking(true, yawNode);
	mCameraNode->setFixedYawAxis(true);

}

//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const FrameEvent& evt)
{
	if (!BaseApplication::frameRenderingQueued(evt)) return false;
	
		
		/*Move->setValue(ogreSin->MoveSpeed);
		Height->setValue(ogreSin->JumpHeight);
		ShootSpeedPerSec->setValue(ogreSin->throwKinfePerSec);
		ShootPower->setValue(ogreSin->shootPower);
		ShootRange->setValue(ogreSin->shootRange);*/
	
		testLifeBar->setProgress(ogreSin->health/100);

		//ogreSin->setMoveSpeed(Move->getValue());
		ogreSin->setJumpHeight(Height->getValue());
		ogreSin->setThrowKinfePerSec(ShootSpeedPerSec->getValue());
		ogreSin->setShootPower(ShootPower->getValue());
		ogreSin->setShootRange(ShootRange->getValue());

		ogreSin->UpdateOgreSin(evt, mPressKeySet, mPressMouseSet);
		
		
		
		DebugDetailsPanel->setParamValue(0, CollisionManager->listnum());

		
		yawNode->setPosition(ogreSin->getPosition());
		yawNode->setOrientation(testYawNode->getOrientation()* rollNode->getOrientation());

		ItemManager->updateItem(evt);
		bulletManager->updateBullet(evt);
		CollisionManager->CheckCollision();

		//createEnemy(Vector3 initailPos, Vector3 scale, string objectTag, string objTag, string meshname, int colRange, int movSpd);ref

		enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(1, 1, 1), "fish", "fish.mesh", 2, 8, 10, 1000);
		enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(1, 1, 1), "fish", "fish.mesh", 2, 8, 10, 1000);
		/*if (st1FishTimer.getMilliseconds() > 1500 && st1fishN < 5)//stage 1 fish*5
		{
			enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 5, Math::RangeRandom(-50, 50)), Vector3(1, 1, 1), "fish", "fish.mesh", 2, 8);
			st1FishTimer.reset();
			st1fishN++;
		}
		if (st1FishTimer.getMilliseconds() > 4000 && st1fishN < 6)
		{
			enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 15, Math::RangeRandom(-50, 50)), Vector3(3, 3, 3), "fish", "fish.mesh", 5, 10);
			st1FishTimer.reset();
			st1fishN++;
		}
		if (st1FishTimer.getMilliseconds() > 1000 && st2pengN < 10 && st1fishN  <10)
		{
			enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 15, Math::RangeRandom(-50, 50)), Vector3(0.1, 0.1, 0.1), "penguin", "penguin.mesh", 5, 12);
			st2PengTimer.reset();
			st2pengN++;
		}
		if (st1FishTimer.getMilliseconds() > 5000 && st2pengN < 11)
		{
			enemyManager->createEnemy(Vector3(Math::RangeRandom(-50, 50), 15, Math::RangeRandom(-50, 50)), Vector3(0.3, 0.3, 0.3), "penguin", "penguin.mesh", 10, 15);
			st2PengTimer.reset();
			st2pengN++;
		}*/
		

		enemyManager->updateEnemy(evt, ogreSin->mSinbadNode);

		return true;
	
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::keyPressed(const KeyboardEvent &evt)
{
	mPressKeySet.insert(evt.keysym.sym);
	return BaseApplication::keyPressed(evt);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::keyReleased(const KeyboardEvent &evt)
{
	mPressKeySet.erase(evt.keysym.sym);
	return BaseApplication::keyReleased(evt);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::mousePressed(const MouseButtonEvent &evt)
{
	mPressMouseSet.insert(evt.button);
	return BaseApplication::mousePressed(evt);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::mouseReleased(const MouseButtonEvent &evt)
{
	mPressMouseSet.erase(evt.button);
	return BaseApplication::mouseReleased(evt);
}

bool TutorialApplication::mouseMoved(const MouseMotionEvent& evt) {

	
	//testYawNode->yaw(Radian(Degree(-evt.xrel * 0.3)));
	//rollNode->pitch(Radian(Degree(evt.yrel * 0.3)));
	//mSinbadNode->setDirection(Vector3(evt.x, 0, evt.y));
	sinCameraNode->setPosition(0, OgreCamDis->getValue(), OgreCamDis->getValue());
	if (CamMovement->isChecked()) {
		sinCameraNode->setPosition(Vector3(OgreCamDis->getValue() * (-ogreSin->getMouseRay().getDirection().x / 4), sinCameraNode->getPosition().y, OgreCamDis->getValue() * (-ogreSin->getMouseRay().getDirection().z / 4) + OgreCamDis->getValue()));
	}
	
	

	return BaseApplication::mouseMoved(evt);
}

//-------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    try
    {
    	TutorialApplication app;
        app.initApp();
		app.go();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
