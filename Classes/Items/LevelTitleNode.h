//
//  LevelTitle.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-9.
//
//

#ifndef __HuaRongStreet__LevelTitleNode__
#define __HuaRongStreet__LevelTitleNode__

#include <iostream>
#include "cocos2d.h"
#include "SuperGlobal.h"

using namespace std;
USING_NS_CC;

class LevelTitleNode : public MenuItemSprite{
public:
    static LevelTitleNode* createWithLeveTitle(LevelTitle* title);
    bool initWithLevelTitle(LevelTitle* title);
public:
    virtual void activate() override;
private:
    void setEnabledelay(float dt);
};


#endif /* defined(__HuaRongStreet__LevelTitleNode__) */
