//
//  KKUDID.h
//  SvUDID
//
//  Created by 刘 波 on 13-11-29.
//  Copyright (c) 2013年 maple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface KKUDID : NSObject

/*
 * @brief obtain Unique Device Identity
 */
+ (NSString*)UDID;

+ (BOOL)updateUDIDInKeyChain:(NSString*)newUDID;

+ (BOOL)setUDIDToKeyChain:(NSString*)udid;

+ (BOOL)removeUDIDFromKeyChain;

+ (NSString*)getUDIDFromKeyChain;

@end
