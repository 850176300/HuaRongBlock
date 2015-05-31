//
//  LoadingLayer.cpp
//  HuaRongBlock
//
//  Created by liuwei on 14-12-16.
//
//

#include "LoadingLayer.h"
#include "STVisibleRect.h"
#include "SceneManager.h"
USING_NS_ST;
Scene* LoadingLayer::scene(){
    Scene* scene = Scene::create();
    
    LoadingLayer* layer = LoadingLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool LoadingLayer::init(){
    if (LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        loading = Sprite::create("loading/zhuomuliao1.png");
        loading->setPosition(STVisibleRect::getCenterOfScene());
        addChild(loading);
        return true;
    }
    return false;
}

void LoadingLayer::onEnterTransitionDidFinish(){
//    KKAds ads;
//    ads.setAdsVisibility(false);
    LayerColor::onEnterTransitionDidFinish();
    runAnimation();
    scheduleOnce(schedule_selector(LoadingLayer::updateToMainScene), 2.5f);
}

void LoadingLayer::runAnimation(){
    Animation* pAnimation = Animation::create();
    
    for (int i = 0; i < 4; ++i) {
        char filename[128];
        sprintf(filename, "loading/zhuomuliao%d.png", i+1);
        pAnimation->addSpriteFrameWithFile(filename);
    }
    pAnimation->setLoops(-1);
    pAnimation->setDelayPerUnit(0.1f);
    
    Animate* animate = Animate::create(pAnimation);
    loading->runAction(animate);
}

void LoadingLayer::updateToMainScene(float) {
    SceneManager::getInstance()->gotoHomeLayer();
}

