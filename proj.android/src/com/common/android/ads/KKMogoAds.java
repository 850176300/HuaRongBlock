package com.common.android.ads;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import com.chartboost.sdk.CBLocation;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

/**
 * Mogo的JNI相关方法的Java端实现
 * 
 * @author Steven.Xc.Tian
 */
public class KKMogoAds extends KKAds  {
	/**
	 * 映射{@link com.amazon.device.ads.AdSize}的广告类型大小
	 * 
	 * @author Steven.Xc.Tian
	 * 
	 */
	public enum STAmazonAdSize {
		SIZE_300x50, SIZE_320x50, SIZE_300x250, SIZE_600x90, SIZE_728x90, SIZE_1024x50, SIZE_AUTO
	}

	private static final String TAG = "KKMogoAds";



	private static KKMogoAds mInstance;


	boolean isRectVisable = false;

	/**
	 * @return 可能会返回null,需要先调用{@link #setup(Context, boolean)}
	 */
	public static KKMogoAds getInstance() {
		return mInstance;
	}

	/**
	 * 设置广告JNI相关环境
	 * 
	 * @param context
	 *            Context
	 * @param debug
	 *            boolean 是否开启debug模式
	 */
	public static void setup(final Context context, boolean debug) {
		if (mInstance == null) {
			mInstance = new KKMogoAds(context, debug);
		}
	}

	private KKMogoAds(Context context, boolean debug) {
		super(context, debug);


		// //////////////////////////////////////
		// init interstitial view
		
		Chartboost.setDelegate(delegate);
	}


	/**
	 * @see KKAds.jni.ads.STAds#disposal()
	 */
	@Override
	protected void disposal() {
	}

	@Override
	public void requestAds() {

	}

	@Override
	public void requestAds(final String phoneBannerId,
			final String tabletBannerId) {

	
		requestAds();
	}

	/**
	 * @see KKAds.jni.ads.STAds#requestRectAds()
	 */
	@Override
	public void requestRectAds() {
		
	
		
	}

	/**
	 * @see KKAds.jni.ads.STAds#requestRectAds(String, String)
	 */
	@Override
	public void requestRectAds(final String phoneRectId,
			final String tabletRectId) {
	
		requestAds();
	}

	/**
	 * @see KKAds.jni.ads.STAds#requestInterstitialAds()
	 */
	@Override
	public void requestInterstitialAds() {
//		if (isInterstitialAdShowing)
//			return;
		Log.i(TAG, "显示全屏广告！！！");
		((Activity) mContext).runOnUiThread(new Runnable() {

			@Override
			public void run() {
				String toastStr = "Loading Interstitial";
				if (Chartboost.hasInterstitial(CBLocation.LOCATION_LEADERBOARD))
					toastStr = "Loading Interstitial From Cache";
				Log.i(TAG, toastStr);
				Chartboost.showInterstitial(CBLocation.LOCATION_LEADERBOARD);
				
			}
		});

	}

	@Override
	public void requestInterstitialAds(final String phoneId,
			final String tabletId) {


	}

	/**
	 * @see KKAds.jni.ads.STAds#removeAds()
	 */
	@Override
	public void removeAds() {
		// 改变状态

	}

	@Override
	public void removeRectAds() {

	}

	/**
	 * @see KKAds.jni.ads.STAds#setAdsVisibility(boolean)
	 */
	@Override
	public void setAdsVisibility(boolean visibility) {

//		final int visi = visibility ? View.VISIBLE : View.GONE;
//		((Activity) mContext).runOnUiThread(new Runnable() {
//
//			@Override
//			public void run() {
//				if (bannerView != null){
//					bannerView.setVisibility(visi);
//				}
//			}
//		});
	}

	@Override
	public void setRectAdsVisibility(boolean visibility) {
//		isRectVisable = visibility;
//		final int visi = visibility ? View.VISIBLE : View.INVISIBLE;
//		((Activity) mContext).runOnUiThread(new Runnable() {
//
//			@Override
//			public void run() {
//				if (rectBannerView != null)
//					rectBannerView.setVisibility(visi);
//
//			}
//		});

	}






	
	
	
	@Override
	public void setInterstitialAdsVisibility(boolean visibility) {
//		isInterstitialAdVisible = visibility;
//		if (isInterstitialAdVisible && interstitial != null) {
//			interstitial.interstitialShow(true);
//		}
	}

