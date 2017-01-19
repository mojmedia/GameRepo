#include "OptionsMenuScene.h"
#include "MainMenuScene.h"
CCScene *OptionsMenu::scene()
{
	CCScene	*scene = CCScene::create();
	OptionsMenu	*layer = OptionsMenu::create();
	scene->addChild(layer);
	return scene;
}
bool OptionsMenu::init()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint	origin = CCDirector::sharedDirector()->getVisibleOrigin();
	scrollingBgLayer = new ScrollingBgLayer(3.0);
	this->addChild(scrollingBgLayer);
	CCLabelBMFont	*nameLabel = CCLabelBMFont::create("Options Menu","PixelFont.fnt");
	nameLabel->setPosition(visibleSize.width / 2, visibleSize.height	*	0.8);
	this->addChild(nameLabel);
	CCMenuItemImage	*presetItem = CCMenuItemImage::create("_bookgame_UI__resume.png","_bookgame_UI__resume.png",this, menu_selector(OptionsMenu::reset));
	presetItem->setPosition(ccp(visibleSize.width * 0.5 - visibleSize.width	* 0.125, visibleSize.height * 0.5));
	CCMenuItemImage	*pmainMenuItem = CCMenuItemImage::create("_bookgame_UI_mainmenu.png","_bookgame_UI_mainmenu.png",this,menu_selector(OptionsMenu::mainMenu));
	pmainMenuItem->setPosition(ccp(visibleSize.width * 0.5 + visibleSize.width * 0.125, visibleSize.height * 0.5));
	CCMenu *pMenu = CCMenu::create(pmainMenuItem, presetItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 10);
	this->scheduleUpdate();
	return true;
}
void OptionsMenu::update(float dt)
{
	scrollingBgLayer->update();
}
void OptionsMenu::mainMenu(CCObject *pSender)
{
	CCScene	*mScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}
void OptionsMenu::reset(CCObject *pSender)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("bazookaGameHighScore", 0);
	CCUserDefault::sharedUserDefault()->flush();
}

