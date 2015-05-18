/*
 * KKSystemFunction_Android.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "KKSystemFunction_Android.h"
#include "platform/android/jni/JniHelper.h"
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

static SystemFunctionManager* sp_SystemFunctionManager = 0;

SystemFunctionManager* SystemFunctionManager::getInstance()
{
    LOGI("%s", "SystemFunctionManager::getInstance()t");
	if (!sp_SystemFunctionManager)
	{
		sp_SystemFunctionManager = new SystemFunctionManager();
	}

	return sp_SystemFunctionManager;
}

void SystemFunctionManager::destroy()
{
	if (sp_SystemFunctionManager)
	{
		delete sp_SystemFunctionManager;

		sp_SystemFunctionManager = 0;
	}
}

bool SystemFunctionManager::init(JNIEnv * pEnv, jobject pJava)
{
	LOGI("func____SystemFunctionManager::init");
	ClassSF = pEnv->GetObjectClass(pJava);
		if (!ClassSF)
		{
			LOGE("get STSystemFunction class Failed!");
			return false;
		}
	ClassSF = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassSF);

	if (!ClassSF) {
		LOGE("<makeGlobalRef>get STSystemFunction class Failed!");
		return false;
	}
	MethodDensityScale = pEnv->GetMethodID(ClassSF, "densityScale", "()F");
	if (!MethodDensityScale) {
		LOGE("get Method MethodDensityScale id Failed!");
		return false;
	}

	MethodCheckNetworkAvailable = pEnv->GetMethodID(ClassSF, "checkNetworkAvailable", "()Z");
	if (!MethodCheckNetworkAvailable) {
		LOGE("get Method MethodCheckNetworkAvailable id Failed!");
		return false;
	}
	MethodIsTabletAvailable = pEnv->GetMethodID(ClassSF, "isTabletAvailable", "()Z");
	if (!MethodIsTabletAvailable) {
			LOGE("get Method MethodIsTabletAvailable id Failed!");
			return false;
		}
	stSFJava = ST_JNI_Helper::makeGlobalRef(pEnv, pJava);
	if (!stSFJava)
	{
		LOGE("Cache stSFJava Failed!");
		return false;
	}
	return true;
}

void SystemFunctionManager::sendEmail(const char* subject, const char* body)
{
	if (!stSFJava)
	{
		LOGW("SystemFunctionManager::sendEmail() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	// Convert the C++ string to C-string, then to JNI String (jstring) for method args
	jstring sub = lEnv->NewStringUTF(subject);
	jstring content = lEnv->NewStringUTF(body);

	lEnv->CallVoidMethod(stSFJava, MethodSendMailByIntent, sub, content);

	lEnv->DeleteLocalRef(sub);
	lEnv->DeleteLocalRef(content);
}

void SystemFunctionManager::popAlertDialog(const char* message)
{
	if (!stSFJava)
	{
		LOGW("SystemFunctionManager::popAlertDialog() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	// Convert the C++ string to C-string, then to JNI String (jstring) for method args
	jstring msg = lEnv->NewStringUTF(message);

	lEnv->CallVoidMethod(stSFJava, MethodPopAlertDialog, msg);

	lEnv->DeleteLocalRef(msg);
}

void SystemFunctionManager::makeToast(const char* message)
{
	if (!stSFJava)
	{
		LOGW("SystemFunctionManager::makeToast() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	// Convert the C++ string to C-string, then to JNI String (jstring) for method args
	jstring msg = lEnv->NewStringUTF(message);

	lEnv->CallVoidMethod(stSFJava, MethodMakeToast, msg);

	lEnv->DeleteLocalRef(msg);
}

void SystemFunctionManager::sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName)
{
	if (!stSFJava)
	{
		LOGI("SystemFunctionManager::sendEmailAndAssetPic() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	jstring jniSubject = lEnv->NewStringUTF(subject.c_str());
	jstring jniMessage = lEnv->NewStringUTF(message.c_str());
	jstring jniAssetName = lEnv->NewStringUTF(assetName.c_str());

	lEnv->CallVoidMethod(stSFJava, MethodSendEmailAndAssetPic, jniSubject, jniMessage, jniAssetName);
	lEnv->DeleteLocalRef(jniSubject);
	lEnv->DeleteLocalRef(jniMessage);
	lEnv->DeleteLocalRef(jniAssetName);
}
void SystemFunctionManager::sendEmailAndFilePic(std::string subject, std::string message, std::string fileName)
{
	if (!stSFJava)
	{
		LOGI("SystemFunctionManager::sendEmailAndFilePic() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	jstring jniSubject = lEnv->NewStringUTF(subject.c_str());
	jstring jniMessage = lEnv->NewStringUTF(message.c_str());
	jstring jniFileName = lEnv->NewStringUTF(fileName.c_str());

	lEnv->CallVoidMethod(stSFJava, MethodSendEmailAndFilePic, jniSubject, jniMessage, jniFileName);
	lEnv->DeleteLocalRef(jniSubject);
	lEnv->DeleteLocalRef(jniMessage);
	lEnv->DeleteLocalRef(jniFileName);
}
std::string SystemFunctionManager::getSdCardPath()
{
    std::string ret("");
	jstring str;
    JniMethodInfo t;
    CCLog("----getSdCardPath-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "getSdCardPath", "()Ljava/lang/String;")) {
    	if(activityObj){
        	str =  (jstring)t.env->CallObjectMethod(activityObj, t.methodID);
        	t.env->DeleteLocalRef(t.classID);
            CCLog("----CallObjectMethod  getSdCardPath -");
            ret = JniHelper::jstring2string(str);

    	}
    }
	return ret;

}
bool SystemFunctionManager::checkNetworkAvailable()
{
	bool value;
	jboolean ret;
	JniMethodInfo t;
	CCLog("----getSdCardPath-");
	jobject activityObj = NULL;
	if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
		activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	}
	if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "checkNetworkAvailable", "()Z")) {
		if(activityObj){
			ret = t.env->CallBooleanMethod(activityObj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			CCLog("----CallObjectMethod  checkNetworkAvailable -");
			value = (ret == JNI_TRUE ? true : false);

		}
	}
	return value;
}
bool SystemFunctionManager::isTabletAvailable()
{
	bool value;
	jboolean ret;
	JniMethodInfo t;
	CCLog("----getSdCardPath-");
	jobject activityObj = NULL;
	if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
		activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	}
	if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "isTabletAvailable", "()Z")) {
		if(activityObj){
			ret = t.env->CallBooleanMethod(activityObj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			CCLog("----CallObjectMethod  isTabletAvailable -");
			value = (ret == JNI_TRUE ? true : false);

		}
	}
	return value;
}
float SystemFunctionManager::densityScale()
{
	LOGI("调用SystemFunctionManager::densityScale() ");
	float value;
	jfloat ret;
	JniMethodInfo t;
	CCLog("----getSdCardPath-");
	jobject activityObj = NULL;
	if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
		activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	}
	if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "densityScale", "()F")) {
		if(activityObj){
			ret = t.env->CallFloatMethod(activityObj, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			CCLog("----CallObjectMethod  densityScale -");
			value = (float)ret;

		}
	}
	LOGI("调用SystemFunctionManager::densityScale() 结束");
	return value;
}
void SystemFunctionManager::rateUs(){
	if (!stSFJava)
		{
			LOGI("SystemFunctionManager::rateUs() failed!");
			return;
		}

		JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

		lEnv->CallVoidMethod(stSFJava, MethodRateUs);
}

void SystemFunctionManager::refreshDCIM(std::string sFileDir)
{
    if (!stSFJava)
    {
    	LOGW("SystemFunctionManager::%s() failed!", __FUNCTION__);
        return;
    }
    LOGI("%s %s", __FILE__, __FUNCTION__);
    JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
    jstring msg = lEnv->NewStringUTF(sFileDir.c_str());
    lEnv->CallVoidMethod(stSFJava, MethodRefreshDCIM, msg);
}

std::string SystemFunctionManager::getDeviceName()
{

	LOGW("SystemFunctionManager::getDeviceName() failed!---");
    std::string ret("");
	jstring str;
	    JniMethodInfo t;
	    CCLog("----getDeviceName-");
	    jobject activityObj = NULL;
	    if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
	    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
	    }
	    if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "getDeviceName", "()Ljava/lang/String;")) {
	    	if(activityObj){
	            CCLog("----CallObjectMethod  getDeviceName -");

	        	str =  (jstring)t.env->CallObjectMethod(activityObj, t.methodID);
	        	t.env->DeleteLocalRef(t.classID);
	            ret = JniHelper::jstring2string(str);
	    	}
	    }
		return ret;
}

void SystemFunctionManager::showDialog(const char* msg,int tag,const char* cancle,const char* yes)
{
    JniMethodInfo t;
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
    	activityObj = (jobject)t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "popAlertDialog", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V")) {
    	if(activityObj){
            CCLog("----CallObjectMethod  popAlertDialog -");
            t.env->CallObjectMethod(activityObj, t.methodID,t.env->NewStringUTF(msg),tag,t.env->NewStringUTF(cancle),t.env->NewStringUTF(yes));
        	t.env->DeleteLocalRef(t.classID);
    	}
    }

}

SystemFunctionManager::~SystemFunctionManager()
{
	ST_JNI_Helper::deleteGlobalRef(ClassSF);
	ST_JNI_Helper::deleteGlobalRef(stSFJava);
}
