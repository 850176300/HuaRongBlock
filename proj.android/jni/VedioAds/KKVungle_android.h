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
#include "KKVedioAdsDelegate.h"



class VedioAdManager: public KKVedioAdsDelegate
{
	KKVedioAdsDelegate* m_AdsDelegate;
public:
	VedioAdManager():m_AdsDelegate(0)
	{

	}
	~VedioAdManager();
    
	static VedioAdManager* getInstance();
    
	static void destroy();
    
	bool init(JNIEnv * pEnv, jobject pAdJava);
    
	void setAdDelegate(KKVedioAdsDelegate* pAdDelegate);
    
public:
	void requestVedioAds();
    
public:
	/* the below methods derived from KKVedioAdsDelegate */
    
	void onVedioCacheSuccessfully();

	void onVedioLoadFailed(const char* errorCode);
    
	void onVedioRewarded(bool isComplete);
    
private:
};

#endif /* defined(__Poem__KKAds_android__) */
