//
//  KKSystemFunction.m
//  BrainFootball
//
//  Created by tangwei1 on 14-6-27.
//
//

#include "KKSystemFunction.h"
#include "RateTool.h"

void KKSystemFunction::openUrl(const char *url)
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
}

void KKSystemFunction::go2RateUs(const char *appId, const char* alertMessage)
{
    [RateTool rateForAppleID:[NSString stringWithUTF8String:appId]
                alertMessage:[NSString stringWithUTF8String:alertMessage]];
}

const char* KKSystemFunction::getDeviceName()
{
    return [[[UIDevice currentDevice] name] UTF8String];
}
