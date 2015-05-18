//
//  KKShareSina.h
//  KKShareKit
//
//  Created by beartech on 13-6-5.
//  Copyright (c) 2013年 可可工作室. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SinaWeibo.h"
#import "TKAlertCenter.h"

/**将下面注释取消，并定义自己的app key，app secret以及授权跳转地址uri
 此demo即可编译运行**/

#define kAppKey_Sina             @"4220610488"
#define kAppSecret_Sina          @"32c72eefb3c1054a97b814ce4b2418de"
#define kAppRedirectURI_Sina     @"http://www.kekestudio.com"
#define Notification_KKShareSinaDidLogin  @"Notification_KKShareSinaDidLogin"
#define Notification_KKShareSinaDidLogout @"Notification_KKShareSinaDidLogout"
#define Notification_KKShareSinaDidSuccess  @"Notification_KKShareSinaDidSuccess"
#define Notification_KKShareSinaDidFail     @"Notification_KKShareSinaDidFail"

#ifndef kAppKey_Sina
#error
#endif

#ifndef kAppSecret_Sina
#error
#endif

#ifndef kAppRedirectURI_Sina
#error
#endif

#define OAuthInfomation_Sina_userID          @"UserIDKey"
#define OAuthInfomation_Sina_accessToken     @"AccessTokenKey"
#define OAuthInfomation_Sina_refreshToken    @"refresh_token"
#define OAuthInfomation_Sina_expirationDate  @"ExpirationDateKey"

@protocol KKShareSinaDelegate;
Class object_getClass(id object);

@interface KKShareSina : NSObject<SinaWeiboDelegate,SinaWeiboRequestDelegate>{
    Class delegateClass;
}


@property (retain, nonatomic) SinaWeibo *sina;
@property (retain, nonatomic) NSDictionary *userInfo;
@property (assign, nonatomic) id<KKShareSinaDelegate> delegate;
//@property(retain, nonatomic) NSArray *statuses;

@property (retain, nonatomic)NSMutableArray *willShareInfo;



+ (KKShareSina *)sharedManager;
- (void)applicationDidBecomeActive;
- (BOOL)handleOpenURL:(NSURL *)url;

#pragma mark ============================================================
#pragma mark == 授权相关
#pragma mark ============================================================
- (BOOL)isAuthValid;
- (void)logIn;
- (void)logOut;
- (NSString*)OAuthInfomationForKey:(NSString*)key;

#pragma mark ============================================================
#pragma mark == 分享相关
#pragma mark ============================================================
//获取用户发布的微博
- (void)getTimeline;

//分享【文字】
- (void)shareText:(NSString*)text;
//分享【文字】
- (void)shareText:(NSString*)text delegate:(id<KKShareSinaDelegate>)aDelegate;

//分享【图片+文字】
- (void)shareText:(NSString*)text image:(UIImage*)image;

//分享【图片+文字】
- (void)shareText:(NSString*)text image:(UIImage*)image delegate:(id<KKShareSinaDelegate>)aDelegate;

@end


@protocol KKShareSinaDelegate <NSObject>
@optional
- (void)KKShareSina_ShareFailWithError:(NSError *)error;
- (void)KKShareSina_ShareFinishLoadingWithResult:(id)result;

@end







