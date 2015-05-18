//
//  ChartboostManager.m
//  ChartboostExampleApp
//
//  Created by wuguiling on 1/23/15.
//  Copyright (c) 2015 chartboost. All rights reserved.
//

#import "ChartboostManager.h"
#import <Chartboost/Chartboost.h>
#import <Chartboost/CBNewsfeed.h>
#import "AppConfigs.h"

@interface ChartboostManager()<CBNewsfeedDelegate,ChartboostDelegate>
{
    BOOL _vedioHasCached;
}
@end

@implementation ChartboostManager

@synthesize viewController = _viewController;

@synthesize location = _location;

@synthesize delegate = _delegate;

+ (ChartboostManager *)sharedManager
{
    static ChartboostManager *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (!instance) {
            instance = [[ChartboostManager alloc] init];
        }
    });
    return instance;
}

///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Getter methods
///////////////////////////////////////////////////////////////////////////////////////////////
- (UIViewController *)viewController
{
    if (!_viewController) {
        _viewController = [[self getWindow] rootViewController];
    }
    NSAssert(!!_viewController, @"没有设置viewController,请先设置");
    return _viewController;
}

- (void)setViewController:(UIViewController *)viewController
{
    if (_viewController != viewController) {
        _viewController = viewController;
    }
}

- (UIWindow *)getWindow
{
    return [[[UIApplication sharedApplication] windows] objectAtIndex:0];
}


-(void)preload
{
    _location = @"";
    _vedioHasCached = NO;
    
    NSString* appId = CHARTBOOST_APP_ID;
    NSString* appSignature = CHARTBOOST_APP_SIGNATURE;
    
    if ([appId isEqualToString:@""]) {
        appId = @"CHARTBOOST_APP_ID";
    }
    if ([appSignature isEqualToString:@""]) {
        appSignature = @"CHARTBOOST_APP_ID";
    }
    [Chartboost startWithAppId:CHARTBOOST_APP_ID appSignature:CHARTBOOST_APP_SIGNATURE delegate:self];
    
    [Chartboost cacheRewardedVideo:_location];
    [Chartboost cacheMoreApps:_location];
    
    // Begin Newsfeed initialization.
    [CBNewsfeed startWithDelegate:self];
    
    
}

-(void)cacheInterstitial {
    [Chartboost cacheInterstitial:_location];
}

-(void)cacheMoreApps {
    [Chartboost cacheMoreApps:_location];
}

-(void)cacheRewardVideo
{
    [Chartboost cacheRewardedVideo:_location];
}

-(void)showInterstitial
{
    
    [Chartboost showInterstitial:_location];
}

-(void)showMoreApps
{
    [Chartboost showMoreApps:self.viewController location:_location];
}
-(void)showNewsfeed
{
    
    [Chartboost cacheRewardedVideo:_location];
}

-(void)showRewardedVideo
{
    if (_vedioHasCached) {
        _vedioHasCached = NO;
        [Chartboost showRewardedVideo:_location];
    }else{
        [self cacheRewardVideo];
        if (_delegate) {
            [_delegate performSelector:@selector(rewardVedioIsNotReady) withObject:nil];
        }
    }
}

-(void)showInPlay
{
    
}

-(void)showNotification
{
    [CBNewsfeed showNotificationUI];
}



#pragma mark ------- Chartboost Delegate Methods---------

#pragma mark - Interstitial Delegate
- (BOOL)shouldRequestInterstitial:(CBLocation)location
{
    return YES;
}

- (BOOL)shouldDisplayInterstitial:(CBLocation)location
{
    NSLog(@"about to display interstitial at location %@", location);
    // For example:
    // if the user has left the main menu and is currently playing your game, return NO;
    
    // Otherwise return YES to display the interstitial
    return YES;
}


- (void)didDisplayInterstitial:(CBLocation)location {
    NSLog(@"Did display interstitial");
    
    // We might want to pause our in-game audio, lets double check that an ad is visible
    if ([Chartboost isAnyViewVisible]) {
        // Use this function anywhere in your logic where you need to know if an ad is visible or not.
        NSLog(@"Pause audio");
    }
}

