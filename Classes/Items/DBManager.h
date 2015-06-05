//
//  DBManager.h
//  X_BrainTest_zlwd
//
//  Created by wuguiling on 1/21/14.
//
//

#ifndef __X_BrainTest_zlwd__DBManager__
#define __X_BrainTest_zlwd__DBManager__

#include <iostream>
#include <vector>
#include "SuperGlobal.h"
#include "SingleTon.h"
#define DBNAME "blockData.sqlite"

#define TABLE1 "allDatas"
#define TABLE2 "typeTable"

#define KEY1 "id"
#define KEY2 "type"
#define KEY3 "level"
#define KEY4 "currentLevel"
#define KEY5 "redo"
#define KEY6 "undo"
#define KEY7 "leastStep"
#define KEY8 "name"
#define KEY9 "star"
#define KEY10 "bestStep"
#define KEY12 "lindex"

#define KEY11 "type"
#define KEY22 "total"
#define KEY33 "completecount"
#define KEY44 "startindex"




using namespace std;
inline string& trim(string &str, string::size_type pos = 0);
inline string& trim(string &str, string::size_type pos)
{
    static const string delim = " \t"; //删除空格或者tab<span></span>字符
    pos = str.find_first_of(delim, pos);
    if (pos == string::npos)
        return str;
    return trim(str.erase(pos, 1));
}

inline string& trimEnd(string &str, string::size_type pos = 0);
inline string& trimEnd(string &str, string::size_type pos)
{
    static const string delim = " \n"; //删除空格或者tab<span></span>字符
    pos = str.find_first_of(delim, pos);
    if (pos == string::npos)
        return str;
    return trim(str.erase(pos, 1));
}

class DBManager:public SingleTon<DBManager> {
    
    friend class SingleTon<DBManager>;
public:
    DBManager();
    void preloadTypes();
    LevelTitle* getLevelTitleByType(string type);
#pragma mark 封装性的功能
    void updateAllTypes();
    Vector<LevelTitle*> allTypes;
#pragma mark 功能一：获取所有题目数量
    int getQuestionCount();
#pragma mark 功能二：读取某个关卡的题目
    LevelDescripe* getQuestionAtIndex(int index);
#pragma mark 功能三：更新数据
    void updateLevelItem(LevelDescripe* item);
#pragma mark 功能三：根据lindex获取题目
    LevelDescripe* getQuestionAtlIndex(int lindex);
private:
//    void writeData(const char* name);
    
};

#endif /* defined(__X_BrainTest_zlwd__DBManager__) */
