#ifndef __wp8Game__OPTIONSMENU_SCENE__
#define __wp8Game__OPTIONSMENU_SCENE__
#include "cocos2d.h"
#include "ScrollingBgLayer.h"
using namespace cocos2d;
class OptionsMenu : public cocos2d::CCLayer
{
public:
	virtual bool init();
	ScrollingBgLayer* scrollingBgLayer;
	static cocos2d::CCScene* scene();
	void update(float dt);
	void reset(CCObject* pSender);
	void mainMenu(CCObject* pSender);
	//------sound------
	CCMenuItemImage* soundOnItem;
	CCMenuItemImage* soundOffItem;
	void SoundOnOff(CCObject* sender);

	CREATE_FUNC(OptionsMenu);
};
#endif