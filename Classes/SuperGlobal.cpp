
//
//  SuperGlobal.c
//  HuaRongBlock
//
//  Created by liuwei on 14-12-7.
//
//

#include "SuperGlobal.h"
#include "DBManager.h"
void LevelDescripe::updateToSplite(){
    DBManager::getInstance()->updateLevelItem(this);
}
