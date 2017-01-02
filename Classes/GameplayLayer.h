#ifndef	__wp8Game__GameplayLayer__
#define	__wp8Game__GameplayLayer__
#include	"cocos2d.h"
using	namespace	cocos2d;
class	GameplayLayer : public	CCLayer
{
public:
	GameplayLayer();
	~GameplayLayer();
	void	update();
	CCArray *getEnemiesArray();
	CCArray *enemyBulletsToBeDeleted;
	CCArray *getEnemyBulletsArray();
	CCArray *getPlayerBulletsArray();
	CCArray *palyerBulletsToBeDeleted;
	
private:	
	CCSize	visibleSize;	
	CCArray*	enemies;//store all the enemy that we create and keep track	of them
	CCArray*	enemiesToBeDeleted;
	CCArray*	enemyBullets;
	CCArray*    playerBullets;
};
#endif	/*	defined(__wp8Game__GameplayLayer__)	*/