- (void)didCacheInterstitial:(NSString *)location {
    NSLog(@"interstitial cached at location %@", location);
}

- (void)didFailToLoadInterstitial:(CBLocation)location
                        withError:(CBLoadError)error
{
    switch(error){
        case CBLoadErrorInternetUnavailable: {
            NSLog(@"Failed to load Interstitial, no Internet connection !");
        } break;
        case CBLoadErrorInternal: {
            NSLog(@"Failed to load Interstitial, internal error !");
        } break;
        case CBLoadErrorNetworkFailure: {
            NSLog(@"Failed to load Interstitial, network error !");
        } break;
        case CBLoadErrorWrongOrientation: {
            NSLog(@"Failed to load Interstitial, wrong orientation !");
        } break;
        case CBLoadErrorTooManyConnections: {
            NSLog(@"Failed to load Interstitial, too many connections !");
        } break;
        case CBLoadErrorFirstSessionInterstitialsDisabled: {
            NSLog(@"Failed to load Interstitial, first session !");
        } break;
        case CBLoadErrorNoAdFound : {
            NSLog(@"Failed to load Interstitial, no ad found !");
        } break;
        case CBLoadErrorSessionNotStarted : {
            NSLog(@"Failed to load Interstitial, session not started !");
        } break;
        case CBLoadErrorNoLocationFound : {
            NSLog(@"Failed to load Interstitial, missing location parameter !");
        } break;
        default: {
            NSLog(@"Failed to load Interstitial, unknown error !");
        }
    }
}
- (void)didFailToRecordClick:(CBLocation)location
                   withError:(CBClickError)error
{
}

- (void)didDismissInterstitial:(NSString *)location {
    NSLog(@"dismissed interstitial at location %@", location);
    [self cacheInterstitial];
}

- (void)didCloseInterstitial:(CBLocation)location
{
}

- (void)didClickInterstitial:(CBLocation)location
{
}
- (BOOL)shouldDisplayMoreApps:(CBLocation)location
{
    return YES;
}
- (void)didDisplayMoreApps:(CBLocation)location
{
}
- (void)didCacheMoreApps:(CBLocation)location
{
}

- (void)didDismissMoreApps:(NSString *)location {
    NSLog(@"dismissed more apps page at location %@", location);
}

- (void)didCloseMoreApps:(CBLocation)location
{
}
- (void)didClickMoreApps:(CBLocation)location
{
}
- (void)didFailToLoadMoreApps:(CBLocation)location
                    withError:(CBLoadError)error
{
}
#pragma mark - Reward Video Delegate
- (BOOL)shouldDisplayRewardedVideo:(CBLocation)location
{
    return YES;
}
- (void)didDisplayRewardedVideo:(CBLocation)location
{
    NSLog(@"didDisplayRewardedVideo !");
}
- (void)didCacheRewardedVideo:(CBLocation)location
{
    NSLog(@"didCacheRewardedVideo !");
    _vedioHasCached = YES;
}


- (void)didFailToLoadRewardedVideo:(NSString *)location withError:(CBLoadError)error {
    switch(error){
        case CBLoadErrorInternetUnavailable: {
            NSLog(@"Failed to load Rewarded Video, no Internet connection !");
        } break;
        case CBLoadErrorInternal: {
            NSLog(@"Failed to load Rewarded Video, internal error !");
        } break;
        case CBLoadErrorNetworkFailure: {
            NSLog(@"Failed to load Rewarded Video, network error !");
        } break;
        case CBLoadErrorWrongOrientation: {
            NSLog(@"Failed to load Rewarded Video, wrong orientation !");
        } break;
        case CBLoadErrorTooManyConnections: {
            NSLog(@"Failed to load Rewarded Video, too many connections !");
        } break;
        case CBLoadErrorFirstSessionInterstitialsDisabled: {
            NSLog(@"Failed to load Rewarded Video, first session !");
        } break;
        case CBLoadErrorNoAdFound : {
            NSLog(@"Failed to load Rewarded Video, no ad found !");
        } break;
        case CBLoadErrorSessionNotStarted : {
            NSLog(@"Failed to load Rewarded Video, session not started !");
        } break;
        case CBLoadErrorNoLocationFound : {
            NSLog(@"Failed to load Rewarded Video, missing location parameter !");
        } break;
        default: {
            NSLog(@"Failed to load Rewarded Video, unknown error !");
        }
    }
}

