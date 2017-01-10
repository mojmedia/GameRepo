#include "gameplayLayer.h"
#include "Enemy.h"

GameplayLayer::GameplayLayer(CCSprite* hero)
{
	this->hero = hero;
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	enemies = new CCArray();
	enemieasToBeDeleted = new CCArray();
	enemyBullets = new CCArray();
	enemyBulletsToBeDeleted = new CCArray();
	playerBullets = new CCArray();
	score = 0;
	gameOver = false;

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
			Enemy* e = (Enemy*)enemies->objectAtIndex(i);
			e->update();
			if (e->getPositionX() < 0)
			{
				gameOver = true;
				enemieasToBeDeleted->addObject(e);
			}
		}
	}
	CCObject* eb = NULL;
	CCARRAY_FOREACH(enemieasToBeDeleted, eb)
	{
		Enemy *target = (Enemy*)(eb);
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
	//-----------------------player rocket and enemies collision---------------
	if (playerBullets->count() >= 0)
	{
		for (int i = 0; i < playerBullets->count(); i++)
		{
			Projectile* p = (Projectile*)playerBullets->objectAtIndex(i);
			if (enemies->count() > 0)
			{
				for (int j = 0; j < enemies->count(); j++)
				{
					Enemy* en = (Enemy*)enemies->objectAtIndex(j);
					if (checkBoxCollision(p, en))
					{
						score++;
						this->removeChild(p);
						playerBullets->removeObject(p);
						enemyBulletsToBeDeleted->addObject(en);
						this->removeChild(en);
						return;
					}
				}
			}
		}
	}

	//----------------------------------enemy bullets and player collision--------------
	if (enemyBullets->count() > 0)
	{
		for (int i = 0; i < enemyBullets->count(); i++)
		{
			Projectile* pr = (Projectile*)enemyBullets->objectAtIndex(i);
			if (checkBoxCollision(pr, hero))
			{
				enemyBulletsToBeDeleted->addObject(pr);
				gameOver = true;
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