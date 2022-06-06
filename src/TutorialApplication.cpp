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
#include "Bullet.h"


//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication() : mSinbadNode(nullptr),
	floor(nullptr),
	floorNode(nullptr),
	KnifeNode(nullptr),
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
	Move = mTrayMgr->createLongSlider(TrayLocation::TL_BOTTOMRIGHT, "MoveSpeed", "MoveSpeed", 250, 80, 44, 0, 20, 11);
	Height = mTrayMgr->createLongSlider(TrayLocation::TL_BOTTOMRIGHT, "JumpHeight", "JumpHeight", 250, 80, 44, 0, 10, 11);
	
	Move->setValue(15);
	Height->setValue(10);

	
}


//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create your scene here :)
	// Create entities
	mSinbad = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh"); 
	mSwordL = mSceneMgr->createEntity("SwordL", "Sword.mesh"); 
	mSwordR = mSceneMgr->createEntity("SwordR", "Sword.mesh"); 

	//floor = mSceneMgr->createEntity("Floor", "cube.mesh");
	//enemy = mSceneMgr->createEntity("Floor", "fish.mesh");

	// Attach each sword entity to sheath
	mSinbad->attachObjectToBone("Sheath.L", mSwordL);
	mSinbad->attachObjectToBone("Sheath.R", mSwordR);

	// Create SceneNode and attach the entity
	mSinbadNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("SinbadNode", Vector3(0, 5, 0)); 
	mSinbadNode->attachObject(mSinbad);


	//-----------------------------------------enemy
	for (int a = 0; a < 10; a++)//fish
	{
		enemy[a] = mSceneMgr->createEntity(enemySinbadName[a], "fish.mesh");
		enemyNode[a] = mSceneMgr->getRootSceneNode()->createChildSceneNode(enemyNodeName[a], Vector3(Math::RangeRandom(-50, 50), 5, 50));
		enemyNode[a]->attachObject(enemy[a]);
	}
	//---------------------------------------------

	/*enemyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("enemyNode", Vector3(20, 5, 0));
	enemyNode->attachObject(enemy);*/

	/*
	floorNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("FloorNode", Vector3(0, 32, 0));
	floorNode->attachObject(floor);
	floorNode->setScale(Vector3(1, 0.05, 1));
	*/

	// Set cumulative blending mode
	mSinbad->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	// Set default key-frame interpolation mode
	Animation::setDefaultInterpolationMode(Animation::IM_SPLINE);
	Animation::setDefaultRotationInterpolationMode(Animation::RIM_SPHERICAL);

	// Set animation state properties ("RunBase")
	mRunBaseState = mSinbad->getAnimationState("RunBase");
	mRunBaseState->setLoop(true);
	mRunBaseState->setEnabled(false);

	// Set animation state properties ("RunTop")
	mRunTopState = mSinbad->getAnimationState("RunTop");
	mRunTopState->setLoop(true);
	mRunTopState->setEnabled(false);

	// Set animation state properties ("DrawSwords")
	mSwordState = mSinbad->getAnimationState("DrawSwords");
	mSwordState->setLoop(false);
	mSwordState->setEnabled(false);

	mJumpStart = mSinbad->getAnimationState("JumpStart");
	mJumpStart->setLoop(false);
	mJumpStart->setEnabled(false);

	mJumpLoop = mSinbad->getAnimationState("JumpLoop");
	mJumpLoop->setLoop(false);
	mJumpLoop->setEnabled(false);

	mJumpEnd = mSinbad->getAnimationState("JumpEnd");
	mJumpEnd->setLoop(false);
	mJumpEnd->setEnabled(false);

	mSwordsVertical = mSinbad->getAnimationState("SliceVertical");
	mSwordsVertical->setLoop(false);
	mSwordsVertical->setEnabled(false);
	mSwordsHorizon = mSinbad->getAnimationState("SliceHorizontal");
	mSwordsHorizon->setLoop(false);
	mSwordsHorizon->setEnabled(false);


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
	
	
	
}


void TutorialApplication::createOgreCamera() {

	testYawNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("testYawNode");
	rollNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("testRollNode");

	yawNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("pitchNode");


	mouseCamera = mSceneMgr->createCamera("mouseCam");
	mouseCamera->setAutoAspectRatio(true);
	mouseCamera->setNearClipDistance(5);
	muoseCameraNode = yawNode->createChildSceneNode("mouseCameraNode");
	muoseCameraNode->attachObject(mouseCamera);
	muoseCameraNode->setPosition(0, 50, 0);
	muoseCameraNode->setAutoTracking(true, yawNode);
	muoseCameraNode->setFixedYawAxis(true);

	mCameraNode->detachObject("myCam");
	sinCameraNode = yawNode->createChildSceneNode("sinCameraNode");
	sinCameraNode->attachObject(mCamera);
	sinCameraNode->setPosition(0, 35, -40);
	sinCameraNode->setAutoTracking(true, yawNode);
	sinCameraNode->setFixedYawAxis(true);

	mCameraNode->setAutoTracking(true, yawNode);
	mCameraNode->setFixedYawAxis(true);

}

