//
//  TableViewTest.cpp
//  HuaRongBlock
//
//  Created by liuwei on 15/6/3.
//
//

#include "TableViewTest.h"
#include "CocosHelper.h"
bool TableViewTest::init(){
    if (LayerColor::initWithColor(Color4B(0, 0, 0, 150))) {
        
        pTableview = SWTableView::create(this, Size(500, 500));
        pTableview->setDelegate(this);
        pTableview->setPosition(Vec2(100, 100));
        pTableview->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
        addChild(pTableview, 10);
        pTableview->setVerticalFillOrder(SWTableView::VerticalFillOrder::TOP_DOWN);
        
        pTableview->reloadData();
        return true;
    }
    return false;
}

Size TableViewTest::cellSizeForTable(SWTableView *table){
    return Size(77*5, 77);
}

TableViewCell* TableViewTest::tableCellAtIndex(SWTableView *table, ssize_t idx){
    TableViewCell* pCell = new TableViewCell();
    pCell->setContentSize(Size(77*5, 77));
    for (int i = 0; i < 5; ++i) {
        Sprite* image = Sprite::create("modify/simple.png");
        image->setPosition(Vec2(77/2.0 + i * 77, 77/2.0));
        pCell->addChild(image);
        image->setTag(idx*5 + i);
    }
    pCell->setIdx(idx);
    pCell->autorelease();
    return pCell;
}

ssize_t TableViewTest::numberOfCellsInTableView(SWTableView *table){
    return (100 - 1) / 5 + 1;
}

void TableViewTest::tableCellTouched(SWTableView *table, cocos2d::extension::TableViewCell *cell, cocos2d::Touch *pTouch){
    for (int i = 0; i < cell->getChildrenCount(); ++i) {
        if (cell->getChildren().at(i)->getBoundingBox().containsPoint(cell->convertTouchToNodeSpace(pTouch))) {
            Sprite* pItem = (Sprite*)cell->getChildren().at(i);
            pItem->setColor(Color3B::GRAY);
            pItem->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=]{
                pItem->setColor(Color3B::WHITE);
            }), NULL));
            break;
            log("the touch Idx is %d", cell->getChildren().at(i)->getTag());
        }
    }
    
    ;
}