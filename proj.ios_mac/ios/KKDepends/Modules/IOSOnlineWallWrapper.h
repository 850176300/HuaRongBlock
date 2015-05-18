//
//  IOSOnlineWallWrapper.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#import <Foundation/Foundation.h>

@interface IOSOnlineWallManager : NSObject

+ (IOSOnlineWallManager *)sharedOnlineWallManager;
+ (void)purgeOnlineWallManager;

- (void)loadOnlineWall;
- (void)checkPoint;

@end
