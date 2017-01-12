#ifndef __wp8Game__GameplayLayer
#define __wp8Game__GameplayLayer

#pragma once
#include "cocos2d.h"
#include "projectile.h"
using namespace cocos2d;
class GameplayLayer :public CCLayer
{
public:
	GameplayLayer(CCSprite* h);
	~GameplayLayer();
	void update();
	CCArray* getEnemiesArray();
	CCArray* enemieasToBeDeleted;
	CCArray* playerBullets;
	CCArray* getPlayerBulletsArray();
	void deleteEnemy(CCObject *target);
	CCArray* getEnemyBulletsArray();
	bool checkBoxCollision(CCSprite* box1, CCSprite *box2);

	
	CCArray* enemyBullets;
	CCArray* enemyBulletsToBeDeleted;
	CCSprite* hero;
	int score;
	bool gameOver;
private:
	CCSize visibleSize;
	CCArray* enemies;
};

#endif //__wp8Game__GameplayLayer
