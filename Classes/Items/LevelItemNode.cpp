//
//  LevelItemNode.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-11.
//
//

#include "LevelItemNode.h"
#include "DBManager.h"

LevelItemNode* LevelItemNode::createWithIndex(string type,int index, int currentCompl, int indexinSql){
    LevelItemNode* pRet = new LevelItemNode();
    if (pRet && pRet->initWithIndex(type, index, currentCompl, indexinSql)){
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool LevelItemNode::initWithIndex(string type,int index, int currentCompl, int indexinSql) {
    if (MenuItem::init()) {
        
        auto sprite1 = Sprite::create("item_bg.png");
        auto sprite2 = Sprite::create("item_bg3.png");
        auto sprite3 = Sprite::create("item_bg2.png");
        if (index > currentCompl) {
            auto lock = Sprite::create("lock.png");
            lock->setPosition(Vec2(sprite1->getContentSize().width/2.0, sprite1->getContentSize().height/2.0));
            sprite2->addChild(lock);
            setNormalImage(sprite2);
            setSelectedImage(sprite1);
            setEnabled(false);
        }else {
            fillTheDescripe(index,indexinSql, type);
            if (_itemDescripe->getStar() == 3) {
                setNormalImage(sprite3);
                setSelectedImage(sprite2);
            }else {
                setNormalImage(sprite1);
                setSelectedImage(sprite2);
            }
            setEnabled(true);
            TTFConfig config2(FONTNAME,45,GlyphCollection::DYNAMIC,nullptr,true);
            __String* name = __String::createWithFormat("%d", index+1);
            Label* nameLabel = Label::createWithTTF(config2, name->getCString());
            float labelWidth = nameLabel->getContentSize().width;
            if (labelWidth > getContentSize().width - 10) {
                nameLabel->setScale((getContentSize().width - 10)*1.0/labelWidth);
            }
            nameLabel->setPosition(Vec2(getContentSize().width/2.0, getContentSize().height/2.0));
            addChild(nameLabel, 2);
            addstars();
        }

        
        return true;
    }
    return false;
}


void LevelItemNode::fillTheDescripe(int indexinType,int index, string type){
    _itemDescripe = DBManager::getInstance()->getQuestionAtIndex(index);
    _itemDescripe->retain();
    _itemDescripe->setIndexInType(indexinType);
}

void LevelItemNode::addstars(){
    auto star1 = Sprite::create("gamestarunlight.png");
    auto star2 = Sprite::create("gamestarunlight.png");
    auto star3 = Sprite::create("gamestarunlight.png");
    
    star2->setAnchorPoint(Vec2(0.5f, 0));
    star1->setAnchorPoint(Vec2(1.0f, 0));
    star3->setAnchorPoint(Vec2(0, 0));
    
    star2->setPosition(Vec2(getContentSize().width/2.0, 8));
    star1->setPosition(Vec2(star2->getPositionX() - star2->getContentSize().width/2.0 - 15, star2->getPositionY()));
    star3->setPosition(Vec2(star2->getPositionX() + star2->getContentSize().width/2.0 + 15, star2->getPositionY()));
    
    addChild(star2);
    addChild(star1);
    addChild(star3);
    
    if (_itemDescripe->getStar() == 1) {
        star1->setTexture(Sprite::create("gamestarlight.png")->getTexture());
    }else if (_itemDescripe->getStar() == 2){
        star1->setTexture(Sprite::create("gamestarlight.png")->getTexture());
        star2->setTexture(Sprite::create("gamestarlight.png")->getTexture());
    }else if (_itemDescripe->getStar() == 3){
        star1->setTexture(Sprite::create("gamestarlight.png")->getTexture());
        star2->setTexture(Sprite::create("gamestarlight.png")->getTexture());
        star3->setTexture(Sprite::create("gamestarlight.png")->getTexture());
    }
}

LevelDescripe* LevelItemNode::getItemDescripe(){
    return _itemDescripe;
}
