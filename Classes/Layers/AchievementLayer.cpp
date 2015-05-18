//
//  AchievementLayer.cpp
//  HuaRongBlock
//
//  Created by liuwei on 14-12-13.
//
//

#include "AchievementLayer.h"
#include "HeadNode.h"
#include "CocosHelper.h"
#include "UserDefaultManager.h"
#include "ConfirmDialog.h"

#define StartX 50

int achieveFlags[] = {50,100,150,200,500,1200};
int diamondArrs[] = {5, 10, 15, 20, 50, 120};
int flagsCount = 7;

Scene* ArchievementLayer::scene(){
    Scene* scene = Scene::create();
    
    ArchievementLayer* layer = ArchievementLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ArchievementLayer::init(){
    if (GameLayerBase::initWithBgFileName("gamebg.png")) {
        createDiamondLayer();
         createHeader();
        frameBg = Sprite::create("big_item_bg.png");
        frameBg->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+(STVisibleRect::getGlvisibleSize().height - HeadNode::getHeadNodeHeight())/2.0);
        frameBg->setColor(Color3B::WHITE);
        addChild(frameBg);
    
        addStarCount();
        addEveryDayArchieve();
        addstarArchieve();
        return true;
    }
    return false;
}

void ArchievementLayer::createDiamondLayer(){
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    
    diamondLayer = Layer::create();
    diamondLayer->ignoreAnchorPointForPosition(false);

    
    
    headercoin = Sprite::create("coin.png");
    headercoin->setAnchorPoint(Vec2(1.0f, 0.5f));
    diamondLayer->setContentSize(headercoin->getContentSize());
    headernum = Label::createWithTTF(config2, convertIntToString(UserDefaultManager::getDiamond()));
    headernum->setColor(Color3B::GRAY);
    headernum->setAnchorPoint(Vec2(1.0, 0.5f));
    headernum->setPosition(Vec2(headercoin->getContentSize().width, headercoin->getContentSize().height/2.0));
    headercoin->setPosition(headernum->getPosition() + Vec2(-headernum->getContentSize().width, 0));
    
    diamondLayer->addChild(headercoin);
    diamondLayer->addChild(headernum);
}

