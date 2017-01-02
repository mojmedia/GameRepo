#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "GameplayLayer.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
	CCSprite*	hero;
	CCSize visibleSize;
	float distFraction;
	//Enemy*	enemy;
	GameplayLayer* gameplayLayer;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
	
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
	//......................gravity...............
	CCPoint	gravity;
	int	jumpTimer;
	bool	jumping;
	// ...................update function...........
	virtual void update(float dt);
	virtual void spawnEnemy(float dt);
	//..............hero controls...................
	void	fireRocket();
	CCRect	leftButton, rightButton;
	//......................function arrow ..........
	/*void buttonControlleft(CCObject *pSender);
	void buttonControldown(CCObject *pSender);
	void buttonControltop(CCObject *pSender);
	void buttonControlright(CCObject *pSender);*/
	//void buttongun(CCObject *pSender);

	//....................touch............
	virtual	void ccTouchesBegan(CCSet* pTouches, CCEvent *event);
	virtual	void ccTouchesMoved(CCSet* pTouches, CCEvent *event);
	virtual	void ccTouchesEnded(CCSet* pTouches, CCEvent *event);
	//..................accelerometer...............
	virtual	void	didAccelerate(CCAcceleration*	pAccelerationValue);
};

#endif // __HELLOWORLD_SCENE_H__
