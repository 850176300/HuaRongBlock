//
//  KKShare_android.cpp
//  Poem
//
//  Created by studio on 14-9-27.
//
//

#include "KKShare_android.h"
#include "platform/android/jni/JniHelper.h"
#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

static KKShareManager* sp_Instance = 0;

KKShareManager::~KKShareManager()
{
    delete sp_Instance;
}

KKShareManager* KKShareManager::getInstance()
{
    
	if (!sp_Instance)
	{
		sp_Instance = new KKShareManager();
	}
    
	return sp_Instance;
}

void KKShareManager::shareWXCircleJNI(const char*  title,const char*  msg,const char*  imgPath,const char*  url,int type)
{
    JniMethodInfo t;
    CCLog("----shareWXCircleJNI-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/WXShareManager","getInstance","()Lcom/common/android/jni/WXShareManager;")){
    	activityObj = t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/jni/WXShareManager", "WXShareToCircleFriend", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID,t.env->NewStringUTF(title),t.env->NewStringUTF(msg),t.env->NewStringUTF(imgPath),t.env->NewStringUTF(url),type);
            t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  WXShareToCircle -");
            
    	}
    }
    m_nShareType = type;
}

void KKShareManager::shareWXOneFriendJNI(const char*  title,const char*  msg,const char*  imgPath,const char*  url,int type)
{
    JniMethodInfo t;
    CCLog("----shareWXOneFriendJNI-");
    jobject activityObj = NULL;
    if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/WXShareManager","getInstance","()Lcom/common/android/jni/WXShareManager;")){
    	activityObj = t.env->CallStaticObjectMethod(t.classID, t.methodID);
    }
    if (JniHelper::getMethodInfo(t, "com/common/android/jni/WXShareManager", "WXShareToOneFriend", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")) {
    	if(activityObj){
        	t.env->CallVoidMethod(activityObj, t.methodID,t.env->NewStringUTF(title),t.env->NewStringUTF(msg),t.env->NewStringUTF(imgPath),t.env->NewStringUTF(url),type);
            t.env->DeleteLocalRef(t.classID);
            CCLog("----CallVoidMethod  WXShareToOneFriend -");

    	}
    }
    m_nShareType = type;
}


string KKShareManager::getUDIDJNI(){
	JniMethodInfo t;
	jobject activityObj = NULL;
	std::string ret = "";
	jstring str;
	if(JniHelper::getStaticMethodInfo(t,"com/common/android/jni/KKSystemFunction","getInstance","()Lcom/common/android/jni/KKSystemFunction;")){
	    	activityObj = t.env->CallStaticObjectMethod(t.classID, t.methodID);
	   }
	    if (JniHelper::getMethodInfo(t, "com/common/android/jni/KKSystemFunction", "getUDID", "()Ljava/lang/String;")) {
	    	if(activityObj){
	    		str = (jstring)t.env->CallObjectMethod(activityObj, t.methodID);
	            t.env->DeleteLocalRef(t.classID);
	            ret = JniHelper::jstring2string(str);
	            CCLog("----CallVoidMethod  WXShareToOneFriend -");

	    	}
	    }
	    return ret;
}

void KKShareManager::shareSucceed()
{
//    KKShare::shareSucceed(m_nShareType);
}




