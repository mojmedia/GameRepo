#include	"GameplayLayer.h"
#include	"Enemy.h"
GameplayLayer::GameplayLayer(CCSprite *_hero)
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	enemies = new	CCArray();
	enemyBullets = new	CCArray();
	enemyBulletsToBeDeleted = new	CCArray();
	enemiesToBeDeleted = new	CCArray();
	palyerBulletsToBeDeleted = new CCArray();
	playerBullets = new	CCArray();
	hero = _hero;
}


	

GameplayLayer::~GameplayLayer()
{
	
}
void	GameplayLayer::update()
{
	if (enemies->count() > 0)
	{
		for (int i = 0; i < enemies->count(); i++)
		{
			Enemy*	e = (Enemy*)enemies->objectAtIndex(i);
			e->update();
			if (e->getPositionX() + e->getContentSize().width / 2 < 0)
			{
				/*enemies->removeObject(e);
				this->removeChild(e, true);*/
				enemiesToBeDeleted->addObject(e);
				
			}
		}
	}
	CCObject*	ee = NULL;
	CCARRAY_FOREACH(enemiesToBeDeleted, ee)
	{
		Enemy* target = (Enemy*)(ee);
		enemies->removeObject(target);
		enemiesToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}
	//enemy	bullets
	if (enemyBullets->count()>	0)
	{
		for (int i = 0; i < enemyBullets->count(); i++)
		{
			Projectile*	pr = (Projectile*)enemyBullets->objectAtIndex(i);
			pr->update();
			if (pr->getPositionX() <= 0)
			{
				enemyBulletsToBeDeleted->addObject(pr);
			}
		}
	}
	CCObject*	eb = NULL;
	CCARRAY_FOREACH(enemyBulletsToBeDeleted, eb)
	{
		Projectile	*target = (Projectile*)(eb);
		enemyBullets->removeObject(target);
		enemyBulletsToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}
	//enemy	bullets	and	player
	if (enemyBullets->count()	>	0)
	{
		for (int i = 0; i < enemyBullets->count(); i++)
		{
			Projectile*	pr = (Projectile*)enemyBullets->objectAtIndex(i);
			if (checkBoxCollision(pr, hero))
			{
				enemyBulletsToBeDeleted->addObject(pr);
				return;
			}
		}
	}
	//player	bullets
	if (playerBullets->count() > 0)
	{
		for (int i = 0; i<playerBullets->count(); i++)
		{
			Projectile*	p = (Projectile*)playerBullets->objectAtIndex(i);
			p->update();
			if (p->getPositionX() >= visibleSize.width)
			{
				palyerBulletsToBeDeleted->addObject(p);

			}
		}
	}
	CCObject*	ep = NULL;
	CCARRAY_FOREACH(palyerBulletsToBeDeleted, ep)
	{
		Projectile	*target = (Projectile*)(ep);
		playerBullets->removeObject(target);
		palyerBulletsToBeDeleted->removeObject(target);
		this->removeChild(target, true);
	}
	//player	rocket	and	enemies	collision
	if (playerBullets->count() >= 0)
	{
		for (int i = 0; i<playerBullets->count(); i++)
		{
			Projectile*	p = (Projectile*)playerBullets->objectAtIndex(i);
			if (enemies->count()	>	0)
			{
				for (int j = 0; j< enemies->count(); j++)
				{
					Enemy*	en = (Enemy*)enemies->objectAtIndex(j);
					if (checkBoxCollision(p, en))
					{
						this->removeChild(p);
						playerBullets->removeObject(p);
						enemiesToBeDeleted->addObject(en);
						return;
					}
				}
			}
		}
	}
	

	
}
CCArray* GameplayLayer::getEnemiesArray()
{
	return	enemies;
}
CCArray*	GameplayLayer::getEnemyBulletsArray()
{
	return	enemyBullets;
}
CCArray*	GameplayLayer::getPlayerBulletsArray()
{
	return	playerBullets;
}
bool	GameplayLayer::checkBoxCollision(CCSprite*	box1, CCSprite	*box2)
{
	CCRect	box1Rect = box1->boundingBox();
	CCRect	box2Rect = box2->boundingBox();
	if (box1Rect.intersectsRect(box2Rect))
	{
		return	true;
	}
	else
	{
		return	false;
	}
}