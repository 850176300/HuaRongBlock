//
//  PlayGameLayer.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#include "PlayGameLayer.h"
#include "CocosHelper.h"
#include "HeadNode.h"
#include "SceneManager.h"
#include "TipLayer.h"
#include "DBManager.h"
#include "ProductSolution.h"
#include "UserDefaultManager.h"
#include "KKLeaderboardAPI.h"
#include "KKShare.h"
#include "KKSystemFunction.h"
#include "GameTipLayer.h"

#define TipDiamondCount 1
Scene* PlayGameLayer::scene(LevelDescripe* descripe){
    Scene* scene = Scene::create();
    PlayGameLayer* layer = PlayGameLayer::createWith(descripe);
    scene->addChild(layer);
    return scene;
}
PlayGameLayer* PlayGameLayer::createWith(LevelDescripe *descripe) {
    PlayGameLayer* pRet = new PlayGameLayer();
    if (pRet && pRet->initWith(descripe)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool PlayGameLayer::initWith(LevelDescripe *descripe) {
    if (GameLayerBase::initWithBgFileName("gamebg.png")) {
        _currentDescripe = descripe;
        _currentDescripe->retain();
        log("===========currentdescripe %d ==========", _currentDescripe->getReferenceCount());
        createHeader();
        TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
        //待添加
        //获取这种类型的总数量
//        LevelTitle* theTitle = DBManager::getInstance()->getLevelTitleByType(_currentDescripe->getTypeName());
//        __String* titleString = __String::createWithFormat("%s(%d/%d) %s", _currentDescripe->getTypeName().c_str(), _currentDescripe->getIndexInType()+1, theTitle->getTotal(), _currentDescripe->getName().c_str());
        LanguageType nType = CCApplication::getInstance()->getCurrentLanguage();
        __String* titleString = nullptr;
        if(LanguageType::CHINESE == nType)
            titleString = __String::createWithFormat("%s",  _currentDescripe->getName().c_str());
        else
            titleString = __String::createWithFormat("Level %d",  descripe->getIndexInType()+1);
        
        
        
        Label* leveltitle = Label::createWithTTF(config2, titleString->getCString());
        leveltitle->setAnchorPoint(Vec2(0 , 0.5f));
        float blankSize = STVisibleRect::getPointOfSceneLeftUp().y - HeadNode::getHeadNodeHeight() - GridHeight;
        leveltitle->setPosition(Vec2(STVisibleRect::getOriginalPoint().x+ (STVisibleRect::getGlvisibleSize().width - GridWidth - ButtonSize) / 3.0, STVisibleRect::getPointOfSceneLeftUp().y - HeadNode::getHeadNodeHeight() - blankSize /2.0));
        addChild(leveltitle);
        
        movefield = MoveField::createwithStirng(_currentDescripe->getLevelString(), _currentDescripe->getRedoString(), _currentDescripe->getUndoString());
        movefield->setAnchorPoint(Vec2(0, 0));
        movefield->setPosition(Vec2(STVisibleRect::getOriginalPoint().x+ (STVisibleRect::getGlvisibleSize().width - GridWidth - ButtonSize) / 3.0, STVisibleRect::getOriginalPoint().y));
        addChild(movefield);
        movefield->setMoveFieldDelegate(this);
        createButtonLayer();
        return true;
    }
    return false;
}

void PlayGameLayer::onEnter(){
    
    GameLayerBase::onEnter();
    coinCount->setString(convertIntToString(UserDefaultManager::getDiamond()));
    
    if (UserDefaultManager::getisFirstTime() == true) {
        UserDefaultManager::setisFirstTime(false);
        GameTipLayer* layer = GameTipLayer::create();
        this->addChild(layer, 300);
    }
}

void PlayGameLayer::createHeader(){
    _scoreBoard = ScoreBoard::create();
    _scoreBoard->setBestStep(_currentDescripe->getBestStep());
    
    ControlButton* backButton = CocosHelper::getButton("back_btn.png", "back_btn.png");
    backButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PlayGameLayer::backButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    backButton->setUserData((void*)"back");
    
    ControlButton* shopButton = CocosHelper::getButton("shop_btn.png", "shop_btn.png");
    shopButton->addTargetWithActionForControlEvents(this, cccontrol_selector(PlayGameLayer::backButtonClicked), Control::EventType::TOUCH_UP_INSIDE);
    shopButton->setUserData((void*)"shop");
    __Array* itemArr = __Array::createWithCapacity(3);
    itemArr->addObject(backButton);
    itemArr->addObject(_scoreBoard);
    itemArr->addObject(shopButton);
    HeadNode* header = HeadNode::createWithItems(itemArr);
    header->showInNode(this);
}

void PlayGameLayer::backButtonClicked(cocos2d::Ref *pSender, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    ControlButton* button = dynamic_cast<ControlButton*>(pSender);
    char* buf = (char *)(button->getUserData());
    string bufString(buf);
    if (bufString.compare("back") == 0) {
        Director::getInstance()->popScene();
    }else if (bufString.compare("shop") == 0) {
        SceneManager::getInstance()->gotoShopLayer();

    }
}

void PlayGameLayer::createButtonLayer(){
//    LayerColor* layer = LayerColor::create(Color4B(255, 0, 0, 150));
    Layer* layer = Layer::create();
    layer->setContentSize(Size(72, PerGridWidth*5));
    layer->ignoreAnchorPointForPosition(false);
    layer->setAnchorPoint(Vec2(1.0, 1.0));
    layer->setPosition(Vec2(STVisibleRect::getPointOfSceneRightUp().x - (STVisibleRect::getGlvisibleSize().width - GridWidth - ButtonSize) / 3.0, movefield->getPositionY() + GridHeight));
    addChild(layer, 2);
    stringstream soundBG;
    if (SoundPlayer::getInstance()->isMusicOpen() ){
        soundBG<<"game_sound_on.png";
    }else {
        soundBG<<"game_sound_off.png";
    }
    ControlButton* soundBtn = CocosHelper::getButton(soundBG.str().c_str(), soundBG.str().c_str());
    soundBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(PlayGameLayer::soundBtnClick), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    soundBtn->setAnchorPoint(Vec2(0.5, 0));
    soundBtn->setPosition(Vec2(layer->getContentSize().width/2.0, 10));
    layer->addChild(soundBtn);
    
    undo = CocosHelper::getButton("back_up.png", "back_down.png");
    undo->addTargetWithActionForControlEvents(movefield, cccontrol_selector(MoveField::onplayerOperationClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    undo->setAnchorPoint(Vec2(0.5f, 0));
    undo->setPosition(Vec2(layer->getContentSize().width/2.0, soundBtn->getPositionY()+soundBtn->getContentSize().height + ButtonDesperate));
    undo->setUserObject(__String::create("undo"));
    layer->addChild(undo, 1);
    if (_currentDescripe->getUndoString().size() < 5) {
        undo->setEnabled(false);
    }
    
    redo = CocosHelper::getButton("next_step_u.png","next_step_d.png");
    redo->addTargetWithActionForControlEvents(movefield, cccontrol_selector(MoveField::onplayerOperationClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    redo->setAnchorPoint(Vec2(0.5f, 0));
    redo->setPosition(Vec2(layer->getContentSize().width/2.0, undo->getPositionY()+undo->getContentSize().height + ButtonDesperate));
    redo->setUserObject(__String::create("redo"));
    layer->addChild(redo, 1);
    if (_currentDescripe->getRedoString().size() < 5) {
        redo->setEnabled(false);
    }
    
    ControlButton* reset = CocosHelper::getButton("reset_u.png","reset_d.png");
    reset->addTargetWithActionForControlEvents(this, cccontrol_selector(PlayGameLayer::resetBtnClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    reset->setAnchorPoint(Vec2(0.5f, 0));
    reset->setPosition(Vec2(layer->getContentSize().width/2.0, redo->getPositionY()+redo->getContentSize().height + ButtonDesperate));
    reset->setUserObject(__String::create("reset"));
    layer->addChild(reset, 1);
    
    
    ControlButton* coin = CocosHelper::getButton("coin.png", "coin.png");
    coin->addTargetWithActionForControlEvents(this, cccontrol_selector(PlayGameLayer::coinBtnClick), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    coin->setAnchorPoint(Vec2(0.5, 1.0f));
    coin->setPosition(Vec2(layer->getContentSize().width/2.0, layer->getContentSize().height - 20));
    
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    coinCount = Label::createWithTTF(config2, convertIntToString(UserDefaultManager::getDiamond()));
    coinCount->setAnchorPoint(Vec2(0.5f, 1.0));
    coinCount->setPosition(coin->getPosition() + Vec2(0, -coin->getContentSize().height - 15));
    layer->addChild(coinCount, 1);
    layer->addChild(coin, 1);

}

void PlayGameLayer::onRedoChanged(bool addOrSub) {
//    SoundPlayer::getInstance()->playclickeffect();
    redo->setEnabled(addOrSub);
}

void PlayGameLayer::onUndoChanged(bool addOrSub) {
//    SoundPlayer::getInstance()->playclickeffect();
    undo->setEnabled(addOrSub);
}

void PlayGameLayer::onAddStep(int stepCount) {
    _scoreBoard->updateStepCount(stepCount);
}

void PlayGameLayer::soundBtnClick(cocos2d::Ref *pSender, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    ControlButton* button = dynamic_cast<ControlButton*>(pSender);
    SoundPlayer::getInstance()->switchVolume();
    stringstream soundBG;
    if (SoundPlayer::getInstance()->isMusicOpen() ){
        soundBG<<"game_sound_on.png";
    }else {
        soundBG<<"game_sound_off.png";
    }
    Scale9Sprite* btnDown = Scale9Sprite::create(soundBG.str().c_str());
    Scale9Sprite* btnNormal = Scale9Sprite::create(soundBG.str().c_str());
    button->setBackgroundSpriteForState(btnNormal, cocos2d::extension::Control::State::NORMAL);
    button->setBackgroundSpriteForState(btnDown, cocos2d::extension::Control::State::HIGH_LIGHTED);
    log("sound button clicked");
    

}

void PlayGameLayer::coinBtnClick(cocos2d::Ref *pSender, Control::EventType type) {

    SoundPlayer::getInstance()->playclickeffect();
    if (UserDefaultManager::getDiamond() < TipDiamondCount) {
        ConfirmDialog* dialog = ConfirmDialog::create();
        //    dialog->setTitleText("提示一个字");
        dialog->setDelegate(this);
        dialog->setTitleText(getLocalString("提示"));
//        dialog->setContentText(getLocalString("钻石不足，您可以到商店购买"));
        dialog->setContentText(getLocalString("钻石不足，您观看视频获取钻石"));
        dialog->show(this);
        dialog->setTag(kTipToVedio);
    }else {
        ConfirmDialog* dialog = ConfirmDialog::create();
        //    dialog->setTitleText("提示一个字");
        dialog->setDelegate(this);
        dialog->setTitleText(getLocalString("提示"));
        dialog->setContentText(
                               getLocalString(__String::createWithFormat("花费%d个钻石获取提示？", TipDiamondCount)->getCString()));
        dialog->show(this);
        dialog->setTag(kTipGame);
    }
}

void PlayGameLayer::resetBtnClicked(cocos2d::Ref *pRef, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    ConfirmDialog* dialog = ConfirmDialog::create();
    //    dialog->setTitleText("提示一个字");
    dialog->setDelegate(this);
    dialog->setTitleText(getLocalString("提示"));
    dialog->setContentText(getLocalString("是否重新开始游戏？"));
    dialog->show(this);
    dialog->setTag(kResetTip);
}

void PlayGameLayer::onFinishedTheGame(){
    SoundPlayer::getInstance()->playWellDoneEffect();
    if (_currentDescripe->getStar() == 0){
        LevelTitle* theTitle = DBManager::getInstance()->getLevelTitleByType(_currentDescripe->getTypeName());
        int completeIndex = theTitle->getCompleteIndex();
        if (completeIndex + 1 <= theTitle->getTotal()) {
            theTitle->setCompleteIndex(completeIndex+1);
            DBManager::getInstance()->updateAllTypes();
        }
        
    }
    
    int currentStep = _scoreBoard->getstepCounts();
    log("the currentStep is %d", currentStep);
    int star = getStarBysteps(currentStep);
    WellDoneLayer* layer = WellDoneLayer::create(star);
    layer->setAbstact(this);
    layer->showInNode(this);
    if (_currentDescripe->getBestStep() == 0) {
        _currentDescripe->setBestStep(currentStep);
    }else{
        if (currentStep < _currentDescripe->getBestStep() ) {
            _currentDescripe->setBestStep(currentStep);
        }
    }
    UserDefaultManager::setStarsCount(star - _currentDescripe->getStar() > 0 ? star - _currentDescripe->getStar() : 0);
    if (_currentDescripe->getStar() == 0) {
        UserDefaultManager::addQuestionCount();
        _currentDescripe->setStar(star);
    }else {
        if (_currentDescripe->getStar() < star) {
            _currentDescripe->setStar(star);
        }
    }
    
    _currentDescripe->updateToSplite();

    KKLeaderboardAPI* api = new KKLeaderboardAPI();
    KKPlayer* player = new KKPlayer();
    KKScore* score = new KKScore();

    
    player->setName(KKSystemFunction::getDeviceName());
    player->setUDID(KKShare::getUDID());
    score->setScore(UserDefaultManager::getStarsCount()*1000+UserDefaultManager::getQuestionCount());
    api->uploadScoreToLeaderboard(6, player, score);
    if (UserDefaultManager::getQuestionCount() >= UserDefaultManager::getNumofQuestion()) {
        
    }
    api->autorelease();
    player->autorelease();
    score->autorelease();
   
}

int PlayGameLayer::getStarBysteps(int step) {
    int bestStep = _currentDescripe->getLeastStep();
    float delta = bestStep*0.1;
    if (ceil(delta) < 3) {
        delta = 3;
    }else {
        delta = ceil(delta);
    }
    if (step <= bestStep + delta) {
        return 3;
    }else if (step > bestStep+delta && step <= bestStep+(int)delta*2){
        return 2;
    }else {
        return 1;
    }
}

#pragma mark welldone delegate
void PlayGameLayer::onNextBtnClicked(){
    LevelTitle* theTitle = DBManager::getInstance()->getLevelTitleByType(_currentDescripe->getTypeName());
    int index = _currentDescripe->getIndexInType();
    if (index + 1 >= theTitle->getTotal()) {
        Director::getInstance()->popScene();
    }else {
        
        LevelDescripe* theLevel = DBManager::getInstance()->getQuestionAtIndex(_currentDescripe->getIndex() + 1);
        theLevel->setIndexInType(index + 1);
        Scene* pScene = PlayGameLayer::scene(theLevel);
        TransitionFade* fade = TransitionFade::create(1.0, pScene);
        Director::getInstance()->replaceScene(fade);
    }
    
}

void PlayGameLayer::onConfirmed(ConfirmDialog *target, bool yesOrNo) {
    if (yesOrNo == 0) {
        return;
    }
    if (target->getTag() == kTipGame) {
        UserDefaultManager::addDiamond(-1*TipDiamondCount);
        coinCount->setString(convertIntToString(UserDefaultManager::getDiamond()));
        string solution = ProductSolutioin::getInstance()->createSolution(movefield->returncurrentState());
        log("solution is %s", solution.c_str());
        if (solution.find("no solution") == string::npos) {
            TipLayer* tipLayer = TipLayer::createWithStrings(movefield->returncurrentState(), solution);
            tipLayer->showInNode(this);
        }
    }else if (target->getTag() == kTipToShop) {
        SceneManager::getInstance()->gotoShopLayer();
    }else if (target->getTag() == kTipToVedio) {
        SceneManager::getInstance()->gotoVedioLayer();
    }else if (target->getTag() == kResetTip) {
        movefield->resetTheGame();
    }
}

