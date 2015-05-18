//
//  HomeLayer.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#ifndef __HuaRongStreet__HomeLayer__
#define __HuaRongStreet__HomeLayer__

#include <iostream>
#include <sstream>
#include "stdio.h"
#include "GameLayerBase.h"
#include "HeadNode.h"
#include "extensions/cocos-ext.h"
#include "ConfirmDialog.h"
USING_NS_CC_EXT;
class HomeLayer : public GameLayerBase, public ConfirmDialogDelegate{
public:
    static Scene* scene();
    CREATE_FUNC(HomeLayer);
    virtual bool init();
    void onBackKeyClicked();
private:
    HeadNode* header;
    ControlButton* starbtn;
    
protected:
    
    virtual void onEnter();
    void itemClickedCallBack(Ref* pSender, Control::EventType touchType);
    void levelItemClicked(Ref* pSender);
    void createHeader();
    void createAllLevels(float startY);
    virtual void onConfirmed(ConfirmDialog* target, bool yesOrNo);
};

#endif /* defined(__HuaRongStreet__HomeLayer__) */
