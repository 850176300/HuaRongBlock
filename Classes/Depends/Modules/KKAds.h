//
//  KKAds.h
//  Poem
//
//  Created by studio on 14-9-29.
//
//

#ifndef __Poem__KKAds__
#define __Poem__KKAds__

#include "cocos2d.h"
#include "KKAdsDelegate.h"

class KKAds
{
public:
	KKAds();
	virtual ~KKAds();
    
    void setAdsDelegate(KKAdsDelegate* delegate);
    
public:
	/**
	 * @brief request and show banner ads
	 */
	void requestAds();
    
    /**
	 * @brief request a interstitial ads
	 */
    void requestInterstitialAds();
    
//    void requestVideoIntertitial();
	/**
	 * @brief remove shown ads or cancel suspending ads
	 */
	void removeAds();
    
    /**
	 * @brief set visibility of ad view, not remove ad from parent node
	 */
	void setAdsVisibility(bool visibility);
	/**
     *    get banner ad size
     */
	void getBannerSize(float[]);
    
    bool getBannerVisible();
    
//    void setBannerAdsPosition(BannerAdsPosition position);
    
    void preloadAds();
    
public:
    /**
     * @brief destroy environment about ads
     */
    static void destroy();
    
    // when interstitial ads shown, set it true
    static bool interstitialShown;
    
    // when user not purchased anything can remove ads, set it true;
    static bool willShowAd;
    
	// indicate current banner ad status
	static bool bannerAdVisibility;
	
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void showOfferWall();
    void bringCointToNative();
#endif
    
};


#endif /* defined(__Poem__KKAds__) */
