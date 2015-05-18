//
//  ShopLayer_Android.h
//  HuaRongBlock
//
//  Created by 兵兵 on 14-12-27.
//
//

#ifndef __HuaRongBlock__ShopLayer_Android__
#define __HuaRongBlock__ShopLayer_Android__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "extensions/cocos-ext.h"


using namespace cocos2d;
using namespace std;
USING_NS_CC_EXT;

class ShopLayer_Android : public GameLayerBase{
public:
public:
    ShopLayer_Android();
    ~ShopLayer_Android();
    static Scene* scene();
    virtual bool init();
    CREATE_FUNC(ShopLayer_Android);
private:
    vector<string> prices;
    vector<string> coins;
    vector<string> iapkeys;
    void createHeader();
    void backButtonClicked(Ref* pRef, Control::EventType type);
    void addShopItems();
    void onShopItemClicked(Ref* pRef, Control::EventType type);
//    Sprite* coin;
//    Label* coinNum;
    Rect viewBtnCenter;
    vector<float> allShopItemY;
    Sprite* itemBg;
    void updateViewButton(float);
//    Label* titile2;
    ControlButton* viewBtn;
    ControlButton* backButton;
    void onloadAdFailed(Ref *pRef);
    void onadFinished(Ref *pRef);
    void showWarmingDialog(float);
    void onBackKeyClicked();
};


#endif /* defined(__HuaRongBlock__ShopLayer_Android__) */
