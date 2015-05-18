//
//  KKShare_android.h
//  Poem
//
//  Created by studio on 14-9-27.
//
//

#ifndef __Poem__KKShare_android__
#define __Poem__KKShare_android__

#include <jni.h>
#include <iostream>
#include <string>
using namespace std;
class KKShareManager {
    
public:
    ~KKShareManager();
    static KKShareManager* getInstance();
    void shareWXCircleJNI(const char*  title,const char*  msg,const char*  imgPath,const char*  url,int type);
    void shareWXOneFriendJNI(const char*  title,const char*  msg,const char*  imgPath,const char*  url,int type);
    string getUDIDJNI();
    void shareSucceed();
    int m_nShareType;
};
#endif /* defined(__Poem__KKShare_android__) */
