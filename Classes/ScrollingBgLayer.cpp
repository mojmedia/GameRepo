#include "ScrollingBgLayer.h"
ScrollingBgLayer::ScrollingBgLayer(float speed)
{
	CCSize	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* bg = CCSprite::create("bookGame_BG.png");
	bg->setPosition(ccp(visibleSize.width* 0.5, visibleSize.height	* 0.5));
	this->addChild(bg, -1);
	hills = ScrollingBg::create("bookGame_hills.png", speed	* 0.3, 142);
	this->addChild(hills);
	treesNbush = ScrollingBg::create("bookGame_treesNbush.png", speed *0.5, 136);
	this->addChild(treesNbush);
	ground = ScrollingBg::create("bookGame_ground.png", speed * 0.8, 0);
	this->addChild(ground);
	grass = ScrollingBg::create("bookGame_grass.png", speed, 0);
	this->addChild(grass);
}
ScrollingBgLayer::~ScrollingBgLayer()
{
}
void ScrollingBgLayer::update()
{
	hills->update();
	treesNbush->update();
	ground->update();
	grass->update();
}