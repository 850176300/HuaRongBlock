//
//  SuperGlobal.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-9.
//
//

#ifndef __HuaRongStreet__SuperGlobal__
#define __HuaRongStreet__SuperGlobal__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "SoundPlayer.h"
//#include "KKAds.h"
USING_NS_CC;
using namespace std;

#define \
Vec2String(pos) \
({ \
    stringstream ss;  \
    ss<<"{"<<pos.x<<","<<pos.y<<"}";\
    ss.str(); \
}) \

typedef struct MoveEventRecorder{
    int itemTag;
    Vec2 movePoint;
}MoveEventRecorder;

inline const char* getLocalString(const string& localS);
const char* getLocalString(const string& localS){
    //获取当前系统环境语言类型
    LanguageType nType = CCApplication::getInstance()->getCurrentLanguage();
    
    //字典
    __Dictionary *pDic;
    
    if(LanguageType::CHINESE == nType)
        //根据语言选择不同的属性表
        pDic = __Dictionary::createWithContentsOfFile("zh-Hans.plist");
    else
        pDic = __Dictionary::createWithContentsOfFile("en.plist");
    
    //返回key对应的value
    if (pDic->valueForKey(localS)->length() < 1) {
        return localS.c_str();
    }
    return (pDic -> valueForKey(localS))->getCString();
}


inline void setBannerVisible(bool visible);

inline void setBannerVisible(bool visible)
{
    
//    KKAds* ad = new KKAds();
//    ad->setAdsVisibility(visible);
//    delete ad;
};

inline string convertIntToString(int num);
string convertIntToString(int num){
    __String* tempString = __String::createWithFormat("%d", num);
    stringstream ss;
    ss<<tempString->getCString();
    return ss.str();
}

inline vector<MoveEventRecorder> SplitString(string tempStr);
vector<MoveEventRecorder> SplitString(string tempStr){
    stringstream ss(tempStr);
    vector<MoveEventRecorder> subStrs;
    int sum = 0;
    for (std::string line; std::getline(ss, line,';'); ) {
        
        string::size_type index = line.find("->");
        if (index != string::npos) {
            string sub = line.substr(0, index);
            string sub2 = line.substr(index+2, line.size() - 1);
            Vec2 step = PointFromString(sub2);
            MoveEventRecorder tconfig;
            tconfig.itemTag = std::atoi(sub.c_str());
            tconfig.movePoint = step;
            subStrs.push_back(tconfig);
            //            log("%d->%s", std::atoi(sub.c_str()), Vec2String(step).c_str());
        }
        sum++;
    }
    std::cout << "\nThe sum is: " << sum << "\n";
    return subStrs;
}

class LevelItem: public Ref{
    CC_SYNTHESIZE(int, index, Index);
    CC_SYNTHESIZE(int, star, StarNum);
public:
    LevelItem():index(0),star(0){};
    LevelItem(int _index, int _star):index(_index),star(_star){};
};

class LevelTitle: public Ref{
    CC_SYNTHESIZE(string, title, Title);
    CC_SYNTHESIZE(int, completeIndex, CompleteIndex);
    CC_SYNTHESIZE(int, total, Total);
    CC_SYNTHESIZE(int, startIndex, StartIndex);
public:
    LevelTitle():title(""),completeIndex(0),total(0),startIndex(0){};
    LevelTitle(string _title, float _index, int _total, int start):title(_title),completeIndex(_index),total(_total), startIndex(start){
       
    };
};

class LevelDescripe : public Ref{
    CC_SYNTHESIZE(int, index, Index);
    CC_SYNTHESIZE(int, indexinType, IndexInType);//当前类别的index
    CC_SYNTHESIZE(string, name, Name);
    CC_SYNTHESIZE(int, star, Star);
    CC_SYNTHESIZE(string, type, TypeName);
    CC_SYNTHESIZE(string, redostr, RedoString);
    CC_SYNTHESIZE(string, undostr, UndoString);
    CC_SYNTHESIZE(string, currentState, CurrentState);
    CC_SYNTHESIZE(string, levelString, LevelString);
    CC_SYNTHESIZE(int, leastStep, LeastStep);
    CC_SYNTHESIZE(int, bestStep, BestStep);
public:
    void updateToSplite();
};


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define FONTNAME "fonts/kangyuan.ttc"
#else
#define FONTNAME "fonts/kangyuan.ttc"
#endif
enum TablesTag {
    kSimple = 0,
    kMedium,
    kDifficult,
};
#define LEFTDIRECTION Vec2(-1,0)
#define RIGHTDIRECTION Vec2(1,0)
#define UPDIRECTION Vec2(0,1)
#define DOWNDIRECTION Vec2(0,-1)
#define PAGEROWCOUNT 5
#define PAGECOLUMCOUNT 3
#define GridWidth 502.0
#define GridHeight 762.0
#define PerGridWidth 102.0
#define ButtonSize 75
#define ButtonDesperate 20
#define DataWidth 4
#define DataHeight 5
#define DayTime "isGameisDay"
#define konVideoIntertitialLoadFailed "onVideoIntertitialLoadFailed"
#define konVideoIntertitialClose "onVideoIntertitialClose"
#endif /* defined(__HuaRongStreet__SuperGlobal__) */
