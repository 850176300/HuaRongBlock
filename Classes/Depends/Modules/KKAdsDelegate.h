//
//  KKAdsDelegate.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#ifndef Brain_KKAdsDelegate_h
#define Brain_KKAdsDelegate_h

class KKAdsDelegate
{
public:
    /**
	 * @brief This event is called once an ad loads successfully.
	 */
	virtual void onBannerLoadSuccessfully() {};
    
	/**
	 * @brief This event is called if an ad fails to load.
	 */
	virtual void onBannerLoadFailed(int errorCode) {};
    
    /**
     * @brief Sent when the banner has just taken over the screen.
     */
    virtual void onBannerClicked() {};
    
    /**
     * @brief Sent when an expanded banner has collapsed back to its original size.
     */
	virtual void onBannerDismissed() {};
    
    /**
	 * @brief This event is called once an interstitial ad loads successfully.
	 */
    virtual void onInterstitialAdLoaded() {};
    
    /**
	 * @brief This event is called if an interstitial ad fails to load.
	 */
    virtual void onInterstitialAdFailed(int errorCode) {};
    
    /**
	 * @brief This event is called if an interstitial ad shown.
	 */
    virtual void onInterstitialShown() {};
    
    /**
	 * @brief This event is called if an interstitial ad closed.
	 */
    virtual void onInterstitialDismissed() {};

    /**
   	 * @brief This event is called if an video interstitial ad closed.
   	 */
//	virtual void onVideoIntertitialClose(bool isFinished){};


	 /**
		 * @brief This event is called if an video interstitial load failed
	*/
//	virtual void onVideoIntertitialLoadFailed() {};
};

#endif
