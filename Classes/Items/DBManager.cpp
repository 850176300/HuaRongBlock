//
//  DBManager.cpp
//  Doctor2
//
//  Created by wuguiling on 1/21/14.
//
//

#include "DBManager.h"
#include "DBTool.h"
#include "cocos2d.h"
#include "STFileUtility.h"
#include "DbConn.h"
#include "CppSQLite3.h"
#include "UserDefaultManager.h"
USING_NS_CC;


DBManager::DBManager(){
    
}

void DBManager::preloadTypes(){
    stringstream content("");
    content<<"select * from ";
    content<<TABLE2;
    log("the content string is %s", content.str().c_str());

    CppSQLite3Query q = DbConn::getInstance()->db.execQuery(content.str().c_str());
    while (!q.eof()) {
        LevelTitle* tconfig = new LevelTitle();
        tconfig->setTitle(q.getStringField(KEY11));
        tconfig->setTotal(q.getIntField(KEY22));
        int completeCount = q.getIntField(KEY33);
        tconfig->setCompleteIndex(completeCount);
        tconfig->setStartIndex(q.getIntField(KEY44));
        
        allTypes.pushBack(tconfig);
        tconfig->autorelease();
        q.nextRow();
    }
    

    bool firstime = UserDefaultManager::getFirstTimeModifySql();
    
    if (firstime == true) {
        stringstream sqlcontent("");
        sqlcontent<<"UPDATE "<<TABLE1<<" SET ";
        sqlcontent<<KEY3<<" = "<<"'H0VVC00000H0H0SSBSSB'";
        sqlcontent<<", "<<KEY4<<" = "<<"'H0VVC00000H0H0SSBSSB'"<<" WHERE "<<KEY1<<" = 317;";
        
        log("UPDATE:!! the content is %s", sqlcontent.str().c_str());
        DbConn::getInstance()->db.execDML(sqlcontent.str().c_str());
        UserDefaultManager::setFirstTimeModifySql();
    }
    log("load all types finished!");
}

LevelTitle* DBManager::getLevelTitleByType(string type) {
    for (int i= 0; i < 7; ++i) {
        if (type.compare(allTypes.at(i)->getTitle()) == 0) {
            return allTypes.at(i);
        }
    }
    return NULL;
}

void DBManager::updateAllTypes(){
    
    for (int i = 0; i < allTypes.size(); ++i) {
        int completeCount = allTypes.at(i)->getCompleteIndex();
        stringstream content;
        content<<"update ";
        content<<TABLE2;
        content<<" set "<<KEY33<<" = "<<completeCount;
        content<<" where "<<KEY11<<" = \'"<<allTypes.at(i)->getTitle()<<"\'";
        log("the content string is %s", content.str().c_str());
        DbConn::getInstance()->db.execDML(content.str().c_str());
        
    }
    

}





#pragma mark 这部分为封装的接口功能
/*
 *  功能1：读取数据中某个表格中数据的总个数，
 *      传入参数：无
 *      返回参数：总个数（int型）
 *  功能2：读取某一个关卡的题目，题目作为类型，必须提前封装。每当做一个项目的时候，必须重新定义这个类型
 *      传入参数：关卡标志，一般为int型，特殊情况，需要重写该方法
 *      返回参数：“题目”类的对象
 *  其余功能等待添加
 *
 *
*/
int DBManager::getQuestionCount(){

    stringstream content;
    content<<"select count(*) from ";
    content<<TABLE1;
    log("the content string is %s", content.str().c_str());
    return DbConn::getInstance()->db.execDML(content.str().c_str());
}

LevelDescripe* DBManager::getQuestionAtIndex(int index) {

    stringstream content;
    content<<"select * from "<<TABLE1<<" where \""<<KEY1<<"\" = \""<<index<<"\"";
    log("the content is %s", content.str().c_str());

    CppSQLite3Query q = DbConn::getInstance()->db.execQuery(content.str().c_str());
    while (!q.eof()) {
        LevelDescripe* level = new LevelDescripe();
        level->setIndex(index);
        level->setName(q.getStringField(KEY8));
        level->setLevelString(q.getStringField(KEY3));
        level->setTypeName(q.getStringField(KEY2));
        level->setStar(q.getIntField(KEY9));
        level->setRedoString(q.getStringField(KEY5));
        level->setUndoString(q.getStringField(KEY6));
        level->setCurrentState(q.getStringField(KEY4));
        level->setLeastStep(q.getIntField(KEY7));
        level->setBestStep(q.getIntField(KEY10));
        level->autorelease();
        return level;
    }
    return NULL;
}

void DBManager::updateLevelItem(LevelDescripe *item) {
    stringstream content;
    content<<"UPDATE "<<TABLE1<<" SET ";
    content<<KEY10<<" = "<<item->getBestStep();
    content<<", "<<KEY9<<" = "<<item->getStar()<<" WHERE "<<KEY1<<" = "<<item->getIndex()<<" ;";
    
    log("UPDATE:!! the content is %s", content.str().c_str());
    DbConn::getInstance()->db.execDML(content.str().c_str());
}








