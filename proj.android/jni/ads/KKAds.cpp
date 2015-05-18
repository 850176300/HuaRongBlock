//
//  KKAds.cpp
//  Poem
//
//  Created by studio on 14-9-29.
//
//

#include "KKAds.h"
#include "KKAds_android.h"
#include "KKSystemFunction.h"

bool KKAds::willShowAd = true;
bool KKAds::interstitialShown = false;
bool KKAds::bannerAdVisibility = false;

void KKAds::requestAds()
{
//	AndroidAdManager::getInstance()->requestAds();
}

void KKAds::removeAds()
{
//	AndroidAdManager::getInstance()->removeAds();
}

void KKAds::requestInterstitialAds()
{
	AndroidAdManager::getInstance()->requestInterstitialAds();
}

void KKAds::setAdsDelegate(KKAdsDelegate* delegate)
{
	AndroidAdManager::getInstance()->setAdDelegate(delegate);
}

bool KKAds::getBannerVisible(){return true;}

//    void setBannerAdsPosition(BannerAdsPosition position)

void KKAds::preloadAds(){

	AndroidAdManager::getInstance()->preloadAds();
}

void KKAds::setAdsVisibility(bool visibility)
{
    bannerAdVisibility = visibility;
//	AndroidAdManager::getInstance()->setAdsVisibility(visibility);
}
void KKAds::getBannerSize( float adSize[])
{
	KKSystemFunction sf;
	if(sf.isTabletAvailable())
	{
		adSize[0]=600*sf.densityScale();
		adSize[1]=90*sf.densityScale();
	}else
	{
		adSize[0]=300*sf.densityScale();
		adSize[1]=50*sf.densityScale();
	}
	LOGI("get banner size adsize (%.2f, %.f)", adSize[0], adSize[1]);
}
void KKAds::destroy()
{
	AndroidAdManager::getInstance()->destroy();
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

void KKAds::showOfferWall()
{
//	showOfferWallJNI();
}

void KKAds::bringCointToNative()
{
//	bringCointToNativeJNI();
}
#endif

KKAds::KKAds()
{
}

KKAds::~KKAds()
{
}
