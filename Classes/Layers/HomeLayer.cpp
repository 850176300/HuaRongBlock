//
//  HomeLayer.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#include "HomeLayer.h"
#include "extensions/cocos-ext.h"
#include "CocosHelper.h"
#include "LevelTitleNode.h"
#include "SceneManager.h"
#include "DBManager.h"
#include "AchievementLayer.h"
#include "LeaderboardLayer.h"
#include "UserDefaultManager.h"
USING_NS_CC_EXT;
#define LevelYSeperate 30
#define LevelXSeperate 15

Scene* HomeLayer::scene(){
    Scene* scene = Scene::create();
    HomeLayer* layer = HomeLayer::create();
    scene->addChild(layer);
    return scene;
}

bool HomeLayer::init(){
    if (GameLayerBase::initWithBgFileName("gamebg.png", false)) {
        createHeader();
        
        float offset = (m_pBg->getScale() - 1.0) * STVisibleRect::getDesignSize().height;
        
        Sprite* _title1 = Sprite::create(getLocalString("game_title.png"));
        Sprite* _title2 = Sprite::create("game_title2.png");
        
        _title1->setAnchorPoint(Vec2(0.5f, 1.0f));
        _title2->setAnchorPoint(Vec2(0.5f, 1.0f));
        _title1->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y - HeadNode::getHeadNodeHeight()-20-offset*1/3.0));
        _title2->setPosition(Vec2(_title1->getPositionX(), _title1->getPositionY() - _title1->getContentSize().height-5));
        addChild(_title1, 1);
        addChild(_title2, 1);
        
        createAllLevels(_title2->getPositionY() - _title2->getContentSize().height-80-offset*1/3.0);
        
        return true;
    }
    return false;
}

void HomeLayer::createAllLevels(float startY){
    Vector<MenuItem*> levelsItems;
    Vector<LevelItem*> items;

    
    for (int i = 0; i < 7; ++i) {
        LevelTitle *title = DBManager::getInstance()->allTypes.at(i);
//        title.setTitle("经典");
//        title.setComplPercent(90);
//        title.setTotal(50);
//        title.setAllItems(items);// = new LevelTitle("经典", 90, 50, items);
        LevelTitleNode* node1 = LevelTitleNode::createWithLeveTitle(title);
        node1->setPosition(Vec2(200, 300));
        node1->setCallback(CC_CALLBACK_1(HomeLayer::levelItemClicked, this));
        node1->setTag(i);
        if (i % 2 == 0) {
            node1->setAnchorPoint(Vec2(1.0, 1.0f));
            node1->setPosition(Vec2(STVisibleRect::getCenterOfScene().x - LevelXSeperate/2.0, startY + LevelYSeperate));
        }else {
            node1->setAnchorPoint(Vec2(0.0, 1.0f));
            node1->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + LevelXSeperate/2.0, startY + LevelYSeperate));
            startY -= node1->getContentSize().height + LevelYSeperate;
        }
        node1->setUserObject(title);
        node1->setEnabled(true);
        levelsItems.pushBack(node1);
    }
    
    Menu* levelMenu = Menu::createWithArray(levelsItems);
    levelMenu->setPosition(Vec2(0, 0));
    levelMenu->setEnabled(true);
    addChild(levelMenu,2);
}

void HomeLayer::createHeader(){
    __Array* arrayHeaderItems = __Array::createWithCapacity(3);
    ControlButton* rankButton = CocosHelper::getButton("rank_btn.png", "rank_btn.png");
    rankButton->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::itemClickedCallBack), Control::EventType::TOUCH_UP_INSIDE);
    rankButton->setUserData((void*)"rank");
    
    ControlButton* shopButton = CocosHelper::getButton("shop_btn.png", "shop_btn.png");
    shopButton->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::itemClickedCallBack), Control::EventType::TOUCH_UP_INSIDE);
    shopButton->setUserData((void*)"shop");
    
    stringstream soundBG;
    if (SoundPlayer::getInstance()->isMusicOpen() ){
        soundBG<<"sound_on.png";
    }else {
        soundBG<<"sound_off.png";
    }
    ControlButton* soundButton = CocosHelper::getButton( soundBG.str().c_str(), soundBG.str().c_str());
    soundButton->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::itemClickedCallBack), Control::EventType::TOUCH_UP_INSIDE);
    soundButton->setUserData((void*)"sound");
    
    time_t t = time(0);
    tm * now = localtime(&t);
    __String* nowString = __String::createWithFormat("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday);
    if (UserDefaultManager::getRecordeTime().compare(nowString->getCString()) >= 0) {
        starbtn = CocosHelper::getButton("starbtn.png", "starbtn.png");
        starbtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::itemClickedCallBack), Control::EventType::TOUCH_UP_INSIDE);
        starbtn->setUserData((void*)"stars");
    }else {
        starbtn = CocosHelper::getButton("starbtn_r.png", "starbtn_r.png");
        starbtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HomeLayer::itemClickedCallBack), Control::EventType::TOUCH_UP_INSIDE);
        starbtn->setUserData((void*)"stars");
    }
    
    
    
    arrayHeaderItems->addObject(starbtn);
    arrayHeaderItems->addObject(rankButton);
    arrayHeaderItems->addObject(shopButton);
    arrayHeaderItems->addObject(soundButton);
    
    header = HeadNode::createWithItems(arrayHeaderItems);
    header->showInNode(this);
}

