//
//  KKShareImpIOS.h
//  BrainFootball
//
//  Created by studio on 14-7-6.
//
//

#import <Foundation/Foundation.h>


@interface KKShareImpIOS : NSObject

@property(nonatomic,assign)int shareType;
+ (KKShareImpIOS *)sharedManager;

-(void)shareSucceed;
@end
