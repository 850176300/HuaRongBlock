//
//  WellDoneLayer.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-19.
//
//

#include "WellDoneLayer.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
#include "KKAds.h"
#include "UserDefaultManager.h"
#include "SoundPlayer.h"
#include "SuperGlobal.h"
USING_NS_ST;
WellDoneLayer* WellDoneLayer::create(float star) {
    WellDoneLayer* pRet = new WellDoneLayer();
    if (pRet && pRet->initWithStar(star)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool WellDoneLayer::initWithStar(float star) {
    if (LayerColor::initWithColor(Color4B(0, 0, 0, 150))) {
        setTouchEnabled(true);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        setSwallowsTouches(true);
        starCount = star;
        wellDoneTipbg = Sprite::create("tip_bg.png");
        wellDoneTipbg->setPosition(STVisibleRect::getCenterOfScene());
        addChild(wellDoneTipbg, 1);
        
        Sprite* title = Sprite::create(getLocalString("welldone.png"));
        title->setAnchorPoint(Vec2(0.5, 1.0));
        title->setPosition(Vec2(wellDoneTipbg->getContentSize().width/2.0, wellDoneTipbg->getContentSize().height - 30));
        wellDoneTipbg->addChild(title);
        
        ControlButton* nextBtn = CocosHelper::getButton(getLocalString("next_step.png"), getLocalString("next_step.png"));
        nextBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(WellDoneLayer::onNextButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
        nextBtn->setAnchorPoint(Vec2(0.5, 0));
        nextBtn->setPosition(Vec2(wellDoneTipbg->getContentSize().width/2.0, 30));
        wellDoneTipbg->addChild(nextBtn);
        
        Sprite* star1bg = Sprite::create("star_left_unlight.png");
        Sprite* star2bg = Sprite::create("star_middle_unlight.png");
        Sprite* star3bg = Sprite::create("star_right_unlight.png");
        
        
        star2bg->setPosition(Vec2(wellDoneTipbg->getContentSize().width/2.0, wellDoneTipbg->getContentSize().height/2.0+30));
        star1bg->setPosition(star2bg->getPosition() + Vec2(-140, -50));
        star3bg->setPosition(star2bg->getPosition() + Vec2(140, -50));
        star1bg->setRotation(5);
        star3bg->setRotation(5);
        wellDoneTipbg->addChild(star1bg);
        wellDoneTipbg->addChild(star2bg);
        wellDoneTipbg->addChild(star3bg);
        
        wellDoneTipbg->setScale(0);
        
        star1 = ProgressTimer::create(Sprite::create("star_left_light.png"));
        star1->setType(cocos2d::ProgressTimer::Type::BAR);
        star1->setMidpoint(Vec2(0, 0.5f));
        star1->setBarChangeRate(Vec2(1, 0));
        star1->setPosition(star1bg->getPosition());
        star1->setPercentage(0);
        wellDoneTipbg->addChild(star1);
        
        
        star2 = ProgressTimer::create(Sprite::create("star_middle_light.png"));
        star2->setType(cocos2d::ProgressTimer::Type::BAR);
        star2->setMidpoint(Vec2(0, 0.5f));
        star2->setBarChangeRate(Vec2(1, 0));
        star2->setPosition(star2bg->getPosition());
        star2->setPercentage(0);
        wellDoneTipbg->addChild(star2);
        
        
        star3 = ProgressTimer::create(Sprite::create("start_right_light.png"));
        star3->setType(cocos2d::ProgressTimer::Type::BAR);
        star3->setMidpoint(Vec2(0, 0.5f));
        star3->setBarChangeRate(Vec2(1, 0));
        star3->setPosition(star3bg->getPosition());
        star3->setPercentage(0);
        wellDoneTipbg->addChild(star3);
        
        return true;
    }
    return false;
}

void WellDoneLayer::showInNode(cocos2d::Node *parent) {
    if (!UserDefaultManager::getIsRemoved()) {
        KKAds ads;
        ads.requestInterstitialAds();
    }
    ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2(0.5f, 0.5f));
    setPosition(STVisibleRect::getCenterOfScene());
    parent->addChild(this, 100);
    CallFunc* action1 = CallFunc::create(std::bind(&WellDoneLayer::runAnimation, this));
    wellDoneTipbg->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f), ScaleTo::create(0.1, 1.0f), action1,NULL));
}

void WellDoneLayer::runAnimation(){
    starsRunAction(star1, starCount, 0);
    starsRunAction(star2, starCount - 1, 1.0f);
    starsRunAction(star3, starCount - 2, 1.9f);
}

void WellDoneLayer::starsRunAction(cocos2d::ProgressTimer *star, float percent, float delaydt) {
    if (percent < 0)
        return;
    if (percent - 1 >= 0){
        ProgressFromTo* action = ProgressFromTo::create(0.3f, 0, 1.0*100);
        star->runAction(Sequence::create(DelayTime::create(delaydt),action, DelayTime::create(0.2f),ScaleTo::create(0.2f, 1.1f),ScaleTo::create(0.1f, 1.0f), NULL));
    }else {
        ProgressFromTo* action = ProgressFromTo::create(0.3f, 0, percent*100);
        star->runAction(Sequence::create(DelayTime::create(delaydt),action, DelayTime::create(0.2f),ScaleTo::create(0.2f, 1.1f),ScaleTo::create(0.1f, 1.0f), NULL));
    }
}

void WellDoneLayer::setAbstact(WellDoneLayerAbstact *delegate) {
    pDelegate = 0;
    pDelegate = delegate;
}

void WellDoneLayer::onNextButtonClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    if (pDelegate) {
        pDelegate->onNextBtnClicked();
    }
}

