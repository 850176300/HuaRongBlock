//
//  ConfirmDialog.h
//  BrainFootball
//
//  Created by tomwey on 6/20/14.
//
//

#ifndef __BrainFootball__ConfirmDialog__
#define __BrainFootball__ConfirmDialog__

#include <iostream>
#include "cocos2d.h"
#include "BaseDialog.h"

using namespace std;
USING_NS_CC;
class ConfirmDialog;
class ConfirmDialogDelegate
{
public:
    virtual void onConfirmed(ConfirmDialog* target, bool yesOrNo) {};
};

class ConfirmDialog : public BaseDialog
{
public:
    ConfirmDialog():m_pDelegate(NULL), m_bConfirmed(false) ,m_pCancelItem(NULL),m_pOKItem(NULL){};
    ~ConfirmDialog() {};
public:
    static ConfirmDialog* create(bool isOneBtn = false);
    virtual bool init(bool isOneBtn = false);
    
    void setDelegate(ConfirmDialogDelegate *delegate);
    
    void setCancel(Sprite* node,Sprite* selectNode);
    void setOK(Sprite* node,Sprite* selectNode);
    void onBackKeyClicked();

private:
    void menuCallback(Ref* sender);
    void dismiss();
    
    MenuItemSprite* getMenuItemSprite(const string& imageName);
private:
    ConfirmDialogDelegate* m_pDelegate;
    bool m_bConfirmed;
    MenuItemSprite* m_pCancelItem;
    MenuItemSprite* m_pOKItem;
    Menu* m_pMenu;
};

#endif /* defined(__BrainFootball__ConfirmDialog__) */
