//
//  TableViewTest.cpp
//  HuaRongBlock
//
//  Created by liuwei on 15/6/3.
//
//

#include "TableViewTest.h"
#include "CocosHelper.h"
#include "STVisibleRect.h"
USING_NS_ST;

bool TableViewTest::init(){
    if (LayerColor::initWithColor(Color4B(0, 0, 0, 150))) {
        
        startIndex = {1, UserDefaultManager::simpleCount+1, UserDefaultManager::simpleCount+UserDefaultManager::mediumCount+1};
        tableCounts = {UserDefaultManager::simpleCount, UserDefaultManager::mediumCount, UserDefaultManager::difficultCount};
        tablecellpaths = {"modify/simple.png", "modify/medium.png", "modify/difficult.png"};
        
        cocos2d::extension::ScrollView* pScrollView = cocos2d::extension::ScrollView::create(Size(5*77, 500));
        pScrollView->ignoreAnchorPointForPosition(false);
        pScrollView->setAnchorPoint(Vec2(.5f, .5f));
        pScrollView->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, STVisibleRect::getCenterOfScene().y - 80));
        pScrollView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
        addChild(pScrollView, 3);
        
        Layer* _container = Layer::create();
        _container->setContentSize(Size(5*77, 500));
        
        for (int i = 0; i < startIndex.size(); ++i) {
            SWTableView* pTableview = SWTableView::create(this, Size(5*77, 500));
            pTableview->ignoreAnchorPointForPosition(false);
            pTableview->setAnchorPoint(Vec2(0, 1.0));
            pTableview->setDelegate(this);
            pTableview->setPosition(Vec2(5*85 * i, 500));
            pTableview->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
            _container->addChild(pTableview);
            pTableview->setVerticalFillOrder(SWTableView::VerticalFillOrder::TOP_DOWN);
            currentSelectTable = (TablesTag)(kSimple + i);
            pTableview->setTag(startIndex.at(i));
            pTableview->setName(convertIntToString(currentSelectTable));
            
            pTableview->reloadData();
        }
        pScrollView->setContainer(_container);
        pScrollView->setBounceable(false);
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
        Sprite* image = Sprite::create(tablecellpaths.at(atoi(table->getName().c_str()) - kSimple));
        image->setPosition(Vec2(77/2.0 + i * 77, 77/2.0));
        pCell->addChild(image);
        image->setTag(idx*5 + i);
    }
    pCell->setIdx(idx);
    pCell->autorelease();
    return pCell;
}

ssize_t TableViewTest::numberOfCellsInTableView(SWTableView *table){
    int count = tableCounts.at(atoi(table->getName().c_str()) - kSimple);
    return (count - 1) / 5 + 1;
}

void TableViewTest::tableCellTouched(SWTableView *table, cocos2d::extension::TableViewCell *cell, cocos2d::Touch *pTouch){
    for (int i = 0; i < cell->getChildrenCount(); ++i) {
        if (cell->getChildren().at(i)->getBoundingBox().containsPoint(cell->convertTouchToNodeSpace(pTouch))) {
            Sprite* pItem = (Sprite*)cell->getChildren().at(i);
            pItem->setColor(Color3B::GRAY);
            pItem->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=]{
                pItem->setColor(Color3B::WHITE);
            }), NULL));
            log("the touch Idx is %d", table->getTag() + cell->getChildren().at(i)->getTag());
            break;
            
        }
    }
    
    ;
}