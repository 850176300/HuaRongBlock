//
//  WellDoneLayer.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-19.
//
//

#ifndef __HuaRongStreet__WellDoneLayer__
#define __HuaRongStreet__WellDoneLayer__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class WellDoneLayerAbstact{
public:
    virtual void onNextBtnClicked() = 0;
    virtual void onSharetoWeChat() {};
    
};

class WellDoneLayer: public LayerColor{
public:
    static WellDoneLayer* create(float star);
    bool initWithStar(float star);
    void showInNode(Node* parent);
    void runAnimation();
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){return true;};
    void setAbstact(WellDoneLayerAbstact* delegate);
private:
    WellDoneLayerAbstact* pDelegate;
    float starCount;
    ProgressTimer* star1;
    ProgressTimer* star2;
    ProgressTimer* star3;
    Sprite* wellDoneTipbg;
    void onNextButtonClicked(Ref* pRef, Control::EventType type);
    void starsRunAction(ProgressTimer* star, float percent, float delaydt);
};
#endif /* defined(__HuaRongStreet__WellDoneLayer__) */
