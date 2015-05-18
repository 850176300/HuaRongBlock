//
//  HeadNode.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#ifndef __HuaRongStreet__HeadNode__
#define __HuaRongStreet__HeadNode__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class HeadNode: public LayerColor{
public:
    static float getHeadNodeHeight();
    static HeadNode* createWithItems(__Array* items);
    bool initWithArray(__Array* items);
public:
    void showInNode(Node* parent);
};
#endif /* defined(__HuaRongStreet__HeadNode__) */
