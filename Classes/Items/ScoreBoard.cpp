//
//  ScoreBoard.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#include "ScoreBoard.h"
#include "SuperGlobal.h"
ScoreBoard* ScoreBoard::create(){
    ScoreBoard* pRet = new ScoreBoard();
    if (pRet && pRet->initWithFile(getLocalString("navigation_center.png"))){
        pRet->initItems();
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_RELEASE(pRet);
        return nullptr;
    }
}

void ScoreBoard::initItems(){
    currentStep = 0;
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    _scroeLabel = Label::createWithTTF(config2, "0");
    _scroeLabel->setPosition(Vec2(getContentSize().width * 0.25, getContentSize().height * 0.3));
    addChild(_scroeLabel);
    
    _stepLabel = Label::createWithTTF(config2, "0");
    _stepLabel->setPosition(Vec2(getContentSize().width * 0.75, getContentSize().height * 0.3));
    addChild(_stepLabel);
}

void ScoreBoard::updateStepCount(int stepCount) {
    if (stepCount == 3) {
        currentStep = 0;
        CallFunc* action = CallFunc::create(std::bind(&Label::setString, _stepLabel, "0"));
        _stepLabel->runAction(Sequence::create(ScaleTo::create(0.2, 1.1f), ScaleTo::create(0.1f, 1.0f), action, NULL));
    }else {
        currentStep += stepCount;
        stringstream ss;
        ss<<currentStep;
        CallFunc* action = CallFunc::create(std::bind(&Label::setString, _stepLabel, ss.str()));
        _stepLabel->runAction(Sequence::create(ScaleTo::create(0.2, 1.1f), ScaleTo::create(0.1f, 1.0f), action, NULL));
    }
}

int ScoreBoard::getstepCounts(){
//    return std::atoi(_stepLabel->getString().c_str());
    return currentStep;
}


void ScoreBoard::setBestStep(int step) {
    __String* scroeString = __String::createWithFormat("%d", step);
    _scroeLabel->setString(scroeString->getCString());
}