//
//  KKShare.m
//  Brain
//
//  Created by tangwei1 on 14-5-29.
//
//

#include "KKShare.h"
#import "KKShareWeiXin.h"
#import "KKShareSina.h"
#import "KKUDID.h"
#include "UserDefaultManager.h"
#include "KKShareImpIOS.h"
#include "HeadNode.h"
#include "ImageUtil.h"

#define APP_DownloadURL @"https://itunes.apple.com/app/id919107620"

#define Title "我爱对诗词"

//type  1  求助
//type  2  分享

void KKShare::shareToWeixinCircle(const char*title,const char*msg,const char*imagePath,const char*url,int type)
{
    
}

void KKShare::shareToWeixinOneFriend(const char*title,const char*msg,const char*imagePath,const char*url,int type)
{
    
}

void KKShare::shareToWeixin(const char *text,int  type)
{
    [[KKShareImpIOS sharedManager]setShareType:type];
    [[KKShareWeiXin sharedManager] sendNews:[NSString stringWithUTF8String:Title]
                                description:[NSString stringWithFormat:@"%@,____你知道这首古诗词吗？ 来一起动动脑子吧! %@",[NSString stringWithUTF8String:text],APP_DownloadURL]
                                 thumbImage:[UIImage imageNamed:[NSString stringWithUTF8String:"Icon-120.png"]]
                                 webpageUrl:APP_DownloadURL
                                WXSceneType:WXSceneTypeAllFriends];
    
}

void KKShare::shareToWeixinFriend(const char *text,int type)
{
    [[KKShareImpIOS sharedManager]setShareType:type];
    [[KKShareWeiXin sharedManager] sendNews:[NSString stringWithUTF8String:Title]
                                description:[NSString stringWithFormat:@"%@,____你知道这首古诗词吗？ 来一起动动脑子吧! %@",[NSString stringWithUTF8String:text],APP_DownloadURL]
                                 thumbImage:[UIImage imageNamed:[NSString stringWithUTF8String:"Icon-120.png"]]
                                 webpageUrl:APP_DownloadURL
                                WXSceneType:WXSceneTypeFriend];
    
}

void KKShare::shareImageToWeixin(cocos2d::Image *image, int type)
{
    [[KKShareImpIOS sharedManager]setShareType:type];
    [[KKShareWeiXin sharedManager] sendImage:ImageUtil::CCImageToUIImage(image) originImage:ImageUtil::CCImageToUIImage(image) WXSceneType:WXSceneTypeAllFriends];
}

void KKShare::shareImageToWeixinFriend(cocos2d::Image *image, int type)
{
    [[KKShareImpIOS sharedManager]setShareType:type];
    
    [[KKShareWeiXin sharedManager] sendImage:ImageUtil::CCImageToUIImage(image) originImage:ImageUtil::CCImageToUIImage(image) WXSceneType:WXSceneTypeFriend];
}
void KKShare::shareToSina(const char *text)
{
//    NSString *question = [NSString stringWithUTF8String:text];
    [[KKShareSina sharedManager] shareText:[NSString stringWithFormat:@"你知道这个足球明星吗？ 来一起猜动动脑子吧! %@",APP_DownloadURL]
                                    image:[UIImage imageNamed:[NSString stringWithUTF8String:text] ]];
}

const char* KKShare::getUDID()
{
    return [[KKUDID UDID] UTF8String];
}

const char* KKShare::getUDIDFromKeyChain()
{
    return [[KKUDID getUDIDFromKeyChain] UTF8String];
}

void KKShare::shareSucceed(int type)
{
    NSString *strTitle = @"";
    NSString *strMsg = @"";
//    int count = UserDefaultManager::getDiamond()+100;
//    if (type==eResqustTypeHelp) {
//        if (UserDefaultManager::getIsFirstHelp()) {
//            return;
//        }
//        UserDefaultManager::setFirstHelp(true);
//        UserDefaultManager::setCointCount(count);
//        strMsg = @"首次求助成功，获得100金币！";
//    }else if (type==eResqustTypeShare){
//        if (UserDefaultManager::getIsFirstShared()) {
//            return;
//        }
//        UserDefaultManager::setFirstShared(true);
//        UserDefaultManager::setCointCount(count);
//        strMsg = @"首次分享成功，获得100金币！";
//    }
//    
//    CCNotificationCenter::sharedNotificationCenter()->postNotification("kUpdateCoinShowNotification");
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:strTitle message:strMsg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [alert show];
    [alert release];
    
}