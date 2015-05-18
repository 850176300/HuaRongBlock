//
//  KKInAppBilling.m
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#include "KKInAppBilling.h"
//#import "IOSIAPWrapper.h"

KKInAppBilling::KKInAppBilling()
{
    
}

KKInAppBilling::~KKInAppBilling()
{
    
}

void KKInAppBilling::setIAPDelegate(KKIAPDelegate *pDelegate)
{
    //[[IOSIAPManager sharedIOSIAPManager] setIAPDelegate:pDelegate];
}

void KKInAppBilling::purchase(const char* sku)
{
    //[[IOSIAPManager sharedIOSIAPManager] purchase:[NSString stringWithUTF8String:sku]];
}

void KKInAppBilling::restore()
{
    //[[IOSIAPManager sharedIOSIAPManager] restore];
}