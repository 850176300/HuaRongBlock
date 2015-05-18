//
//  IOSIAPWrapper.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#import <Foundation/Foundation.h>

#include "KKInAppBilling.h"

@interface IOSIAPManager : NSObject

+ (IOSIAPManager *)sharedIOSIAPManager;
+ (void)purgeIOSIAPManager;

- (void)setIAPDelegate:(KKIAPDelegate *)delegate;
- (void)purchase:(NSString*)pid;
- (void)restore;

@end
