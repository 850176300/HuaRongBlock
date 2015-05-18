//
//  IOSAdsWrapper.m
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#import "IOSAdsWrapper.h"
#import "ChartboostManager.h"

@interface IOSAdsManager () <ChartboostManagerDelegate>
{
    KKAdsDelegate* _delegate;
}

@end
@implementation IOSAdsManager

static IOSAdsManager* instance = nil;

+ (IOSAdsManager *)sharedIOSAdsManager
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if ( !instance ) {
            instance = [[IOSAdsManager alloc] init];
        }
    });
    return instance;
}

- (id)init
{
    if ( self = [super init] ) {
        [[ChartboostManager sharedManager]setDelegate:self];
    }
    return self;
}

+ (void)purgeIOSAdsManager
{
    if ( instance ) {
        [instance release];
        instance = nil;
    }
}

- (void)dealloc
{
    [super dealloc];
}

- (void)setAdsDelegate:(KKAdsDelegate *)delegate
{
    _delegate = delegate;
}

//- (void)setBannerAdsPosition:(BannerAdsPosition)position
//{
//    [[AdsMoGoManager sharedManager] setBannerAdPosition:position];
//}

- (BOOL)bannerIsVisible
{
    return [[AdsMoGoManager sharedManager] bannerIsShowing];
}

-(void)preloadAds
{
    [[AdsMoGoManager sharedManager]preloadAllAds];
    [AdsMoGoManager sharedManager].BannerAdPosition = BannerAdPositionBottom;
}
- (void)preloadAdsForBannerId:(NSString *)bannerId
               interstitialId:(NSString *)interstitialId
{
    [[AdsMoGoManager sharedManager] preloadAdsForBannerId:bannerId interstitialId:interstitialId];
}

- (void)showBannerAds
{
    [[AdsMoGoManager sharedManager] showBannerAd];
}

- (void)removeBannerAds
{
    [[AdsMoGoManager sharedManager] removeBannerAd];
}

- (void)setBannerAdsVisible:(BOOL)yesOrNo
{
    if ( !yesOrNo ) {
        [[AdsMoGoManager sharedManager] hideBannerAd];
    } else {
        [[AdsMoGoManager sharedManager] showBannerAd];
    }
    
}

- (CGSize)bannerAdsSize
{
    return [[AdsMoGoManager sharedManager] bannerSize];
}

- (void)showInterstitalAds
{
    [[AdsMoGoManager sharedManager] showInterstitial];
}

#pragma mark -
#pragma mark GADBannerViewDelegate methods

#pragma mark - Banner delegate
- (void)bannerAdDidLoad
{
    if ( _delegate ) {
        _delegate->onBannerLoadSuccessfully();
    }
}

- (void)bannerAdDidFailToLoad
{
    if ( _delegate ) {
        _delegate->onBannerLoadFailed(0);
    }
}

// 点击了banner时候调用
- (void)willPresentModalViewForBanner
{
    if ( _delegate ) {
        _delegate->onBannerClicked();
    }
}
// 点击了banner后，广告内容页dismiss时调用
- (void)didDismissModalViewForBanner
{
    if ( _delegate ) {
        _delegate->onBannerDismissed();
    }
}
// 跳到app store时调用
- (void)willLeaveApplicationFromBanner
{
    
}

#pragma mark - Interstitial delegate

- (void)interstitialDidFailToLoad
{
    if ( _delegate ) {
        _delegate->onInterstitialAdFailed(0);
    }
}

- (void)interstitialDidShow
{
    cocos2d::CCDirector::sharedDirector()->pause();
    if ( _delegate ) {
        _delegate->onInterstitialShown();
    }
}

- (void)interstitialDidDismiss
{
    cocos2d::CCDirector::sharedDirector()->resume();
    if ( _delegate ) {
        _delegate->onInterstitialDismissed();
    }
}

@end
