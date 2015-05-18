/*
 * com_common_android_jni_KKShare.cpp
 *
 *  Created on: 2014-10-7
 *      Author: studio
 */

#include "com_common_android_jni_KKShare.h"
#include "KKShare_android.h"
#include "KKShare.h"


JNIEXPORT void JNICALL Java_com_common_android_jni_KKShare_nativeShareSucceed
  (JNIEnv *pEnv, jobject thisObj, jint type)
{

	KKShare::shareSucceed(type);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_KKShare_nativeShareCancel
  (JNIEnv *pEnv, jobject thisObj, jint type)
{

}
