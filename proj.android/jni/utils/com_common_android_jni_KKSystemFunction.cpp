/*
 * com_common_android_jni_KKSystemFunction.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "com_common_android_jni_KKSystemFunction.h"
#include "KKSystemFunction_Android.h"

JNIEXPORT void JNICALL Java_com_common_android_jni_KKSystemFunction_nativeInit
(JNIEnv * pEnv, jobject thisObj)
{
    LOGI("%s", "Java_com_common_android_jni_KKSystemFunction_nativeInit");
	SystemFunctionManager::getInstance()->init(pEnv, thisObj);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_KKSystemFunction_nativeDestroy
(JNIEnv * pEnv, jobject jobjSf)
{
	SystemFunctionManager::getInstance()->destroy();
}

