//
//  KKVedioAdsDelegate.h
//  HuaRongBlock
//
//  Created by liuwei on 15-1-12.
//
//

#ifndef HuaRongBlock_KKVedioAdsDelegate_h
#define HuaRongBlock_KKVedioAdsDelegate_h
#include <iostream>

class KKVedioAdsDelegate{
public:
    virtual void onVedioAdsCacheSuccessfully(){};
    virtual void onVedioAdsLoadFailed(const char* error){};
//    virtual void onVedioAdsRewarded(bool isComplete){};
    virtual void onVedioAdsRewarded(int coint){};
};


#endif
