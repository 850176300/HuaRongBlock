/*
 * ST_SystemFunction_Android.h
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#ifndef ST_SYSTEMFUNCTION_ANDROID_H_
#define ST_SYSTEMFUNCTION_ANDROID_H_

#include "ST_JNI_Helper.h"
#include <string>
using namespace std;
class SystemFunctionManager
{
public:
	SystemFunctionManager() :
			ClassSF(0),
			stSFJava(0),
			MethodSendMailByIntent(0),
			MethodPopAlertDialog(0),
			MethodMakeToast(0),
			MethodRateUs(0),
			MethodSendEmailAndAssetPic(0),
			MethodSendEmailAndFilePic(0),
			MethodGetSdCardPath(0),
			MethodCheckNetworkAvailable(0),
			MethodIsTabletAvailable(0),
			MethodDensityScale(0),
            MethodRefreshDCIM(0),
            MethodGetDeviceName(0)
	{
	}
	~SystemFunctionManager();

	static SystemFunctionManager* getInstance();

	static void destroy();

	bool init(JNIEnv * pEnv, jobject pJava);

public:
	void sendEmail(const char* subject, const char* body);
	void popAlertDialog(const char* message);
	void makeToast(const char* message);
	void rateUs();
	void sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName);
	void sendEmailAndFilePic(std::string subject, std::string message,std::string fileName);
	std::string getSdCardPath();
	bool checkNetworkAvailable();
	bool isTabletAvailable();
	float densityScale();
    /*
     * 向服务器发送后台统计数据，在APP出的时候发送
     */
	void endAnalytics();
    void refreshDCIM(std::string sFileDir);
    std::string getDeviceName();
    void showDialog(const char* msg,int tag,const char* cancle,const char* yes);
private:
	/*>>>>>>>> below declaration is used by jni <<<<<<<<*/
	// Cached Classes.
	jclass ClassSF;
	// Cached java object
	jobject stSFJava;
	// Cached active Methods.
	jmethodID MethodSendMailByIntent;
	jmethodID MethodPopAlertDialog;
	jmethodID MethodMakeToast;
	jmethodID MethodRateUs;
	jmethodID MethodSendEmailAndAssetPic;
	jmethodID MethodSendEmailAndFilePic;
	jmethodID MethodGetSdCardPath;
	jmethodID MethodCheckNetworkAvailable;
	jmethodID MethodIsTabletAvailable;
	jmethodID MethodDensityScale;
    jmethodID MethodRefreshDCIM;
    jmethodID MethodGetDeviceName;
};

#endif /* ST_SYSTEMFUNCTION_ANDROID_H_ */
