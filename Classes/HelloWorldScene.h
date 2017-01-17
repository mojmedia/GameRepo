#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "gameplayLayer.h"
#include "HUDLayer.h"
#include "ScrollingBgLayer.h"
#include <spine/spine-cocos2dx.h>

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	CCSprite* hero;
	Enemy* enemy;
	float distFraction;
	GameplayLayer* gameplayLayer;
	CCLabelBMFont* scoreLabel;
	HUDLayer* hudLayer;
	ScrollingBgLayer* scrollingBgLayer;
	extension::CCSkeletonAnimation* skeletonNode; 

	virtual bool init();

	void gamePaused();
	void gameResumed();
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	void update(float dt);
	void spawnEnemy(float dt);
	void fireRocket();
	CCRect leftButton, rightButton;
	CCPoint gravity;
	void GameOver();
	int jumpTimer;
	bool jumping;
	// implement the "static node()" method manually
	//touch handle
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	
	typedef enum ActionState // تعریف حاتهای مختلف فعالیت بازی و قهرمان بازی
	{
		kActionStateNone = 0,
		kActionStateIdle,
		kActionStateBoost
	};
	typedef enum PlayerState
	{
		kPlayerStateNone = 0,
		kPLayerStateIdle,
		kPlayerStateBoost
	};
	///for action state
	ActionState mActionState;
	PlayerState mPlayerState;

	CCAction* mIdleAction;// درحالتی ک روس زمین راه میرود
	CCAction* mBoostAction;// حالت پرش

	void idleAnim();
	void boostAnim();
	void AnimationStates();

	// virtual void buttonControl(CCObject* pSender);
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
