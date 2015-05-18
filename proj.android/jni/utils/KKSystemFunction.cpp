/*
 * KKSystemFunction.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "KKSystemFunction.h"
#include "KKSystemFunction_Android.h"
#include  "KKDialogManager_android.h"

KKSystemFunction::KKSystemFunction()
{
}
KKSystemFunction::~KKSystemFunction()
{
}

void KKSystemFunction::sendEmail(const char* subject, const char* body)
{
	SystemFunctionManager::getInstance()->sendEmail(subject, body);
}

void KKSystemFunction::openUrl(const char *url)
{
    
}

void KKSystemFunction::go2RateUs(const char* appId, const char* alertMessage)
{
    
}

const char* KKSystemFunction::getDeviceName()
{
    return SystemFunctionManager::getInstance()->getDeviceName().c_str();
}

void KKSystemFunction::popAlertDialog(const char* message)
{
	SystemFunctionManager::getInstance()->showDialog(message,0,"cancle","ok");
}

void KKSystemFunction::popAlertDialog(const char*msg,int tag,const char*cancle,const char*yes)
{
	SystemFunctionManager::getInstance()->showDialog(msg,tag,cancle,yes);
}

std::string KKSystemFunction::getSdCardPath()
{
	return SystemFunctionManager::getInstance()->getSdCardPath();
}

void KKSystemFunction::makeToast(const char* message)
{
	
}



void KKSystemFunction::saveImage(std::string fileCache,CCObject* selector,CallFunction callback){
}

bool KKSystemFunction::checkNetworkAvailable()
{
	return SystemFunctionManager::getInstance()->checkNetworkAvailable();

}

bool KKSystemFunction::isTabletAvailable()
{
	return SystemFunctionManager::getInstance()->isTabletAvailable();

}
float KKSystemFunction::densityScale()
{
	return SystemFunctionManager::getInstance()->densityScale();
}

void KKSystemFunction::refreshDCIM(std::string sFileDir)
{
    CCLOG("%s", __func__);
    SystemFunctionManager::getInstance()->refreshDCIM(sFileDir);
}


void KKSystemFunction::setDialogDelegate(KKDialogDelegate* delegate)
{
	KKDialogManager_android::setDialogDelegate(delegate);
}
