#ifndef __DB_CONN_H__
#define __DB_CONN_H__

#include "cocos2d.h"
#include "CppSQLite3.h"
USING_NS_CC;

using namespace std;

class DbConn
{
private:
    
    char * errMsg = NULL;//错误信息
    int result;//sqlite3_exec返回值
    
public:
    
    CC_SYNTHESIZE(string, modelName, ModelName);
    
    CppSQLite3DB db;
	static DbConn* getInstance();
    
	bool init();
    void closeDB();

    
	~DbConn();
};



#endif // __HELLOWORLD_SCENE_H__
