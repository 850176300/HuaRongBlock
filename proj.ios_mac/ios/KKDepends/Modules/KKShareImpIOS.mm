//
//  KKShareImpIOS.m
//  BrainFootball
//
//  Created by studio on 14-7-6.
//
//

#import "KKShareImpIOS.h"
#import "KKShare.h"

@implementation KKShareImpIOS

+ (KKShareImpIOS *)sharedManager{
    
    static KKShareImpIOS *instance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        instance =  [[KKShareImpIOS alloc] init];
    });
    return instance;
}
-(void)shareSucceed
{
    KKShare::shareSucceed(_shareType);
}
@end
