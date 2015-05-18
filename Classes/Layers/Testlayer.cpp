//
//  Testlayer.cpp
//  HuaRongBlock
//
//  Created by liuwei on 15-2-5.
//
//

#include "Testlayer.h"
#include "UserDefaultManager.h"
#include "SuperGlobal.h"
#include "DBManager.h"
#include "GameTipLayer.h"
#include "ProductSolution.h"
#include "TipLayer.h"

Scene* TestLayer::scene(){
    Scene* pScene = Scene::create();
    
    TestLayer* _layer = TestLayer::create();
    
    pScene->addChild(_layer);
    
    return pScene;
}


bool TestLayer::init(){
    if (GameLayerBase::initWithBgFileName("gamebg.png", false)) {
        Button* pBtn = Button::create("star1.png");
        pBtn->setPosition(STVisibleRect::getCenterOfScene());
        pBtn->addTouchEventListener(CC_CALLBACK_2(TestLayer::btnCLick, this));
        addChild(pBtn,10);
        
        contentLabel = Label::createWithSystemFont("fsa", "fdsa", 40);
        resultLabel = Label::createWithSystemFont("fsa", "fdsa", 40);
        contentLabel->setPosition(Vec2(STVisibleRect::getCenterOfScene().x,  STVisibleRect::getCenterOfScene().y + 100));
        resultLabel->setPosition(Vec2(STVisibleRect::getCenterOfScene().x,  STVisibleRect::getCenterOfScene().y + 200));
        addChild(contentLabel, 2);
        addChild(resultLabel, 3);
        
        return true;
    }
    return false;
}

void TestLayer::updateLabel(float) {
    if (i < 465) {
        LevelDescripe* _dd = DBManager::getInstance()->getQuestionAtIndex(1+i++);
        string solution = ProductSolutioin::getInstance()->createSolution(_dd->getLevelString());
        
        contentLabel->setString(_dd->getTypeName() +",第"+convertIntToString(i+1)+"关:"+_dd->getName());
        log("solution is %s", solution.c_str());
        if (solution.find("no solution") == string::npos) {
            //                TipLayer* tipLayer = TipLayer::createWithStrings(_dd->getLevelString(), solution);
            //                tipLayer->showInNode(this);
            
            
            resultLabel->setString("查找出结果");
        }else {
            resultLabel->setString("没有找到结果");
            ofstream myfile;
            myfile.open ("/Users/liuwei/Desktop/result.txt");
            myfile<<contentLabel->getString().c_str();
            myfile.close();
            unschedule(schedule_selector(TestLayer::updateLabel));
        }
    }else {
        unschedule(schedule_selector(TestLayer::updateLabel));
    }
}

void TestLayer::btnCLick(cocos2d::Ref *_ref, Widget::TouchEventType type) {
    if (type == Widget::TouchEventType::ENDED) {
        this->schedule(schedule_selector(TestLayer::updateLabel), 0.5);
        
    }
}
