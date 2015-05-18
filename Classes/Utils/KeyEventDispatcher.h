//
//  KeyEventDispatcher.h
//  HuaRongBlock
//
//  Created by liuwei on 14-12-22.
//
//

#ifndef __HuaRongBlock__KeyEventDispatcher__
#define __HuaRongBlock__KeyEventDispatcher__

#include <iostream>
#include "cocos2d.h"
#include "SingleTon.h"
USING_NS_CC;
class KeyEventDispatcherDelegate: public LayerColor{
public:
    virtual void onBackKeyClicked() = 0;
};

class KeyEventDispatcher: public SingleTon<KeyEventDispatcher>{
    friend class SingleTon<KeyEventDispatcher>;
public:
    KeyEventDispatcher();
    void keyRelease(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void addEventDelegate(KeyEventDispatcherDelegate* pDelegate);
    void removeDelegate(Ref* apDelegate);
    
protected:
    __Array* m_pDelegates;
};

#endif /* defined(__HuaRongBlock__KeyEventDispatcher__) */
