#ifndef	__wp8Game__MAINMENU_SCENE__
#define	__wp8Game__MAINMENU_SCENE__
#include "cocos2d.h"
#include "ScrollingBgLayer.h"
#include <spine/spine-cocos2dx.h>
using namespace	cocos2d;
class MainMenu : public	cocos2d::CCLayer
{
public:
	virtual	bool init();
	ScrollingBgLayer *scrollingBgLayer;
	void optionsScene(CCObject *pSender);
	void playGame(CCObject *pSender);
	void update(float dt);
	static cocos2d::CCScene *scene();
	CREATE_FUNC(MainMenu);
	void MoveDownFinished(CCNode *sender);
	void MoveUpFinished(CCNode *sender);
	extension::CCSkeletonAnimation *skeletonNode;
};
#endif