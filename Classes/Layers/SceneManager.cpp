//
//  SceneManager.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#include "SceneManager.h"
#include "HomeLayer.h"
#include "LevelDetailLayer.h"
#include "PlayGameLayer.h"
#include "ShopLayer.h"
#include "LoadingLayer.h"
#include "ShopLayer_Android.h"
SceneManager::SceneManager(){
    
}

void SceneManager::gotoloading(){
    Scene* pScene = LoadingLayer::scene();
    if (!Director::getInstance()->getRunningScene()){
        Director::getInstance()->runWithScene(pScene);
    }else {
        Director::getInstance()->replaceScene(pScene);
    }
}

void SceneManager::gotoHomeLayer(){
    Scene* pScene = HomeLayer::scene();
    if (!Director::getInstance()->getRunningScene()){
        Director::getInstance()->runWithScene(pScene);
    }else {
        Director::getInstance()->replaceScene(pScene);
    }
}

void SceneManager::gotoLevelLayer(LevelTitle* thetitle){
    Scene* pScene = LevelDetail::scene(thetitle);
    if (!Director::getInstance()->getRunningScene()){
        
        Director::getInstance()->runWithScene(pScene);
    }else {
        TransitionFade* fade = TransitionFade::create(1.0, pScene);
        Director::getInstance()->replaceScene(fade);
    }
}

void SceneManager::gotoPlayGame(LevelDescripe *descripe) {
    Scene* pScene = PlayGameLayer::scene(descripe);
    TransitionFade* fade = TransitionFade::create(1.0, pScene);
    Director::getInstance()->pushScene(fade);
}

void SceneManager::gotoShopLayer(){

    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Scene* pScene = ShopLayer::scene();
    Director::getInstance()->pushScene(pScene);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CCLog("进入积分榜界面======================");
//    KKOfferWallAdapter::showOfferWall();
    Scene* pScene = ShopLayer_Android::scene();
    Director::getInstance()->pushScene(pScene);
#endif
}

void SceneManager::gotoVedioLayer()
{
    Scene* pScene = ShopLayer_Android::scene();
    Director::getInstance()->pushScene(pScene);
}
