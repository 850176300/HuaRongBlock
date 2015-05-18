/*
 * com_common_android_jni_KKDialogManager.cpp
 *
 *  Created on: 2014-10-19
 *      Author: studio
 */

#include "com_common_android_jni_KKDialogManager.h"
#include  "KKDialogManager_android.h"
/*
 * Class:     com_common_android_jni_KKDialogManager
 * Method:    DialogNegativeCLicked
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_android_jni_KKDialogManager_DialogNegativeCLicked
  (JNIEnv *pEnv, jclass thisClass, jint tag)
{
	KKDialogManager_android::DialogNegativeCLicked(tag);
}

/*
 * Class:     com_common_android_jni_KKDialogManager
 * Method:    DialogPositiveCLicked
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_android_jni_KKDialogManager_DialogPositiveCLicked
  (JNIEnv *pEnv, jclass thisClass, jint tag)
{

	KKDialogManager_android::DialogPositiveCLicked(tag);
}

