//
//  UserDefaultManager.cpp
//  X_BrainTest_zlwd
//
//  Created by studio on 14-2-20.
//
//

#include "UserDefaultManager.h"
#include "DataBase64.h"
#include "DBManager.h"
//#include "KKAds.h"
//#include "../../ios/ShareHelp.h"

#define kTotalNum "kTotalNum"
#define kIsRemoveAds "kIsRemoveAds"
#define DiamondCount "DiamondCount"
#define QuestionCount "QuestionCount"
#define StarCount "StarCount"
#define FirstBuy "FirstBuy"
#define RecieveDiamond "RecieveDiamond"
#define kLoginTime "kLoginTime"
#define kFirstTime "kFirstTime"
#define kLastCount "LastCount"
#define kRecordeTime1 "kRecordeTime1"
#define kViewState "viewState"
#define kFirstTimeModify "FirstTimeModify"

void UserDefaultManager::setDefault()
{
    
    UserDefault *userdefault = UserDefault::getInstance();
    if (!userdefault->getBoolForKey("isSetUp")) {
        userdefault->setBoolForKey("isSetUp", true);
        setIntegerForKey(DiamondCount, 10);
        setIntegerForKey(QuestionCount, 0);
        setIntegerForKey(StarCount, 0);
        setIntegerForKey(RecieveDiamond, 0);
        setIntegerForKey(StarCount, 0);
        setBoolForKey(kIsRemoveAds, false);
        setIntegerForKey(kTotalNum, 0);
        setBoolForKey(kFirstTime, true);
        time_t t = time(0);
        tm * now = localtime(&t);
        __String* timeString = __String::createWithFormat("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday-1);
        log("%d年%d月%d日", now->tm_year, now->tm_mon, now->tm_mday);
        setStringForKey(kLoginTime, timeString->getCString());
        setIntegerForKey(kLastCount, 10);
        setStringForKey(kRecordeTime1, timeString->getCString());
        setIntegerForKey(kViewState, 0);
    }
}



int UserDefaultManager::getNumofQuestion() {
    int total = getIntegerForKey(kTotalNum);
    if (total == 0) {
        total = DBManager::getInstance()->getQuestionCount();
        setIntegerForKey(kTotalNum, total);
    }
    return total;
}


void UserDefaultManager::setIsRemoved(bool remove)
{
    setBoolForKey(kIsRemoveAds, remove);
}

bool UserDefaultManager::getIsRemoved()
{
    return getBoolForKey(kIsRemoveAds);
}

bool UserDefaultManager::getIsFirstBuy(){
    return getBoolForKey(FirstBuy);
}

void UserDefaultManager::setIsFirstBuy(bool isBuy) {
    setBoolForKey(FirstBuy, isBuy);
}

void UserDefaultManager::addDiamond(int count) {
    int preCount = getIntegerForKey(DiamondCount);
    preCount += count;
    if (preCount < 0) {
        preCount = 0;
    }
    setIntegerForKey(DiamondCount, preCount);
}

int UserDefaultManager::getDiamond(){
    return getIntegerForKey(DiamondCount);
}

int UserDefaultManager::getQuestionCount(){
    return getIntegerForKey(QuestionCount);
}

void UserDefaultManager::addQuestionCount(int count){
    int questionIndex = getIntegerForKey(QuestionCount);
    setIntegerForKey(QuestionCount, questionIndex+count);
}

int UserDefaultManager::getStarsCount(){
    return getIntegerForKey(StarCount);
}

void UserDefaultManager::setStarsCount(int count) {
    int stars = getIntegerForKey(StarCount);
    setIntegerForKey(StarCount, stars+count);
}

int UserDefaultManager::getReciveCount(){
    return getIntegerForKey(RecieveDiamond);
}

void UserDefaultManager::setRecieveCount(int count) {
    setIntegerForKey(RecieveDiamond, count);
}


string UserDefaultManager::getRecordeTime(){
    return getStringForKey(kLoginTime);
}

void UserDefaultManager::setRecordTime(const string &time) {
    setStringForKey(kLoginTime, time);
}

string UserDefaultManager::getRecordeTime1(){
    return getStringForKey(kRecordeTime1);
}

void UserDefaultManager::setRecordTime1(const string &time) {
    setStringForKey(kRecordeTime1, time);
}


bool UserDefaultManager::getisFirstTime(){
    return getBoolForKey(kFirstTime);
}

void UserDefaultManager::setisFirstTime(bool isFirst) {
    setBoolForKey(kFirstTime, isFirst);
}

int UserDefaultManager::getLastCount(){
    return getIntegerForKey(kLastCount);
}

void UserDefaultManager::setLastCount(int pCount) {
    setIntegerForKey(kLastCount, pCount);
}

int UserDefaultManager::getViewState(){
    return getIntegerForKey(kViewState);
}

void UserDefaultManager::setViewState(int state) {
    //0.表示可以观看视频
    //1.表示可以领取钻石
    //2.表示没有钻石可以领取
    setIntegerForKey(kViewState, state);
}

float UserDefaultManager::getBannerHeight(){
    if (!UserDefaultManager::getIsRemoved()) {
//        KKAds ads;
//        float adSize[2] = {0};
//        ads.getBannerSize(adSize);
//        return adSize[1];
    }
    return 0;
}

bool UserDefaultManager::getFirstTimeModifySql(){
    return !getBoolForKey(kFirstTimeModify);
}

void UserDefaultManager::setFirstTimeModifySql(){
    setBoolForKey(kFirstTimeModify, true);
}