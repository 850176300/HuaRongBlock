//
//  UserDefaultManager.h
//  X_BrainTest_zlwd
//
//  Created by studio on 14-2-20.
//
//

#ifndef __X_BrainTest_zlwd__UserDefaultManager__
#define __X_BrainTest_zlwd__UserDefaultManager__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class UserDefaultManager {
    
public:
    
    static void setDefault();
    
//set/get 所有题目数量
    static int getNumofQuestion();

    static bool getIsFirstBuy();
    static void setIsFirstBuy(bool isBuy);

    static bool getIsRemoved();
    static void setIsRemoved(bool remove);
    
    static void addDiamond(int count);
    static int getDiamond();
    
    static void addQuestionCount(int count = 1);
    static int getQuestionCount();
    
    static int getStarsCount();
    static void setStarsCount(int count);
    
    static int getReciveCount();
    static void setRecieveCount(int count);
    
    static string getRecordeTime();
    static void setRecordTime(const string& time);
    static string getRecordeTime1();
    static void setRecordTime1(const string& time);
    
    static bool getisFirstTime();
    static void setisFirstTime(bool isFirst);
    
    static int getLastCount();
    static void setLastCount(int pCount);
    
    static int getViewState();
    static void setViewState(int state);
    
    static bool getFirstTimeModifySql();
    static void setFirstTimeModifySql();
    
    static float getBannerHeight();
};



#endif /* defined(__X_BrainTest_zlwd__UserDefaultManager__) */
