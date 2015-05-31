//
//  ShopLayer.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-22.
//
//

#include "ShopLayer.h"
#include "CocosHelper.h"
#include "HeadNode.h"
#include "UserDefaultManager.h"
#include "SuperGlobal.h"


Scene* ShopLayer::scene(){
    Scene* scene = Scene::create();
    ShopLayer* layer = ShopLayer::create();
    scene->addChild(layer);
    return scene;
}

bool ShopLayer::init(){
    if (GameLayerBase::initWithBgFileName("gamebg.png", false)) {
        prices = {"$0.99", "$1.99", "$7.99", "$0.99"};
        coins = {"8", "20", "100"};
        iapkeys = {"com.kekestudio.HuaRongDao.coins8",
            "com.kekestudio.HuaRongDao.coins20",
            "com.kekestudio.HuaRongDao.coins100",
            "com.kekestudio.HuaRongDao.removeAds"};
        createHeader();
        addShopItems();
        return true;
    }
    return false;
}

void ShopLayer::createHeader(){
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    
    Label* title = Label::createWithTTF(config2, getLocalString("商店"));
    ControlButton* backButton = CocosHelper::getButton("back_btn.png", "back_btn.png");
    backButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ShopLayer::backButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    backButton->setUserData((void*)"back");
    title->setColor(Color3B::GRAY);
    
    __Array* arrItems = __Array::create( backButton, title,NULL);
    HeadNode* pHeader = HeadNode::createWithItems(arrItems);
    pHeader->showInNode(this);
}


void ShopLayer::addShopItems(){
    itemBg = Sprite::create("iapbg.png");
    itemBg->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+(STVisibleRect::getGlvisibleSize().height - HeadNode::getHeadNodeHeight())/2.0);
    addChild(itemBg);
    
    coin = Sprite::create("coin.png");
    coin->setPosition(Vec2(itemBg->getContentSize().width / 2.0, itemBg->getContentSize().height - 40));
    itemBg->addChild(coin);
    
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    TTFConfig config3(FONTNAME,50,GlyphCollection::DYNAMIC,nullptr,true);
    coinNum = Label::createWithTTF(config3, convertIntToString(UserDefaultManager::getDiamond()));
    coinNum->setAnchorPoint(Vec2(0, 0.5f));
    coinNum->setPosition(Vec2(coin->getPositionX() + coin->getContentSize().width / 2.0 + 10, coin->getPositionY()));
    itemBg->addChild(coinNum);
    coinNum->setColor(Color3B::GRAY);
    
    float starty = coin->getPositionY() - 50;
    
    Vector<MenuItem*> _subItems;
    for (int i = 0; i < 5; ++i) {
        if (i == 4) {
            MenuItemSprite* restoreBtn = CocosHelper::menuItemSprite("noads.png");
            restoreBtn->setAnchorPoint(Vec2(0.5f, 0));
            restoreBtn->setPosition(Vec2(coin->getPositionX(), starty - restoreBtn->getContentSize().height - 35));
            restoreBtn->setCallback(CC_CALLBACK_1(ShopLayer::onRestoreItemClicked, this));
            
            Label* restore = Label::createWithTTF(config2, getLocalString("恢复购买"));
            restore->setAnchorPoint(Vec2(0.5f,0.5f));
            restore->setPosition(restoreBtn->getContentSize().width/2.0,restoreBtn->getContentSize().height/2.0);
            restore->setColor(Color3B::BLACK);
            restoreBtn->addChild(restore);
            _subItems.pushBack(restoreBtn);
            allShopItemY.push_back(restoreBtn->getPositionY()+restoreBtn->getContentSize().height/2.0);
            break;
        }
        if (i == 3) {
            MenuItemSprite* shopItem = CocosHelper::menuItemSprite("noads.png");
            Label *lefeL = Label::createWithTTF(config2, getLocalString(getLocalString("移除广告")));
            lefeL->setAnchorPoint(Vec2(0, 0.5f));
            lefeL->setPosition(Vec2(20, shopItem->getContentSize().height/2.0));
            shopItem->addChild(lefeL);
            
            shopItem->setCallback(CC_CALLBACK_1(ShopLayer::onShopItemClicked, this));
            shopItem->setAnchorPoint(Vec2(0.5f, 0));
            shopItem->setPosition(Vec2(coin->getPositionX(), starty - shopItem->getContentSize().height - 35));
            starty = shopItem->getPositionY();
            allShopItemY.push_back(shopItem->getPositionY()+shopItem->getContentSize().height/2.0);
            shopItem->setTag(i);
            Label* rightL = Label::createWithTTF(config2, prices.at(i));
            rightL->setAnchorPoint(Vec2(1.0, 0.5f));
            rightL->setPosition(Vec2(shopItem->getContentSize().width - 15, lefeL->getPositionY()));
            shopItem->addChild(rightL);
            _subItems.pushBack(shopItem);
            rightL->setColor(Color3B::BLACK);
            lefeL->setColor(Color3B::BLACK);
            continue;
        }
        MenuItemSprite* shopItem = CocosHelper::menuItemSprite("shop_item.png");
        Label *lefeL = Label::createWithTTF(config2, coins.at(i));
        Label* rightL = Label::createWithTTF(config2, prices.at(i));
        lefeL->setAnchorPoint(Vec2(0, 0.5f));
        lefeL->setPosition(Vec2(95, shopItem->getContentSize().height/2.0));
        rightL->setAnchorPoint(Vec2(1.0, 0.5f));
        rightL->setPosition(Vec2(shopItem->getContentSize().width - 15, lefeL->getPositionY()));
        shopItem->addChild(lefeL);
        shopItem->addChild(rightL);
        
        shopItem->setCallback(CC_CALLBACK_1(ShopLayer::onShopItemClicked, this));
        shopItem->setAnchorPoint(Vec2(0.5f, 0));
        shopItem->setPosition(Vec2(coin->getPositionX(), starty - shopItem->getContentSize().height - 35));
        starty = shopItem->getPositionY();
        allShopItemY.push_back(shopItem->getPositionY()+shopItem->getContentSize().height/2.0);
        shopItem->setTag(i);
        _subItems.pushBack(shopItem);
    }
    
    Menu* theMenu = Menu::createWithArray(_subItems);
    theMenu->setPosition(Vec2(0, 0));
    itemBg->addChild(theMenu);
    
    
