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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_




#include "BaseApplication.h"
#include "Bullet.h"
#include "Collision.h"
#include "CollisionListener.h"
#include "OgreSin.cpp"
#include "ItemUnit.cpp"
#include "Item.h"
#include "OgrePageManager.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"
#include "enemyManage.h"
#include <vector>
#include <string>
#include <vector>

using namespace Ogre;
using namespace OgreBites;
using namespace std;

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication();
    virtual ~TutorialApplication();
	

protected:
	virtual void createScene(void);
	virtual void setup(void);
	virtual bool frameRenderingQueued(const FrameEvent &evt);

	// InputListener
	virtual bool keyPressed(const KeyboardEvent &evt);
	virtual bool keyReleased(const KeyboardEvent &evt);
	virtual bool mousePressed(const MouseButtonEvent &evt);
	virtual bool mouseReleased(const MouseButtonEvent &evt);
	virtual bool mouseMoved(const MouseMotionEvent& evt);
	void createOgreCamera();

	SceneNode* mSinbadNode;
	SceneNode* floorNode;
	SceneNode* enemyNode[10];//change to array to store mutiple enemy
	Camera* sinCamera;
	SceneNode* sinCameraNode;
	SceneNode* yawNode;
	SceneNode* testYawNode;
	SceneNode* rollNode;
	SceneNode* mouseCameraNode;
	
	Entity* mSinbad;
	Entity* mSwordL;
	Entity* mSwordR;
	Entity* floor;
	Entity* enemy[10];//change to array to store mutiple enemy

	bool mSwordAtHand;

	AnimationState* mRunBaseState;
	AnimationState* mRunTopState;
	AnimationState* mSwordState;
	AnimationState* mJumpStart;
	AnimationState* mJumpLoop;
	AnimationState* mJumpEnd;
	AnimationState* mSwordsVertical;
	AnimationState* mSwordsHorizon;

	Camera* mouseCamera;
	Bullet* bulletManager;
	Collision* CollisionManager;
	Item* ItemManager;
	OgreSin* ogreSin;
	ItemUnit* testItem;
	enemyManage* enemyManager;

	WidgetList MoveSpeed;
	WidgetList JumpHeight;

	Slider *Move;
	Slider* Height;
	Slider* ShootRange;
	Slider* ShootPower;
	Slider* ShootSpeedPerSec;
	Slider* OgreCamDis;
	CheckBox* CamMovement;
	OgreBites::ProgressBar* testLifeBar;
	OgreBites::ProgressBar* monsterLifeBar;
	ParamsPanel* DebugDetailsPanel;

	Ray r;
	Timer Knife_timer;
	Timer enemyResTimer;
	Timer enemyMovTimer;
	Timer st1FishTimer;
	Timer st2PengTimer;
	int st1fishN = 0;//5
	int st2pengN = 0;//10
	int enemyCount = 0;
	float throwKinfePerSec = 350;
	
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
	

	std::set<Keycode> mPressKeySet;
	std::set<unsigned char> mPressMouseSet;

	//
	enemyUnit* enemyHAHA;
};

#endif // __TutorialApplication_h_
