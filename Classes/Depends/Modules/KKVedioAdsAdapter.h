//
//  KKVedioAdsAdapter.h
//  HuaRongBlock
//
//  Created by liuwei on 15-1-12.
//
//

#ifndef HuaRongBlock_KKVedioAdsAdapter_h
#define HuaRongBlock_KKVedioAdsAdapter_h

#include <iostream>
#include "SingleTon.h"
#include "KKVedioAdsDelegate.h"

class KKVedioAdsAdapter : public SingleTon<KKVedioAdsAdapter>{
    friend class SingleTon<KKVedioAdsAdapter>;
public:
    void showVedioAds();
    void setAdsDelegate(KKVedioAdsDelegate *delegate);
};

#endif
