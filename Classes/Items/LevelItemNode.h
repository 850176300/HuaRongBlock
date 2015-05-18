//
//  LevelItemNode.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-11.
//
//

#ifndef __HuaRongStreet__LevelItemNode__
#define __HuaRongStreet__LevelItemNode__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SuperGlobal.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
class LevelItemNode: public MenuItemSprite{
private:
    LevelDescripe* _itemDescripe;
public:
    ~LevelItemNode(){CC_SAFE_RELEASE(_itemDescripe);};
    static LevelItemNode* createWithIndex(string type,int index, int currentCompl, int indexinSql);
    bool initWithIndex(string type,int index, int currentCompl, int indexinSql);
    LevelDescripe* getItemDescripe();
protected:
    
    void fillTheDescripe(int indexinType,int index, string type);
    void addstars();
};
#endif /* defined(__HuaRongStreet__LevelItemNode__) */