- (void)didDismissRewardedVideo:(CBLocation)location
{
    NSLog(@"didDismissRewardedVideo !");
    [self cacheRewardVideo];
}
- (void)didCloseRewardedVideo:(CBLocation)location
{
    NSLog(@"didCloseRewardedVideo !");
}
- (void)didClickRewardedVideo:(CBLocation)location
{
    NSLog(@"didClickRewardedVideo !");
}

- (void)didCompleteRewardedVideo:(CBLocation)location withReward:(int)reward {
    NSLog(@"completed rewarded video view at location %@ with reward amount %d", location, reward);
    if (_delegate) {
        [_delegate performSelector:@selector(rewardVedioDidComplete) withObject:[NSNumber numberWithInt:reward]];
    }
}

#pragma mark - InPlay Delegate

- (void)didCacheInPlay:(CBLocation)location {
    NSLog(@"Successfully cached inPlay");
}

- (void)didFailToLoadInPlay:(CBLocation)location
                  withError:(CBLoadError)error {
    
    NSString *errorString = @"";
    switch(error){
        case CBLoadErrorInternetUnavailable: {
            errorString = @"Failed to load In Play, no Internet connection !";
        } break;
        case CBLoadErrorInternal: {
            errorString = @"Failed to load In Play, internal error !";
        } break;
        case CBLoadErrorNetworkFailure: {
            errorString = @"Failed to load In Play, network errorString !";
        } break;
        case CBLoadErrorWrongOrientation: {
            errorString = @"Failed to load In Play, wrong orientation !";
        } break;
        case CBLoadErrorTooManyConnections: {
            errorString = @"Failed to load In Play, too many connections !";
        } break;
        case CBLoadErrorFirstSessionInterstitialsDisabled: {
            errorString = @"Failed to load In Play, first session !";
        } break;
        case CBLoadErrorNoAdFound : {
            errorString = @"Failed to load In Play, no ad found !";
        } break;
        case CBLoadErrorSessionNotStarted : {
            errorString = @"Failed to load In Play, session not started !";
        } break;
        case CBLoadErrorNoLocationFound : {
            errorString = @"Failed to load In Play, missing location parameter !";
        } break;
        default: {
            errorString = @"Failed to load In Play, unknown error !";
        }
    }
}

#pragma mark - General Delegate
- (void)willDisplayVideo:(CBLocation)location
{ }
- (void)didCompleteAppStoreSheetFlow
{ }
- (void)didPauseClickForConfirmation
{ }

- (void)didFailToLoadMoreApps:(CBLoadError)error {
    switch(error){
        case CBLoadErrorInternetUnavailable: {
            NSLog(@"Failed to load More Apps, no Internet connection !");
        } break;
        case CBLoadErrorInternal: {
            NSLog(@"Failed to load More Apps, internal error !");
        } break;
        case CBLoadErrorNetworkFailure: {
            NSLog(@"Failed to load More Apps, network error !");
        } break;
        case CBLoadErrorWrongOrientation: {
            NSLog(@"Failed to load More Apps, wrong orientation !");
        } break;
        case CBLoadErrorTooManyConnections: {
            NSLog(@"Failed to load More Apps, too many connections !");
        } break;
        case CBLoadErrorFirstSessionInterstitialsDisabled: {
            NSLog(@"Failed to load More Apps, first session !");
        } break;
        case CBLoadErrorNoAdFound: {
            NSLog(@"Failed to load More Apps, Apps not found !");
        } break;
        case CBLoadErrorSessionNotStarted : {
            NSLog(@"Failed to load More Apps, session not started !");
        } break;
        default: {
            NSLog(@"Failed to load More Apps, unknown error !");
        }
    }
}

@end
