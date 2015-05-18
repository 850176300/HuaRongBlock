//
//  BaseDialog.cpp
//  BrainFootball
//
//  Created by tomwey on 6/20/14.
//
//

#include "BaseDialog.h"
#include "SuperGlobal.h"
BaseDialog::~BaseDialog(){

}


BaseDialog::BaseDialog(){
    
}

BaseDialog* BaseDialog::create()
{
    BaseDialog* dialog = new BaseDialog();
    dialog->autorelease();
    dialog->init();
    return dialog;
}

bool BaseDialog::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 150)) ) {
        return false;
    }
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    setSwallowsTouches(true);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    m_pContentLayer = CCLayer::create();
    m_pContentLayer->ignoreAnchorPointForPosition(false);
    m_pContentLayer->setAnchorPoint(Point(.5, .5));
    m_pContentLayer->setPosition(Point(visibleSize.width * .5,
                                         visibleSize.height * .5));
    this->addChild(m_pContentLayer);
    
    m_pContentLayer->setScale(0.1);
    
    // 背景
    m_pBg = Sprite::create("tiptitle.png");
    m_pContentLayer->addChild(m_pBg);
    m_pBg->setPosition(Point(m_pContentLayer->getContentSize().width/2,
                            m_pContentLayer->getContentSize().height/2));
    
    
    // 标题
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    m_pTitleLabel = Label::createWithTTF(config2, getLocalString("提示"));
    m_pTitleLabel->setColor(Color3B::GRAY);
    m_pBg->addChild(m_pTitleLabel);
    m_pTitleLabel->setAnchorPoint(Point(.5, 1.0));
    m_pTitleLabel->setPosition(Point(m_pBg->getContentSize().width/2,
                                       m_pBg->getContentSize().height - 50));
    m_pTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    m_pTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
//    m_pTitleLabel->setColor(Color3B(69, 153, 43));
    m_pTitleLabel->setVisible(true);
    return true;
}

void BaseDialog::show(Node* parent, bool animated)
{
    // 隐藏广告
    setBannerVisible(false);
    
    if ( !this->getParent() ) {
        parent->addChild(this, 200);
    }
    
    if ( !animated ) {
        m_pContentLayer->setScale(1.0);
    } else {
        FiniteTimeAction* a1 = ScaleTo::create(.2, .5);
        FiniteTimeAction* a2 = ScaleTo::create(.15, 1.2);
        FiniteTimeAction* a3 = ScaleTo::create(.11, 0.9);
        FiniteTimeAction* a4 = ScaleTo::create(.09, 1.0);
        m_pContentLayer->runAction(CCSequence::create(a1,a2,a3,a4,NULL));
    }
}

void BaseDialog::onEnter(){
    KeyEventDispatcher::getInstance()->addEventDelegate(this);
    LayerColor::onEnter();
    
}

void BaseDialog::onExit(){
        KeyEventDispatcher::getInstance()->removeDelegate(this);
    LayerColor::onExit();
}

void BaseDialog::setTitleText(const char *title)
{
    if ( title && m_pTitleLabel )
        m_pTitleLabel->setString(title);
        
}

void BaseDialog::setContentText(const char *content)
{
    if ( content && m_pContentLabel )
        m_pContentLabel->setString(content);
}

const Label* BaseDialog::getTitleLabel() const
{
    return m_pTitleLabel;
}

bool BaseDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    return true;
}


void BaseDialog::onBackKeyClicked(){
    
}