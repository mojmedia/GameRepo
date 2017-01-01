#include "projectile.h"


Projectile::Projectile()
{
}
Projectile::~Projectile()
{
}

Projectile* Projectile::createProjectile(CCPoint p, int _type)
{
	Projectile* ob = new Projectile();
	if (ob && ob->initProjectile(p, _type))
	{
		ob->autorelease();

		return ob;
	}

	CC_SAFE_DELETE(ob);
	return NULL;
}

bool Projectile::initProjectile(CCPoint p, int _type)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	type = _type;
	if (type == 1)
	{
		this->initWithFile("bookGame_bullet.png");
	}
	else if (type == 2)
	{
		this->initWithFile("bookGame_rocket.png");
	}
	this->setPosition(p);
	return true;
}

void Projectile::update()
{
	if (type == 1)
	{
		CCPoint _mp = this->getPosition();
		CCPoint _MP = ccpAdd(_mp, ccp(-7, 0));
		this->setPosition(_MP);
	}
	else if (type == 2)
	{
		CCPoint _mp = this->getPosition();
		CCPoint _Mp = ccpAdd(_mp, ccp(+7, 0));
		this->setPosition(_Mp);
	}
}