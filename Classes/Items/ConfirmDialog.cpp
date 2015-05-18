//
//  ConfirmDialog.cpp
//  BrainFootball
//
//  Created by tomwey on 6/20/14.
//
//

#include "ConfirmDialog.h"
#include "SuperGlobal.h"
ConfirmDialog* ConfirmDialog::create(bool isOneBtn)
{
    ConfirmDialog* dialog = new ConfirmDialog();
    dialog->autorelease();
    dialog->init(isOneBtn);
    return dialog;
}

bool ConfirmDialog::init(bool isOneBtn)
{
    if ( !BaseDialog::init() ) {
        return false;
    }
    
    /* 添加按钮 */
    if (isOneBtn) {
        
        // OK
        MenuItemSprite* ok = getMenuItemSprite(getLocalString("game_btn_notice.png"));
        ok->setCallback(CC_CALLBACK_1(ConfirmDialog::menuCallback, this));
        ok->setAnchorPoint(Point(0.5, 0));
        ok->setPosition(Point(m_pBg->getContentSize().width*0.5, 30));
        ok->setTag(101);
        
//        CCLabelTTF* okLabel = CCLabelTTF::create("好的", "Arial Rounded MT Bold", 40);
//        ok->addChild(okLabel);
//        okLabel->setColor(ccc3(43, 169, 45));
//        okLabel->setPosition(CCPoint(ok->getContentSize().width * .5,
//                                     ok->getContentSize().height * .5 + 3));
        
        m_pCancelItem = ok;
        m_pMenu = CCMenu::create(ok, NULL);
        m_pBg->addChild(m_pMenu);
        m_pMenu->setPosition(Vec2::ZERO);
    }else{
        
        // No
        MenuItemSprite* no = getMenuItemSprite(getLocalString("btn_alert_no_normal.png"));
        no->setCallback(CC_CALLBACK_1(ConfirmDialog::menuCallback, this));
        no->setTag(101);
        
//        CCLabelTTF* noLabel = CCLabelTTF::create("否", "Arial Rounded MT Bold", 40);
//        no->addChild(noLabel);
//        noLabel->setPosition(CCPoint(no->getContentSize().width * .5,
//                                     no->getContentSize().height * .5 + 3));
        
        // Yes
        MenuItemSprite* yes = getMenuItemSprite(getLocalString("game_btn_notice.png"));
        yes->setCallback(CC_CALLBACK_1(ConfirmDialog::menuCallback, this));
        yes->setTag(100);
        
//        CCLabelTTF* yesLabel = CCLabelTTF::create("是", "Arial Rounded MT Bold", 40);
//        yes->addChild(yesLabel);
//        yesLabel->setColor(ccc3(43, 169, 45));
//        yesLabel->setPosition(CCPoint(yes->getContentSize().width * .5,
//                                      yes->getContentSize().height * .5 + 3));
        
        no->setAnchorPoint(Point(1.0, 0));
        yes->setAnchorPoint(Point(0, 0));
        yes->setPosition(Point(40, 50));
        no->setPosition(Point(m_pBg->getContentSize().width - yes->getPositionX(),
                                 yes->getPositionY()));
        m_pMenu = CCMenu::create(no, yes, NULL);
        m_pBg->addChild(m_pMenu);
        m_pMenu->setPosition(Vec2::ZERO);
        
        m_pOKItem = yes;
        m_pCancelItem = no;
    }
    TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
    /* 添加内容显示 */
    m_pContentLabel = Label::createWithTTF(config2, "");
    m_pContentLabel->setDimensions(m_pBg->getContentSize().width * .9,
                                          m_pBg->getContentSize().height * .55);
    m_pContentLabel->setAnchorPoint(Point(.5, 1.0));
    m_pContentLabel->setPosition(Point(m_pBg->getContentSize().width * .5,
                                         m_pBg->getContentSize().height - 120));
    m_pBg->addChild(m_pContentLabel);
    m_pContentLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    m_pContentLabel->setVerticalAlignment(TextVAlignment::CENTER);
    m_pContentLabel->setColor(Color3B::GRAY);
    
    return true;
}


void ConfirmDialog::setDelegate(ConfirmDialogDelegate *delegate)
{
    m_pDelegate = delegate;
}

void ConfirmDialog::setCancel(cocos2d::Sprite *node, cocos2d::Sprite *selectNode)
{
    m_pCancelItem->setNormalImage(node);
    m_pCancelItem->setSelectedImage(selectNode);
    
}

void ConfirmDialog::setOK(cocos2d::Sprite *node,cocos2d::Sprite *selectNode)
{
    m_pOKItem->setNormalImage(node);
    m_pOKItem->setSelectedImage(selectNode);
}
void ConfirmDialog::menuCallback(cocos2d::Ref *pRef)
{
    Node* sender = dynamic_cast<Node*>(pRef);
    m_bConfirmed = sender->getTag() == 100 ? true : false;
    m_pContentLayer->runAction(CCSequence::create(ScaleTo::create(.3, 0.0), CallFunc::create(std::bind(&ConfirmDialog::dismiss, this)), NULL));
    
}

void ConfirmDialog::dismiss()
{
    setBannerVisible(true);
    if ( m_pDelegate ) {
        m_pDelegate->onConfirmed(this, m_bConfirmed);
    }
    this->getParent()->removeChild(this, true);
}


MenuItemSprite* ConfirmDialog::getMenuItemSprite(const string& imageName){
    Sprite* sprite1 = Sprite::create(imageName);
    Sprite* sprite2 = Sprite::create(imageName);
    sprite2->setColor(Color3B::GRAY);
    MenuItemSprite* item = MenuItemSprite::create(sprite1, sprite2);
    return item;
}

void ConfirmDialog::onBackKeyClicked() {
    BaseDialog::onBackKeyClicked();
    log("让对话框消失");
    dismiss();
}

