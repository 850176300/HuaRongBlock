//
//  LevelDetailLayer.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-11.
//
//

#include "LevelDetailLayer.h"
#include "HeadNode.h"
#include "CocosHelper.h"
#include "SceneManager.h"
#include "GameController.h"
#include "LevelItemNode.h"

#define LevelItemWidth 184 
#define LevelItemHeight 99

Scene* LevelDetail::scene(LevelTitle* thetitle){
    Scene* scene = Scene::create();
    LevelDetail* layer = LevelDetail::createWithLevel(thetitle);
    scene->addChild(layer);
    return scene;
}

LevelDetail* LevelDetail::createWithLevel(LevelTitle* thetitle) {
    LevelDetail* pRet = new LevelDetail();
    if (pRet && pRet->initWithLevel(thetitle)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool LevelDetail::initWithLevel(LevelTitle* thetitle) {
    if (GameLayerBase::initWithBgFileName("gamebg.png")) {
        currentLevel = thetitle;
        currentLevel->retain();
        currentPage = 1;
        createHeader(thetitle->getTitle());
        addPageControl();
        addScrollView();
        return true;
    }
    return false;
}

void LevelDetail::createHeader(string title) {
    ControlButton* backButton = CocosHelper::getButton("back_btn.png", "back_btn.png");
    backButton->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelDetail::backButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    Label *label1 = Label::createWithTTF(config2, getLocalString(title.c_str()));
//    label1->setColor(Color3B(255, 255, 255));
    label1->setColor(Color3B::GRAY);
    
    __Array* items = __Array::createWithCapacity(2);
    items->addObject(backButton);
    items->addObject(label1);
    
    HeadNode* header = HeadNode::createWithItems(items);
    header->showInNode(this);
}

void LevelDetail::addScrollView(){
    m_pScrollView = ScrollMenu::create();
    m_pScrollView->setViewSize(Size(STVisibleRect::getGlvisibleSize().width, titleTip->getPositionY() - titleTip->getContentSize().height-20-GameController::getInstance()->getBannerHeight()));
    m_pScrollView->ignoreAnchorPointForPosition(false);
    m_pScrollView->setAnchorPoint(Vec2(0.5f, 1.0f));
    m_pScrollView->setPosition(Vec2(titleTip->getPositionX(), titleTip->getPositionY() - titleTip->getContentSize().height-20));
    m_pScrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    addChild(m_pScrollView, 2);
    
    m_pScrollView->setScrollEnable(false);
    
    scrollviewXseperate = (STVisibleRect::getGlvisibleSize().width - LevelItemWidth * 3) / 4.0;
    scrollviewYseperate = scrollviewXseperate * 0.618f;
    this->scheduleOnce(schedule_selector(LevelDetail::loadlevelItemsInSchedule), 0.1f);
}

void LevelDetail::onEnterTransitionDidFinish(){
    GameLayerBase::onEnterTransitionDidFinish();
    this->unschedule(schedule_selector(LevelDetail::loadlevelItemsInSchedule));
    this->scheduleOnce(schedule_selector(LevelDetail::loadlevelItemsInSchedule), 0.1f);
}

void LevelDetail::backButtonClicked(cocos2d::Ref *pSender, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    SceneManager::getInstance()->gotoHomeLayer();
}

void LevelDetail::addPageControl(){
    preBtn  = CocosHelper::getButton("pre_u.png", "pre_d.png");
    preBtn->setTag(kPreBtn);
    preBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelDetail::pageControlButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    
    nextBtn = CocosHelper::getButton("next_u.png", "next_d.png");
    nextBtn->setTag(kNextBtn);
    nextBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LevelDetail::pageControlButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    
    
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    titleTip = Label::createWithTTF(config2, "0-151");

    addChild(titleTip, 1);
    addChild(preBtn, 1);
    addChild(nextBtn, 1);
    
    refreshTipLabel();
}

void LevelDetail::refreshTipLabel(){
    __String *tip = __String::createWithFormat("%d-%d",1+(PAGECOLUMCOUNT*PAGEROWCOUNT)*(currentPage-1),(PAGECOLUMCOUNT*PAGEROWCOUNT)*currentPage > currentLevel->getTotal() ? currentLevel->getTotal() : (PAGECOLUMCOUNT*PAGEROWCOUNT)*currentPage  );
    titleTip->setString(tip->getCString());
    log("the current page is %d!!!!!!!!!!!!!!", currentPage);
    if (currentPage >= 1.0*currentLevel->getTotal()/(PAGECOLUMCOUNT*PAGEROWCOUNT)) {
//        nextBtn->getBackgroundSprite()->setColor(Color3B::GRAY);
        preBtn->setOpacity(100);
        nextBtn->setEnabled(false);
    }else {
//        nextBtn->getBackgroundSprite()->setColor(Color3B::WHITE);
        preBtn->setOpacity(255);
        nextBtn->setEnabled(true);
    }
    if (currentPage == 1){
//        preBtn->getBackgroundSprite()->setColor(Color3B::GRAY);
        preBtn->setOpacity(100);
        preBtn->setEnabled(false);
    }else {
        log("set pre button enable true");
//        preBtn->getBackgroundSprite()->setColor(Color3B::WHITE);
        preBtn->setOpacity(255);
        preBtn->setEnabled(true);
    }
    
    titleTip->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y - HeadNode::getHeadNodeHeight()-80));
    preBtn->setAnchorPoint(Vec2(1.0, 0.5f));
    nextBtn->setAnchorPoint(Vec2(0, 0.5));
    preBtn->setPosition(Vec2(titleTip->getPositionX() - titleTip->getContentSize().width/2.0-15, titleTip->getPositionY()));
    nextBtn->setPosition(Vec2(titleTip->getPositionX() + titleTip->getContentSize().width/2.0+15, titleTip->getPositionY()));
}

