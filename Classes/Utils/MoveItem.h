//
//  MoveItem.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#ifndef __HuaRongStreet__MoveItem__
#define __HuaRongStreet__MoveItem__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MoveItem;
class MoveItemDelegate{
public:
    virtual void touchItembegan(MoveItem* pItem){};
    virtual void touchItemMove(MoveItem* pItem, Vec2 delta){};
    virtual void touchItemEnd(MoveItem* pItem){};
};


class MoveItem : public Sprite{
public:
    ~MoveItem();
    static MoveItem* create(string file, string usertag);
    bool initWithStringValue(string file, string usertag);
    virtual bool onTouchBegan(Touch *touch, Event *event) ;
    virtual void onTouchMoved(Touch *touch, Event *event) ;
    virtual void onTouchEnded(Touch *touch, Event *event) ;
    virtual void onTouchCancelled(Touch *touch, Event *event) ;
    void setTouchEnable(bool enable);
    void setTouchDelegate(MoveItemDelegate* delegate);
    void setStartLocation(Vec2 location);
    Vec2 getStartLocation();
    CC_SYNTHESIZE(Vec2, curretnPosition, PositionNow);
    CC_SYNTHESIZE(int, startTag, OldTag);
private:
    EventListener* _listener;
    Vec2 startLocation;
    bool _touchenable;
    MoveItemDelegate* _pDelegate;
};

#endif /* defined(__HuaRongStreet__MoveItem__) */
