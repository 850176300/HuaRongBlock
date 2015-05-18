//
//  KKAdsAdapter.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#ifndef Brain_KKAdsAdapter_h
#define Brain_KKAdsAdapter_h

#include "cocos2d.h"
#include "KKAdsDelegate.h"

using namespace cocos2d;

typedef enum {
    BannerAdsPositionTop = 0,
    BannerAdsPositionBottom,
} BannerAdsPosition;

class KKAdsAdapter
{
public:
    KKAdsAdapter();
    virtual ~KKAdsAdapter();
    
    void setAdsDelegate(KKAdsDelegate *delegate);
    
public:
    /*
     * 预加载横幅或者全屏广告
     * @param bannerId 横幅广告ID 如果为NULL则不会加载
     * @param interstitialId 全屏广告ID 如果为NULL则不会加载
     */
    void preloadAds();
    
    // 显示横幅广告
    void showBannerAds();
    
    // 设置横幅广告显示的位置
    void setBannerAdsPosition(BannerAdsPosition position);
    
    // 移除横幅广告
    void removeBannerAds();
    
    // 设置横幅广告是否显示
    void setBannerAdsVisible(bool visible);
    bool getBannerVisible();
    
    // 获取横幅广告的大小
    CCSize getBannerAdsSize();
    
    // 显示全屏广告
    void showInterstitalAds();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void showOfferWall();
    void bringCointToNative();
#endif
};

#endif
