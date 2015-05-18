//
//  KKInAppBilling.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#ifndef Brain_KKInAppBilling_h
#define Brain_KKInAppBilling_h

#include "KKIAPDelegate.h"

class KKInAppBilling
{
public:
    KKInAppBilling();
    ~KKInAppBilling();
    
    void setIAPDelegate(KKIAPDelegate *pDelegate);
    
public:
    virtual void purchase(const char* sku);
    
    virtual void restore();
    
};

#endif
