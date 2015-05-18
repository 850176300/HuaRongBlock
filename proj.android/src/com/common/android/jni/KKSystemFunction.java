package com.common.android.jni;

import java.util.UUID;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.util.Log;

/**
 * 提供给JNI调用Android系统功能
 * 
 * @author Steven.Xc.Tian
 */
public class KKSystemFunction {
	private final Activity stContext;

	private static KKSystemFunction mInstance;
	

	/**
	 * 设置环境
	 * 
	 * @param context
	 */
	public static void setup(Activity context) {
		if (mInstance == null)
			mInstance = new KKSystemFunction(context);
	}

	public static KKSystemFunction getInstance() {
		return mInstance;
	}

	private KKSystemFunction(Activity context) {
		stContext = context;
		nativeInit();
	}

	public void destroy() {
		nativeDestroy();
		mInstance = null;
	}


	public String getSdCardPath() {
		if (Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState())) {
			return Environment.getExternalStorageDirectory().getAbsolutePath();
		} else {
			return stContext.getFilesDir().getAbsolutePath();
		}
	}

	public boolean checkNetworkAvailable() {
		ConnectivityManager manager = (ConnectivityManager) stContext.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo info = manager.getActiveNetworkInfo();
		if (info == null || !info.isAvailable()) {
			return false;
		}
		return true;
	}

	public boolean isTabletAvailable() {
		return (stContext.getResources().getConfiguration().screenLayout & Configuration.SCREENLAYOUT_SIZE_MASK) >= Configuration.SCREENLAYOUT_SIZE_LARGE;
	}

	//float densityScale;
	public float densityScale() {
		return (stContext.getResources().getDisplayMetrics().density);
	}

	/**
	 * 扫描指定文件夹的文件，解决保存图谱按后，系统不能即使更新相册的问题
	 * @param dir
	 */
	public void refreshDCIM(String _file){
		
		final Uri data = Uri.parse("file://"+_file);
		((Activity) stContext).runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Intent scanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
				scanIntent.setData(data);
				stContext.sendBroadcast(scanIntent);
			}
		});
	}
	

	public String getDeviceName()
	{
		final SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(stContext);  
        final String id = prefs.getString("device_name", null ); 
        String name = Build.PRODUCT;
        if (id != null) {
			name = id;
		}
        Log.e("Name", name);
        return name;
	}

	public String getUDID(){
		 final SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(stContext);  
         final String id = prefs.getString("device_id", null ); 
         Log.e("UUID", id);
         UUID uuid = null;
         if (id != null) {
        	 uuid = UUID.fromString(id);  
         }
         if (uuid != null) {
			return uuid.toString();
		}else {
			return "";
		}
	}

	public void popAlertDialog(final String message,final int dialogTag,final String cancle,final String yes) {
		((Activity) stContext).runOnUiThread(new Runnable() {

			@Override
			public void run() {
				new AlertDialog.Builder(stContext).
				setMessage(message).
				setNegativeButton(cancle, new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int whichButton) {
						/* User clicked NO so do some stuff */
						KKDialogManager.DialogNegativeCLicked(dialogTag);
					}
				}).
				setPositiveButton(yes, new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog, int whichButton) {
								/* User clicked OK so do some stuff */
								KKDialogManager.DialogPositiveCLicked(dialogTag);
							}
						}).create().show();
			}
		});
	}
	
	private native void nativeInit();

	private native void nativeDestroy();
}
