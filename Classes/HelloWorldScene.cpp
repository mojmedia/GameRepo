#include "HelloWorldScene.h"
#include "gameplayLayer.h"

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
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	gravity = ccp(0, -5);
	jumping = false;
	jumpTimer = 0;
	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);

	hudLayer = new HUDLayer();
	this->addChild(hudLayer, 15); //keeping at top most layer

	//--------------------------------------------------Hero-------
	HelloWorld::hero = CCSprite::create("bookGame_tinyBazooka.png");
	HelloWorld::hero->setPosition(ccp(visibleSize.width * 0.25, visibleSize.height * 0.5));
	this->addChild(HelloWorld::hero, 0);
	//کار با انیمیشن به سبک spritesheet میباشد
	CCSpriteBatchNode* spritebatch = CCSpriteBatchNode::create("player_anim.png");
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("player_anim.plist");
	hero->createWithSpriteFrameName("player_idle_1.png");
	hero->addChild(spritebatch);
	//انیمیشن حالت معمولی
	CCArray* animFrames = CCArray::createWithCapacity(4);
	char str1[100] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str1, "player_idle_%d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str1);
		animFrames->addObject(frame);
	}
	CCAnimation* idleanimation = CCAnimation::createWithSpriteFrames(animFrames, 0.25f);
	//hero->runAction(CCRepeatForever::create(CCAnimate::create(idleanimation)));//4-5 خط کد است 
	mIdleAction = CCRepeatForever::create(CCAnimate::create(idleanimation));
	mIdleAction->retain();
	//پرش animation
	animFrames->removeAllObjects();
	char str2[100] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(str2, "player_boost_%d.png", i);
		CCSpriteFrame* frame = cache->spriteFrameByName(str2);
		animFrames->addObject(frame);
	}
	CCAnimation* boostanimation = CCAnimation::createWithSpriteFrames(animFrames, 0.25f);
	hero->runAction(CCRepeatForever::create(CCAnimate::create(boostanimation)));
	mBoostAction = CCRepeatForever::create(CCAnimate::create(boostanimation));
	mBoostAction->retain();
	//---------------------------------------------GameplayLayer------
	gameplayLayer = new GameplayLayer(hero);
	this->addChild(gameplayLayer);

	leftButton = CCRectMake(0, 0, visibleSize.width / 2, visibleSize.height);
	rightButton = CCRectMake(visibleSize.width / 2, 0, visibleSize.width / 2
		, visibleSize.height);
	//--------------------------------------------------btn------

	this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);

	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	return true;
}

void HelloWorld::update(float dt)
{

	//-----------------------------------------------Not Game Over
	if (!gameplayLayer->gameOver)
	{
		scrollingBgLayer->update();
		CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		gameplayLayer->update();

		hudLayer->updateScore(gameplayLayer->score);

		//CCLog("updating");
		CCPoint p = HelloWorld::hero->getPosition();
		//HelloWorld::hero->setPosition(ccp(p.x + 5, p.y));
		if (p.x - hero->getContentSize().width*0.5 > visiblesize.width)
		{
			hero->setPositionX(origin.x);
		}
		//---------------------------------ACCELEROMETER------شتاب سنج-----------------

		//float maxY = visiblesize.height - hero->getContentSize().height / 2;
		//float minY = hero->getContentSize().height / 2;
		//float distStep = (distFraction * dt);//ضرب کار خاصی نمیکنه چون فک کنم مقدارش یکه
		//float newY = hero->getPosition().y + distStep;
		//newY = MIN(MAX(newY, minY), maxY);//خیلی نکته توشه 
		//hero->setPosition(ccp(hero->getPosition().x, newY));

		//------------------------------------JUMPPING-------------------پرش---------------
		if (jumping)
		{
			jumpTimer = 10;
			jumping = false;
		}
		if (jumpTimer > 0 && hero->getPositionY() < visiblesize.height - hero->getContentSize().height / 2)
		{
			mPlayerState = kPlayerStateBoost;
			jumpTimer--;
			CCPoint p = hero->getPosition();
			CCPoint mP = ccpAdd(p, ccp(0, 7));
			hero->setPosition(ccp(hero->getPositionX(), hero->getPositionY() + 7));
		}
		else if (hero->getPositionY() > origin.y + hero->getContentSize().height / 2)
		{
			mPlayerState = kPLayerStateIdle;
			jumpTimer = 0;
			CCPoint p = hero->getPosition();
			CCPoint pM = ccpAdd(p, gravity);
			hero->setPosition(pM);
		}
		this->AnimationStates();
	}
	else
	{
		GameOver();
	}
}

