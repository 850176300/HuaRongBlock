//
//  KKShare.c
//  BrainFootball
//
//  Created by studio on 14-7-27.
//
//

#include "KKShare.h"
#include "KKShare_android.h"
#include "cocos2d.h"
#include "UserDefaultManager.h"
#include "ConfirmDialog.h"
#include "KKShare_android.h"
#include "KKSystemFunction.h"

#define SHARE_URL "http://kekestudio.com"

USING_NS_CC;

void saveScreenImage(CCImage* image)
{
    
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "curSceen.jpg";
    
    bool issuccess=image->saveToFile(fullpath.c_str());
    if (issuccess)
    {
        CCLog("Your image was saved to your Camera Roll!");
    }else
    {
        CCLog("Your image was unable to be saved. Please check your device storage and try again.");
    }
    
}
void KKShare::shareToWeixinCircle(const char*title,const char*msg,const char*imagePath,const char*url,int type)
{
    KKShareManager::getInstance()->shareWXCircleJNI(title,msg,imagePath,url,type);
    
}

void KKShare::shareToWeixinOneFriend(const char*title,const char*msg,const char*imagePath,const char*url,int type)
{
	KKShareManager::getInstance()->shareWXOneFriendJNI(title,msg,imagePath,url,type);
    
}
void KKShare::shareToWeixin(const char *text,int  type)
{
	bool canShow = false;
	int flag = 0;
//    if (type==eResqustTypeHelp) {
//        if (UserDefaultManager::getIsFirstHelp()) {
//        	canShow = true;
//        	flag = 0;
//        }
//    }else if (type==eResqustTypeShare){
//        if (UserDefaultManager::getIsFirstShared()) {
//        	canShow = true;
//        	flag = 1;
//        }
//    }
    KKShareManager::getInstance()->shareWXCircleJNI("",text,"",SHARE_URL,type);
}

void KKShare::shareToWeixinFriend(const char *text,int type)
{

	bool canShow = false;
	int flag = 0;
//    if (type==eResqustTypeHelp) {
//        if (UserDefaultManager::getIsFirstHelp()) {
//        	canShow = true;
//        	flag = 0;
//        }
//    }else if (type==eResqustTypeShare){
//        if (UserDefaultManager::getIsFirstShared()) {
//        	canShow = true;
//        	flag = 1;
//        }
//    }
	KKShareManager::getInstance()->shareWXOneFriendJNI("",text,"",SHARE_URL,type);
}

void KKShare::shareImageToWeixin(CCImage* image,int type)
{

    saveScreenImage(image);
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "curSceen.jpg";
    KKShareManager::getInstance()->shareWXCircleJNI("","",fullpath.c_str(),"",type);
}

void KKShare::shareImageToWeixinFriend(CCImage* image,int type)
{
    
    saveScreenImage(image);
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "curSceen.jpg";
	KKShareManager::getInstance()->shareWXOneFriendJNI("","",fullpath.c_str(),"",type);
}

void KKShare::shareToSina(const char *text)
{
}
const char*  KKShare::getUDID()
{
//    return getUDIDJNI();
	std::string udid = KKShareManager::getInstance()->getUDIDJNI();
    std::string str(udid);
    log("+++++++++udid+++%s", udid.c_str());
    log("+++++++++str+++%s", str.c_str());
	return str.c_str();
}

const char* KKShare::getUDIDFromKeyChain()
{
	return "";
}

void KKShare::shareSucceed(int type)
{
    std::string strTitle = "";
    std::string strMsg = "";

    int coint = 0;//UserDefaultManager::getCointCount()+100;
//
//    if (type==eResqustTypeHelp) {
//        if (UserDefaultManager::getIsFirstHelp()) {
//            return;
//        }
//        UserDefaultManager::setFirstHelp(true);
//        UserDefaultManager::setCointCount(coint);
//        strMsg = "首次求助成功，获得100金币！";
//    }else if (type==eResqustTypeShare){
//        if (UserDefaultManager::getIsFirstShared()) {
//            return;
//        }
//        UserDefaultManager::setFirstShared(true);
//        UserDefaultManager::setCointCount(coint);
//        strMsg = "首次分享成功，获得100金币！";
//    }

//    showAlertDialogJNI(strTitle.c_str(),strMsg.c_str());

    
//    // 弹出提示框
//    ConfirmDialog* dialog = ConfirmDialog::create(true);
//    dialog->setTouchPriority(kCCMenuHandlerPriority - 12000);
//    dialog->setTag(20111);
//    dialog->setContentText(strMsg.c_str());
//    dialog->show(CCDirector::sharedDirector()->getRunningScene());
//    CCNotificationCenter::sharedNotificationCenter()->postNotification("kUpdateCoinShowNotification");

//    CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
//    scene->scheduleOnce(schedule_selector(KKShare::showDialog), 0.2);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void KKShare::showDialog(){

//    // 弹出提示框
//    ConfirmDialog* dialog = ConfirmDialog::create(true);
//    dialog->setTouchPriority(kCCMenuHandlerPriority - 12000);
//    dialog->setTag(20111);
//    dialog->setContentText(strMsg.c_str());
//    dialog->show(CCDirector::sharedDirector()->getRunningScene());
//    CCNotificationCenter::sharedNotificationCenter()->postNotification("kUpdateCoinShowNotification");
}
#endif
