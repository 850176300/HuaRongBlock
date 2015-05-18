//
//  LeaderboardLayer.cpp
//  HuaRongBlock
//
//  Created by liuwei on 14-12-14.
//
//

#include "LeaderboardLayer.h"
#include "CocosHelper.h"
#include "HeadNode.h"
#include "SuperGlobal.h"
#include "KKSystemFunction.h"
#define TITLE1X 50
#define TITLE2X 160
#define TITLE3X 255
#define TITLE4X 450



RankItem* RankItem::createWith(int rank, int score, const string &name, bool isSlef){
    RankItem* pRet = new RankItem();
    if (pRet && pRet->init(rank, score, name, isSlef)) {
        pRet->autorelease();
        return pRet;
    }else{
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool RankItem::init(int rank, int score, const string &name, bool isSlef) {
    if (Widget::init()) {
        Sprite* bg = NULL;
        if (isSlef) {
            bg = Sprite::create("rank_bg2.png");
        }else {
            bg = Sprite::create("rank_bg.png");
        }
        setContentSize(bg->getContentSize());
        bg->setAnchorPoint(Vec2::ZERO);
        bg->setPosition(Vec2::ZERO);
        addChild(bg);
        
        TTFConfig config2(FONTNAME,30,GlyphCollection::DYNAMIC,nullptr,true);
        Label* lrank = Label::createWithTTF(config2, convertIntToString(rank));
        lrank->setPosition(Vec2(TITLE1X-10, bg->getContentSize().height/2.0));
        addChild(lrank);
        
        Label* lscore1 = Label::createWithTTF(config2, convertIntToString(score/1000));
        lscore1->setPosition(Vec2(TITLE3X-25, bg->getContentSize().height/2.0));
        addChild(lscore1);
        
        Label* lscore2 = Label::createWithTTF(config2, convertIntToString(score%1000));
        lscore2->setPosition(Vec2(TITLE2X-18, bg->getContentSize().height/2.0));
        addChild(lscore2);
        
        Label* lname = Label::createWithTTF(config2, name);
        if (lname->getContentSize().width > 300) {
            lname->setScale(400.0/lname->getContentSize().width);
            lname->setAnchorPoint(Vec2(1.0, 0.5f));
            lname->setPosition(Vec2(bg->getContentSize().width - 20, bg->getContentSize().height/2.0));

        }else {
            lname->setPosition(Vec2(TITLE4X, bg->getContentSize().height/2.0));
        }
        addChild(lname);
        
        return true;
    }
    return false;
}





Scene* Leaderboard::scene() {
    Scene* scene = Scene::create();
    
    Leaderboard* layer = Leaderboard::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool Leaderboard::init(){
    if (GameLayerBase::initWithBgFileName("gamebg.png", false)) {
        api = new KKLeaderboardAPI();
        api->setDelegate(this);
        
        createHeader();
        createAllTitiles();
        backButton->setEnabled(false);
        loadData(6);
        
        return true;
    }
    return false;
}


void Leaderboard::createHeader(){
    backButton = CocosHelper::getButton("back_btn.png", "back_btn.png");
    backButton->addTargetWithActionForControlEvents(this, cccontrol_selector(Leaderboard::backButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    Label *label1 = Label::createWithTTF(config2, getLocalString("排行榜"));
    //    label1->setColor(Color3B(255, 255, 255));
    label1->setColor(Color3B::GRAY);
    
    loadingImage = Sprite::create("loading/image1.png");
    
    __Array* items = __Array::createWithCapacity(2);
    items->addObject(backButton);
    items->addObject(label1);
    items->addObject(loadingImage);
    
    HeadNode* header = HeadNode::createWithItems(items);
    header->showInNode(this);
}

void Leaderboard::createAllTitiles(){
    frameBg = Sprite::create("big_item_bg.png");
    frameBg->setPosition(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+(STVisibleRect::getGlvisibleSize().height - HeadNode::getHeadNodeHeight())/2.0);
    frameBg->setColor(Color3B::WHITE);
    addChild(frameBg);
    
    TTFConfig config2(FONTNAME,30,GlyphCollection::DYNAMIC,nullptr,true);
    Label* title1 = Label::createWithTTF(config2, getLocalString("名次"));
    Label* title2 = Label::createWithTTF(config2, getLocalString("完成关卡"));
    Sprite* title3 = Sprite::create("star1.png");
    Label* title4 = Label::createWithTTF(config2, getLocalString("英雄"));
    
    title1->setAnchorPoint(Vec2(0.5f, 1.0));
    title1->setPosition(Vec2(TITLE1X, frameBg->getContentSize().height-25));
    title2->setAnchorPoint(Vec2(0.5f, 1.0));
    title2->setPosition(Vec2(TITLE2X, frameBg->getContentSize().height-25));
    title3->setAnchorPoint(Vec2(0.5f, 1.0));
    title3->setPosition(Vec2(TITLE3X, frameBg->getContentSize().height-15));
    title4->setAnchorPoint(Vec2(0.5f, 1.0));
    title4->setPosition(Vec2(TITLE4X, frameBg->getContentSize().height-25));
    
    title1->setColor(Color3B::GRAY);
    title2->setColor(Color3B::GRAY);
    title4->setColor(Color3B::GRAY);
    frameBg->addChild(title1);
    frameBg->addChild(title2);
    frameBg->addChild(title3);
    frameBg->addChild(title4);
    
    
    TTFConfig tconfig(FONTNAME,50,GlyphCollection::DYNAMIC,nullptr,true);
    centerLabel = Label::createWithTTF(tconfig, getLocalString("加载数据......"));
    centerLabel->setPosition(Vec2(frameBg->getContentSize().width/2.0, frameBg->getContentSize().height/2.0));
    centerLabel->setColor(Color3B::GRAY);
    frameBg->addChild(centerLabel);
}

void Leaderboard::backButtonClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    Director::getInstance()->popScene();
}

void Leaderboard::runloadingAnimate(){
    Animation* pAnimation = Animation::create();
    for (int i = 0; i < 11; ++i) {
        char filename[128];
        sprintf(filename, "loading/image%d.png", i + 1);
        pAnimation->addSpriteFrameWithFile(filename);
    }
    pAnimation->setDelayPerUnit(0.1);
    pAnimation->setLoops(-1);
    Animate* animate = Animate::create(pAnimation);
    loadingImage->runAction(animate);
}

void Leaderboard::loadData(unsigned int dataType)
{
    runloadingAnimate();
    api->setTag(dataType);
    api->requestScoresForLeaderboard(dataType);
}

void Leaderboard::onLoadedSuccessfully(cocos2d::Ref *result, kRequestResourceType type) {
    loadingImage->stopAllActions();
    loadingImage->setVisible(false);
    
    log("数据加载成功");
    __Dictionary* dict = dynamic_cast<__Dictionary*>(result);
    __Array* array = dynamic_cast<__Array*>(dict->objectForKey("scores"));
    
    if (array->count() <= 0) {
        centerLabel->setString(getLocalString("暂时没有数据!"));
    }else {
        
        
        centerLabel->removeFromParent();
        ui::ScrollView* scoreScorllview = ui::ScrollView::create();
        scoreScorllview->setContentSize(Size(520, frameBg->getContentSize().height - 65-70));
        scoreScorllview->ignoreAnchorPointForPosition(false);
        scoreScorllview->setAnchorPoint(Vec2(0.5f, 1.0f));
        scoreScorllview->setPosition(Vec2(frameBg->getContentSize().width/2.0, frameBg->getContentSize().height-60));
        scoreScorllview->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        frameBg->addChild(scoreScorllview);
        
        
        if (array->count()*65+65 > scoreScorllview->getContentSize().height) {
            scoreScorllview->setInnerContainerSize(Size(scoreScorllview->getContentSize().width, array->count()*65+65));
        }else {
            scoreScorllview->setInnerContainerSize(scoreScorllview->getContentSize() + Size(0, 65));
        }
        Size theSize = scoreScorllview->getInnerContainer()->getContentSize();
        for (int i = 0; i < (array->count() > 200 ? 200 : array->count()); ++i) {
            KKScore* theScore = dynamic_cast<KKScore*>(array->getObjectAtIndex(i));
            RankItem* item = RankItem::createWith(i+1, theScore->getScore(), theScore->getUserName());
            item->ignoreAnchorPointForPosition(false);
            item->setAnchorPoint(Vec2(0.5, 0));
            item->setPosition(Vec2(520/2.0, theSize.height - 60 - 65*i));
            scoreScorllview->addChild(item);
        }
//        if (array->count() > 200) {
            TTFConfig config2(FONTNAME,30,GlyphCollection::DYNAMIC,nullptr,true);
//            Label* tip = Label::createWithTTF(config2, getLocalString("共")+convertIntToString(array->count())+getLocalString("位玩家"));
////            tip->setDimensions(frameBg->getContentSize().width, 80);
//            tip->setAnchorPoint(Vec2(0.0f, 0.0f));
//            tip->setPosition(frameBg->getBoundingBox().getMinX(), frameBg->getBoundingBox().getMaxY()+15);
//            addChild(tip);
//        }
        
        string deviceName = KKSystemFunction::getDeviceName();
        log("本地玩家 is %s", deviceName.c_str());
        int rank = ((__Integer*)dict->objectForKey("me.rank"))->getValue();
        int score = ((__Integer*)dict->objectForKey(CCString::createWithFormat("me.score%d", api->getTag())->getCString()))->getValue();
        RankItem* selfItem = RankItem::createWith(rank, score, deviceName, true);
        selfItem->ignoreAnchorPointForPosition(false);
        selfItem->setAnchorPoint(Vec2(0.5f, 0));
        selfItem->setPosition(Vec2(frameBg->getContentSize().width/2.0, 15));
        frameBg->addChild(selfItem);
        
    }
    backButton->setEnabled(true);
}

void Leaderboard::onLoadedFailure(int errorCode) {
   
    loadingImage->stopAllActions();
    loadingImage->setVisible(false);
    centerLabel->setString(getLocalString("数据加载失败,请重试!"));
     backButton->setEnabled(true);
}

