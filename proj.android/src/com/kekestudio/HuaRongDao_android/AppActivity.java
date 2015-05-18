/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.kekestudio.HuaRongDao_android;

import java.io.UnsupportedEncodingException;
import java.util.UUID;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.provider.Settings.Secure;
import android.util.Log;

import com.common.android.ads.KKMogoAds;
import com.common.android.jni.KKSystemFunction;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import com.vungle.publisher.KKVungle;


public class AppActivity extends Cocos2dxActivity {
    protected static final String PREFS_DEVICE_ID = "device_id";  
    protected static final String PREFS_DEVICE_NAME = "device_name";  
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		 final SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);  
         final String id = prefs.getString(PREFS_DEVICE_ID, null ); 
         final String name = prefs.getString(PREFS_DEVICE_NAME, null ); 
		 if (id == null) {
			 synchronized (AppActivity.class) {  
				UUID  uuid;
		        final String androidId = Secure.getString(this.getContentResolver(), Secure.ANDROID_ID);  
		        try {  
		             if (!"9774d56d682e549c".equals(androidId)) {  
		                 uuid = UUID.nameUUIDFromBytes(androidId.getBytes("utf8"));  
		             } else {  
		                 final String deviceId = ((TelephonyManager) this.getSystemService( Context.TELEPHONY_SERVICE )).getDeviceId();  
		                 uuid = deviceId!=null ? UUID.nameUUIDFromBytes(deviceId.getBytes("utf8")) : UUID.randomUUID();  
		             }  
		         } catch (UnsupportedEncodingException e) {  
		             throw new RuntimeException(e);  
		         }  
		         // Write the value out to the prefs file  
		         prefs.edit().putString(PREFS_DEVICE_ID, uuid.toString() ).commit();  
			 }
		}
		 
		if (name == null) {
			 prefs.edit().putString(PREFS_DEVICE_NAME, Build.PRODUCT).commit();  
		}

	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Poem should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
//    	ÂæÆ‰ø°ÂàùÂßãÂåñ
  
    	
//    	
    	KKSystemFunction.setup(this);
    	
//    	ÂπøÂëäÂàùÂßãÂåñ
    	KKMogoAds.setup(this, true);

    	
    	KKVungle.setup(this, true, "54ba10a4249050db52000011");
    	return glSurfaceView;
    }

	@Override
	protected void onResume() {
		super.onResume();
		KKVungle.getInstance().resume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		KKVungle.getInstance().pause();
	}

    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
//        String result = data.getExtras().getString("result");//ÂæóÂà∞Êñ∞Activity ÂÖ≥Èó≠ÂêéËøîÂõûÁöÑÊï∞ÊçÆ

    	Log.e("-onActivityResult-", "-requestCode-"+requestCode);
    	Log.e("-onActivityResult-", "-resultCode-"+resultCode);
//    	if(requestCode==100){
//
//        	Log.e("-onActivityResult-", "-resultCode-"+resultCode);
////        	if(resultCode==100){
//        		WXShareManager.getInstance().shareSuceessed();
////        	}
//    	}

    }
    static {
        System.loadLibrary("cocos2dcpp");
    }  
}
