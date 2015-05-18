//
//  KeyEventDispatcher.cpp
//  HuaRongBlock
//
//  Created by liuwei on 14-12-22.
//
//

#include "KeyEventDispatcher.h"

KeyEventDispatcher::KeyEventDispatcher(){
    m_pDelegates = __Array::create();
    m_pDelegates->retain();
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = [this](EventKeyboard::KeyCode code, Event* event){
        keyRelease(code, event);
    };
    listenerkeyPad->onKeyPressed = [this](EventKeyboard::KeyCode code, Event* event){
        keyRelease(code, event);
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerkeyPad, 1);
}

void KeyEventDispatcher::keyRelease(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        log("响应返回键点击");
        for (int i = m_pDelegates->count() - 1; i >= 0; --i) {
            KeyEventDispatcherDelegate* lpDelegate = dynamic_cast<KeyEventDispatcherDelegate*>(m_pDelegates->getObjectAtIndex(i));
            if(lpDelegate)
            {
                
                lpDelegate->onBackKeyClicked();
                break;
            }
        }
    }
}


void KeyEventDispatcher::addEventDelegate(KeyEventDispatcherDelegate *pDelegate) {
    
     m_pDelegates->addObject(pDelegate);
}

void KeyEventDispatcher::removeDelegate(Ref* apDelegate){
    m_pDelegates->removeObject(apDelegate);
}
