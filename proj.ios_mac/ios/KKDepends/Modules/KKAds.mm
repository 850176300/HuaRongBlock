//
//  KKAds.m
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#include "KKAds.h"
#include "ChartboostManager.h"
//#import "IOSAdsWrapper.h"

KKAds::KKAds()
{
    
}

KKAds::~KKAds()
{
//    [IOSAdsManager purgeIOSAdsManager];
}

void KKAds::setAdsDelegate(KKAdsDelegate* delegate)
{
//    [[IOSAdsManager sharedIOSAdsManager] setAdsDelegate:delegate];
}

//void KKAds::setBannerAdsPosition(BannerAdsPosition position)
//{
//    [[IOSAdsManager sharedIOSAdsManager] setBannerAdsPosition:position];
//}

// 预加载广告
void KKAds::preloadAds()
{
    [[ChartboostManager sharedManager] preload];
//    [[IOSAdsManager sharedIOSAdsManager]preloadAds];
}

// 显示横幅广告
void KKAds::requestAds()
{
//    [[IOSAdsManager sharedIOSAdsManager] showBannerAds];
}

// 移除横幅广告
void KKAds::removeAds()
{
//    [[IOSAdsManager sharedIOSAdsManager] removeBannerAds];
}

// 设置横幅广告是否显示
void KKAds::setAdsVisibility(bool visibility)
{
//    visibility ?
//    [[IOSAdsManager sharedIOSAdsManager] setBannerAdsVisible:YES] :
//    [[IOSAdsManager sharedIOSAdsManager] setBannerAdsVisible:NO];
}

bool KKAds::getBannerVisible()
{
    return true;
//    return [[IOSAdsManager sharedIOSAdsManager] bannerIsVisible];
}

// 获取横幅广告的大小
void KKAds::getBannerSize(float *sizes)
{
    
//    CGSize size = [[IOSAdsManager sharedIOSAdsManager] bannerAdsSize];
//    sizes[0] = size.width;
//    sizes[1] = size.height;
}

// 显示全屏广告
void KKAds::requestInterstitialAds()
{
    [[ChartboostManager sharedManager] showInterstitial];
}
