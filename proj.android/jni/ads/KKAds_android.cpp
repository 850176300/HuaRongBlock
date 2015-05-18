//
//  KKAds_android.cpp
//  Poem
//
//  Created by studio on 14-9-29.
//
//

#include "KKAds_android.h"
#include "platform/android/jni/JniHelper.h"
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "cocos2d.h"


using namespace cocos2d;
using namespace std;

static AndroidAdManager* sp_AndroidAdManager = 0;

AndroidAdManager* AndroidAdManager::getInstance()
{
	if (!sp_AndroidAdManager)
	{
		sp_AndroidAdManager = new AndroidAdManager();
	}
    
	return sp_AndroidAdManager;
}

void AndroidAdManager::destroy()
{
	if (sp_AndroidAdManager)
	{
		delete sp_AndroidAdManager;
        
		sp_AndroidAdManager = 0;
	}
}

bool AndroidAdManager::init(JNIEnv * pEnv, jobject pAdJava)
{
    LOGE("AndroidAdManager::init");
	// get class
//	ClassAds = pEnv->GetObjectClass(pAdJava);
//	if (!ClassAds)
//	{
//		LOGE("get InAppBilling class Failed!");
//		return false;
//	}
//	ClassAds = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassAds);
//	// get method id --- purchaseManaged(String)
//	MethodRequestAds = pEnv->GetMethodID(ClassAds, "requestAds", "()V");
//	if (!MethodRequestAds)
//	{
//		LOGE("get Method requestAds id Failed!");
//		return false;
//	}
//
//	MethodRequestInterstitialAds = pEnv->GetMethodID(ClassAds, "requestInterstitialAds", "()V");
//	if (!MethodRequestInterstitialAds)
//	{
//		LOGE("get Method requestInterstitialAds id Failed!");
//		return false;
//	}
//
//	// get method id --- purchaseUnmanaged(String)
//	MethodRemoveAds = pEnv->GetMethodID(ClassAds, "removeAds", "()V");
//	if (!MethodRemoveAds)
//	{
//		LOGE("get Method removeAds id Failed!");
//		return false;
//	}
//
//	MethodSetAdsVisibility = pEnv->GetMethodID(ClassAds, "setAdsVisibility", "(Z)V");
//	if (!MethodSetAdsVisibility)
//	{
//		LOGE("get Method removeAds id Failed!");
//		return false;
//	}
//
////	// Caches objects.
////	KKAdsJava = ST_JNI_Helper::makeGlobalRef(pEnv, pAdJava);
////
//////	KKAdsJava = JniHelper::getClassID(pAdJava,pEnv);
////	if (!KKAdsJava)
////	{
////		LOGE("Cache stIABJava Failed!");
////		return false;
////	}
//
//    JniMethodInfo t;
//    jobject activityObj = NULL;
//    if(JniHelper::getStaticMethodInfo(t,"com/common/android/ads/KKMogoAds","getInstance","()Lcom/common/android/ads/KKMogoAds;")){
//    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
//        CCLog("----shareWXOneFriendJNI-");
//    	KKAdsJava = ST_JNI_Helper::makeGlobalRef(pEnv, activityObj);
//    //
//    //	KKAdsJava = JniHelper::getClassID(pAdJava,pEnv);
//    	if (!KKAdsJava)
//    	{
//    		LOGE("Cache stIABJava Failed!");
//    		return false;
//    	}
//    }
	return true;
}

void AndroidAdManager::setAdDelegate(KKAdsDelegate* pAdDelegate)
{
	m_AdsDelegate = pAdDelegate;
}

void AndroidAdManager::requestAds()
{
//    LOGE("AndroidAdManager::requestAds");
//	if (!KKAdsJava)
//	{
//		LOGE("STAds::requestAds() failed!");
//		return;
//	}
//
//	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
//
//	lEnv->CallVoidMethod(KKAdsJava, MethodRequestAds);

    JniMethodInfo t;
    CCLog("----requestAds-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/ads/KKMogoAds","getInstance","()Lcom/common/android/ads/KKMogoAds;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/ads/KKMogoAds", "requestAds", "()V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID);
        	t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  requestAds -");

    	}
    }
}

void AndroidAdManager::requestInterstitialAds()
{
    JniMethodInfo t;
    CCLog("----requestInterstitialAds-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/ads/KKMogoAds","getInstance","()Lcom/common/android/ads/KKMogoAds;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/ads/KKMogoAds", "requestInterstitialAds", "()V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID);
        	t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  requestInterstitialAds -");

    	}
    }
//	if (!KKAdsJava)
//	{
//		LOGE("STAds::requestInterstitialAds() failed!");
//		return;
//	}
//
//	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
//
//	lEnv->CallVoidMethod(KKAdsJava, MethodRequestInterstitialAds);
}

void AndroidAdManager::removeAds()
{
    JniMethodInfo t;
    CCLog("----removeAds-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/ads/KKMogoAds","getInstance","()Lcom/common/android/ads/KKMogoAds;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/ads/KKMogoAds", "removeAds", "()V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID);
        	t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  removeAds -");

    	}
    }
//	if (!KKAdsJava)
//	{
//		LOGE("STAds::removeAds() failed!");
//		return;
//	}
//
//	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
//
//	lEnv->CallVoidMethod(KKAdsJava, MethodRemoveAds);
}

void AndroidAdManager::setAdsVisibility(bool visibility)
{
    JniMethodInfo t;
    CCLog("----setAdsVisibility-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/ads/KKMogoAds","getInstance","()Lcom/common/android/ads/KKMogoAds;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/ads/KKMogoAds", "setAdsVisibility", "(Z)V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID,(jboolean)visibility);
        	t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  setAdsVisibility -");

    	}
    }
//	if (!KKAdsJava)
//	{
//		LOGE("STAds::setAdsVisibility(bool) failed!");
//		return;
//	}
//
//	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
//
//	lEnv->CallVoidMethod(KKAdsJava, MethodSetAdsVisibility, visibility);
}


void AndroidAdManager::preloadAds(){
	 JniMethodInfo t;
	CCLog("----preloadads-");
	jobject activityObj = NULL;
	if(JniHelper::getStaticMethodInfo(t,"com/common/android/ads/KKMogoAds","getInstance","()Lcom/common/android/ads/KKMogoAds;")){
		activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	}
	if (JniHelper::getMethodInfo(t, "com/common/android/ads/KKMogoAds", "preloadads", "()V")) {
		if(activityObj){
			t.env->CallVoidMethod(activityObj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			CCLog("----CallVoidMethod  preloadads -");

		}
	}
}

/*============================================*/
void AndroidAdManager::onBannerLoadSuccessfully()
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onBannerLoadSuccessfully();
	}
}

void AndroidAdManager::onBannerLoadFailed(int errorCode)
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onBannerLoadFailed(errorCode);
	}
}

void AndroidAdManager::onBannerClicked()
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onBannerClicked();
	}
}

void AndroidAdManager::onBannerDismissed()
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onBannerDismissed();
	}
}

void AndroidAdManager::onInterstitialAdLoaded()
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onInterstitialAdLoaded();
	}
}

void AndroidAdManager::onInterstitialAdFailed(int errorCode)
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onInterstitialAdFailed(errorCode);
	}
}

void AndroidAdManager::onInterstitialShown()
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onInterstitialShown();
	}
}

void AndroidAdManager::onInterstitialDismissed()
{
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onInterstitialDismissed();
	}
}

AndroidAdManager::~AndroidAdManager()
{
	ST_JNI_Helper::deleteGlobalRef(ClassAds);
	ST_JNI_Helper::deleteGlobalRef(KKAdsJava);
}

