//
//  DBTool.h
//  X_BrainTest_zlwd
//
//  Created by wuguiling on 1/10/14.
//
//

#include <iostream>
using namespace std;

class DBTool
{
public:
//    *************************************
//                 封装 sqlite3
//    *************************************
    
//    打开数据库  path为数据库路径
    static void openDB(const char *path);
    
//    判断表是否存在
    static bool tableIsExist(string  table);
    
//    创建表  先判断是否存在该表 若不存在创建 反之则不创建
    static void createTable(const char *  table,const char *  sqlStr);
    
//    删除表   先判断表是否存在 若存在删除 反之则不删除
    static void dropTable(const char *  table,const char *  sqlStr);
    
//    插入一条数据
    static void insertData(const char *  sqlStr);
    
//    删除一条数据
    static void deleteData(const char *  sqlStr);
    
//    修改一条数据
    static void updateData(const char *  sqlStr);
    
//    获取一个纪录的条数
    static int getDataCount(const char *  sqlStr);
    
//    读取查询结果的信息
//    sender最好是一个vector
    static void getDataInfo(void *sender,const char * sqlStr);
    
//    表的字段数
    static int getColumCount(string  table);
    
//    关闭打开的数据库
    static void closeDB();
    
protected:
    
    static int selectCallback(void* para,int nCount,char** pValue,char** pName);
    static int isExistedCallback(void* para,int nCount,char** pValue,char** pName);
    static int countCallback(void* para,int nCount,char** pValue,char** pName);
    static int callback(void* para,int nCount,char** pValue,char** pName);
};
