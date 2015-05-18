//
//  LevelTitle.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-9.
//
//

#include "LevelTitleNode.h"
#include "SuperGlobal.h"

LevelTitleNode* LevelTitleNode::createWithLeveTitle(LevelTitle* title){
    LevelTitleNode* pRet = new LevelTitleNode();
    if (pRet && pRet->initWithLevelTitle(title)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool LevelTitleNode::initWithLevelTitle(LevelTitle* title) {
    string bgPath = "steps_bg1.png";
    if (title->getCompleteIndex() * 1.0 / title->getTotal() > 0.5) {
        bgPath = "steps_bg2.png";
    }
    if (MenuItemSprite::init()) {
        Sprite* normalImage = Sprite::create(bgPath);
        Sprite* selectImage = Sprite::create(bgPath);
        selectImage->setColor(Color3B::GRAY);
        setNormalImage(normalImage);
        setSelectedImage(selectImage);
        
        
        TTFConfig config2(FONTNAME,40,GlyphCollection::DYNAMIC,nullptr,true);
        
        Label *label1 = Label::createWithTTF(config2, getLocalString(title->getTitle()));
//        label1->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
        label1->setAnchorPoint(Vec2(0.0f, 0.5f));
        label1->setPosition(Vec2(15, getContentSize().height/2.0));
        addChild(label1);
        
        stringstream percent;
        percent<<(int)(100.0*title->getCompleteIndex()/title->getTotal())<<"%";
        Label *label2 = Label::createWithTTF(config2, percent.str().c_str());
//        label2->setAlignment(TextHAlignment::RIGHT, TextVAlignment::CENTER);
        label2->setAnchorPoint(Vec2(1.0f, 0.5f));
        label2->setPosition(Vec2(getContentSize().width - 15, getContentSize().height/2.0));
        addChild(label2);
        
        return true;
    }
    return false;
}


void LevelTitleNode::activate(){
    MenuItemSprite::activate();
    setEnabled(false);
    if (getParent()) {
        Menu* p_menu = (Menu*)getParent();
        p_menu->setEnabled(false);
    }
    this->scheduleOnce(schedule_selector(LevelTitleNode::setEnabledelay), 0.5f);
}

void LevelTitleNode::setEnabledelay(float dt){
    setEnabled(true);
    if (getParent()) {
        Menu* p_menu = (Menu*)getParent();
        p_menu->setEnabled(true);
    }
}



