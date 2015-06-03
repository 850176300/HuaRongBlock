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
        centerTitle->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y - 30);
        addChild(centerTitle, 1);
  

        TableViewTest* pLayer = TableViewTest::create();
        this->addChild(pLayer, 2);
        

        return true;
    }
    return false;
}


