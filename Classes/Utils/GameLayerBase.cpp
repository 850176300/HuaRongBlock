//
//  GameLayerBase.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#include "GameLayerBase.h"
#include "CocosHelper.h"
//#include "DeviceTool.h"
#include "KKAds.h"
#include "UserDefaultManager.h"



GameLayerBase::GameLayerBase()
{
    
}

GameLayerBase::~GameLayerBase(){
    log("the class %s consturctor========", __FUNCTION__);
    
}

bool GameLayerBase::init(){
    if (CCLayer::init()) {
        
        return true;
    }
    return false;
}

bool GameLayerBase::initWithBgFileName(const char *apFileName, bool showAds /*= true*/)
{
    if(LayerColor::init())
    {
        //场景背景
        m_pBg = Sprite::create(apFileName);
        m_pBg->setPosition(STVisibleRect::getCenterOfScene());
        m_pBg->setScale(1/Director::getInstance()->getOpenGLView()->getScaleX()*STVisibleRect::getRealDesignScale());
        this->addChild(m_pBg, 0);
        
//        Sprite* bg2 = Sprite::create(apFileName);
//        bg2->setPosition(STVisibleRect::getCenterOfScene());
//        bg2->setScale(1/Director::getInstance()->getOpenGLView()->getScaleX()*STVisibleRect::getRealDesignScale());
//        this->addChild(bg2, 0);
        //        if (showAds) {
        //            AdvertiseAdapter::showBannerAd();
        //        }else{
        //            AdvertiseAdapter::hideBannerAd();
        //        }
        
        isShowAds = showAds;
        if (showAds) {
            log("show the banner %s", __FUNCTION__);
        }else {
            log("donnot need show banner %s", __FUNCTION__);
        }
//        auto listenerkeyPad = EventListenerKeyboard::create();
//        listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameLayerBase::onKeyReleased, this);
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
        //        this->setKeypadEnabled(true);
       
        return true;
    }
    return false;
}

void GameLayerBase::setShowAds(bool isShow) {
    isShowAds = isShow;
}
void GameLayerBase::onEnter(){
    KeyEventDispatcher::getInstance()->addEventDelegate(this);
    Layer::onEnter();
    if (isShowAds && !UserDefaultManager::getIsRemoved()) {
        KKAds ads;
        ads.setAdsVisibility(true);
    }else{
        KKAds ads;
        ads.setAdsVisibility(false);
    }

}

void GameLayerBase::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    scheduleOnce(schedule_selector(GameLayerBase::removeunuseCache), 0);
}

void GameLayerBase::removeunuseCache(float) {
     Director::getInstance()->getTextureCache()->removeUnusedTextures();
  
}

void GameLayerBase::setADVisible(bool visible) {

}

void GameLayerBase::onExit(){
    KeyEventDispatcher::getInstance()->removeDelegate(this);
    CCLayer::onExit();
}

void GameLayerBase::onBackKeyClicked() {
    Director::getInstance()->popScene();
}
