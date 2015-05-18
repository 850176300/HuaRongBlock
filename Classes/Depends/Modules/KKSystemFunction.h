//
//  KKSystemFunction.h
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-7-9.
//
//

#ifndef __MysteryGuardians__SystemFunction__
#define __MysteryGuardians__SystemFunction__
#include "cocos2d.h"
#include "KKDialogDelegate.h"
USING_NS_CC;

typedef void (CCObject::*CallFunction)(void*,void*);
//#define callBack(_SELECTOR) (CallFunction)(&_SELECTOR)

typedef enum {
    NewsModeLaunch = 0,
    NewsModeResume,
    NewsModeReturnHome,
    NewsModeCount,
}NewsBlastMode;

class KKSystemFunction {
    
public:
	KKSystemFunction();
	~KKSystemFunction();
public:
    /**
     *  @brief Send Email by system default.
     *
     *  @param subject email subject.
     *  @param content email subject.
     */
    virtual void sendEmail(const char* subject, const char* body);
    
    // 打开一个链接
    static void openUrl(const char* url);
    
    // 去评论
    static void go2RateUs(const char* appId, const char* alertMessage);
    
    // 获取设备名称
    static const char* getDeviceName();
    /**
     *
     */
    virtual void popAlertDialog(const char* message);
    void popAlertDialog(const char*msg,int tag,const char*cancle,const char*yes);
    virtual void makeToast(const char* message);
    
    virtual void saveImage(std::string fileCache,CCObject*,CallFunction);
	std::string getSdCardPath();
	bool checkNetworkAvailable();
	bool isTabletAvailable();
    float densityScale();
    
    /*
     * 向服务器发送后台统计数据，在APP出的时候发送
     */
    void refreshDCIM(std::string sFileDir);
    void setDialogDelegate(KKDialogDelegate* delegate);
};

#endif /* defined(__MysteryGuardians__SystemFunction__) */
