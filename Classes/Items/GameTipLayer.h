//
//  GameTipLayer.h
//  HuaRongBlock
//
//  Created by 兵兵 on 14-12-21.
//
//

#ifndef __HuaRongBlock__GameTipLayer__
#define __HuaRongBlock__GameTipLayer__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class GameTipLayer : public LayerColor{
public:
    virtual bool init();
    CREATE_FUNC(GameTipLayer);
    
protected:
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onEnter();
    Sprite* bg;
};

#endif /* defined(__HuaRongBlock__GameTipLayer__) */
