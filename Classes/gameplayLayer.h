#ifndef __wp8Game__GameplayLayer
#define __wp8Game__GameplayLayer

#pragma once
#include "cocos2d.h"
#include "projectile.h"
using namespace cocos2d;
class GameplayLayer :public CCLayer
{
public:
	GameplayLayer();
	~GameplayLayer();
	void update();
	CCArray* getEnemiesArray();
	CCArray* enemieasToBeDeleted;
	CCArray* playerBullets;
	CCArray* getPlayerBulletsArray();
	void deleteEnemy(CCObject *target);
	CCArray* getEnemyBulletsArray();

	CCArray* enemies;
	CCArray* enemyBullets;
	CCArray* enemyBulletsToBeDeleted;

private:
	CCSize visibleSize;
};

#endif //__wp8Game__GameplayLayer
