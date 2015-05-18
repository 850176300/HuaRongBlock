//
//  BaseDialog.h
//  BrainFootball
//
//  Created by tomwey on 6/20/14.
//
//

#ifndef __BrainFootball__BaseDialog__
#define __BrainFootball__BaseDialog__

#include <iostream>
#include "cocos2d.h"
#include "KeyEventDispatcher.h"
USING_NS_CC;

class BaseDialog : public KeyEventDispatcherDelegate
{
public:
    BaseDialog();
    ~BaseDialog();
    static BaseDialog* create();
    virtual bool init();
    
public:
    void show(Node* parent, bool animated = true);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) ;
public:
    
    void setTitleText(const char*);
    const Label* getTitleLabel() const;
    
    void setContentText(const char* content);
    virtual void onBackKeyClicked();
    void onEnter();
    void onExit();
protected:
    // 内容层
    Layer* m_pContentLayer;
    Sprite* m_pBg;
    
    Label* m_pContentLabel;
private:
    // 标题
    Label* m_pTitleLabel;
};

#endif /* defined(__BrainFootball__BaseDialog__) */
