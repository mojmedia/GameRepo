#include "ParticleSpin.h"
ParticleSpin::ParticleSpin()
{
	spinCounter = 0;
}
ParticleSpin::~ParticleSpin()
{}
ParticleSpin* ParticleSpin::create(CCPoint _cp, char *fileName)
{
	ParticleSpin *pc = new ParticleSpin();
	if (pc && pc->initWithFile(fileName))
	{
		pc->setPosition(_cp);
		pc->init();
		pc->autorelease();
		return pc;
	}
	CC_SAFE_DELETE(pc);
	return NULL;
}
 
bool ParticleSpin::init()
{
	gravity = ccp(0, -0.25);
	speed.x = CCRANDOM_MINUS1_1() * 2.0f;
	speed.y = rand() % 3 + 1;
	CCLOG("speed x %f", speed.x);
	return true;
}

void ParticleSpin::update(float dt)
{
	spinCounter += dt * 4;
	CCPoint initpos = this->getPosition();
	CCPoint finalpos;
	finalpos.x = initpos.x + speed.x;
	speed.y += gravity.y;
	finalpos.y = initpos.y + speed.y + gravity.y;
	this->setPosition(finalpos);
	this->setRotation(CC_RADIANS_TO_DEGREES(spinCounter * speed.x));
}