void ArchievementLayer::createHeader(){
    ControlButton* backButton = CocosHelper::getButton("back_btn.png", "back_btn.png");
    backButton->addTargetWithActionForControlEvents(this, cccontrol_selector(ArchievementLayer::backButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    Label *label1 = Label::createWithTTF(config2, getLocalString("成就"));
    //    label1->setColor(Color3B(255, 255, 255));
    label1->setColor(Color3B::GRAY);
    
    __Array* items = __Array::createWithCapacity(2);
    items->addObject(backButton);
    items->addObject(label1);
//    items->addObject(diamondLayer);
    
    HeadNode* header = HeadNode::createWithItems(items);
    header->showInNode(this);
}


void ArchievementLayer::backButtonClicked(cocos2d::Ref *pSender, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    Director::getInstance()->popScene();
}


void ArchievementLayer::addStarCount(){
    Sprite* star = Sprite::create("star2.png");
    star->setAnchorPoint(Vec2(1.0, 1.0));
    star->setPosition(Vec2(frameBg->getContentSize().width/2.0-100, frameBg->getContentSize().height-20));
    frameBg->addChild(star);
    
    diamondLayer->ignoreAnchorPointForPosition(false);
    diamondLayer->setAnchorPoint(Vec2(0, 1.0));
    diamondLayer->setPosition(Vec2(frameBg->getContentSize().width/2.0+130, frameBg->getContentSize().height-20));
    frameBg->addChild(diamondLayer);
    
    TTFConfig config2(FONTNAME,50,GlyphCollection::DYNAMIC,nullptr,true);
    __String* score = __String::createWithFormat("%d", UserDefaultManager::getStarsCount());
    Label* Scount = Label::createWithTTF(config2, score->getCString());
    Scount->setColor(Color3B::GRAY);
    Scount->setAnchorPoint(Vec2(0.0, 0.5f));
    Scount->setPosition(star->getPosition() + Vec2(10, -star->getContentSize().height/2.0-5));
    frameBg->addChild(Scount);
}

void ArchievementLayer::addEveryDayArchieve(){
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    Label* title = Label::createWithTTF(config2, getLocalString("每日登录奖励："));
    title->setColor(Color3B::GRAY);
    title->setAnchorPoint(Vec2(0.0, 1.0));
    title->setPosition(Vec2(StartX, frameBg->getContentSize().height -  120));
    frameBg->addChild(title);
    
    time_t t = time(0);
    tm * now = localtime(&t);
    __String* nowString = __String::createWithFormat("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday);
    MenuItemSprite* themenuItem = NULL;
    title2 = Label::createWithTTF(config2, getLocalString("今日可领取钻石"));
    if (UserDefaultManager::getRecordeTime().compare(nowString->getCString()) < 0) {
        Sprite* sprite1 = Sprite::create("star_bg1.png");
        Sprite* sprite2 = Sprite::create("star_bg1.png");
        sprite2->setColor(Color3B::GRAY);
        themenuItem = MenuItemSprite::create(sprite1, sprite2);
        themenuItem->setCallback(CC_CALLBACK_1(ArchievementLayer::oneveryDayClicked, this));
        themenuItem->setAnchorPoint(Vec2(0.0, 1.0f));
        themenuItem->setPosition(title->getPosition() + Vec2(0, -title->getContentSize().height-20));
        num = Label::createWithTTF(config2, "1");
        num->setAnchorPoint(Vec2(1.0, 0.5f));
        num->setPosition(themenuItem->getContentSize().width - 20, themenuItem->getContentSize().height / 2.0);
        themenuItem->addChild(num);
        
        coin = Sprite::create("coin.png");
        coin->setAnchorPoint(Vec2(1.0f, 0.5f));
        coin->setPosition(num->getPosition() + Vec2(-num->getContentSize().width - 15, 0));
        themenuItem->addChild(coin);
    }else {
        Sprite* sprite1 = Sprite::create("blank.png");
        Sprite* sprite2 = Sprite::create("blank.png");
        sprite2->setColor(Color3B::GRAY);
        themenuItem = MenuItemSprite::create(sprite1, sprite2);
        themenuItem->setCallback(CC_CALLBACK_1(ArchievementLayer::oneveryDayClicked, this));
        themenuItem->setAnchorPoint(Vec2(0.0, 1.0f));
        themenuItem->setPosition(title->getPosition() + Vec2(0, -title->getContentSize().height-20));
        title2->setString(getLocalString("今日奖励已领取"));
        title2->setColor(Color3B::GRAY);
    }
    
    title2->setAnchorPoint(Vec2(0, 0.5f));
    title2->setPosition(Vec2(20, themenuItem->getContentSize().height/2.0));
    themenuItem->addChild(title2);
    
    Menu* theMenu = Menu::createWithItem(themenuItem);
    theMenu->setPosition(Vec2::ZERO);
    frameBg->addChild(theMenu);
    
}


void ArchievementLayer::oneveryDayClicked(cocos2d::Ref *pRef) {
//    MenuItemSprite* item = dynamic_cast<MenuItemSprite* >(pRef);
    if (title2->getString().compare("今日奖励已领取") == 0) {
        ConfirmDialog* dialog = ConfirmDialog::create(true);
        //    dialog->setTitleText("提示一个字");
        dialog->setTitleText(getLocalString("提示"));
        dialog->setContentText(getLocalString("今日奖励已领取"));
        dialog->show(this);
        
    }else {
        time_t t = time(0);
        tm * now = localtime(&t);
        __String* nowString = __String::createWithFormat("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday);
        UserDefaultManager::setRecordTime(nowString->getCString());
        title2->setString(getLocalString("今日奖励已领取"));
//        title2->setColor(Color3B::GRAY);
//        Sprite* sprite1 = Sprite::create("blank.png");
//        Sprite* sprite2 = Sprite::create("blank.png");
//        sprite2->setColor(Color3B::GRAY);
//        item->setNormalImage(sprite1);
//        item->setSelectedImage(sprite2);
        num->removeFromParent();
        coin->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3f, diamondLayer->getPosition()), ScaleTo::create(0.3f, 0), NULL), CallFunc::create([=](){
            UserDefaultManager::addDiamond(1);
            headercoin->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f), ScaleTo::create(0.1f, 1.0f), NULL));
            headernum->setString(convertIntToString(UserDefaultManager::getDiamond()));
            headercoin->setPosition(headernum->getPosition() + Vec2(-headernum->getContentSize().width, 0));
            
        }),CallFunc::create(std::bind(&Sprite::removeFromParent, coin)),NULL));
    }
}

