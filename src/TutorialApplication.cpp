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
	Move = mTrayMgr->createLongSlider(TL_RIGHT, "MoveSpeed", "MoveSpeed", 250, 80, 44, 0, 10, 11);
	Height = mTrayMgr->createLongSlider(TL_NONE, "JumpHeight", "JumpHeight", 250, 80, 44, 0, 10, 11);
	Move->setValue(5);
	Height->setValue(5);
}


//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create your scene here :)
	// Create entities
	mSinbad = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh"); 
	mSwordL = mSceneMgr->createEntity("SwordL", "Sword.mesh"); 
	mSwordR = mSceneMgr->createEntity("SwordR", "Sword.mesh"); 

	// Attach each sword entity to sheath
	mSinbad->attachObjectToBone("Sheath.L", mSwordL);
	mSinbad->attachObjectToBone("Sheath.R", mSwordR);

	// Create SceneNode and attach the entity
	mSinbadNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("SinbadNode", Vector3(0, 0, 65)); 
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


	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	// Create a Light and set its position
	Light* light = mSceneMgr->createLight("MainLight");
	SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightNode");
	lightNode->attachObject(light);
	lightNode->setPosition(200, 600, 500);
}


//-------------------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const FrameEvent &evt)
{
	if (!BaseApplication::frameRenderingQueued(evt)) return false;

	// Check keyboard to determine running mode
	bool bRunning = false;
	bool bJumpStart = false;
	bool bJumpLoop = false;
	bool bJumpEnd = false;
	
	if ((mPressKeySet.count('j') != 0) && (mPressKeySet.count('l') == 0))
	{
		// Turn left and run
		bRunning = true;
		mSinbadNode->translate(Vector3(-Move->getValue(), 0, 0) * evt.timeSinceLastFrame);
		mSinbadNode->resetOrientation();
		mSinbadNode->yaw(Radian(-Math::HALF_PI));
	}
	else if ((mPressKeySet.count('j') == 0) && (mPressKeySet.count('l') != 0))
	{
		// Turn right and run
		bRunning = true;
		mSinbadNode->translate(Vector3(Move->getValue(), 0, 0) * evt.timeSinceLastFrame);
		mSinbadNode->resetOrientation();
		mSinbadNode->yaw(Radian(Math::HALF_PI));
	}
	else if ((mPressKeySet.count('i') != 0) && (mPressKeySet.count('k') == 0))
	{
		// Turn right and run
		bRunning = true;
		mSinbadNode->translate(Vector3(0, 0, -Move->getValue()) * evt.timeSinceLastFrame);
		mSinbadNode->resetOrientation();
		mSinbadNode->yaw(Radian(Math::PI));
	}
	else if ((mPressKeySet.count('i') == 0) && (mPressKeySet.count('k') != 0))
	{
		// Turn right and run
		bRunning = true;
		mSinbadNode->translate(Vector3(0, 0, Move->getValue()) * evt.timeSinceLastFrame);
		mSinbadNode->resetOrientation();
		//mSinbadNode->yaw(Radian(Math::HALF_PI));
	}

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
	
	if(mSwordsVertical->getEnabled())
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
		else 
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
	

	if(bRunning)
	{
		// Advance the animation
		mRunBaseState->setEnabled(true);
		mRunBaseState->addTime(evt.timeSinceLastFrame);
	}
	else
	{
		// Reset node orientation and time position
		mSinbadNode->resetOrientation();

		mRunBaseState->setEnabled(false);
		mRunBaseState->setTimePosition(0);

		mRunTopState->setEnabled(false);
		mRunTopState->setTimePosition(0);
	}

	

	

	// Check if swords are being drawn or put
	if(mSwordState->getEnabled())
	{
		// Continue drawing or putting swords until ended
		if(mSwordState->hasEnded())
		{
			mSwordState->setEnabled(false);
			mSwordState->setTimePosition(0);

			mSwordAtHand = !mSwordAtHand;
		}
		else if(mSwordState->getTimePosition() >= (0.5 * mSwordState->getLength()))
		{
			// Dettach each sword entity
			mSinbad->detachObjectFromBone(mSwordL);
			mSinbad->detachObjectFromBone(mSwordR);

			// Attach each sword entity to sheath or hand
			if(mSwordAtHand)
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
	else if(mPressMouseSet.count(BUTTON_LEFT) != 0)
	{
		// Start drawing or putting swords
		mSwordState->setEnabled(true);
		mSwordState->addTime(evt.timeSinceLastFrame);

		// Disable the RunTop animation
		mRunTopState->setEnabled(false);
		mRunTopState->setTimePosition(0);
	}
	else if(bRunning)
	{
		mRunTopState->setEnabled(true);
		mRunTopState->addTime(evt.timeSinceLastFrame);
	}

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
