//
//  ChartboostManager.h
//  ChartboostExampleApp
//
//  Created by wuguiling on 1/23/15.
//  Copyright (c) 2015 chartboost. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ChartboostManagerDelegate;

@interface ChartboostManager : NSObject

@property (nonatomic, assign) UIViewController *viewController;

@property (nonatomic, assign) NSString* location;

@property (nonatomic, assign) id<ChartboostManagerDelegate> delegate;

+ (ChartboostManager *)sharedManager;

-(void)cacheInterstitial;

-(void)cacheMoreApps;

-(void)cacheRewardVideo;

-(void)preload;

-(void)showInterstitial;

-(void)showMoreApps;

-(void)showNewsfeed;

-(void)showRewardedVideo;

//-(void)showInPlay;

-(void)showNotification;

@end



@protocol ChartboostManagerDelegate <NSObject>

#pragma mark - Interstitial delegate
@optional
- (void)interstitialDidFailToLoad;
- (void)interstitialDidShow;
- (void)interstitialDidDismiss;

#pragma mark - Interstitial delegate
@optional
- (void)rewardVedioIsNotReady;
- (void)rewardVediolDidShow;
- (void)rewardVedioDidDismiss;

//视频完整播放完(获得奖励)
- (void)rewardVedioDidComplete:(NSNumber*)cointNum;

//视频没有播放完 关闭视频
- (void)rewardVedioCloseClicked;

#pragma mark - NewsBlast delegate
@optional
- (void)newsblastDidNotShow;
- (void)newsblastDidShow;
- (void)newsblastDidClickOK;
- (void)newsblastDidClickCancel;

@end

