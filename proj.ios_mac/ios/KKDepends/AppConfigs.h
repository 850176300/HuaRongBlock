//
//  AppConfigs.h
//  AdsPopupDemo
//
//  Created by tang.wei on 13-12-13.
//  Copyright (c) 2013年 tang.wei. All rights reserved.
//

/*************************** MoPub账号设置 **************************/


#define IPHONE_BANNER_ID         @"dd0f365ca8be497a947bda4cc9fba93c"
#define IPHONE_FULLSCREEN_ID     @"9b74801a89534cad913ba738e60cd541"

#define IPAD_BANNER_ID           @"4c79f056fe974f92bb5304bd2d9906e8"
#define IPAD_FULLSCREEN_ID       @"8e027ade5f824b24b237a625de10a73f"

// 方块广告，如果不需要支持可以留空
#define IPHONE_MEDIUM_RECT_ID    @""
#define IPAD_MEDIUM_RECT_ID      @""

// Chartboost账号，如果不需要支持开启chartboost会话，可以留空
#define CHARTBOOST_APP_ID        @"549383d704b0165887da1c51"
#define CHARTBOOST_APP_SIGNATURE @"ab2bc4e764e0cb204334b9e735c8df765b4eaf43"

// 交叉推广相关
#define IPHONE_FULLSCREEN_ID_CROSSPROMO   @""
#define IPAD_FULLSCREEN_ID_CROSSPROMO     @""

/*************************** Flurry账号 ****************************/
// 如果留空不设置，那么表示不支持Flurry
#define FLURRY_KEY               @""

/*************************** Privacy Page设置 ****************************/
// 如果留空默认为http://www.xxx.com/privacy.html, 其中xxx为bundle id中间部分
#define PRIVACY_PAGE_URL         @""
