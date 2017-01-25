#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
CCScene* OptionsMenu::scene()
{
	CCScene *scene = CCScene::create();
	OptionsMenu *layer = OptionsMenu::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool OptionsMenu::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//-----------sound-----
	//sound onoff items
	soundOnItem = CCMenuItemImage::create("_bookgame_UI_soundON.png", "_bookgame_UI_soundON.png", this, NULL);
	soundOffItem = CCMenuItemImage::create("_bookgame_UI_soundOFF.png", "_bookgame_UI_soundOFF.png", this, NULL);
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	CCMenuItemToggle* soundToggleItem;
	if (isPaused == false)
	{
		soundToggleItem = CCMenuItemToggle::createWithTarget(this,
			menu_selector(OptionsMenu::SoundOnOff), soundOnItem, soundOffItem, NULL);//نحوه ی افزودن دکمه های تاگلی-دو حالته
	}
	else
	{
		soundToggleItem = CCMenuItemToggle::createWithTarget(this,
			menu_selector(OptionsMenu::SoundOnOff), soundOffItem, soundOnItem, NULL);
	}
	soundToggleItem->setPosition(ccp(visibleSize.width* 0.5, visibleSize.height * 0.5));

	//---------------------

	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);
	CCLabelBMFont *nameLabel = CCLabelBMFont::create("Bazooka Setting", "PixelFont.fnt");//پیغام
	nameLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.8);
	this->addChild(nameLabel);
	CCMenuItemImage *presetItem = CCMenuItemImage::create("_bookgame_UI__resume.png",
		"_bookgame_UI__resume.png", this, menu_selector(OptionsMenu::reset));//دکمه ی ریست 
	presetItem->setPosition(ccp(visibleSize.width * 0.5 - visibleSize.width *
		0.125, visibleSize.height * 0.5));
	CCMenuItemImage *pmainMenuItem = CCMenuItemImage::create("_bookgame_UI_mainmenu.png",
		"_bookgame_UI_mainmenu.png", this, menu_selector(OptionsMenu::mainMenu));//دکمه خانه
	pmainMenuItem->setPosition(ccp(visibleSize.width * 0.5 + visibleSize.width * 0.125, visibleSize.height * 0.5));
	CCMenu* pMenu = CCMenu::create(pmainMenuItem, presetItem, soundToggleItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 10);
	this->scheduleUpdate();
	return true;
}

void OptionsMenu::update(float dt)
{
	scrollingBgLayer->update();
}

void OptionsMenu::mainMenu(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	CCScene *mScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}

void OptionsMenu::reset(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	CCUserDefault::sharedUserDefault()->setIntegerForKey("bazookaGameHighScore", 0);//ریست کردن امتیاز کاربر
	CCUserDefault::sharedUserDefault()->flush();
}

void OptionsMenu::SoundOnOff(CCObject* sender)
{
	CCMenuItemToggle *toggleItem = (CCMenuItemToggle *)sender;
	if (toggleItem->selectedItem() == soundOffItem)
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("tinyBazooka_kSoundPausedKey", true);
		CCUserDefault::sharedUserDefault()->flush();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
	}
	else if (toggleItem->selectedItem() == soundOnItem)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");
		CCUserDefault::sharedUserDefault()->setBoolForKey("tinyBazooka_kSoundPausedKey", false);
		CCUserDefault::sharedUserDefault()->flush();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}