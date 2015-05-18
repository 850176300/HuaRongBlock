//
//  KKShareSina.m
//  KKShareKit
//
//  Created by beartech on 13-6-5.
//  Copyright (c) 2013年 可可工作室. All rights reserved.
//

#import "KKShareSina.h"

@implementation KKShareSina
@synthesize sina;
@synthesize userInfo;
@synthesize delegate;
//@synthesize statuses;
@synthesize willShareInfo;

+ (KKShareSina *)sharedManager{
    
    static KKShareSina *sharedKKShareSinaInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        sharedKKShareSinaInstance =  [[KKShareSina alloc] init];
    });
    return sharedKKShareSinaInstance;
}

-(id)init{
    self = [super init];
    if(self){
        sina = [[SinaWeibo alloc] initWithAppKey:kAppKey_Sina appSecret:kAppSecret_Sina appRedirectURI:kAppRedirectURI_Sina andDelegate:self];
        willShareInfo = [[NSMutableArray alloc]init];
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        NSDictionary *sinaweiboInfo = [defaults objectForKey:@"SinaWeiboAuthData"];
        if ([sinaweiboInfo objectForKey:@"AccessTokenKey"] && [sinaweiboInfo objectForKey:@"ExpirationDateKey"] && [sinaweiboInfo objectForKey:@"UserIDKey"])
        {
            sina.accessToken = [sinaweiboInfo objectForKey:@"AccessTokenKey"];
            sina.expirationDate = [sinaweiboInfo objectForKey:@"ExpirationDateKey"];
            sina.userID = [sinaweiboInfo objectForKey:@"UserIDKey"];
            [self getUserInfo];
        }
    }
    return self;
}

- (void)applicationDidBecomeActive{
    [self.sina applicationDidBecomeActive];
}

- (BOOL)handleOpenURL:(NSURL *)url{
    return [self.sina handleOpenURL:url];
}


#pragma mark ============================================================
#pragma mark == 授权相关
#pragma mark ============================================================
- (void)storeAuthData{
    NSDictionary *authData = [NSDictionary dictionaryWithObjectsAndKeys:
                              sina.accessToken, @"AccessTokenKey",
                              sina.expirationDate, @"ExpirationDateKey",
                              [NSString stringWithFormat:@"%lld",[sina.userID longLongValue]], @"UserIDKey",
                              sina.refreshToken, @"refresh_token", nil];
    [[NSUserDefaults standardUserDefaults] setObject:authData forKey:@"SinaWeiboAuthData"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:Notification_KKShareSinaDidLogin object:nil];

    
    [self getUserInfo];
    
    if (willShareInfo && [willShareInfo count]>0) {
        NSDictionary *dic = [willShareInfo objectAtIndex:0];
        NSString *postText = [dic objectForKey:@"status"];
        UIImage *postImage = [dic objectForKey:@"pic"];
        if (postText && postImage) {
            [self shareText:postText image:postImage delegate:delegate];
        }
        else if (postText){
            [self shareText:postText  delegate:delegate];
        }
    }
}

- (void)removeAuthData{
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:@"SinaWeiboAuthData"];
    [userInfo release];userInfo = nil;
    [[NSNotificationCenter defaultCenter] postNotificationName:Notification_KKShareSinaDidLogout object:nil];
}

- (NSDictionary*)readAuthData{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSDictionary *sinaweiboInfo = [defaults objectForKey:@"SinaWeiboAuthData"];
    return sinaweiboInfo;
}

- (BOOL)isAuthValid{
    return sina.isAuthValid;
}

- (void)logIn{
    [sina logIn];
}

- (void)logOut{
    [sina logOut];
}

- (NSString*)OAuthInfomationForKey:(NSString*)key{
    if ([self isAuthValid]) {
        NSMutableDictionary *dictionary = [[NSUserDefaults standardUserDefaults] objectForKey:@"SinaWeiboAuthData"];
        return [dictionary objectForKey:key];
    }
    else{
        return nil;
    }
}


#pragma mark ============================================================
#pragma mark == 网络请求
#pragma mark ============================================================
//获取用户信息
- (void)getUserInfo{
    if ([self isAuthValid]) {
        [sina requestWithURL:@"users/show.json"
                      params:[NSMutableDictionary dictionaryWithObject:sina.userID forKey:@"uid"]
                  httpMethod:@"GET"
                    delegate:self];
    }
    else{
        [self logIn];
    }
}

//获取用户发布的微博
- (void)getTimeline{
    if ([self isAuthValid]) {
        [sina requestWithURL:@"statuses/user_timeline.json"
                      params:[NSMutableDictionary dictionaryWithObject:sina.userID forKey:@"uid"]
                  httpMethod:@"GET"
                    delegate:self];
    }
    else{
        [self logIn];
    }
}

//分享【文字】
- (void)shareText:(NSString*)text
{
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    [params setObject:(text)?text:@""             forKey:@"status"];

    if ([self isAuthValid]) {
        [sina requestWithURL:@"statuses/update.json" params:params httpMethod:@"POST" delegate:self];
    }
    else{
        [willShareInfo removeAllObjects];
        [willShareInfo addObject:params];
        [self logIn];
    }
}

- (void)shareText:(NSString *)text delegate:(id<KKShareSinaDelegate>)aDelegate{
    delegate = aDelegate;
    delegateClass = object_getClass(aDelegate);
    [self shareText:text];
}

//分享【图片+文字】
- (void)shareText:(NSString*)text image:(UIImage*)image
{
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    [params setObject:(text)?text:@""             forKey:@"status"];
    [params setObject:(image)?image:@""           forKey:@"pic"];

    if ([self isAuthValid]) {
        [sina requestWithURL:@"statuses/upload.json" params:params httpMethod:@"POST" delegate:self];
    }
    else{
        [willShareInfo removeAllObjects];
        [willShareInfo addObject:params];
        [self logIn];
    }
}

