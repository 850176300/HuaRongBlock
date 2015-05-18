//
//  ShopLayer_Android.cpp
//  HuaRongBlock
//
//  Created by 兵兵 on 14-12-27.
//
//

#include "ShopLayer_Android.h"

#include "ShopLayer.h"
#include "CocosHelper.h"
#include "HeadNode.h"
#include "UserDefaultManager.h"
#include "SuperGlobal.h"
#include "KKAds.h"
#include "ConfirmDialog.h"
#include "KKVedioAdsAdapter.h"

static int sg_awardCoint;

ShopLayer_Android::ShopLayer_Android(){
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ShopLayer_Android::onadFinished), konVideoIntertitialClose, nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ShopLayer_Android::onloadAdFailed), konVideoIntertitialLoadFailed, nullptr);
}

ShopLayer_Android::~ShopLayer_Android(){
    NotificationCenter::getInstance()->removeObserver(this, konVideoIntertitialLoadFailed);
    NotificationCenter::getInstance()->removeObserver(this, konVideoIntertitialClose);
}

Scene* ShopLayer_Android::scene(){
    Scene* scene = Scene::create();
    ShopLayer_Android* layer = ShopLayer_Android::create();
    scene->addChild(layer);
    return scene;
}

bool ShopLayer_Android::init(){
    if (GameLayerBase::initWithBgFileName("gamebg.png", false)) {
        time_t t = time(0);
        tm * now = localtime(&t);
        __String* nowString = __String::createWithFormat("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday);
        
        if (UserDefaultManager::getRecordeTime1().compare(nowString->getCString()) != 0) {
            UserDefaultManager::setLastCount(10);
            UserDefaultManager::setRecordTime1(nowString->getCString());
            UserDefaultManager::setViewState(0);
        }
        
        
        
        prices = {"广告视频", "广告视频", "广告视频", "广告视频", "广告视频", "广告视频" ,"广告视频", "广告视频", "广告视频" ,"广告视频"};
        coins = {"已观看", "已观看", "已观看", "已观看", "已观看", "已观看", "已观看", "已观看", "已观看", "已观看"};
        createHeader();
        addShopItems();
        return true;
    }
    return false;
}

void ShopLayer_Android::createHeader(){
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    
    Label* title = Label::createWithTTF(config2, getLocalString("获取钻石"));
    backButton = CocosHelper::getButton("back_btn.png", "back_btn.png");
    backButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ShopLayer_Android::backButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    backButton->setUserData((void*)"back");
    title->setColor(Color3B::GRAY);
    
    __Array* arrItems = __Array::create( backButton, title,NULL);
    HeadNode* pHeader = HeadNode::createWithItems(arrItems);
    pHeader->showInNode(this);
}


void ShopLayer_Android::addShopItems(){
    itemBg = Sprite::create("big_item_bg.png");
    itemBg->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+(STVisibleRect::getGlvisibleSize().height - HeadNode::getHeadNodeHeight())/2.0);
    addChild(itemBg);
    
    
    Sprite* centerBG = Sprite::create("center.png");
    centerBG->setAnchorPoint(Vec2(0.5, 1.0f));
    centerBG->setPosition(Vec2(itemBg->getBoundingBox().getMidX(), itemBg->getBoundingBox().getMaxY() - 40));
    addChild(centerBG);
    
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    Label* title1 = Label::createWithTTF(config2, getLocalString("看视频赠送钻石"));
    title1->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    title1->setDimensions(itemBg->getContentSize().width - 60, title1->getHeight());
    title1->setAnchorPoint(Vec2(.5f, 1.0f));
    title1->setPosition(Vec2(centerBG->getBoundingBox().getMidX(), centerBG->getBoundingBox().getMinY()-30));
    addChild(title1);
    
//    titile2 = Label::createWithTTF(config2, getLocalString("今日剩余观看次数：") + convertIntToString(UserDefaultManager::getLastCount()));
//    titile2->setAnchorPoint(Vec2(.5f, 1.0f));
//    titile2->setPosition(Vec2(title1->getBoundingBox().getMidX(), title1->getBoundingBox().getMinY()-20));
//    addChild(titile2);
    
    title1->setColor(Color3B::GRAY);
//    titile2->setColor(Color3B::GRAY);
    
    viewBtn = CocosHelper::getButton("clickb.png", "clickb.png");
    viewBtn->setAnchorPoint(Vec2(.5f, 1.0f));
    viewBtn->setPosition(Vec2(title1->getBoundingBox().getMidX(), title1->getBoundingBox().getMinY()-30));
    viewBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ShopLayer_Android::onShopItemClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    addChild(viewBtn);
    viewBtn->setTag(UserDefaultManager::getViewState());
    if (viewBtn->getTag() == 2) {
        viewBtn->setBackgroundSpriteForState(Scale9Sprite::create("item_gray.png"), cocos2d::extension::Control::State::NORMAL);
        viewBtn->setEnabled(false);
    }
    
    
    
    viewBtnCenter = viewBtn->getBoundingBox();
    updateViewButton(0);
}

