//
//  IOSAdsWrapper.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#import <Foundation/Foundation.h>

#include "KKAds.h"

@interface IOSAdsManager : NSObject

@property (nonatomic, copy) NSString* chartboostAppId;
@property (nonatomic, copy) NSString* chartboostAppSignture;

@property (nonatomic, copy) NSString* adUnitId;

+ (IOSAdsManager *)sharedIOSAdsManager;
+ (void)purgeIOSAdsManager;

-(void)preloadAds;

- (void)preloadAdsForBannerId:(NSString *)bannerId
               interstitialId:(NSString *)interstitialId;

- (void)setAdsDelegate:(KKAdsDelegate *)delegate;

//- (void)setBannerAdsPosition:(BannerAdsPosition)position;
- (BOOL)bannerIsVisible;

- (void)showBannerAds;
- (void)removeBannerAds;
- (void)setBannerAdsVisible:(BOOL)yesOrNo;

- (CGSize)bannerAdsSize;

- (void)showInterstitalAds;

@end
