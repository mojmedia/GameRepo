#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "gameplayLayer.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	CCSprite* hero;
	Enemy* enemy;
	float distFraction;
	GameplayLayer* gameplayLayer;

	virtual bool init();

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
	 virtual void ccTouchesBegan(CCSet* pTouches , CCEvent* event);
	 virtual void ccTouchesMoved(CCSet* pTouches , CCEvent* event);
	 virtual void ccTouchesEnded(CCSet* pTouches , CCEvent* event);

	 virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	// virtual void buttonControl(CCObject* pSender);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
