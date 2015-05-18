//
//  GameTipLayer.cpp
//  HuaRongBlock
//
//  Created by 兵兵 on 14-12-21.
//
//

#include "GameTipLayer.h"
#include "STVisibleRect.h"
#include "SuperGlobal.h"
USING_NS_ST;
bool GameTipLayer::init(){
    if (LayerColor::initWithColor(Color4B(0, 0, 0, 255))) {
        setTouchEnabled(true);
        setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
        setSwallowsTouches(true);
        bg = Sprite::create(getLocalString("youyitix.png"));
        bg->setPosition(STVisibleRect::getCenterOfScene());
        addChild(bg);
        bg->setScale(0);
        
        return true;
    }
    return false;
}


void GameTipLayer::onEnter(){
    Layer::onEnter();
    bg->runAction(Sequence::create(ScaleTo::create(0.3f, 1.1f), ScaleTo::create(0.1f, 1.0f), NULL));
}

bool GameTipLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->runAction(Sequence::create(ScaleTo::create(0.3f, 0), CallFunc::create(std::bind(&Layer::removeFromParent, this)), NULL));
    return true;
}




