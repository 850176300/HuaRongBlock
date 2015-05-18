//
//  KKVedioAdsAdapter.m
//  HuaRongBlock
//
//  Created by liuwei on 15-1-12.
//
//

#import <Foundation/Foundation.h>
#include "KKVedioAdsAdapter.h"
#include "ChartboostManager.h"

@interface KKVedioImpIOS : NSObject<ChartboostManagerDelegate>

@property(nonatomic,assign)KKVedioAdsDelegate *delegate;
+(KKVedioImpIOS*) shared;

@end

@implementation KKVedioImpIOS

+(KKVedioImpIOS*)shared
{
    static KKVedioImpIOS *instance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        instance =  [[KKVedioImpIOS alloc] init];
    });
    return instance;
}
#pragma mark - Interstitial delegate
- (void)rewardVedioIsNotReady
{
    if (_delegate) {
        _delegate->onVedioAdsLoadFailed(nullptr);
    }
}

- (void)rewardVediolDidShow
{
    
}
- (void)rewardVedioDidDismiss
{
    
}

//视频完整播放完(获得奖励)
- (void)rewardVedioDidComplete:(NSNumber *)cointNum
{
    
    if (_delegate) {
        _delegate->onVedioAdsRewarded([cointNum intValue]);
    }
}

//视频没有播放完 关闭视频
- (void)rewardVedioCloseClicked
{
    
}
@end

void KKVedioAdsAdapter::showVedioAds(){
    [[ChartboostManager sharedManager]setDelegate:[KKVedioImpIOS shared]];
    [[ChartboostManager sharedManager]showRewardedVideo];
}

void KKVedioAdsAdapter::setAdsDelegate(KKVedioAdsDelegate *delegate) {
    [[KKVedioImpIOS shared]setDelegate:delegate];
}