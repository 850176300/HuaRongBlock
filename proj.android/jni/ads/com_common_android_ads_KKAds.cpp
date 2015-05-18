/*
 * com_common_android_ads_KKAds.cpp
 *
 *  Created on: 2014-10-3
 *      Author: studio
 */

#include "com_common_android_ads_KKAds.h"
#include "KKAds_android.h"

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeInit
(JNIEnv * pEnv, jobject thisObj)
{
    LOGI("%s", "Java_com_common_android_ads_KKAds_nativeInit");
	AndroidAdManager::getInstance()->init(pEnv, thisObj);
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeDestroy
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->destroy();
}

JNIEXPORT void Java_com_common_android_ads_KKAds_nativeAdLoadSuccessfully
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->onBannerLoadSuccessfully();
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeAdLoadFailed
(JNIEnv * pEnv, jobject thisObj, jint errorCode)
{
	AndroidAdManager::getInstance()->onBannerLoadFailed(errorCode);
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeInterstitialAdLoaded
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->onInterstitialAdLoaded();
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeInterstitialAdFailed
(JNIEnv * pEnv, jobject thisObj, jint errorCode)
{
	AndroidAdManager::getInstance()->onInterstitialAdFailed(errorCode);
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeInterstitialAdShown
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->onInterstitialShown();
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeInterstitialAdDismissed
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->onInterstitialDismissed();
}

JNIEXPORT void JNICALL Java_com_common_android_ads_KKAds_nativeClickedBannerAd
(JNIEnv * pEnv, jobject thisObj)
{
}