void ArchievementLayer::addstarArchieve(){
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    Label* title = Label::createWithTTF(config2, getLocalString("成就奖励："));
    title->setColor(Color3B::GRAY);
    title->setAnchorPoint(Vec2(0.0, 1.0));
    title->setPosition(Vec2(StartX, frameBg->getContentSize().height -  120 - 220));
    frameBg->addChild(title);
    
    int startRecieve = UserDefaultManager::getReciveCount();
    if (startRecieve < flagsCount - 1) {
        ArchieveItem* item1 = ArchieveItem::createWith(startRecieve, diamondArrs[startRecieve]);
        item1->ignoreAnchorPointForPosition(false);
        item1->setAnchorPoint(Vec2(0, 1.0));
        item1->setPosition(Vec2(StartX, title->getPosition().y-title->getContentSize().height - 20));
        item1->settheClickeDelegate(this);
        frameBg->addChild(item1);
    }
    startRecieve++;
    if (startRecieve < flagsCount - 1) {
        ArchieveItem* item1 = ArchieveItem::createWith(startRecieve, diamondArrs[startRecieve]);
        item1->ignoreAnchorPointForPosition(false);
        item1->setAnchorPoint(Vec2(0, 1.0));
        item1->setPosition(Vec2(StartX, title->getPosition().y-title->getContentSize().height - 20 - 104-20));
        item1->settheClickeDelegate(this);
        frameBg->addChild(item1);
        _secondItem = NULL;
        _secondItem = item1;
    }else {
        _secondItem = nullptr;
    }
}

void ArchievementLayer::clickedTheAchieveItem(ArchieveItem *item, bool boolen, int coinCount) {
    if (boolen == false) {
        ConfirmDialog* dialog = ConfirmDialog::create(true);
        //    dialog->setTitleText("提示一个字");
        dialog->setTitleText(getLocalString("提示"));
        dialog->setContentText(getLocalString("对不起，你当前的成就值没有达到领取要求"));
        dialog->show(this);
    }else {
        UserDefaultManager::setRecieveCount(UserDefaultManager::getReciveCount()+1);
        Sprite* coin = Sprite::create("coin.png");
        coin->setPosition(Vec2(item->getBoundingBox().getMidX(), item->getBoundingBox().getMidY()));
        frameBg->addChild(coin);
        coin->runAction(Sequence::create(Spawn::create(MoveTo::create(0.3f, diamondLayer->getPosition()), ScaleTo::create(0.3f, 0), NULL), CallFunc::create([=](){
            UserDefaultManager::addDiamond(coinCount);
            headercoin->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f), ScaleTo::create(0.1f, 1.0f), NULL));
            headernum->setString(convertIntToString(UserDefaultManager::getDiamond()));
            headercoin->setPosition(headernum->getPosition() + Vec2(-headernum->getContentSize().width, 0));
            
        }),CallFunc::create(std::bind(&Sprite::removeFromParent, coin)),NULL));
        
        item->runAction(Sequence::create(ScaleTo::create(0.3, 1.0, 0),CallFunc::create(std::bind(&ArchieveItem::removeFromParent, item)), NULL));
        if (_secondItem != NULL) {
            Point secondPos = _secondItem->getPosition();
            _secondItem->runAction(Sequence::create(MoveTo::create(0.3, item->getPosition()), CallFunc::create([=]( ){
                int startRecieve = UserDefaultManager::getReciveCount()+1;
                if (startRecieve < flagsCount - 1) {
                    ArchieveItem* item1 = ArchieveItem::createWith(startRecieve, diamondArrs[startRecieve]);
                    item1->ignoreAnchorPointForPosition(false);
                    item1->setAnchorPoint(Vec2(0, 1.0));
                    item1->setPosition(secondPos);
                    item1->settheClickeDelegate(this);
                    frameBg->addChild(item1);
                    _secondItem = NULL;
                    _secondItem = item1;
                }else {
                    _secondItem = NULL;
                }
            }),NULL));
        }
        
                          
    }
}







