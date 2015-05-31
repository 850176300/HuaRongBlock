//
//  HomeLayer.h
//  HuaRongBlock
//
//  Created by liuwei on 15/5/31.
//
//

#ifndef __HuaRongBlock__HomeLayer__
#define __HuaRongBlock__HomeLayer__

#include <istream>
#include "cocos2d.h"
#include "GameLayerBase.h"
using namespace std;
USING_NS_CC;

class HomeLayer : public GameLayerBase{
public:
    static Scene* scene();
    CREATE_FUNC(HomeLayer);
    virtual bool init();
};

#endif /* defined(__HuaRongBlock__HomeLayer__) */