//    MenuItemSprite* restoreBtn = CocosHelper::menuItemSprite("noads.png");
//    restoreBtn->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, itemBg->getBoundingBox().getMinY()*0.5 + STVisibleRect::getOriginalPoint().y*0.5));
//    restoreBtn->setCallback(CC_CALLBACK_1(ShopLayer::onRestoreItemClicked, this));
//    
//    Label* restore = Label::createWithTTF(config2, getLocalString("恢复购买"));
//    restore->setPosition(restoreBtn->getPosition());
//    restore->setColor(Color3B::BLACK);
//    Menu* restoreMenu = Menu::create(restoreBtn, NULL);
//    restoreMenu->setAnchorPoint(Vec2::ZERO);
//    restoreMenu->setPosition(Vec2::ZERO);
//    addChild(restoreMenu);
//    addChild(restore);
//    Label* footer = Label::createWithTTF(config2, "购买任意钻石去广告");
//    footer->setAnchorPoint(Vec2(0.5f, 0));
//    footer->setColor(Color3B::GRAY);
//    footer->setPosition(Vec2(itemBg->getContentSize().width/2.0, 20));
//    itemBg->addChild(footer);
}

void ShopLayer::onShopItemClicked(cocos2d::Ref *pRef) {
    SoundPlayer::getInstance()->playclickeffect();
    Node* pNode = dynamic_cast<Node*>(pRef);
//    iap->purchase(iapkeys.at(pNode->getTag()).c_str());
//    this->purchaseSuccess(iapkeys.at(pNode->getTag()).c_str());
}



void ShopLayer::backButtonClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    Director::getInstance()->popScene();
}


void ShopLayer::onRestoreItemClicked(cocos2d::Ref *pref) {
//    iap->restore();
}

void ShopLayer::purchaseSuccess(const char *pid) {
    int count = 0;
    for (vector<string>::size_type i = 0; i < iapkeys.size(); ++i) {
        if (iapkeys.at(i).compare(pid) == 0) {
            break;
        }
        count++;
    }
    if (count == 3) {
        UserDefaultManager::setIsRemoved(true);
//        KKAds ads;
//        ads.removeAds();
        return;
    }
    if (!UserDefaultManager::getIsFirstBuy()) {
        UserDefaultManager::setIsFirstBuy(true);
//
    }
    Sprite* coinIcon = Sprite::create("coin.png");
    coinIcon->setPosition(100 , allShopItemY.at(count));
    itemBg->addChild(coinIcon);
    log("the coinicon position is %.2f, %.2f", coinIcon->getPositionX(), coinIcon->getPositionY());
    
    coinIcon->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3f, coin->getPosition()), ScaleTo::create(0.3f, 0),NULL), CallFunc::create([=]( ){
        UserDefaultManager::addDiamond(atoi(coins.at(count).c_str()));
        coin->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f), ScaleTo::create(0.1f, 1.0), NULL));
        coinNum->setString(convertIntToString(UserDefaultManager::getDiamond()));
        
    }),CallFunc::create(std::bind(&Sprite::removeFromParent, coinIcon)),NULL));
    
    

}

void ShopLayer::restoreSuccess(const char *pid) {
    if (iapkeys.at(3).compare(pid) == 0) {
        UserDefaultManager::setIsRemoved(true);
//        KKAds ads;
//        ads.removeAds();
    }
}

void ShopLayer::restoreFailure(const char *pid, int errorCode) {
    
}


void ShopLayer::purchaseFailure(const char *pid, int errorCode) {
    
}
