//
//  KKShare.h
//  Brain
//
//  Created by tangwei1 on 14-5-29.
//
//

#ifndef Brain_KKShare_h
#define Brain_KKShare_h

#include "cocos2d.h"
USING_NS_CC;
enum {
    eResqustTypeShare = 0,
    eResqustTypeHelp,
};


class KKShare {
    
    
public:
    static void shareToWeixinCircle(const char*title,const char*msg,const char*imagePath,const char*url,int type);
    static void shareToWeixinOneFriend(const char*title,const char*msg,const char*imagePath,const char*url,int type);
    
    static void shareToWeixin(const char* text,int type);
    static void shareToWeixinFriend(const char* text,int type);
    static void shareImageToWeixin(CCImage* image,int type);
    static void shareImageToWeixinFriend(CCImage* image,int type);
    static void shareToSina(const char* text);
    
    static const char* getUDID();
    static const char* getUDIDFromKeyChain();
    
    static void shareSucceed(int type);
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void showDialog();
#endif
};

#endif
