//
//  GameController.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#ifndef __HuaRongStreet__GameController__
#define __HuaRongStreet__GameController__

#include <iostream>
#include "cocos2d.h"
#include "SingleTon.h"
USING_NS_CC;
class GameController: public SingleTon<GameController>{
    friend class SingleTon<GameController>;
public:
    GameController();
    float getBannerHeight();
};

#endif /* defined(__HuaRongStreet__GameController__) */