void ShopLayer_Android::updateViewButton(float){
    removeChildByTag(1021);
    removeChildByTag(1022);
    removeChildByTag(1023);
    
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    if (UserDefaultManager::getViewState() == 0) {
        Label* ll = Label::createWithTTF(config2, getLocalString("观看视频"));
        ll->setPosition(Vec2(viewBtnCenter.getMidX(), viewBtnCenter.getMidY()));
        addChild(ll, 10);
        ll->setTag(1021);
    }else if (UserDefaultManager::getViewState() == 1){
        Label* ll = Label::createWithTTF(config2, getLocalString("领取钻石"));
        ll->setAnchorPoint(Vec2(0, 0.5f));
        ll->setPosition(Vec2(viewBtnCenter.getMinX() + 20, viewBtnCenter.getMidY()));
        addChild(ll, 10);
        ll->setTag(1021);
        
        Label* num = Label::createWithTTF(config2, "1");
        num->setAnchorPoint(Vec2(1.0, 0.5f));
        num->setPosition(Vec2(viewBtnCenter.getMaxX() - 15, viewBtnCenter.getMidY()));
        addChild(num);
        num->setTag(1022);
        
        
        Sprite* coin = Sprite::create("coin.png");
        coin->setAnchorPoint(Vec2(1.0f, 0.5f));
        coin->setPosition(num->getPosition() + Vec2(-num->getContentSize().width - 15, 0));
        addChild(coin);
        coin->setTag(1023);
    }else {
        Label* ll = Label::createWithTTF(config2, getLocalString("今日无可观看视频"));
        ll->setPosition(Vec2(viewBtnCenter.getMidX(), viewBtnCenter.getMidY()));
        addChild(ll, 10);
        ll->setTag(1021);
    }
}

void ShopLayer_Android::onShopItemClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    Node* pNode = dynamic_cast<Node*>(pRef);
    if (pNode->getTag() == 0) {
//        KKAds ads;
//        ads.requestVideoIntertitial();
        KKVedioAdsAdapter::getInstance()->showVedioAds();
        
        viewBtn->setEnabled(false);
        backButton->setEnabled(false);
    }else if (pNode->getTag() == 1) {
        int num = UserDefaultManager::getLastCount();
        if (num - 1 >= 1) {
            pNode->setTag(0);
            UserDefaultManager::addDiamond(1);
            UserDefaultManager::setViewState(0);
            UserDefaultManager::setLastCount(num - 1);
//            titile2->setString(getLocalString("今日剩余观看次数：") + convertIntToString(num - 1));
        }else {
            pNode->setTag(2);
            UserDefaultManager::addDiamond(1);
            UserDefaultManager::setViewState(2);
            UserDefaultManager::setLastCount(0);
            ((ControlButton*)pNode)->setBackgroundSpriteForState(Scale9Sprite::create("item_gray.png"), cocos2d::extension::Control::State::NORMAL);
            ((ControlButton*)pNode)->setEnabled(false);
//            titile2->setString(getLocalString("今日剩余观看次数：") + convertIntToString(num - 1));
        }
        updateViewButton(0);
    }
    
}



void ShopLayer_Android::backButtonClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    Director::getInstance()->popScene();
}

void ShopLayer_Android::onadFinished(cocos2d::Ref *pRef) {
    log("ShopLayer_Android::onadFinished");
    __String* bString = dynamic_cast<__String*>(pRef);
    int coint = bString->intValue();
    sg_awardCoint = coint;
//    if (string("yes").compare(bString->getCString()) == 0) {
        log("观看广告成功！");
        UserDefaultManager::setViewState(1);
        viewBtn->setTag(1);
        scheduleOnce(schedule_selector(ShopLayer_Android::updateViewButton), 0.5f);
        viewBtn->setEnabled(true);
        backButton->setEnabled(true);
//    }else if (string("no").compare(bString->getCString()) == 0){
//        log("观看广告失败！");
//        viewBtn->setEnabled(true);
//        backButton->setEnabled(true);
//        viewBtn->setTag(0);
//    }else {
//        log("无法识别");
//    }
}

void ShopLayer_Android::onloadAdFailed(Ref *pRef){
    log("ShopLayer_Android::onloadAdFailed");

    viewBtn->setTag(0);
    scheduleOnce(schedule_selector(ShopLayer_Android::showWarmingDialog), 0.5f);

}


void ShopLayer_Android::showWarmingDialog(float) {
    ConfirmDialog* dialog = ConfirmDialog::create(true);
    dialog->setTitleText(getLocalString("警告"));
    dialog->setContentText(getLocalString("视频广告加载失败，请检查网络，重新加载！"));
    dialog->show(this);
    viewBtn->setEnabled(true);
    backButton->setEnabled(true);
}

void ShopLayer_Android::onBackKeyClicked(){
    
}