- (void)shareText:(NSString *)text image:(UIImage *)image delegate:(id<KKShareSinaDelegate>)aDelegate{
    delegate = aDelegate;
    delegateClass = object_getClass(aDelegate);
    [self shareText:text image:image];
}

#pragma mark ============================================================
#pragma mark ==SinaWeiboDelegate
#pragma mark ============================================================
- (void)sinaweiboDidLogIn:(SinaWeibo *)sinaweibo
{
    NSLog(@"sinaweiboDidLogIn userID = %@ accesstoken = %@ expirationDate = %@ refresh_token = %@", sinaweibo.userID, sinaweibo.accessToken, sinaweibo.expirationDate,sinaweibo.refreshToken);
    [self storeAuthData];
}

- (void)sinaweiboDidLogOut:(SinaWeibo *)sinaweibo
{
    NSLog(@"sinaweiboDidLogOut");
    [self removeAuthData];
}

- (void)sinaweiboLogInDidCancel:(SinaWeibo *)sinaweibo
{
    NSLog(@"sinaweiboLogInDidCancel");
}

- (void)sinaweibo:(SinaWeibo *)sinaweibo logInDidFailWithError:(NSError *)error
{
    NSLog(@"sinaweibo logInDidFailWithError %@", error);
}

- (void)sinaweibo:(SinaWeibo *)sinaweibo accessTokenInvalidOrExpired:(NSError *)error
{
    NSLog(@"sinaweiboAccessTokenInvalidOrExpired %@", error);
    [self removeAuthData];
}

#pragma mark ============================================================
#pragma mark ==SinaWeiboRequest Delegate
#pragma mark ============================================================
- (void)request:(SinaWeiboRequest *)request didFailWithError:(NSError *)error
{
    //获取用户信息
    if ([request.url hasSuffix:@"users/show.json"])
    {
        [userInfo release], userInfo = nil;
    }
    //获取用户发布的微博
    else if ([request.url hasSuffix:@"statuses/user_timeline.json"])
    {
        //        [statuses release], statuses = nil;
    }
    //分享【文字】
    else if ([request.url hasSuffix:@"statuses/update.json"])
    {
        NSLog(@"Post status failed with error : %@", error);
        Class currentClass = object_getClass(self.delegate);
        if ((currentClass == delegateClass) && [self.delegate respondsToSelector:@selector(KKShareSina_ShareFailWithError:)]) {
            [self.delegate KKShareSina_ShareFailWithError:error];
        }
        
        [[TKAlertCenter defaultCenter] postAlertWithMessage:[NSString stringWithFormat:@"分享【文字】失败: %@",error]];
        [willShareInfo removeAllObjects];
        [[NSNotificationCenter defaultCenter] postNotificationName:Notification_KKShareSinaDidFail object:nil];
    }
    //分享【图片+文字】
    else if ([request.url hasSuffix:@"statuses/upload.json"])
    {
        NSLog(@"Post image status failed with error : %@", error);
        
        Class currentClass = object_getClass(self.delegate);
        if ((currentClass == delegateClass) && [self.delegate respondsToSelector:@selector(KKShareSina_ShareFailWithError:)]) {
            [self.delegate KKShareSina_ShareFailWithError:error];
        }
        
        [[TKAlertCenter defaultCenter] postAlertWithMessage:[NSString stringWithFormat:@"分享【图片+文字】失败: %@",error]];
        [willShareInfo removeAllObjects];
        [[NSNotificationCenter defaultCenter] postNotificationName:Notification_KKShareSinaDidFail object:nil];
    }
}

- (void)request:(SinaWeiboRequest *)request didFinishLoadingWithResult:(id)result
{
    //获取用户信息
    if ([request.url hasSuffix:@"users/show.json"])
    {
        if ([result isKindOfClass:[NSDictionary class]]) {
            [userInfo release];userInfo = nil;
            userInfo = [result retain];
            NSLog(@"【新浪微博】获取用户信息成功！");
        }
        else{
            NSLog(@"【新浪微博】获取用户信息失败！");
        }
    }
    //获取用户发布的微博
    else if ([request.url hasSuffix:@"statuses/user_timeline.json"])
    {
        //        [statuses release];
        //        statuses = [[result objectForKey:@"statuses"] retain];
    }
    else if ([request.url hasSuffix:@"statuses/update.json"])
    {
        Class currentClass = object_getClass(self.delegate);
        if ((currentClass == delegateClass) && [self.delegate respondsToSelector:@selector(KKShareSina_ShareFinishLoadingWithResult:)]) {
            [self.delegate KKShareSina_ShareFinishLoadingWithResult:result];
        }
        
        [[TKAlertCenter defaultCenter] postAlertWithMessage:@"分享【文字】成功"];
        [willShareInfo removeAllObjects];
        [[NSNotificationCenter defaultCenter] postNotificationName:Notification_KKShareSinaDidSuccess object:nil];
    }
    else if ([request.url hasSuffix:@"statuses/upload.json"])
    {
        Class currentClass = object_getClass(self.delegate);
        if ((currentClass == delegateClass) && [self.delegate respondsToSelector:@selector(KKShareSina_ShareFinishLoadingWithResult:)]) {
            [self.delegate KKShareSina_ShareFinishLoadingWithResult:result];
        }
        
        [[TKAlertCenter defaultCenter] postAlertWithMessage:@"分享【图片+文字】成功"];
        [willShareInfo removeAllObjects];
        [[NSNotificationCenter defaultCenter] postNotificationName:Notification_KKShareSinaDidSuccess object:nil];
    }
}


@end
