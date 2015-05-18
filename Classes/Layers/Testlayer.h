//
//  Testlayer.h
//  HuaRongBlock
//
//  Created by liuwei on 15-2-5.
//
//

#ifndef __HuaRongBlock__Testlayer__
#define __HuaRongBlock__Testlayer__

#include <iostream>
#include "GameLayerBase.h"
#include "ui/CocosGui.h"
USING_NS_CC;
using namespace cocos2d::ui;

class TestLayer : public GameLayerBase{
public:
    static Scene* scene();
    virtual bool init();
    CREATE_FUNC(TestLayer);
private:
    void updateLabel(float);
    Label* contentLabel;
    Label* resultLabel;
    int i = 300;
    void btnCLick(Ref* _ref,Widget::TouchEventType type);
};

#endif /* defined(__HuaRongBlock__Testlayer__) */
