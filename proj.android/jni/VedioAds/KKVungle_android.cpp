//
//  KKAds_android.cpp
//  Poem
//
//  Created by studio on 14-9-29.
//
//

#include "KKVungle_android.h"
#include "platform/android/jni/JniHelper.h"
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

static VedioAdManager* sp_VedioAdManager = 0;

VedioAdManager* VedioAdManager::getInstance()
{
	if (!sp_VedioAdManager)
	{
		sp_VedioAdManager = new VedioAdManager();
	}
    
	return sp_VedioAdManager;
}

void VedioAdManager::destroy()
{
	if (sp_VedioAdManager)
	{
		delete sp_VedioAdManager;
        
		sp_VedioAdManager = 0;
	}
}

bool VedioAdManager::init(JNIEnv * pEnv, jobject pAdJava)
{
    LOGE("VedioAdManager::init");
    
	return true;
}

void VedioAdManager::setAdDelegate(KKVedioAdsDelegate* pAdDelegate)
{
	m_AdsDelegate = pAdDelegate;
}

void VedioAdManager::requestVedioAds()
{
    JniMethodInfo t;
    CCLog("----requestVedioAds-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/vungle/publisher/KKVungle","getInstance","()Lcom/vungle/publisher/KKVungle;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/vungle/publisher/KKVungle", "requestAds", "()V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID);
        	t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  requestVedioAds -");
            
    	}
    }
}



/*============================================*/

void VedioAdManager::onVedioCacheSuccessfully()
{
    
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onVedioAdsCacheSuccessfully();
	}
}

void VedioAdManager::onVedioLoadFailed(const char* errorCode)
{
    
	if (m_AdsDelegate)
	{
		m_AdsDelegate->onVedioAdsLoadFailed(errorCode);
	}
}

void VedioAdManager::onVedioRewarded(bool isComplete)
{
    if (isComplete == true) {
    	log("jni-------观看已经结束");
    }else {
    	log("jni-------观看没有结束");
    }
	if (m_AdsDelegate != 0)
	{
		m_AdsDelegate->onVedioAdsRewarded(isComplete);
	}
}

VedioAdManager::~VedioAdManager()
{
}