void HelloWorld::spawnEnemy(float dt)
{

	if (!gameplayLayer->gameOver)
	{
		CCLog("spawnEnemy");
		Enemy* e = Enemy::createEnemy(gameplayLayer);
		gameplayLayer->addChild(e);
		gameplayLayer->getEnemiesArray()->addObject(e);
	}
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	if (!gameplayLayer->gameOver)
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		//CCLog("began");
		CCTouch *touch = (CCTouch*)pTouches->anyObject();//گرفتن شیئی که تاچ خورده است
		CCPoint location = touch->getLocationInView();//مکانی از شیء که تاچ خورده 
		location = CCDirector::sharedDirector()->convertToGL(location);//تبدیل سیستم مکان دهی از ویو کوردینیت به جی ال 

		CCPoint initPos = hero->getPosition();
		CCMoveTo* actMove = CCMoveTo::create(0.6, location);
		CCRotateBy* actRotateby = CCRotateBy::create(1.5, 720);

		CCBlink* actTinTo = CCBlink::create(1.0, 5);
		CCDelayTime* actDelayTime = CCDelayTime::create(0.3);
		CCMoveTo* actMoveToInit = CCMoveTo::create(0.7, initPos);
		CCSequence* actSequence = CCSequence::create(actMove, actRotateby, actTinTo,
			actDelayTime, actMoveToInit, NULL);
		//hero->runAction(actSequence);
		if (rightButton.containsPoint(location))
		{
			fireRocket();
		}
		else if (leftButton.containsPoint(location))
		{
			jumping = true;
		}
	}
}

void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	//CCLog("move");

}

void HelloWorld::ccTouchesEnded(CCSet* pTouches, CCEvent* event)
{
	//CCLog("end");
}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();

	distFraction = visiblesize.width * pAccelerationValue->x;
	auto move = CCMoveTo::create(0.5, ccp(hero->getPositionY(), distFraction));
	auto ease = CCEaseOut::create(move, 1.0);
	//hero->runAction(ease);
	//hero->setPositionY(distFraction);
}

//void HelloWorld::buttonControl(CCObject* pSender)
//{
//	CCSprite* test = CCSprite::create("CloseNormal.png");
//	test->setPosition(ccp(hero->getPosition().x + hero->getContentSize().width / 2
//		, hero->getPosition().y));
//	test->setScale(0.5);
//	this->addChild(test);
//}

void HelloWorld::fireRocket()
{
	CCPoint p = hero->getPosition();

	p.x = p.x + hero->getContentSize().width / 2;
	p.y = p.y - hero->getContentSize().height * 0.05;
	Projectile* rocket = Projectile::createProjectile(p, 2);
	gameplayLayer->addChild(rocket);
	gameplayLayer->getPlayerBulletsArray()->addObject(rocket);
}

void HelloWorld::GameOver()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	//--------------------------------
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(HelloWorld::spawnEnemy));
	if (gameplayLayer->getEnemiesArray()->count() > 0)
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			en->pauseSchedulerAndActions();
			//en->cleanup();
		}
	}
	//--------------------------------

	//if (gameplayLayer->getEnemiesArray()->count() > 0)
	//{
	//	for (int i = 0; i < gameplayLayer->getEnemiesArray()->count(); i++)
	//	{
	//		Enemy* en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
	//		en->unscheduleAllSelectors();
	//	}
	//}

	CCLabelBMFont* gameOverLabel = CCLabelBMFont::create("GAMEOVER SHODI", "PixelFont.fnt");
	gameOverLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height* 0.6));
	this->addChild(gameOverLabel, 10);

	int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("bazookaGameHighScore");

	if (gameplayLayer->score > highScore)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("bazookaGameHighScore", gameplayLayer->score);
		CCUserDefault::sharedUserDefault()->flush();
		CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create("NEW HIGH SCORE", "font.fnt");
		newHighScoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.4));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75);
		CCLabelBMFont* gOscoreLabel = CCLabelBMFont::create("0", "font.fnt");
		gOscoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.25));
		this->addChild(gOscoreLabel, 10);
		gOscoreLabel->setScale(0.75);
		char scoreTxt[100];
		sprintf(scoreTxt, "%d", gameplayLayer->score);
		gOscoreLabel->setString(scoreTxt);
	}
	else
	{
		CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create("BETTERLUCK NEXT TIME", "font.fnt");
		newHighScoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75);
	}
}

void HelloWorld::gamePaused()
{
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(HelloWorld::spawnEnemy));
	if (gameplayLayer->getEnemiesArray()->count() > 0)
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			en->pauseSchedulerAndActions();

		}
	}
}

void HelloWorld::gameResumed()
{
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	if (gameplayLayer->getEnemiesArray()->count() > 0)
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			en->resumeSchedulerAndActions();
		}
	}
}

void HelloWorld::idleAnim()
{
	if (mActionState != kActionStateIdle)
	{
		hero->stopAllActions();
		hero->runAction(mIdleAction);
		mActionState = kActionStateIdle;
	}
}

void HelloWorld::boostAnim()
{
	if (mActionState != kActionStateBoost)
	{
		hero->stopAllActions();
		hero->runAction(mBoostAction);
		mActionState = kActionStateBoost;
	}
}

void HelloWorld::AnimationStates()
{
	CCLOG("action state");
	switch (mPlayerState)
	{
	case kPLayerStateIdle:
		this->idleAnim(); break;
	case kPlayerStateBoost:
		this->boostAnim(); break;
	default: break;
	}
}