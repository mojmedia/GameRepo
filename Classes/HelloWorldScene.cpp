#include "HelloWorldScene.h"


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

	//--------------------------------------------------Enemy
	//enemy = Enemy::createEnemy();
	//this->addChild(enemy);

	//--------------------------------------------------BackGround
	CCSprite* bg = CCSprite::create("bookGame_Bg.png");
	bg->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
	this->addChild(bg, -1);

	//--------------------------------------------------Hero
	HelloWorld::hero = CCSprite::create("bookGame_tinyBazooka.png");
	HelloWorld::hero->setPosition(ccp(visibleSize.width * 0.25, visibleSize.height * 0.5));
	//hero->setAnchorPoint(ccp(0.75, 0.75));
	this->addChild(HelloWorld::hero, 0);
	//CCRotateBy* actRotate = CCRotateBy::create(0.75, 270);
	//CCRepeatForever *actRepeatForEver = CCRepeatForever::create(actRotate);
	//hero->runAction(actRepeatForEver);
	//--------------------------------------------------GameplayLayer------
	gameplayLayer = new GameplayLayer();
	this->addChild(gameplayLayer);


	leftButton = CCRectMake(0, 0, visibleSize.width / 2, visibleSize.height);
	rightButton = CCRectMake(visibleSize.width / 2, 0, visibleSize.width / 2
		, visibleSize.height);
	//--------------------------------------------------btn------

//	auto pCloseItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png");
////menu_selector(HelloWorld::buttonControl)
//	pCloseItem->setPosition(ccp(0.125 * visibleSize.width, 0.125 * visibleSize.height));
//
//	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
//	pMenu->setPosition(CCPointZero);
//	this->addChild(pMenu, 1);


	this->setTouchEnabled(true);
	this->setAccelerometerEnabled(true);

	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy), 3.0);
	return true;
}

void HelloWorld::update(float dt)
{


	CCSize visiblesize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	gameplayLayer->update();

	//CCLog("updating");
	CCPoint p = HelloWorld::hero->getPosition();
	//HelloWorld::hero->setPosition(ccp(p.x + 5, p.y));
	if (p.x - hero->getContentSize().width*0.5 > visiblesize.width)
	{
		hero->setPositionX(origin.x);
	}
	//----------------------------------Enemies
	if (gameplayLayer->getEnemiesArray()->count() >= 0)//راه رفتن دشمنان
	{
		for (int i = 0; i < gameplayLayer->getEnemiesArray()->count(); i++)
		{
			Enemy* e = (Enemy*)gameplayLayer->getEnemiesArray()->objectAtIndex(i);
			e->update();
			if (e->getPositionX() + e->getContentSize().width*0.5 < 0)//اگه بیرون رفته از صحنه
			{
				gameplayLayer->enemieasToBeDeleted->addObject(e);
			}
		}
	}
	CCObject* ee = NULL;
	CCARRAY_FOREACH(gameplayLayer->enemieasToBeDeleted, ee)
	{
		Enemy *target = (Enemy*)(ee);
		//gameplayLayer->deleteEnemy(ee);

		gameplayLayer->enemies->removeObject(ee);
		gameplayLayer->enemieasToBeDeleted->removeObject(ee);
		this->removeChild((Enemy*)ee, true);
	}

	//---------------------------------ACCELEROMETER------شتاب سنج-----------------
	float maxY = visiblesize.height - hero->getContentSize().height / 2;
	float minY = hero->getContentSize().height / 2;
	float distStep = (distFraction * dt);//ضرب کار خاصی نمیکنه چون فک کنم مقدارش یکه
	float newY = hero->getPosition().y + distStep;
	newY = MIN(MAX(newY, minY), maxY);//خیلی نکته توشه 
	hero->setPosition(ccp(hero->getPosition().x, newY));

}

void HelloWorld::spawnEnemy(float dt)
{
	CCLog("spawnEnemy");

	Enemy* e = Enemy::createEnemy(gameplayLayer);
	gameplayLayer->addChild(e);
	gameplayLayer->getEnemiesArray()->addObject(e);
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent* event)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//CCLog("began");
	CCTouch *touch = (CCTouch*)pTouches->anyObject();//گرفتن شیئی که تاچ خورده است
	CCPoint location = touch->getLocationInView();//مکانی از شیء که تاچ خورده 
	location = CCDirector::sharedDirector()->convertToGL(location);//تبدیل سیستم مکان دهی از ویو کوردینیت به جی ال 

	//CCPoint initPos = hero->getPosition();
	//CCMoveBy* actMove = CCMoveBy::create(1, location);
	//CCRotateBy* actRotateby = CCRotateBy::create(1.5, 720);

	//CCBlink* actTinTo = CCBlink::create(1.0, 5);
	//CCDelayTime* actDelayTime = CCDelayTime::create(0.3);
	//CCMoveTo* actMoveToInit = CCMoveTo::create(0.7, initPos);
	//CCSequence* actSequence = CCSequence::create(actMove, actRotateby, actTinTo,
	//	actDelayTime, actMoveToInit, NULL);

	//hero->runAction(actSequence);

	if (rightButton.containsPoint(location))
	{
		fireRocket();
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