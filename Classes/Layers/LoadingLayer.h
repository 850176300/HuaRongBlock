//
//  LoadingLayer.h
//  HuaRongBlock
//
//  Created by liuwei on 14-12-16.
//
//

#ifndef __HuaRongBlock__LoadingLayer__
#define __HuaRongBlock__LoadingLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class LoadingLayer : public LayerColor{
public:
    static Scene* scene();
    virtual bool init();
    CREATE_FUNC(LoadingLayer);
protected:
    virtual void onEnterTransitionDidFinish();
    void runAnimation();
    Sprite* loading;
    
    void updateToMainScene(float);
};
#endif /* defined(__HuaRongBlock__LoadingLayer__) */