ArchieveItem* ArchieveItem::createWith(int leastCount, int coinCount) {
    ArchieveItem* pRet = new ArchieveItem();
    if (pRet && pRet->initWith(leastCount, coinCount)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return pRet;
    }
    
}


bool ArchieveItem::initWith(int leastCount, int coinCount) {
    if (Layer::init()) {
        _coinCount = coinCount;
        MenuItemSprite* bgMenu = nullptr;
        if (leastCount == UserDefaultManager::getReciveCount() && UserDefaultManager::getStarsCount() >= achieveFlags[leastCount]) {
            Sprite* sprite1 = Sprite::create("star_bg1.png");
            Sprite* sprite2 = Sprite::create("star_bg1.png");
            sprite2->setColor(Color3B::GRAY);
            bgMenu = MenuItemSprite::create(sprite1, sprite2);
            bgMenu->setTag(1);
        }else {
            Sprite* sprite1 = Sprite::create("blank.png");
            Sprite* sprite2 = Sprite::create("blank.png");
            sprite2->setColor(Color3B::GRAY);
            bgMenu = MenuItemSprite::create(sprite1, sprite2);
            bgMenu->setTag(0);
        }
        bgMenu->setAnchorPoint(Vec2(0, 0.0));
        bgMenu->setPosition(Vec2::ZERO);
        bgMenu->setCallback(CC_CALLBACK_1(ArchieveItem::onClicked, this));
        setContentSize(bgMenu->getContentSize());
        
        Menu* theMenu = Menu::createWithItem(bgMenu);
        theMenu->setPosition(Vec2::ZERO);
        addChild(theMenu);
        
        
        Sprite* star = Sprite::create("star1.png");
        star->setAnchorPoint(Vec2(0, 0.5f));
        star->setPosition(Vec2(5, bgMenu->getContentSize().height/2.0));
        addChild(star);
        
        TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
        __String* stringn = __String::createWithFormat("%s%d%s", getLocalString("收集"),achieveFlags[leastCount], getLocalString("个"));
        content = Label::createWithTTF(config2, stringn->getCString());
        content->setAnchorPoint(Vec2(0, 0.5f));
        content->setPosition(star->getPosition() + Vec2(star->getContentSize().width + 5, 0));
        addChild(content);
        
        
        num = Label::createWithTTF(config2, convertIntToString(coinCount));
        num->setAnchorPoint(Vec2(1.0, 0.5f));
        num->setPosition(bgMenu->getContentSize().width - 10, bgMenu->getContentSize().height / 2.0);
        addChild(num);
        
        Sprite* coin = Sprite::create("coin.png");
        coin->setAnchorPoint(Vec2(1.0f, 0.5f));
        coin->setPosition(num->getPosition() + Vec2(-num->getContentSize().width - 5, 0));
        addChild(coin);
        if (bgMenu->getTag() == 0) {
            content->setColor(Color3B::GRAY);
            num->setColor(Color3B::GRAY);
        }
        return true;
    }
    return false;
}

void ArchieveItem::settheClickeDelegate(ArchieveDelegate *delegate) {
    pDelegate = 0;
    pDelegate = delegate;
}

void ArchieveItem::onClicked(cocos2d::Ref *pRef) {
    SoundPlayer::getInstance()->playclickeffect();
    MenuItemSprite* pNode = dynamic_cast<MenuItemSprite*>(pRef);
    pNode->setEnabled(false);
    if (pNode->getTag() == 1) {
        pNode->setNormalImage(Sprite::create("blank.png"));
        content->setColor(Color3B::GRAY);
        num->setColor(Color3B::GRAY);
        if (pDelegate) {
            pDelegate->clickedTheAchieveItem(this, true, _coinCount);
        }
    }else {
        if (pDelegate) {
            pDelegate->clickedTheAchieveItem(this, false, _coinCount);
        }
    }
}


