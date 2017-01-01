#ifndef __wp8Game__Enemy__
#define __wp8Game__Enemy__

#pragma once
#include "cocos2d.h"
#include "gameplayLayer.h"
#include "projectile.h"

using namespace cocos2d;


class Enemy : public CCSprite
{
public:
	GameplayLayer* gameplayLayer;

	Enemy(void);
	~Enemy(void);
	static Enemy* createEnemy(GameplayLayer* _gameplayLayer);
	bool initEnemy(GameplayLayer* _gameplayLayer);
	void update();
	void shoot(float dt);
};

#endif //__wp8Game__Enemy__