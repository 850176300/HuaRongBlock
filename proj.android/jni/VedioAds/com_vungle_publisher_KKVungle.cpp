
#include "com_vungle_publisher_KKVungle.h"
#include "KKVungle_android.h"

JNIEXPORT void JNICALL Java_com_vungle_publisher_KKVungle_nativeAdCacheSuccessfully
  (JNIEnv * pEnv, jobject thisObj)
{
	VedioAdManager::getInstance()->onVedioCacheSuccessfully();
}

JNIEXPORT void JNICALL Java_com_vungle_publisher_KKVungle_nativeAdLoadFailed
  (JNIEnv * pEnv, jobject thisObj, jstring str)
{
	VedioAdManager::getInstance()->onVedioLoadFailed("");
}

JNIEXPORT void JNICALL Java_com_vungle_publisher_KKVungle_nativeAdRewarded
  (JNIEnv * pEnv, jobject thisObj, jboolean jbst)
{
	if (jbst == JNI_TRUE) {
		VedioAdManager::getInstance()->onVedioRewarded(true);
	}else {
		VedioAdManager::getInstance()->onVedioRewarded(false);
	}




}

JNIEXPORT void JNICALL Java_com_vungle_publisher_KKVungle_nativeInit
  (JNIEnv * pEnv, jobject thisObj)
{

}

JNIEXPORT void JNICALL Java_com_vungle_publisher_KKVungle_nativeDestroy
  (JNIEnv * pEnv, jobject thisObj)
{

}
