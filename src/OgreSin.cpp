#ifndef __OgreSin_cpp_
#define __OgreSin_cpp_



#include "BaseApplication.h"
#include "CollisionListener.h"
#include "Bullet.h";
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class OgreSin :public CollisionListener, public BaseApplication
{
public:

	
	void createScene(void) {
		/*
		bulletEntity = mSceneMgr->createEntity("Bullet", "Sinbad.mesh");
		bulletNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BulletNode", inpos);
		bulletNode->attachObject(bulletEntity);
		bulletNode->setDirection(direct);
		*/
	}

	virtual void OnCollision(CollisionListener* object)override {

		/*
		BulletNode->detachObject("Knife" + std::to_string(ID));
		BulletNode->attachObject(colliderEntity);
		*/
		if (object->objectTag == "Bullet") {

			//mSinbadNode->setScale(Vector3(2,2,2));
			
			
		}
		else if (object->objectTag == "Speeditem") {

			MoveSpeed += 20;
			health -= 5;

		}
		else if (object->objectTag == "Healitem") {



		}
	}

	void CreateOgreSin() {

		// Create your scene here :)
	// Create entities
		mSinbad = CurSceneMgr->createEntity("Sinbad_1", "Sinbad.mesh");
		mSwordL = CurSceneMgr->createEntity("SwordL_1", "Sword.mesh");
		mSwordR = CurSceneMgr->createEntity("SwordR_1", "Sword.mesh");

		//floor = mSceneMgr->createEntity("Floor", "cube.mesh");
		//enemy = mSceneMgr->createEntity("Floor", "fish.mesh");

		// Attach each sword entity to sheath
		mSinbad->attachObjectToBone("Sheath.L", mSwordL);
		mSinbad->attachObjectToBone("Sheath.R", mSwordR);

		// Create SceneNode and attach the entity
		mSinbadNode = CurSceneMgr->getRootSceneNode()->createChildSceneNode("SinbadNode_1", Vector3(-20, 5, 0));
		mSinbadNode->attachObject(mSinbad);

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

	}

	void CreateOgreCamera(SceneManager*& curSceneMgr) {

		testYawNode = CurSceneMgr->getRootSceneNode()->createChildSceneNode("testYawNode_1");
		rollNode = CurSceneMgr->getRootSceneNode()->createChildSceneNode("testRollNode_1");

		yawNode = CurSceneMgr->getRootSceneNode()->createChildSceneNode("pitchNode_1");


		mouseCamera = CurSceneMgr->createCamera("mouseCam_1");
		mouseCamera->setAutoAspectRatio(true);
		mouseCamera->setNearClipDistance(5);
		mouseCameraNode = yawNode->createChildSceneNode("mouseCameraNode_1");
		mouseCameraNode->attachObject(mouseCamera);
		mouseCameraNode->setPosition(0, 50, 0);
		mouseCameraNode->setAutoTracking(true, yawNode);
		mouseCameraNode->setFixedYawAxis(true);

	}

	void UpdateOgreSin(const FrameEvent& evt, std::set<Keycode> mPressKeySet, std::set<unsigned char> mPressMouseSet) {

		r = MTrayMgr->getCursorRay(mouseCamera);

		UpdateControll(evt,  mPressKeySet, mPressMouseSet);
		UpdateAnimate(evt, mPressKeySet, mPressMouseSet);

		yawNode->setPosition(mSinbadNode->getPosition());
		yawNode->setOrientation(testYawNode->getOrientation() * rollNode->getOrientation());


		bRunning = false;
		bJumpStart = false;
		bJumpLoop = false;
		bJumpEnd = false;
		rturn = false;
		lturn = false;
		forward = false;
		backward = false;
		throwKnife = false;

		nodeCurPos = mSinbadNode->getPosition();

	};

	void UpdateControll(const FrameEvent& evt, std::set<Keycode> mPressKeySet, std::set<unsigned char> mPressMouseSet) {

		if (mPressMouseSet.count(BUTTON_LEFT) != 0 && Knife_timer.getMilliseconds() > throwKinfePerSec) {

			throwKnife = true;
			Knife_timer.reset();

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
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);

		}
		else if (rturn == true && backward == true) {


			mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() - Radian(Degree(135)), testYawNode->getOrientation().yAxis()));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);
		}
		else if (lturn == true && forward == true) {

			mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() + Radian(Degree(45)), testYawNode->getOrientation().yAxis()));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);
		}
		else if (lturn == true && backward == true) {

			mSinbadNode->setOrientation(Quaternion(yawNode->getOrientation().getYaw() + Radian(Degree(135)), testYawNode->getOrientation().yAxis()));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);

		}
		else if (rturn == true) {

			mSinbadNode->setDirection(Vector3(yawNode->getOrientation().xAxis().x, 0, yawNode->getOrientation().xAxis().z));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);
		}
		else if (lturn == true) {

			mSinbadNode->setDirection(Vector3(-yawNode->getOrientation().xAxis().x, 0, -yawNode->getOrientation().xAxis().z));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);
		}
		else if (forward == true) {

			mSinbadNode->setDirection(Vector3(-yawNode->getOrientation().zAxis().x, 0, -yawNode->getOrientation().zAxis().z));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);
		}
		else if (backward == true) {

			mSinbadNode->setDirection(Vector3(yawNode->getOrientation().zAxis().x, 0, yawNode->getOrientation().zAxis().z));
			mSinbadNode->translate(mSinbadNode->getOrientation().zAxis() * evt.timeSinceLastFrame * MoveSpeed);
		}


		mSinbadNode->setDirection(Vector3(-r.getDirection().x, 0, -r.getDirection().z));

		if ((mPressKeySet.count(' ') != 0))
		{
			mJumpStart->setEnabled(true);
		}

		if ((mPressKeySet.count('z') != 0))
		{
			//mSwordsVertical->setEnabled(true);
		}


		if ((mPressKeySet.count('x') != 0))
		{
			//mSwordsHorizon->setEnabled(true);
		}


		if (throwKnife == true) {

			BulletManager->createBullet(mSinbadNode->getPosition(), mSinbadNode->getOrientation(),  shootPower, shootRange);

		}


		if (mJumpLoop->getEnabled())
		{

			if (!mJumpLoop->hasEnded())
			{

				if (mJumpLoop->getTimePosition() < 0.5 * mJumpLoop->getLength())
				{

					mSinbadNode->translate(Vector3(0, JumpHeight* (mJumpLoop->getLength() / 2 - mJumpLoop->getTimePosition()), 0) * evt.timeSinceLastFrame);
				}
				else
				{
					mSinbadNode->translate(Vector3(0, -JumpHeight * (mJumpLoop->getTimePosition() - (mJumpLoop->getLength() / 2)), 0) * evt.timeSinceLastFrame);
				}
			}
		}

	}

	void UpdateAnimate(const FrameEvent& evt, std::set<Keycode> mPressKeySet, std::set<unsigned char> mPressMouseSet) {

		/*if (mSwordsVertical->getEnabled())
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
		}*/

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
					//mSinbad->attachObjectToBone("Sheath.L", mSwordL);
					//mSinbad->attachObjectToBone("Sheath.R", mSwordR);
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

	Vector3 getPosition() {

		return mSinbadNode->getPosition();

	}

	Ray getMouseRay() {


		return r;

	}

	void setMoveSpeed(float speed) {

		
		MoveSpeed = speed;
		

	}

	void setJumpHeight(float height) {

		
		
		JumpHeight = height;

	}

	void setThrowKinfePerSec(float perSec) {

		throwKinfePerSec = perSec;
		
	}

	void setShootPower(float power) {

		shootPower = power;

	}

	void setShootRange(float range) {

		shootRange = range;

	}

	

	OgreSin(SceneManager*& curSceneMgr, Collision*& collisionManager,Bullet*& bulletManager,TrayManager*& mTrayMgr):mRunBaseState(nullptr),
		mRunTopState(nullptr),
		mSwordState(nullptr),
		mJumpStart(nullptr),
		mJumpLoop(nullptr),
		mJumpEnd(nullptr),
		mSwordsVertical(nullptr),
		mSwordsHorizon(nullptr) {

		CurSceneMgr = curSceneMgr;
		CollisionManager = collisionManager;
		BulletManager = bulletManager;
		MTrayMgr = mTrayMgr;

		CreateOgreSin();
		CreateOgreCamera(curSceneMgr);
		CollisionManager->Register(this);
		objectTag = "OgreSin";
		colliderRange = 5;
	}
	~OgreSin() {



	}


	float throwKinfePerSec = 100;
	float MoveSpeed = 15;
	float JumpHeight = 50;
	float shootPower = 108;
	float shootRange = 60;
	float health = 100;

protected:

	SceneManager* CurSceneMgr;
	Collision* CollisionManager;
	Bullet* BulletManager;
	TrayManager* MTrayMgr;

	SceneNode* mSinbadNode;
	Camera* sinCamera;
	SceneNode* sinCameraNode;
	SceneNode* yawNode;
	SceneNode* testYawNode;
	SceneNode* rollNode;
	SceneNode* mouseCameraNode;


	Entity* mSinbad;
	Entity* mSwordL;
	Entity* mSwordR;

	bool mSwordAtHand;
	
	

	
	Timer Knife_timer;

	AnimationState* mRunBaseState;
	AnimationState* mRunTopState;
	AnimationState* mSwordState;
	AnimationState* mJumpStart;
	AnimationState* mJumpLoop;
	AnimationState* mJumpEnd;
	AnimationState* mSwordsVertical;
	AnimationState* mSwordsHorizon;

	Camera* mouseCamera;
	Ray r;

	float startjumptime = 2;
	float loopjumptime = 6;
	float endjumptime = 2;
	bool rturn = false;
	bool lturn = false;
	bool forward = false;
	bool backward = false;
	bool bRunning = false;
	bool bJumpStart = false;
	bool bJumpLoop = false;
	bool bJumpEnd = false;
	bool throwKnife = false;


	//std::set<Keycode> mPressKeySet;
	//std::set<unsigned char> mPressMouseSet;

};



#endif