//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const FrameEvent& evt)
{
	if (!BaseApplication::frameRenderingQueued(evt)) return false;
	

		// Check keyboard to determine running mode
		
		//mTrayMgr->hideCursor();
		
		r = mTrayMgr->getCursorRay(mouseCamera);
		
		
		updateControl(evt);
		updateAnimate(evt);
		
		yawNode->setPosition(mSinbadNode->getPosition());
		yawNode->setOrientation(testYawNode->getOrientation()* rollNode->getOrientation());
		if(KnifeNode!=nullptr)
		KnifeNode->translate(KnifeNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
		for (int a = 0; a < 10; a++)
		{
			float tempdis = enemyNode[a]->getPosition().distance(mSinbadNode->getPosition());
			Vector3 temp = Vector3((enemyNode[a]->getPosition().x-mSinbadNode->getPosition().x), (enemyNode[a]->getPosition().y - mSinbadNode->getPosition().y) , (enemyNode[a]->getPosition().z - mSinbadNode->getPosition().z) )/ tempdis * evt.timeSinceLastFrame*8;

			enemyNode[a]->setPosition(enemyNode[a]->getPosition() - temp);
		}

		bRunning = false;
		bJumpStart = false;
		bJumpLoop = false;
		bJumpEnd = false;
		rturn = false;
		lturn = false;
		forward = false;
		backward = false;
		throwKnife = false;

		return true;
	
}

void TutorialApplication::updateControl(const FrameEvent& evt) {

	if (mPressMouseSet.count(BUTTON_LEFT) != 0) {

		throwKnife = true;

	}
	if ((mPressKeySet.count('a') == 0) && (mPressKeySet.count('d') != 0))
	{
		// Turn left and run
		bRunning = true;
		
		//mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
		
		rturn = true;
	}
	else if ((mPressKeySet.count('a') != 0) && (mPressKeySet.count('d') == 0))
	{
		// Turn right and run
		bRunning = true;
		
		//mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
		lturn = true;
	}
	if ((mPressKeySet.count('w') == 0) && (mPressKeySet.count('s') != 0))
	{
		// Turn right and run
		bRunning = true;
		
		//mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
		backward = true;
	}
	else if ((mPressKeySet.count('w') != 0) && (mPressKeySet.count('s') == 0))
	{
		// Turn right and run
		bRunning = true;
		
		//mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
		forward = true;
	}

	if (rturn == true && forward == true) {
		
		mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() - Radian(Degree(45)), testYawNode->getOrientation().yAxis()));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());

	}
	else if (rturn == true && backward == true) {

		
		mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() - Radian(Degree(135)), testYawNode->getOrientation().yAxis()));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
	}
	else if (lturn == true && forward == true) {
		
		mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() + Radian(Degree(45)), testYawNode->getOrientation().yAxis()));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
	}
	else if (lturn == true && backward == true) {
		
		mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() + Radian(Degree(135)), testYawNode->getOrientation().yAxis()));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());

	}
	else if (rturn == true) {
		
		mSinbadNode->setDirection(Vector3(yawNode->getOrientation().xAxis().x, 0, yawNode->getOrientation().xAxis().z));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
	}
	else if (lturn == true) {
		
		mSinbadNode->setDirection(Vector3(-yawNode->getOrientation().xAxis().x, 0, -yawNode->getOrientation().xAxis().z));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
	}
	else if (forward == true) {
		
		mSinbadNode->setDirection(Vector3(-yawNode->getOrientation().zAxis().x, 0, -yawNode->getOrientation().zAxis().z));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
	}
	else if (backward == true) {
		
		mSinbadNode->setDirection(Vector3(yawNode->getOrientation().zAxis().x, 0, yawNode->getOrientation().zAxis().z));
		mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * Move->getValue());
	}


	mSinbadNode->setDirection(Vector3(-r.getDirection().x, 0, -r.getDirection().z));

	if ((mPressKeySet.count(' ') != 0))
	{
		mJumpStart->setEnabled(true);
	}

	if ((mPressKeySet.count('z') != 0))
	{
		mSwordsVertical->setEnabled(true);
	}


	if ((mPressKeySet.count('x') != 0))
	{
		mSwordsHorizon->setEnabled(true);
	}


	if (throwKnife == true) {

		
			KnifeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("KnifeNode" + std::to_string(count));
			Knife = mSceneMgr->createEntity("Knife" + std::to_string(count), "Sword.mesh");
			KnifeNode->attachObject(Knife);
			KnifeNode->setOrientation(mSinbadNode->getOrientation());
			KnifeNode->setPosition(mSinbadNode->getPosition());
			
		
		
		count++;
	}
	

	if (mJumpLoop->getEnabled())
	{
		
		if(!mJumpLoop->hasEnded())
		{

			if (mJumpLoop->getTimePosition() < 0.5 * mJumpLoop->getLength())
			{

				mSinbadNode->translate(Vector3(0, Height->getValue(), 0) * evt.timeSinceLastFrame);
			}
			else
			{
				mSinbadNode->translate(Vector3(0, -Height->getValue(), 0) * evt.timeSinceLastFrame);
			}
		}
	}

}

