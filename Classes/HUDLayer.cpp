#include "HUDLayer.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

HUDLayer::HUDLayer()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//moved the score label to the center
	scoreLabel = CCLabelBMFont::create("Score: 0", "font.fnt");
	scoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.9));
	this->addChild(scoreLabel, 10);
	scoreLabel->setScale(0.5);

	CCMenuItemImage*pauseItem = CCMenuItemImage::create("_bookgame_UI__pause.png", "_bookgame_UI__pause.png",
		this, menu_selector(HUDLayer::pauseGame));
	pauseItem->setPosition(ccp(visibleSize.width - pauseItem->getContentSize().width / 2,
		visibleSize.height - pauseItem->getContentSize().height / 2));
	pauseMenu = CCMenu::create(pauseItem, NULL);
	pauseMenu->setPosition(CCPointZero);
	this->addChild(pauseMenu);
}

void HUDLayer::pauseGame(CCObject* pSender)
{
	//audio-------------
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	//-------------------
	HelloWorld* helloWorld = (HelloWorld*)this->getParent();
	if (!helloWorld->gameplayLayer->gameOver)
	{
		pauseMenu->setTouchEnabled(false);
		CCMenuItemImage* resumeItem =
			CCMenuItemImage::create("_bookgame_UI__resume.png",
			"_bookgame_UI__resume.png", this,
			menu_selector(HUDLayer::resumeGame));
		resumeItem->setPosition(ccp(visibleSize.width * 0.5,
			visibleSize.height* 0.5));
		resumeMenu = CCMenu::create(resumeItem, NULL);
		resumeMenu->setPosition(CCPointZero);
		this->addChild(resumeMenu);
		helloWorld->gamePaused();
	}
}

void HUDLayer::resumeGame(CCObject* pSender)
{
	//audio
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//--------------

	pauseMenu->setTouchEnabled(true);
	this->removeChild(resumeMenu);
	HelloWorld* helloWorld = (HelloWorld*)this->getParent();
	helloWorld->gameResumed();
}

HUDLayer::~HUDLayer(void)
{
}

void HUDLayer::updateScore(int score)
{
	char scoreTxt[100];
	sprintf(scoreTxt, "Score: %d", score);
	scoreLabel->setString(scoreTxt);
}