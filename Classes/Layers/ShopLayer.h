//
//  ShopLayer.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-22.
//
//

#ifndef __HuaRongStreet__ShopLayer__
#define __HuaRongStreet__ShopLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "extensions/cocos-ext.h"
#include "KKInAppBilling.h"
#include "KKIAPDelegate.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class ShopLayer : public GameLayerBase, public KKIAPDelegate{
public:
    ShopLayer():iap(NULL){ iap = new KKInAppBilling(); iap->setIAPDelegate(this);};
    ~ShopLayer(){CC_SAFE_DELETE(iap);};
    static Scene* scene();
    virtual bool init();
    CREATE_FUNC(ShopLayer);
private:
    vector<string> prices;
    vector<string> coins;
    vector<string> iapkeys;
    void createHeader();
    void backButtonClicked(Ref* pRef, Control::EventType type);
    void addShopItems();
    void onShopItemClicked(Ref* pRef);
    void onRestoreItemClicked(Ref* pref);
    virtual void purchaseSuccess(const char* pid);
    virtual void purchaseFailure(const char* pid, int errorCode);
    virtual void restoreSuccess(const char* pid);
    virtual void restoreFailure(const char* pid, int errorCode);
    KKInAppBilling* iap;
    Sprite* coin;
    Label* coinNum;
    vector<float> allShopItemY;
    Sprite* itemBg;
};
#endif /* defined(__HuaRongStreet__ShopLayer__) */
