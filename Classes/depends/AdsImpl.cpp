#include "AdsImpl.h"
//#include "STAds.h"
//#include "SuperGlobal.h"
void AdsImpl::onBannerLoadSuccessfully()
{
}

void AdsImpl::onBannerLoadFailed( int errorCode )
{
}

void AdsImpl::onBannerClicked()
{
//    CCNotificationCenter::sharedNotificationCenter()->postNotification(InstertialShown);
}

void AdsImpl::onBannerDismissed()
{
//    CCNotificationCenter::sharedNotificationCenter()->postNotification(InstertialDismiss);
}

void AdsImpl::onInterstitialAdLoaded()
{
}

void AdsImpl::onInterstitialAdFailed( int errorCode )
{
}

void AdsImpl::onInterstitialShown()
{
    
//    STAds::interstitialShown=true;
//    CCNotificationCenter::sharedNotificationCenter()->postNotification(InstertialShown);
    
}

void AdsImpl::onInterstitialDismissed()
{
//    STAds::interstitialShown=false;
//    CCNotificationCenter::sharedNotificationCenter()->postNotification(InstertialDismiss);
}

AdsImpl* AdsImpl::getInstance()
{
    if (!instance)
    {
        instance = new AdsImpl();
    }
    return instance;
}

AdsImpl::AdsImpl()
{
    
}

AdsImpl* AdsImpl::instance = NULL;