	@Override
	public void requestInterstitialAds(final int type) {
//		if (isInterstitialAdShowing)
//			return;
//
//		((Activity) mContext).runOnUiThread(new Runnable() {
//
//			@Override
//			public void run() {
//				loadInterstitialAds(getInterstitialAdsId(type));
//			}
//		});
	}


	/**
	 * 加载全屏或cross promo 广告
	 * @param AdsId
	 */
	private void loadInterstitialAds(String AdsId) {
//
//		if (interstitial != null)
//			interstitial.refreshAd();
//		if (AdsId != null) {
//			/**
//			 * 初始化全插屏为手动刷新模式（芒果后台全插屏轮换时间设置为禁用）
//			 */
//			AdsMogoInterstitialManager.setDefaultInitManualRefresh(true);
//			/**
//			 * 设置全插屏展示的activity
//			 */
//			AdsMogoInterstitialManager.setInitActivity((Activity)mContext);
//			interstitial = AdsMogoInterstitialManager.shareInstance().adsMogoInterstitialByAppKey(AdsId);
//			interstitial.setAdsMogoInterstitialListener(this);
//			interstitial.interstitialShow(true);
//
//		}else{
//			Log.e("", "loadInterstitialAds() error,AdsId is null!");
//		}
	}




	
	private ChartboostDelegate delegate = new ChartboostDelegate() {

		@Override
		public boolean shouldRequestInterstitial(String location) {
			Log.i(TAG, "SHOULD REQUEST INTERSTITIAL '"+ (location != null ? location : "null"));		
			return true;
		}
	
		@Override
		public boolean shouldDisplayInterstitial(String location) {
			Log.i(TAG, "SHOULD DISPLAY INTERSTITIAL '"+ (location != null ? location : "null"));
			return true;
		}
	
		@Override
		public void didCacheInterstitial(String location) {
			Log.i(TAG, "DID CACHE INTERSTITIAL '"+ (location != null ? location : "null"));
		}
	
		@Override
		public void didFailToLoadInterstitial(String location, CBImpressionError error) {
			Log.i(TAG, "DID FAIL TO LOAD INTERSTITIAL '"+ (location != null ? location : "null")+ " Error: " + error.name());
//			Toast.makeText(mContext.getApplicationContext(), "INTERSTITIAL '"+location+"' REQUEST FAILED - " + error.name(), Toast.LENGTH_SHORT).show();
		}
	
		@Override
		public void didDismissInterstitial(String location) {
			Log.i(TAG, "DID DISMISS INTERSTITIAL: "+ (location != null ? location : "null"));
		}
	
		@Override
		public void didCloseInterstitial(String location) {
			Log.i(TAG, "DID CLOSE INTERSTITIAL: "+ (location != null ? location : "null"));
		}
	
		@Override
		public void didClickInterstitial(String location) {
			Log.i(TAG, "DID CLICK INTERSTITIAL: "+ (location != null ? location : "null"));
		}
	
		@Override
		public void didDisplayInterstitial(String location) {
			Log.i(TAG, "DID DISPLAY INTERSTITIAL: " +  (location != null ? location : "null"));
		}
	
		@Override
		public boolean shouldRequestMoreApps(String location) {
			Log.i(TAG, "SHOULD REQUEST MORE APPS: " +  (location != null ? location : "null"));
			return true;
		}
	
		@Override
		public boolean shouldDisplayMoreApps(String location) {
			Log.i(TAG, "SHOULD DISPLAY MORE APPS: " +  (location != null ? location : "null"));
			return true;
		}
	
		@Override
		public void didFailToLoadMoreApps(String location, CBImpressionError error) {
			Log.i(TAG, "DID FAIL TO LOAD MOREAPPS " +  (location != null ? location : "null")+ " Error: "+ error.name());
//			Toast.makeText(mContext.getApplicationContext(), "MORE APPS REQUEST FAILED - " + error.name(), Toast.LENGTH_SHORT).show();
		}
	
		@Override
		public void didCacheMoreApps(String location) {
			Log.i(TAG, "DID CACHE MORE APPS: " +  (location != null ? location : "null"));
		}
	
		@Override
		public void didDismissMoreApps(String location) {
			Log.i(TAG, "DID DISMISS MORE APPS " +  (location != null ? location : "null"));
		}
	
		@Override
		public void didCloseMoreApps(String location) {
			Log.i(TAG, "DID CLOSE MORE APPS: "+  (location != null ? location : "null"));
		}
	
		@Override
		public void didClickMoreApps(String location) {
			Log.i(TAG, "DID CLICK MORE APPS: "+  (location != null ? location : "null"));
		}
	
		@Override
		public void didDisplayMoreApps(String location) {
			Log.i(TAG, "DID DISPLAY MORE APPS: " +  (location != null ? location : "null"));
		}
	
		@Override
		public void didFailToRecordClick(String uri, CBClickError error) {
			Log.i(TAG, "DID FAILED TO RECORD CLICK " + (uri != null ? uri : "null") + ", error: " + error.name());
//			Toast.makeText(mContext.getApplicationContext(), "FAILED TO RECORD CLICK " + (uri != null ? uri : "null") + ", error: " + error.name(), Toast.LENGTH_SHORT).show();
		}
	
		@Override
		public boolean shouldDisplayRewardedVideo(String location) {
			Log.i(TAG, String.format("SHOULD DISPLAY REWARDED VIDEO: '%s'",  (location != null ? location : "null")));
			return true;
		}
	
		@Override
		public void didCacheRewardedVideo(String location) {
			Log.i(TAG, String.format("DID CACHE REWARDED VIDEO: '%s'",  (location != null ? location : "null")));
		}
	
		@Override
		public void didFailToLoadRewardedVideo(String location,
				CBImpressionError error) {
			Log.i(TAG, String.format("DID FAIL TO LOAD REWARDED VIDEO: '%s', Error:  %s",  (location != null ? location : "null"), error.name()));
//			Toast.makeText(mContext.getApplicationContext(), String.format("DID FAIL TO LOAD REWARDED VIDEO '%s' because %s", location, error.name()), Toast.LENGTH_SHORT).show();
		}
	
		@Override
		public void didDismissRewardedVideo(String location) {
			Log.i(TAG, String.format("DID DISMISS REWARDED VIDEO '%s'",  (location != null ? location : "null")));
		}
	
		@Override
		public void didCloseRewardedVideo(String location) {
			Log.i(TAG, String.format("DID CLOSE REWARDED VIDEO '%s'",  (location != null ? location : "null")));
		}
	
		@Override
		public void didClickRewardedVideo(String location) {
			Log.i(TAG, String.format("DID CLICK REWARDED VIDEO '%s'",  (location != null ? location : "null")));
		}
	
		@Override
		public void didCompleteRewardedVideo(String location, int reward) {
			Log.i(TAG, String.format("DID COMPLETE REWARDED VIDEO '%s' FOR REWARD %d",  (location != null ? location : "null"), reward));
		}
		
		@Override
		public void didDisplayRewardedVideo(String location) {
			Log.i(TAG, String.format("DID DISPLAY REWARDED VIDEO '%s' FOR REWARD", location));
		}
		
		@Override
		public void willDisplayVideo(String location) {
			Log.i(TAG, String.format("WILL DISPLAY VIDEO '%s", location));
		}

	};

	@Override
	public void preloadads() {
		// TODO Auto-generated method stub
		
		((Activity) mContext).runOnUiThread(new Runnable() {

			@Override
			public void run() {
				Log.i(TAG, "Preloading Interstitial Ad");
//				Chartboost.cacheInterstitial(CBLocation.LOCATION_LEADERBOARD);
			}
		});

	}
}