void LevelDetail::pageControlButtonClicked(cocos2d::Ref *pSender, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    this->unschedule(schedule_selector(LevelDetail::loadlevelItemsInSchedule));
    Node* pNode = dynamic_cast<Node*>(pSender);
    if (pNode->getTag() == kPreBtn) {
        --currentPage;
    }else {
        ++currentPage;
    }
    refreshTipLabel();
    this->scheduleOnce(schedule_selector(LevelDetail::loadlevelItemsInSchedule), 0.1f);
}

void LevelDetail::loadlevelItemsInSchedule(float dt) {
    Vector<MenuItem*> allmenuItems;
    int count = -(PAGECOLUMCOUNT*PAGEROWCOUNT)*(currentPage-1)+((PAGECOLUMCOUNT*PAGEROWCOUNT)*currentPage > currentLevel->getTotal() ? currentLevel->getTotal() : (PAGECOLUMCOUNT*PAGEROWCOUNT)*currentPage);

    float starty = m_pScrollView->getContentSize().height;
    for (int i= (PAGECOLUMCOUNT*PAGEROWCOUNT)*(currentPage-1);  i < (PAGECOLUMCOUNT*PAGEROWCOUNT)*(currentPage-1)+count; ++i) {
        LevelItemNode* node  = LevelItemNode::createWithIndex(currentLevel->getTitle(), i, currentLevel->getCompleteIndex(), currentLevel->getStartIndex()+i);
        node->ignoreAnchorPointForPosition(false);
        node->setAnchorPoint(Vec2(0, 1.0));
        if (i % 3 == 0) {
            node->setPosition(Vec2(scrollviewXseperate, starty));

        }else if (i % 3 == 1) {
            node->setPosition(Vec2(scrollviewXseperate*2 + LevelItemWidth, starty));

        }else if (i % 3 == 2) {
            node->setPosition(Vec2(scrollviewXseperate*3 + LevelItemWidth*2, starty));
            starty -= LevelItemHeight + scrollviewYseperate;
        }
        node->setCallback(CC_CALLBACK_1(LevelDetail::onChooseoneLevelItem, this));
        allmenuItems.pushBack(node);
    }
    Menu* itemMenu = Menu::createWithArray(allmenuItems);
    itemMenu->setPosition(Vec2::ZERO);
    m_pScrollView->setMenu(itemMenu);
    m_pScrollView->setContentOffset(Vec2(0, m_pScrollView->getViewSize().height - m_pScrollView->getContentSize().height));
}

void LevelDetail::onChooseoneLevelItem(cocos2d::Ref *pSener) {
//    log("ite clicked");
    SoundPlayer::getInstance()->playclickeffect();
    LevelItemNode* pNode  = dynamic_cast<LevelItemNode*>(pSener);
    SceneManager::getInstance()->gotoPlayGame(pNode->getItemDescripe());
}

void LevelDetail::onBackKeyClicked()
{
    SceneManager::getInstance()->gotoHomeLayer();

}

