#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pEGLView->setFrameSize(800, 480);
	pDirector->setOpenGLView(pEGLView);

	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	//اضافه کردن صدا
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("bgMusic.wav");//بارگزاری
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bgMusic.wav", true);//پخش صدا 
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("enemyKill.wav");//بارگزاری
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("fireRocket.wav");//بارگزاری
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("gunshot.wav");//بارگزاری
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("playerKill.wav");//بارگزاری
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pop.wav");//بارگزاری
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("rocketExplode.wav");//بارگزاری

	// create a scene. it's an autorelease object
	CCScene *pScene = MainMenu::scene();

	// run
	pDirector->runWithScene(pScene);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->stopAnimation();
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	//-----------audio pause AND resume
	if (isPaused == false)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine() ->pauseBackgroundMusic();
	}
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->startAnimation();
	bool isPaused = CCUserDefault::sharedUserDefault()->getBoolForKey("tinyBazooka_kSoundPausedKey");
	if (isPaused == false)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}
