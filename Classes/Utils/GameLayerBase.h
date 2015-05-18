//
//  GameLayerBase.h
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#ifndef __LibDoctor__GameLayerBase__
#define __LibDoctor__GameLayerBase__

#include <iostream>
#include "STVisibleRect.h"
#include "SuperGlobal.h"
#include "KeyEventDispatcher.h"
USING_NS_ST;
enum
{
    //背景z order
    kGameLayerZBg = 0,
    //游戏元素z order,分上下两层(目前分两层就够用了)
    kGameLayerZEleBottom,
    kGameLayerZEleUp,
    //按钮类z order
    kGameLayerZUI
};

/*
 游戏baseLayer, 其特点:
 1. 有可折叠的公共按钮(reset, home, music)；
 2. 有一居中放置的背景图片
 */
class GameLayerBase: public KeyEventDispatcherDelegate
{
public:
    GameLayerBase();
    ~GameLayerBase();
    bool isShowAds;
    virtual bool init();
    virtual bool initWithBgFileName(const char* apFileName, bool showAds = true);
    virtual void onEnter();
    virtual void onExit();

//    virtual void keyBackClicked();
    void setShowAds(bool isShow);
    void setADVisible(bool visible);
    virtual void onBackKeyClicked();
protected:
    
    virtual void onEnterTransitionDidFinish();
    void removeunuseCache(float);
public:
    Sprite* m_pBg;
    

};
#endif /* defined(__LibDoctor__GameLayerBase__) */
