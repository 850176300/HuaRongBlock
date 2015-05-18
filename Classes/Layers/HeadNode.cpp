//
//  HeadNode.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#include "HeadNode.h"
#include "STVisibleRect.h"
USING_NS_ST;

#define XSeperate 60 //边框间距，自定义
float HeadNode::getHeadNodeHeight(){
    Sprite* bg = Sprite::create("navigation.png");
    return bg->getContentSize().height;//*STVisibleRect::getRealDesignScale();
}

HeadNode* HeadNode::createWithItems(cocos2d::__Array *items) {
    HeadNode* pRet = new HeadNode();
    if (pRet && pRet->initWithArray(items)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool HeadNode::initWithArray(cocos2d::__Array *items) {
    if (LayerColor::init()) {
        ignoreAnchorPointForPosition(false);
        
        Sprite* bg = Sprite::create("navigation.png");
        bg->setAnchorPoint(Vec2(0.5f, 1.0f));
        bg->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneRightUp().y));
        addChild(bg, 0);
        
        
        float totalWidth = 0;
        Ref* _obj;
        CCARRAY_FOREACH(items, _obj){
            Node* pNode = dynamic_cast<Node*>(_obj);
            totalWidth += pNode->getContentSize().width;
        };
        float deltaSeperate = (bg->getContentSize().width - XSeperate*2 - totalWidth) /(items->count() <= 3 ? 2.0 : 1.0*(items->count()-1));
        float itemx = XSeperate;
        int count = 0;
        CCARRAY_FOREACH(items, _obj){
            Node* pNode = dynamic_cast<Node*>(_obj);
            pNode->ignoreAnchorPointForPosition(false);
            pNode->setAnchorPoint(Vec2(0, 0.5f));
            pNode->setPosition(Vec2(itemx, bg->getContentSize().height/2.0));
            itemx += pNode->getContentSize().width + deltaSeperate;
            pNode->setTag(count++);
            bg->addChild(pNode);
        };
        if (items->count() == 2) {
            if (bg->getChildByTag(1)) {
                bg->getChildByTag(1)->setAnchorPoint(Vec2(0.5f, 0.5f));
                bg->getChildByTag(1)->setPositionX(bg->getContentSize().width/2.0);
            }
        }
        if (items->count() == 2 || items->count() == 3) {
            if (bg->getChildByTag(0)) {
                bg->getChildByTag(0)->setPositionX(bg->getChildByTag(0)->getPositionX() - 30);
            }
        }
//        bg->setScale(STVisibleRect::getRealDesignScale());
        return true;
    }
    return false;
}

void HeadNode::showInNode(cocos2d::Node *parent) {
    setAnchorPoint(Vec2(0.5f, 1.0f));
    setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y));
    parent->addChild(this, 0);
}

