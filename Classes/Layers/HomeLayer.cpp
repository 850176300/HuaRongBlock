//
//  HomeLayer.cpp
//  HuaRongBlock
//
//  Created by liuwei on 15/5/31.
//
//

#include "HomeLayer.h"
#include "SuperGlobal.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
#include "TableViewTest.h"
USING_NS_ST;
Scene* HomeLayer::scene(){
    Scene* pScene = Scene::create();
    
    HomeLayer* layer = HomeLayer::create();
    
    pScene->addChild(layer);
    
    return pScene;
}

bool HomeLayer::init(){
    bool isDay = UserDefault::getInstance()->getBoolForKey(DayTime, true);
    string file = "modify/day_bg.png";
    if (isDay == false) {
        file = string("modify/night_bg.png");
    }
    if (GameLayerBase::initWithBgFileName(file.c_str())) {
        
        Sprite* centerTitle = Sprite::create("modify/title.png");
        centerTitle->setAnchorPoint(Vec2(0.5, 1.0));
        centerTitle->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y - 60);
        addChild(centerTitle, 1);
  
//
//        TableViewTest* pLayer = TableViewTest::create();
//        this->addChild(pLayer, 2);
        MenuItemSprite* lightBtn = CocosHelper::menuItemSprite("modify/night.png");
        MenuItemSprite* settingBtn = CocosHelper::menuItemSprite("modify/setting.png");
        MenuItemSprite* vedioBtn = CocosHelper::menuItemSprite("modify/video.png");
        string soundFile = "modify/sound1.png";
        if (!SoundPlayer::getInstance()->isMusicOpen()) {
            soundFile = "modify/sound2.png";
        }
        MenuItemSprite* soundBtn = CocosHelper::menuItemSprite(soundFile.c_str());
        MenuItemSprite* shareBtn = CocosHelper::menuItemSprite("modify/share.png");

        lightBtn->setTag(kLightBtnTag);
        settingBtn->setTag(kSettingBtnTag);
        vedioBtn->setTag(kVedioBtnTag);
        soundBtn->setTag(kSoundBtnTag);
        shareBtn->setTag(kShareBtnTag);
        
        lightBtn->setAnchorPoint(Vec2(0, 0));
        settingBtn->setAnchorPoint(Vec2(1.0, 0));
        vedioBtn->setAnchorPoint(Vec2(0.5, 0));
        soundBtn->setAnchorPoint(Vec2(1.0, 0));
        shareBtn->setAnchorPoint(Vec2(1.0, 0));
        
        lightBtn->setPosition(Vec2(STVisibleRect::getOriginalPoint().x + 15, 60*0.618+STVisibleRect::getOriginalPoint().y));
        settingBtn->setPosition(Vec2(STVisibleRect::getPointOfSceneRightBottom().x - 15, 60*0.618 + STVisibleRect::getOriginalPoint().y));
        vedioBtn->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, lightBtn->getBoundingBox().getMaxY() + 15));
        soundBtn->setPosition(settingBtn->getPosition()+Vec2(15, 0));
        shareBtn->setPosition(settingBtn->getPosition()+Vec2(15, 0));
        
        lightBtn->setCallback(CC_CALLBACK_1(HomeLayer::onClickedMenuItems, this));
        settingBtn->setCallback(CC_CALLBACK_1(HomeLayer::onClickedMenuItems, this));
        vedioBtn->setCallback(CC_CALLBACK_1(HomeLayer::onClickedMenuItems, this));
        
        
        Menu* pBtns = Menu::create(lightBtn, settingBtn, vedioBtn, NULL);
        pBtns->setAnchorPoint(Vec2(0, 0));
        pBtns->setPosition(Vec2(0, 0));
        addChild(pBtns, 2);
        
        float maxHeight = centerTitle->getBoundingBox().getMidY() - vedioBtn->getBoundingBox().getMaxY();
        log("the max height is %.2f", maxHeight);
        Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
        float tableHeight = maxHeight - 100*1.618;
        
        
        return true;
    }
    return false;
}

void HomeLayer::onClickedMenuItems(cocos2d::Ref *pRef) {
    
}


