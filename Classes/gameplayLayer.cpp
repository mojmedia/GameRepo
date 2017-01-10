#include "gameplayLayer.h"


GameplayLayer::GameplayLayer()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	enemies = new CCArray();
	enemieasToBeDeleted = new CCArray();
	enemyBullets = new CCArray();
	enemyBulletsToBeDeleted = new CCArray();
	playerBullets = new CCArray();
}

GameplayLayer::~GameplayLayer()
{}

CCArray* GameplayLayer::getEnemiesArray()
{
	return enemies;
}

void GameplayLayer::update()
{
	//-----------------------enemy---------------------
	if (enemies->count() > 0)
	{
		for (int i = 0; i < enemies->count(); i++)
		{
			Projectile* pr = (Projectile*)enemies->objectAtIndex(i);
			pr->update();
			if (pr->getPositionX() < 0)
			{
				enemieasToBeDeleted->addObject(pr);
			}
		}
	}
	CCObject* eb = NULL;
	CCARRAY_FOREACH(enemieasToBeDeleted, eb)
	{
		Projectile *target = (Projectile*)(eb);
		enemies->removeObject(target);
		enemieasToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}
	//-----------------------enemyBullet---------------------
	if (enemyBullets != NULL && enemyBullets->count() > 0)
	{
		for (int i = 0; i < enemyBullets->count(); i++)
		{
			Projectile* pr = (Projectile*)enemyBullets->objectAtIndex(i);
			pr->update();
			if (pr->getPositionX() <= 0)
			{
				enemyBulletsToBeDeleted->addObject(pr);
			}
		}
	}
	CCObject* eeb = NULL;
	CCARRAY_FOREACH(enemyBulletsToBeDeleted, eeb)
	{
		Projectile *target = (Projectile*)(eeb);
		enemyBullets->removeObject(target);
		enemyBulletsToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}
	//-----------------------PlayerBullet---------------------
	if (playerBullets != NULL && playerBullets->count() > 0)
	{
		for (int i = 0; i < playerBullets->count(); i++)
		{
			Projectile* p = (Projectile*)playerBullets->objectAtIndex(i);
			p->update();
			if (p->getPositionX() >= visibleSize.width)
			{
				this->removeChild(p);
				playerBullets->removeObject(p);
			}
		}
	}
}

void GameplayLayer::deleteEnemy(CCObject *target)
{
	enemieasToBeDeleted->removeObject(target);
	enemies->removeObject(target);
}

CCArray* GameplayLayer::getEnemyBulletsArray()
{
	return enemyBullets;
}

CCArray* GameplayLayer::getPlayerBulletsArray()
{
	return playerBullets;
}

bool GameplayLayer::checkBoxCollision(CCSprite* box1, CCSprite *box2)
{
	CCRect box1Rect = box1->boundingBox();
	CCRect box2Rect = box2->boundingBox();
	if (box1Rect.intersectsRect(box2Rect))
	{
		return true;
	}
	else
	{
		return false;
	}
}