//
//  KKAds_android.h
//  Poem
//
//  Created by studio on 14-9-29.
//
//

#ifndef __Poem__KKAds_android__
#define __Poem__KKAds_android__

#include "../utils/ST_JNI_Helper.h"
#include "KKAdsDelegate.h"


class AndroidAdManager: public KKAdsDelegate
{
	KKAdsDelegate* m_AdsDelegate;
public:
	AndroidAdManager() :
    m_AdsDelegate(0),
    KKAdsJava(0),
    ClassAds(0),
    MethodRequestAds(0),
    MethodRemoveAds(0),
    MethodRequestInterstitialAds(0),
    MethodSetAdsVisibility(0)
	{
	}
	~AndroidAdManager();
    
	static AndroidAdManager* getInstance();
    
	static void destroy();
    
	bool init(JNIEnv * pEnv, jobject pAdJava);
    
	void setAdDelegate(KKAdsDelegate* pAdDelegate);
    
public:
	void requestAds();
    
	void requestInterstitialAds();
    
	void removeAds();
    
	void setAdsVisibility(bool visibility);

	void preloadAds();
    
public:
	/* the below methods derived from KKAdsDelegate */
    
	void onBannerLoadSuccessfully();
    
	void onBannerLoadFailed(int errorCode);
    
	void onBannerClicked();
    
	void onBannerDismissed();
    
	void onInterstitialAdLoaded();
    
	void onInterstitialAdFailed(int errorCode);
    
	void onInterstitialShown();
    
	void onInterstitialDismissed();
    
private:
	/*>>>>>>>> below declaration is used by jni <<<<<<<<*/
	// Cached Classes.
	jclass ClassAds;
	// Cached java object
	jobject KKAdsJava;
	// Cached active Methods.
	jmethodID MethodRequestAds;
	jmethodID MethodRemoveAds;
	jmethodID MethodRequestInterstitialAds;
	jmethodID MethodSetAdsVisibility;
};

#endif /* defined(__Poem__KKAds_android__) */
