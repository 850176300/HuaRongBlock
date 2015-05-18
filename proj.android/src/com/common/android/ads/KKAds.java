package com.common.android.ads;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.FrameLayout.LayoutParams;

/**
 * 所有广告的父类，JNI基于此类进行调用，具体方法，各个广告子类实现
 * 
 * @author Steven.Xc.Tian
 * 
 */
public abstract class KKAds {
	protected final Context mContext;
	protected final boolean debug;
	// View group to which the ad view will be added
	protected ViewGroup adViewContainer;
	protected FrameLayout.LayoutParams bannnerAdViewLayoutParams;
	protected FrameLayout.LayoutParams rectAdViewLayoutParams;
	// current device is tablet?
	protected final boolean isTablet;
	//
	protected final float densityScale;

	private static boolean isInit = false;
	protected boolean isInterstitialAdShowing = false;

	public boolean isInterstitialAdShowing() {
		return isInterstitialAdShowing;
	}

	public void setInterstitialAdShowing(boolean isInterstitialAdShowing) {
		this.isInterstitialAdShowing = isInterstitialAdShowing;
	}

	protected KKAds(Context context, boolean debug) {
		mContext = context;
		this.debug = debug;
		adViewContainer = (ViewGroup) ((Activity) context).findViewById(android.R.id.content);
		densityScale = mContext.getResources().getDisplayMetrics().density;
		isTablet = isTablet(context);

		bannnerAdViewLayoutParams = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT,
				Gravity.BOTTOM);

		if (!isInit) {
			nativeInit();
			isInit = true;
		}

	}

	/**
	 * 程序退出后进行清理
	 */
	public void destroy() {
		nativeDestroy();
		disposal();
	}

	/**
	 * 设置Banner广告条的位置，默认为 600x90, Gravity.CENTER | Gravity.BOTTOM
	 * <p>
	 * <b>NOTE：需要在 {@link #requestAds()}之前调用</b>
	 * </p>
	 * 
	 * @param width
	 * @param height
	 * @param gravity
	 *            such as Gravity.CENTER, Gravity.BOTTOM, or Gravity.CENTER |
	 *            Gravity.BOTTOM ...
	 */
	public void setBannnerAdViewLayoutParams(float width, float height, int gravity) {
		bannnerAdViewLayoutParams = new LayoutParams((int) (width * densityScale), (int) (height * densityScale),
				gravity);
	}

	public abstract void  preloadads() ;
	
	/**
	 * 请求banner类型的广告
	 */
	public abstract void requestAds();

	/**
	 * 请求banner类型的广告
	 * 
	 * @param String
	 *            phone id
	 * @param String
	 *            tablet id
	 */
	public abstract void requestAds(String phoneBannerId, String tabletBannerId);

	/**
	 * 请求rect banner类型广告
	 */
	public abstract void requestRectAds();

	/**
	 * 请求rect banner类型的广告
	 * 
	 * @param String
	 *            phone id
	 * @param String
	 *            tablet id
	 */
	public abstract void requestRectAds(String phoneRectId, String tabletRectId);

	/**
	 * 请求 interstitial ads
	 * 广告类型为全屏广告
	 */
	
	public abstract void requestInterstitialAds();
	/**
	 * 根据类型的请求interstitial ads
	 * @param type 0为全屏，1为cross promo
	 */
	@Deprecated
	public abstract void requestInterstitialAds(int type);

	/**
	 * 请求 interstitial ads
	 * 广告类型为全屏广告
	 * 
	 * @param String
	 *            phone id
	 * @param String
	 *            tablet id
	 */
	public abstract void requestInterstitialAds(String phoneId, String tabletId);


	/**
	 * 去除Banner广告
	 */
	public abstract void removeAds();

	/**
	 * 去除rect banner广告
	 */
	public abstract void removeRectAds();

	/**
	 * 隐藏Banner广告，没有进行实质性的移除工作
	 */
	public abstract void setAdsVisibility(boolean visibility);

	/**
	 * 隐藏rect banner广告，没有进行实质性的移除工作
	 */
	public abstract void setRectAdsVisibility(boolean visibility);
	/**
	 * 隐藏全屏广告
	 */
	protected abstract void setInterstitialAdsVisibility(boolean visibility);

	/**
	 * 广告完成退出后进行清理
	 */
	protected abstract void disposal();

	protected native void nativeAdLoadSuccessfully();

	protected native void nativeAdLoadFailed(int errorCode);
	
	protected native void nativeClickedBannerAd();

	protected native void nativeInterstitialAdLoaded();

	protected native void nativeInterstitialAdFailed(int errorCode);

	protected native void nativeInterstitialAdShown();

	protected native void nativeInterstitialAdDismissed();

	/* 通知本地代码加载 */
	private native void nativeInit();

	private native void nativeDestroy();

	protected String getMetaData(String key) {
		String metaValue = null;
		try {
			ApplicationInfo ai = mContext.getPackageManager().getApplicationInfo(mContext.getPackageName(),
					PackageManager.GET_META_DATA);
			Bundle bundle = ai.metaData;
			Object o = bundle.get(key);
			if (o != null)
				metaValue = o.toString();
		} catch (NameNotFoundException e) {
		}
		return metaValue;
	}

	public static boolean isTablet(Context context) {
		return (context.getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) >= Configuration.SCREENLAYOUT_SIZE_LARGE;
	}
	
	/**
	 * 广告类型
	 * @author liuhailong
	 *
	 */
	public class AdsType{
		public static final int ADS_INTERSTITIAL=0;
		public static final int ADS_CREOSSPROMON=1;
		public static final int ADS_BANNER=2;
		
		
	}
}
