#include "AppDelegate.h"
#include "STVisibleRect.h"
#include "SceneManager.h"
#include "DBManager.h"
#include "UserDefaultManager.h"
//#include "KKAds.h"
#include "DatabaseHelper.h"
//#include "KKVedioAdsAdapter.h"
USING_NS_ST;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    bool lCreateRes = DatabaseHelper::getInstance()->createDatabase("blockData.sqlite");
    assert(lCreateRes);
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    STVisibleRect::setupVisibleRect(director->getWinSizeInPixels(), Size(640, 960));
    Size realDesignSize = STVisibleRect::getRealDesignSize();
    director->getOpenGLView()->setDesignResolutionSize(realDesignSize.width, realDesignSize.height, ResolutionPolicy::SHOW_ALL);
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    UserDefaultManager::setDefault();

    DBManager::getInstance()->preloadTypes();
    // create a scene. it's an autorelease object
      SceneManager::getInstance()->gotoPlayGame(DBManager::getInstance()->getQuestionAtlIndex(1));
    if ( UserDefaultManager::getIsRemoved() == false ) {
        //showad
    }
    
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    KKOfferWallAdapter::setOfferWallDelegate(this);
//#endif
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    if ( !UserDefaultManager::getIsRemoved() ) {
//        KKAds* ad = new KKAds();
//        ad->requestInterstitialAds();
//        delete ad;
    }
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    
//    KKOfferWallAdapter::spendPoint();
//#endif
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

//void AppDelegate::spendFailed(int point) {
//    
//}
//
//void AppDelegate::spendSucceed(int point) {
//    log("off wall suceed=======spendSucceed====%d",point);
//    UserDefaultManager::addDiamond(point);
//}


void AppDelegate::onVedioAdsRewarded(int coint) {
    log("AppDelegate:;onVideoIntertitialClose");
//    __String* pRef = __String::create(isComplete == true ? "yes":"no");
    __String* pRef = __String::createWithFormat("%d",coint);
    NotificationCenter::getInstance()->postNotification("onVideoIntertitialClose", pRef);
}

void AppDelegate::onVedioAdsLoadFailed(const char *error){
    log("AppDelegate:;onVideoIntertitialLoadFailed");
    NotificationCenter::getInstance()->postNotification("onVideoIntertitialLoadFailed");
}