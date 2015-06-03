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
#include "CCMultiColumnTableView.h"
USING_NS_CC;

class TableViewTest : public LayerColor, public SWTableViewDataSource, public SWTableViewDelegate{
public:
    virtual bool init();
    CREATE_FUNC(TableViewTest);
protected:
    virtual Size cellSizeForTable(SWTableView *table);
    
    virtual TableViewCell* tableCellAtIndex(SWTableView *table, ssize_t idx);
    
    virtual ssize_t numberOfCellsInTableView(SWTableView *table);
    
    virtual void tableCellTouched(SWTableView* table, TableViewCell* cell, Touch* pTouch);

private:
    SWTableView* pTableview;
};



#endif /* defined(__HuaRongBlock__TableViewTest__) */