void TutorialApplication::updateAnimate(const FrameEvent& evt) {


	

	if (mSwordsVertical->getEnabled())
	{
		mSwordsVertical->addTime(evt.timeSinceLastFrame);
		if (mSwordsVertical->hasEnded())
		{
			mSwordsVertical->setTimePosition(0);
			mSwordsVertical->setEnabled(false);
		}
	}

	if (mSwordsHorizon->getEnabled())
	{
		mSwordsHorizon->addTime(evt.timeSinceLastFrame);
		if (mSwordsHorizon->hasEnded())
		{
			mSwordsHorizon->setTimePosition(0);
			mSwordsHorizon->setEnabled(false);
		}
	}

	if (mJumpStart->getEnabled())
	{
		mJumpStart->addTime(evt.timeSinceLastFrame);
		if (mJumpStart->hasEnded())
		{
			mJumpLoop->setEnabled(true);
		}

	}

	if (mJumpLoop->getEnabled())
	{
		mJumpStart->setEnabled(false);
		mJumpLoop->addTime(evt.timeSinceLastFrame);
		if (mJumpLoop->hasEnded())
		{
			mJumpEnd->setEnabled(true);

		}
		


	}

	if (mJumpEnd->getEnabled())
	{
		mJumpLoop->setEnabled(false);
		mJumpEnd->addTime(evt.timeSinceLastFrame);


	}

	if (mJumpEnd->hasEnded())
	{
		mJumpEnd->setEnabled(false);
		mJumpStart->setTimePosition(0);
		mJumpLoop->setTimePosition(0);
		mJumpEnd->setTimePosition(0);
	}


	if (bRunning)
	{
		// Advance the animation
		mRunBaseState->setEnabled(true);
		mRunBaseState->addTime(evt.timeSinceLastFrame);
	}
	else
	{
		// Reset node orientation and time position
		//mSinbadNode->resetOrientation();

		mRunBaseState->setEnabled(false);
		mRunBaseState->setTimePosition(0);

		mRunTopState->setEnabled(false);
		mRunTopState->setTimePosition(0);
	}





	// Check if swords are being drawn or put
	if (mSwordState->getEnabled())
	{
		// Continue drawing or putting swords until ended
		if (mSwordState->hasEnded())
		{
			mSwordState->setEnabled(false);
			mSwordState->setTimePosition(0);

			mSwordAtHand = !mSwordAtHand;
		}
		else if (mSwordState->getTimePosition() >= (0.5 * mSwordState->getLength()))
		{
			// Dettach each sword entity
			mSinbad->detachObjectFromBone(mSwordL);
			mSinbad->detachObjectFromBone(mSwordR);

			// Attach each sword entity to sheath or hand
			if (mSwordAtHand)
			{
				mSinbad->attachObjectToBone("Sheath.L", mSwordL);
				mSinbad->attachObjectToBone("Sheath.R", mSwordR);
			}
			else
			{
				mSinbad->attachObjectToBone("Handle.L", mSwordL);
				mSinbad->attachObjectToBone("Handle.R", mSwordR);
			}
		}

		mSwordState->addTime(evt.timeSinceLastFrame);
	}
	else if (mPressMouseSet.count(BUTTON_LEFT) != 0)
	{
		// Start drawing or putting swords
		mSwordState->setEnabled(true);
		mSwordState->addTime(evt.timeSinceLastFrame);

		// Disable the RunTop animation
		mRunTopState->setEnabled(false);
		mRunTopState->setTimePosition(0);
	}
	else if (bRunning)
	{
		mRunTopState->setEnabled(true);
		mRunTopState->addTime(evt.timeSinceLastFrame);
	}
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
