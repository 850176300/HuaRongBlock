//
//  DBTool.cpp
//  Doctor2
//
//  Created by wuguiling on 1/10/14.
//
//

#include "DBTool.h"
#include "sqlite3.h"
#include <vector>

using namespace std;

// 数据库指针
sqlite3 *gDB = NULL;
//state ment句柄，承载着sql语句
sqlite3_stmt *gStmt = NULL;
//错误信息
char *gErrorMsg = NULL;
//sql语句
string gSqlStr;
//sqlite 返回值
int gResult;
//colum个数
int gColumCount = 0;

void DBTool::openDB(const char *path)
{
    gResult = sqlite3_open(path, &gDB);
    if (gResult != SQLITE_OK) {
        printf( "打开数据库失败，错误码:%d ，错误原因:%s\n" , gResult,  gErrorMsg);
    }
}

bool DBTool::tableIsExist(string  table)
{    
    if (gDB==NULL) {
        return false;
    }
    bool isExist;
    gSqlStr = "select count(type) from sqlite_master where type='table' and name ='"+table+"'"; 
    gResult =sqlite3_exec(gDB, gSqlStr.c_str(), isExistedCallback, &isExist, &gErrorMsg);
    return isExist;
    
}

void DBTool::createTable(const char *  table, const char *  sqlStr)
{
    if (tableIsExist(table)) {
        gResult = sqlite3_exec(gDB, sqlStr, NULL, NULL, &gErrorMsg);
        if (gResult!=SQLITE_OK) {
            printf( "创建表失败，错误码:%d ，错误原因:%s\n" , gResult, gErrorMsg);
        }
    }
}


void DBTool::dropTable(const char *  table, const char *  sqlStr)
{
    if (tableIsExist(table)) {
        gResult = sqlite3_exec(gDB, sqlStr, NULL, NULL, &gErrorMsg);
        if (gResult!=SQLITE_OK) {
            printf( "删除表失败，错误码:%d ，错误原因:%s\n" , gResult, gErrorMsg);
        }
    }
}

void DBTool::insertData(const char *  sqlStr)
{    
    gResult = sqlite3_exec(gDB, sqlStr, NULL, NULL, &gErrorMsg);
    if (gResult!=SQLITE_OK) {
        printf( "插入失败，错误码:%d ，错误原因:%s\n" , gResult, gErrorMsg);
    }
}

void DBTool::deleteData(const char *  sqlStr)
{
    gResult = sqlite3_exec(gDB, sqlStr, NULL, NULL, &gErrorMsg);
    if (gResult!=SQLITE_OK) {
        printf( "删除纪录失败，错误码:%d ，错误原因:%s\n" , gResult, gErrorMsg);
    }
}

void DBTool::updateData(const char *  sqlStr)
{    
    gResult = sqlite3_exec(gDB, sqlStr, NULL, NULL, &gErrorMsg);
    if (gResult!=SQLITE_OK) {
        printf( "更新纪录失败，错误码:%d ，错误原因:%s\n" , gResult, gErrorMsg);
    }
}

int DBTool::getDataCount(const char *  sqlStr)
{
    int count=0;
    gResult = sqlite3_exec( gDB, sqlStr , countCallback, &count, &gErrorMsg );
    return count;
}

void DBTool::getDataInfo(void *sender, const char * sqlStr)
{
    
    gResult = sqlite3_exec( gDB, sqlStr , selectCallback, sender, &gErrorMsg );
    if (gResult!=SQLITE_OK) {
        printf( "查询失败，错误码:%d ，错误原因:%s\n" , gResult, gErrorMsg);
    }

}

int DBTool::getColumCount(string table)
{
    if (gDB==NULL) {
        return false;
    }
    int count;
    gSqlStr = "select count(type) from sqlite_master where type='table' and name ='"+table+"'";
    gResult =sqlite3_exec(gDB, gSqlStr.c_str(), callback, &count, &gErrorMsg);
    return gColumCount;
}

void DBTool::closeDB()
{
    sqlite3_close(gDB);
}

int DBTool::isExistedCallback(void *para, int nCount, char **pValue, char **pName)
{
    bool isExisted = (bool*) para;
    isExisted = (**pValue)!='0';
    return 0;
}
int DBTool::selectCallback(void* para,int nCount,char** pValue,char** pName)
{
    vector<string>* data =  (vector<string> *) para;
    string s;
    for(int i=0;i<nCount;i++)
    {
        s+=pName[i];
        s+=":";
        s+=pValue[i];
        s+="\n";
//        cout<<"colum:"<<pName[i]<<"   value"<<pValue[i]<<endl;
        data->push_back(pValue[i]);
    }
    gColumCount = nCount;
    return 0;
}

int DBTool::countCallback(void *para, int nCount, char **pValue, char **pName)
{
    int *recordCount = (int *)para;
    (*recordCount)++;
    return 0;
}
int DBTool::callback(void *para, int nCount, char **pValue, char **pName)
{
    int *cout = (int*)para;
    gColumCount = *cout;
    gColumCount = nCount;
    return 0;
}