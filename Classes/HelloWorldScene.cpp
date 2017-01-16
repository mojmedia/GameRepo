//بسم االله الرحمن الرحیم
#include "HelloWorldScene.h"
#include "Projectile.h"
#include "GameplayLayer.h"


USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	//...................background............
	CCSprite*	bg = CCSprite::create("bookGame_Bg.png");
	bg->setPosition(ccp(visibleSize.width *	0.5, visibleSize.height	* 0.5));
	this->addChild(bg, -1);

	//.................hero....................
	hero = CCSprite::create("bookGame_tinyBazooka.png");
	hero->setPosition(ccp(visibleSize.width	*	0.25, visibleSize.height	*
		0.5));
	this->addChild(hero, 5);
	//.....................add GameplayLayer....
	gameplayLayer = new	GameplayLayer(hero);
	this->addChild(gameplayLayer);
	//...............scheduleUpdate.............
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	//................set touch layer...........
	this->setTouchEnabled(true);
	//................set accelerometer.........
	this->setAccelerometerEnabled(true);
	//.............hero contorls................
	leftButton = CCRectMake(0, 0, visibleSize.width / 2, visibleSize.height);
	rightButton = CCRectMake(visibleSize.width / 2, 0, visibleSize.width / 2,
		visibleSize.height);
	//................hud...................
	hudLayer = new	HUDLayer();
	this->addChild(hudLayer, 15);
	//..................arrowkey................
	/*CCMenuItemImage	*arrowleft = CCMenuItemImage::create("l.png",
		"l-1.png", this, menu_selector(HelloWorld::buttonControlleft));
	arrowleft->setPosition(ccp(origin.x + 40,
		origin.y+40));
	CCMenuItemImage	*arrowdown = CCMenuItemImage::create("b.png",
		"b-1.png", this, menu_selector(HelloWorld::buttonControldown));
	arrowdown->setPosition(ccp(origin.x + 110,
		origin.y + 40));
	CCMenuItemImage	*arrowtop = CCMenuItemImage::create("t.png",
		"t-1.png", this, menu_selector(HelloWorld::buttonControltop));
	arrowtop->setPosition(ccp(origin.x + 110,
		origin.y + 110));
	CCMenuItemImage	*arrowright = CCMenuItemImage::create("r.png",
		"r-1.png", this, menu_selector(HelloWorld::buttonControlright));
	arrowright->setPosition(ccp(origin.x + 180,
		origin.y + 40));
	CCMenuItemImage	*gun = CCMenuItemImage::create("firing_gun.png",
		"firing_gun1.png", this, menu_selector(HelloWorld::buttongun));
	gun->setPosition(ccp(visibleSize.width-(gun->getContentSize().width/2 +10),
		gun->getContentSize().height / 2+5));
	CCMenu*	pMenu = CCMenu::create(arrowleft,arrowdown,arrowtop,arrowright,gun,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);*/
	//.................enemy...................
	/*enemy = Enemy::createEnemy();
	this->addChild(enemy);*/
	//....................gravity...........
	gravity = ccp(0, -5);
	jumping = false;
	jumpTimer = 0;	
    return true;
}
void HelloWorld::update(float dt)
{
	if (!gameplayLayer->gameOver)
	{
		//enemy->update();
		gameplayLayer->update();
		//CCLog("update");
		/*CCPoint	p = hero->getPosition();
		hero->setPosition(ccp(p.x + 5, p.y));
		if ((hero->getPositionX() - hero->getContentSize().width / 2)>
		visibleSize.width)
		{
		hero->setPosition(ccp(0.0 - hero->getContentSize().width / 2, hero->getPositionY()));
		}*/
		//.............accelometer............
		/*float maxY = visibleSize.height - hero->getContentSize().height / 2;
		float minY = hero->getContentSize().height / 2;
		float distStep = (distFraction * dt);
		float newY = hero->getPosition().y + distStep;
		newY = MIN(MAX(newY, minY), maxY);
		hero->setPosition(ccp(hero->getPosition().x, newY));*/
		//....................jumpping................
		if (jumping)
		{
			jumpTimer = 10;
			jumping = false;
		}
		if (jumpTimer > 0)
		{
			jumpTimer--;
			CCPoint	p = hero->getPosition();
			CCPoint	mP = ccpAdd(p, ccp(0, 7));
			hero->setPosition(mP);
		}
		else
		{
			jumpTimer = 0;
			CCPoint	p = hero->getPosition();
			CCPoint	pM = ccpAdd(p, gravity);
			hero->setPosition(pM);
		}
		float	maxY = visibleSize.height - hero->getContentSize().height / 2;
		float	minY = hero->getContentSize().height / 2;
		float	newY = hero->getPosition().y;
		newY = MIN(MAX(newY, minY), maxY);
		hero->setPosition(ccp(hero->getPosition().x, newY));
		//................scoring................
		hudLayer->updateScore(gameplayLayer->score);

	}
		else
		{
			gameover();
		}
	
	
}
void HelloWorld::spawnEnemy(float dt)
{
	//CCLog("spawn enemy");
	Enemy*	e = Enemy::createEnemy(gameplayLayer);
	gameplayLayer->addChild(e);
	gameplayLayer->getEnemiesArray()->addObject(e);
	e->shoot(0.016);
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	//.......................defindetouchposition............
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint	location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	//CCLog("location:	xpos:%f	,	ypos:%f", location.x, location.y);
	// .................moveto touch position.................
	/*CCMoveTo	*actionMove = CCMoveTo::create(1, location);
	CCEaseSineInOut	*easeInOut = CCEaseSineInOut::create(actionMove);
	hero->runAction(easeInOut);*/
	//...............multi movement...................
	/*CCPoint	initPos = hero->getPosition();
	CCMoveTo* actionMove = CCMoveTo::create(1, location);
	CCRotateBy* rotateBy = CCRotateBy::create(2.0, 180);
	CCTintTo* tintTo = CCTintTo::create(1.0, 255, 125, 125);
	CCDelayTime* delay = CCDelayTime::create(1.0);
	CCMoveTo* moveToInit = CCMoveTo::create(1, initPos);
	CCTintTo* tintTo1 = CCTintTo::create(1.0, 0, 0, 0);
	CCSequence* sequence = CCSequence::create(actionMove, rotateBy, tintTo,delay, moveToInit,tintTo1, NULL);
	hero->runAction(sequence);*/
	if (!gameplayLayer->gameOver)
	{
		if (rightButton.containsPoint(location))
		{
			fireRocket();
		}
		if (leftButton.containsPoint(location))
		{
			jumping = true;
		}
	}
	
}
void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	CCLog("move");
}
void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	CCLog("ended");
}
void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
	distFraction = visibleSize.height* pAccelerationValue->x;
}
/*
void HelloWorld::buttonControlleft(CCObject *pSender)
{
	CCMoveBy *actionMove = CCMoveBy::create(1.0,cocos2d::CCPoint(-20,0));
	CCEaseSineInOut	*easeInOut = CCEaseSineInOut::create(actionMove);
	hero->runAction(easeInOut);
}
void HelloWorld::buttonControldown(CCObject *pSender)
{
	CCMoveBy *actionMove = CCMoveBy::create(1.0, cocos2d::CCPoint(0, -20));
	CCEaseSineInOut	*easeInOut = CCEaseSineInOut::create(actionMove);
	hero->runAction(easeInOut);
}
void HelloWorld::buttonControlright(CCObject *pSender)
{
	CCMoveBy *actionMove = CCMoveBy::create(1.0, cocos2d::CCPoint(20, 0));
	CCEaseSineInOut	*easeInOut = CCEaseSineInOut::create(actionMove);
	hero->runAction(easeInOut);
}
void HelloWorld::buttonControltop(CCObject *pSender)
{
	float maxY = visibleSize.height - hero->getContentSize().height / 2;
	float minY = hero->getContentSize().height / 2;
	if (hero->getPosition().y + hero->getContentSize().height/2 < maxY)
	{
		CCMoveBy *actionMove = CCMoveBy::create(1.0, cocos2d::CCPoint(0, 20));
		CCEaseSineInOut	*easeInOut = CCEaseSineInOut::create(actionMove);
		hero->runAction(easeInOut);
	}
	
//}*/
//void HelloWorld::buttongun(CCObject *pSender)
//{
//	CCSprite* test = CCSprite::create("bookGame_rocket.png");
//	test->setPosition(ccp(hero->getPosition().x + hero->getContentSize().width / 2, hero->getPosition().y - 7));
//	this->addChild(test);
//	//CCMoveTo *actionMove = CCMoveTo::create(1.0, cocos2d::CCPoint(hero->getPosition().x + visibleSize.width, hero->getPosition().y - 7));
//	//CCEaseSineIn *easeInOut = CCEaseSineIn::create(actionMove);
//	//test->runAction(easeInOut);
//	
//}
//....................fire rocket..........
void	HelloWorld::fireRocket()
{
	CCPoint	p = hero->getPosition();
	p.x = p.x + hero->getContentSize().width / 2;
	p.y = p.y - hero->getContentSize().height	*	0.05;
	Projectile*	rocket = Projectile::createProjectile(p, 2);
	gameplayLayer->addChild(rocket);
	gameplayLayer->getPlayerBulletsArray()->addObject(rocket);
}
void HelloWorld::gameover(){
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(HelloWorld::spawnEnemy));
	if (gameplayLayer->getEnemiesArray()->count() >0)
	{
		for (int i = 0; i< gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy*	en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			en->unscheduleAllSelectors();
			CCLabelBMFont*	gameOverLabel = CCLabelBMFont::create("GAMEOVER",
				"PixelFont.fnt");
			gameOverLabel->setPosition(ccp(visibleSize.width	*	0.5, visibleSize.height
				*	0.6));
			this->addChild(gameOverLabel, 10);
			
		}
	}
	highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bazooka Game High Score");
	if (gameplayLayer->score>highScore)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("bazooka Game High Score", gameplayLayer->score);
		CCUserDefault::sharedUserDefault()->flush();
		CCLabelBMFont*	newHighScoreLabel = CCLabelBMFont::create("NEW	HIGH SCORE",	"PixelFont.fnt");
			newHighScoreLabel->setPosition(ccp(visibleSize.width	*	0.5,
			visibleSize.height	*	0.5));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75);
		CCLabelBMFont*	gOscoreLabel = CCLabelBMFont::create("0",
			"PixelFont.fnt");
		gOscoreLabel->setPosition(ccp(visibleSize.width	*	0.5,
			visibleSize.height	*	0.4));
		this->addChild(gOscoreLabel, 10);
		gOscoreLabel->setScale(0.75);
		char	scoreTxt[100];
		sprintf(scoreTxt, "%d", gameplayLayer->score);
		gOscoreLabel->setString(scoreTxt);
	}
	else
	{
		CCLabelBMFont*	newHighScoreLabel = CCLabelBMFont::create("BETTER LUCK	NEXT	TIME",	"PixelFont.fnt");
			newHighScoreLabel->setPosition(ccp(visibleSize.width	*	0.5,
			visibleSize.height	*	0.5));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75);
	}
}
void HelloWorld::gamePaused()
{
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(HelloWorld::spawnEnemy));
	if (gameplayLayer->getEnemiesArray()->count()>0)
	{
		for (int i = 0; i< gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy*	en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			en->pauseSchedulerAndActions();
		}
	}
}
void	HelloWorld::gameResumed()
{
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	if (gameplayLayer->getEnemiesArray()->count()>0)
	{
		for (int i = 0; i< gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy*	en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			en->resumeSchedulerAndActions();
		}
	}
}



