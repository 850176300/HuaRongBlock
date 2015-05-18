//
//  KKIAPDelegate.h
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#ifndef Brain_KKIAPDelegate_h
#define Brain_KKIAPDelegate_h

class KKIAPDelegate
{
public:
    virtual void purchaseSuccess(const char* pid) = 0;
    
    virtual void purchaseFailure(const char* pid, int errorCode) = 0;
    
    virtual void restoreSuccess(const char* pid) {};
    
    virtual void restoreFailure(const char* pid, int errorCode) {};
};

#endif
