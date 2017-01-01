#ifndef __wp8Game__Prijectile__
#define __wp8Game__Prijectile__

#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Projectile : public CCSprite
{
public:
	Projectile(void);
	~Projectile(void);

	int type;
	static Projectile* createProjectile(CCPoint p , int _type);
	bool initProjectile(CCPoint p , int _type);
	void update();

};

#endif //__wp8Game__Prijectile__