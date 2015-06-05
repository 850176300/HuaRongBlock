//
//  TableViewTest.h
//  HuaRongBlock
//
//  Created by liuwei on 15/6/3.
//
//

#ifndef __HuaRongBlock__TableViewTest__
#define __HuaRongBlock__TableViewTest__

#include <iostream>
#include "cocos2d.h"
#include "SWTableView.h"
#include "UserDefaultManager.h"
#include "cocos-ext.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

class TableSelectDelegate{
public:
    virtual void selectAtIndex(int index) = 0;
};

class TableViewTest : public LayerColor, public SWTableViewDataSource, public SWTableViewDelegate{
    

    
public:
    virtual bool init(Size contentSize);
    
    static TableViewTest* create(Size contentSize);
protected:
    virtual Size cellSizeForTable(SWTableView *table);
    
    virtual TableViewCell* tableCellAtIndex(SWTableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(SWTableView *table);
    
    virtual void tableCellTouched(SWTableView* table, TableViewCell* cell, Touch* pTouch);

    CC_SYNTHESIZE(TableSelectDelegate*, pDelegate, Delegate);
private:
    vector<int> tableCounts;
    vector<int> startIndex;
    vector<string> tablecellpaths;
    TablesTag currentSelectTable = kSimple;
    Size tableCellSize;
    Vec2 cellPoint;
    int colum;
};



#endif /* defined(__HuaRongBlock__TableViewTest__) */
