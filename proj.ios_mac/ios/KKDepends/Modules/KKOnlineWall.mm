//
//  KKOnlineQWall.m
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#include "KKOnlineWall.h"
#import "IOSOnlineWallWrapper.h"
#include "UserDefaultManager.h"
#include "CommonMessageBox.h"

void KKOnlineWall::showOnlineWall()
{
    [[IOSOnlineWallManager sharedOnlineWallManager] loadOnlineWall];
}

void KKOnlineWall::bringCoinsToNative()
{
    [[IOSOnlineWallManager sharedOnlineWallManager] checkPoint];
}

void KKOnlineWall::bringCoinsToNative(int num)
{
    int coin = UserDefaultManager::getCointCount();
    coin = coin + num;
    UserDefaultManager::setCointCount(coin);
    CommonMessageBox* messageBox = CommonMessageBox::showMessageBox("提示", "积分墙的金币已到账，请查收", NULL,NULL,NULL,false);
    if (messageBox) {
        CCDirector::sharedDirector()->getRunningScene()->addChild(messageBox,1000);
    }
}