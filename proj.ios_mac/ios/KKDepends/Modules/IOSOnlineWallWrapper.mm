//
//  IOSOnlineWallWrapper.m
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#import "IOSOnlineWallWrapper.h"
#import "DMOfferWallViewController.h"
#import "DMOfferWallManager.h"

#include "KKOnlineWall.h"

#define kPublisherID @"96ZJ27yQzeOPLwTAXT"

@interface IOSOnlineWallManager () <DMOfferWallManagerDelegate, DMOfferWallDelegate>

@end

@implementation IOSOnlineWallManager
{
    DMOfferWallViewController* _offerWallViewController;
    DMOfferWallManager* _offerWallManager;
    
    int _cointCount;
    int _consumeCount;
}

static IOSOnlineWallManager* instance = nil;

+ (IOSOnlineWallManager *)sharedOnlineWallManager
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if ( !instance ) {
            instance = [[IOSOnlineWallManager alloc] init];
        }
    });
    
    return instance;
}

- (id)init
{
    if ( self = [super init] ) {
        
        _cointCount = 0;
        _consumeCount = 0;
        
        _offerWallViewController = [[DMOfferWallViewController alloc] initWithPublisherID:kPublisherID];
        // !!!:重要：如果需要禁用应用内下载，请将此值设置为YES。
//        _offerWallViewController.disableStoreKit = YES;
        _offerWallViewController.delegate = self;
        
        _offerWallManager = [[DMOfferWallManager alloc] initWithPublishId:kPublisherID userId:nil];
        _offerWallManager.delegate = self;
    }
    
    return self;
}

- (void)dealloc
{
    _offerWallViewController.delegate = nil;
    [_offerWallViewController release];
    _offerWallViewController = nil;
    
    _offerWallManager.delegate = nil;
    [_offerWallManager release];
    _offerWallManager = nil;
    
    [super dealloc];
}

+ (void)purgeOnlineWallManager
{
    if ( instance ) {
        [instance release];
        instance = nil;
    }
}

- (void)loadOnlineWall
{
    UIViewController* root = [[[[UIApplication sharedApplication] windows] objectAtIndex:0] rootViewController];
    [_offerWallViewController presentOfferWallWithViewController:root];
}

#pragma mark - DMOfferWallDelegate <NSObject>
// 积分墙开始加载数据。
// Offer wall starts to work.
- (void)offerWallDidStartLoad {
    NSLog(@"offerWallDidStartLoad");
}

// 积分墙加载完成。此方法实现中可进行积分墙入口Button显示等操作。
// Load offer wall successfully. You can set your IBOutlet.hidden to NO in this callback.
// This IBOutlet is the one which response to present OfferWall.
- (void)offerWallDidFinishLoad {
    NSLog(@"offerWallDidFinishLoad");
    //    [self.view makeToast:@"Offer Wall Loading Finished."];
}

// 积分墙加载失败。可能的原因由error部分提供，例如网络连接失败、被禁用等。建议在此隐藏积分墙入口Button。
// Failed to load offer wall. You should set THE IBOutlet.hidden to YES in this callback.
- (void)offerWallDidFailLoadWithError:(NSError *)error {
    NSLog(@"offerWallDidFailLoadWithError:%@", error);
    //    [self.view makeToast:@"Offer Wall Loading Failed."];
}

-(void)offerWallDidClosed{
    NSLog(@"offer Wall closed!");
    //    [self.view makeToast:@"Offer Wall closed."];
}

#pragma mark - DMOfferWallManagerDelegate <NSObject>

#pragma mark Point Check Callbacks
// 积分查询成功之后，回调该接口，获取总积分和总已消费积分。
- (void)offerWallDidFinishCheckPointWithTotalPoint:(NSInteger)totalPoint andTotalConsumedPoint:(NSInteger)consumed {
    NSLog(@"offerWallDidFinishCheckPoint");
    _cointCount = totalPoint;
    _consumeCount = consumed;
    [self consume:(totalPoint-consumed)];
}

// 积分查询失败之后，回调该接口，返回查询失败的错误原因。
- (void)offerWallDidFailCheckPointWithError:(NSError *)error {
    NSLog(@"offerWallDidFailCheckPointWithError:%@", error);
    _cointCount = 0;
    _consumeCount = 0;
}

#pragma mark Consume Callbacks
// 消费请求正常应答后，回调该接口，并返回消费状态（成功或余额不足），以及总积分和总已消费积分。
- (void)offerWallDidFinishConsumePointWithStatusCode:(DMOfferWallConsumeStatusCode)statusCode
                                          totalPoint:(NSInteger)totalPoint
                                  totalConsumedPoint:(NSInteger)consumed {
    NSLog(@"offerWallDidFinishConsumePoint");
    switch (statusCode) {
        case DMOfferWallConsumeStatusCodeSuccess:
            KKOnlineWall::bringCoinsToNative(_cointCount-_consumeCount);
            _cointCount = 0;
            _consumeCount = 0;
            NSLog(@"消费成功！");
            break;
        case DMOfferWallConsumeStatusCodeInsufficient:
            NSLog(@"消费失败，余额不足！");
            break;
        default:
            break;
    }
}

// 消费请求异常应答后，回调该接口，并返回异常的错误原因。
- (void)offerWallDidFailConsumePointWithError:(NSError *)error {
    NSLog(@"offerWallDidFailConsumePointWithError:%@", error);
}

- (void)offerWallDidCheckEnableState:(BOOL)enable
{
    
}

- (void)checkPoint
{
    [_offerWallManager requestOnlinePointCheck];
}

- (void)consume:(int)count
{
    [_offerWallManager requestOnlineConsumeWithPoint:count];
}

@end