void HomeLayer::onEnter(){
    GameLayerBase::onEnter();
    time_t t = time(0);
    tm * now = localtime(&t);
    __String* nowString = __String::createWithFormat("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday);
    if (UserDefaultManager::getRecordeTime().compare(nowString->getCString()) >= 0) {
        starbtn->setBackgroundSpriteForState(Scale9Sprite::create("starbtn.png"), Control::State::NORMAL);
        starbtn->setBackgroundSpriteForState(Scale9Sprite::create("starbtn.png"), Control::State::HIGH_LIGHTED);
        starbtn->setBackgroundSpriteForState(Scale9Sprite::create("starbtn.png"), cocos2d::extension::Control::State::DISABLED);
        
        starbtn->setPreferredSize(Sprite::create("starbtn.png")->getContentSize());
    }else {
        starbtn->setBackgroundSpriteForState(Scale9Sprite::create("starbtn_r.png"), Control::State::NORMAL);
        starbtn->setBackgroundSpriteForState(Scale9Sprite::create("starbtn_r.png"), Control::State::HIGH_LIGHTED);
        starbtn->setBackgroundSpriteForState(Scale9Sprite::create("starbtn_r.png"), cocos2d::extension::Control::State::DISABLED);
        starbtn->setPreferredSize(Sprite::create("starbtn_r.png")->getContentSize());
    }
}


void HomeLayer::itemClickedCallBack(cocos2d::Ref *pSender, Control::EventType touchType) {
    if (touchType != Control::EventType::TOUCH_UP_INSIDE) {
        return;
    }
    SoundPlayer::getInstance()->playclickeffect();
    ControlButton* button = dynamic_cast<ControlButton*>(pSender);
    char* buf = (char *)(button->getUserData());
    string bufString(buf);
    if (bufString.compare("rank") == 0){
        Director::getInstance()->pushScene(Leaderboard::scene());
        log("rank button clicked");
    }else if (bufString.compare("shop") == 0){
        log("shop button clicked");
        SceneManager::getInstance()->gotoShopLayer();

    }else if (bufString.compare("sound") == 0){
        SoundPlayer::getInstance()->switchVolume();
        stringstream soundBG;
        if (SoundPlayer::getInstance()->isMusicOpen() ){
            soundBG<<"sound_on.png";
        }else {
            soundBG<<"sound_off.png";
        }
        Scale9Sprite* btnDown = Scale9Sprite::create(soundBG.str().c_str());
        Scale9Sprite* btnNormal = Scale9Sprite::create(soundBG.str().c_str());
        button->setBackgroundSpriteForState(btnNormal, cocos2d::extension::Control::State::NORMAL);
        button->setBackgroundSpriteForState(btnDown, cocos2d::extension::Control::State::HIGH_LIGHTED);
        log("sound button clicked");
    }else if (bufString.compare("stars") == 0) {
        Director::getInstance()->pushScene(ArchievementLayer::scene());
        log("stars button clicked");
    }else {
        log("the invalid button clicked event");
    }
}

void HomeLayer::levelItemClicked(cocos2d::Ref *pSender) {
    Node* pNode  = dynamic_cast<Node*>(pSender);
    LevelTitle* title = dynamic_cast<LevelTitle*>(pNode->getUserObject());
    SceneManager::getInstance()->gotoLevelLayer(title);
}

void HomeLayer::onBackKeyClicked() {
    ConfirmDialog* dialog = ConfirmDialog::create();
    //    dialog->setTitleText("提示一个字");
    dialog->setTitleText(getLocalString("提示"));
    dialog->setContentText(getLocalString("是否退出游戏？"));
    dialog->setDelegate(this);
    dialog->show(this);
}

void HomeLayer::onConfirmed(ConfirmDialog *target, bool yesOrNo) {
    if (yesOrNo == true) {
        Director::getInstance()->end();
    }else {
        return;
    }
}

