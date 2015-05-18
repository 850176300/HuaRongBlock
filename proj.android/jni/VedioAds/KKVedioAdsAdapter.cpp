//
//  KKVedioAdsAdapter.cpp
//  BrainJZW
//
//  Created by studio on 15-1-11.
//
//

#include "KKVedioAdsAdapter.h"
#include "KKVungle_android.h"

void KKVedioAdsAdapter::setAdsDelegate(KKVedioAdsDelegate *delegate)
{
	VedioAdManager::getInstance()->setAdDelegate(delegate);
}

void KKVedioAdsAdapter::showVedioAds()
{

	VedioAdManager::getInstance()->requestVedioAds();
}
