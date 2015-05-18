
#include "DbConn.h"
#include "cocos2d.h"
#include "sqlite3.h"
#include "CppSQLite3.h"


USING_NS_CC;


static DbConn* s_sharedDbConn= NULL;

DbConn* DbConn::getInstance()
{
    if ( !s_sharedDbConn )
	{
		s_sharedDbConn = new DbConn;
		s_sharedDbConn->init();
	}
	return s_sharedDbConn;
}


bool DbConn::init()
{    
    std::string filename = FileUtils::getInstance()->getWritablePath() + "blockData.sqlite";
    CCLOG(" %s ",filename.c_str());
    db.open(filename.c_str());
    return true;
}


void DbConn::closeDB() {
    db.close();
}

DbConn::~DbConn()
{
    closeDB();
}





