//
//  TipLayer.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-19.
//
//

#include "TipLayer.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
USING_NS_ST;

TipLayer* TipLayer::createWithStrings(std::string originString, std::string tipString) {
    TipLayer* pRet = new TipLayer();
    if (pRet && pRet->initWithStrings(originString, tipString)){
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool TipLayer::initWithStrings(std::string originString, std::string tipString) {
    if (LayerColor::initWithColor(Color4B(0, 0, 0, 220))) {
        performCount = 0;
        gridView = Sprite::create("game_center_bg.png");
        gridView->setAnchorPoint(Vec2(0, 0));
        gridView->setPosition(Vec2(STVisibleRect::getOriginalPoint().x+ (STVisibleRect::getGlvisibleSize().width - GridWidth - ButtonSize) / 3.0, STVisibleRect::getOriginalPoint().y));
        addChild(gridView);
        
        
        ControlButton* closeBtn = CocosHelper::getButton("close.png", "close.png");
        closeBtn->setAnchorPoint(Vec2(1.0, 0.5));
        closeBtn->setPosition(Vec2(STVisibleRect::getPointOfSceneRightBottom().x - 50, gridView->getBoundingBox().getMaxY() + 0.5*(STVisibleRect::getPointOfSceneRightUp().y - gridView->getBoundingBox().getMaxY())));
        
        closeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(TipLayer::onButtonsClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
        addChild(closeBtn);
        
        
        replay = CocosHelper::getButton("replay.png", "replay.png");
        replay->setAnchorPoint(Vec2(1.0, 0.5));
        replay->setPosition(closeBtn->getPosition() + Vec2(-20-closeBtn->getContentSize().width, 0));
        replay->addTargetWithActionForControlEvents(this, cccontrol_selector(TipLayer::onButtonsClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
        addChild(replay);
        
        
        closeBtn->setUserObject(__String::create("close"));
        replay->setUserObject(__String::create("replay"));
        replay->setOpacity(100);
        replay->setEnabled(false);
        HImages = {"g_h.png","h_h.png","m_h.png","z_h.png","zy_h.png"};
        VImages = {"g_v.png","h_v.png","m_v.png","z_v.png","zy_v.png"};
        this->theoriginString = string(originString);
        putallitems(originString);
        allRecorders = SplitString(tipString);
        TTFConfig config2(FONTNAME,50,GlyphCollection::DYNAMIC,nullptr,true);
        tipLabel = Label::createWithTTF(config2, string(getLocalString("提示："))+ "0/"+convertIntToString(allRecorders.size()));
        tipLabel->setAnchorPoint(Vec2(0, 0.5f));
        tipLabel->setPosition(Vec2(STVisibleRect::getOriginalPoint().x+50, gridView->getBoundingBox().getMaxY() + 0.5*(STVisibleRect::getPointOfSceneRightUp().y - gridView->getBoundingBox().getMaxY())));
        addChild(tipLabel, 10);
        return true;
    }
    return false;
}

void TipLayer::putallitems(string currentString) {
    int vCount = 0;
    int hCount = 0;
    for (int i = 0; i < DataHeight; ++i) {
        for (int j = 0; j < DataWidth; ++j) {
            Sprite* item = NULL;
            if (currentString.at(i*DataWidth + j) == 'S') {
                item = Sprite::create("s.png");
                item->setUserObject(__String::create("S"));
            }else if (currentString.at(i*DataWidth + j) == 'C'){
                item = Sprite::create("cc.png");
                item->setUserObject(__String::create("C"));
            }else if (currentString.at(i*DataWidth + j) == 'V') {
                item = Sprite::create(VImages[vCount++]);
                item->setUserObject(__String::create("V"));
            }else if (currentString.at(i*DataWidth + j) == 'H') {
                item = Sprite::create(HImages[hCount++]);
                item->setUserObject(__String::create("H"));
            }else {
                continue;
            }
            item->setTag(i*DataWidth + j);
            item->setAnchorPoint(Vec2(0, 1.0f));
            item->setPosition(Vec2(1+PerGridWidth*j, GridHeight - 1 - PerGridWidth*i ));
            gridView->addChild(item);
        }
    }
}

void TipLayer::showInNode(Node* parent){
    ignoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2(0.5f, 0.5f));
    setScale(0);
    setPosition(STVisibleRect::getCenterOfScene());
    parent->addChild(this, 100);
    CallFunc* action = CallFunc::create(std::bind(&TipLayer::startSchedule, this));
    this->runAction(Sequence::create(ScaleTo::create(0.3f, 1.1f), ScaleTo::create(0.1f, 1.0f), action,NULL));
    
}

void TipLayer::startSchedule(){
    schedule(schedule_selector(TipLayer::update), 0.5f);
}

void TipLayer::update(float dt) {
    if (performCount < allRecorders.size()){
        performRecorde(allRecorders.at(performCount++));
    }else {
        unschedule(schedule_selector(TipLayer::update));
        gridView->getChildByTag(13)->runAction(Sequence::create(MoveBy::create(0.2f, Vec2(0, -PerGridWidth)), NULL));
        CallFunc* action1 = CallFunc::create(std::bind(&TipLayer::replaySchedule, this));
        this->runAction(Sequence::create(DelayTime::create(0.4f), action1, NULL));
        
    }
}

void TipLayer::replaySchedule() {
    replay->setOpacity(255);
    replay->setEnabled(true);
}

void TipLayer::onButtonsClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    Node* pNode = dynamic_cast<Node*>(pRef);
    __String* objString = dynamic_cast<__String*>(pNode->getUserObject());
    if (string("close").compare(objString->getCString()) == 0) {
        unschedule(schedule_selector(TipLayer::update));
        this->runAction(Sequence::create(DelayTime::create(0.2f), ScaleTo::create(0.3, 0), CallFunc::create(std::bind(&LayerColor::removeFromParent, this)), NULL));
    }else if (string("replay").compare(objString->getCString()) == 0){
        unschedule(schedule_selector(TipLayer::update));
        gridView->removeAllChildren();
        putallitems(this->theoriginString);
        performCount = 0;
        schedule(schedule_selector(TipLayer::update), 0.5f);
        replay->setOpacity(100);
        replay->setEnabled(false);
        tipLabel->setString(string(getLocalString("提示："))+"0/"+convertIntToString((int)allRecorders.size()));
    }
}


void TipLayer::performRecorde(MoveEventRecorder recorder) {
    Vec2 moveStep = recorder.movePoint;
    moveStep = Vec2(PerGridWidth*moveStep.x, PerGridWidth*moveStep.y);
    if (gridView->getChildByTag(recorder.itemTag)) {
        CallFunc* action1= CallFunc::create( std::bind( &Node::setTag, gridView->getChildByTag(recorder.itemTag), recorder.itemTag+recorder.movePoint.dot(Vec2(1, -4))));
        gridView->getChildByTag(recorder.itemTag)->runAction(Sequence::create(MoveBy::create(0.3f, moveStep), action1, NULL));
        //        log("tag is %.2f", recorder.itemTag+recorder.movePoint.dot(Vec2(1, -4)));
        tipLabel->setString(string(getLocalString("提示："))+convertIntToString(performCount)+"/"+convertIntToString(allRecorders.size()));
    }
}
