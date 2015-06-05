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
#include "STSystemFunction.h"
USING_NS_ST;

TableViewTest* TableViewTest::create(cocos2d::Size contentSize) {
    TableViewTest* pRet = new TableViewTest();
    if (pRet && pRet->init(contentSize)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool TableViewTest::init(cocos2d::Size contentSize){
    if (LayerColor::init()) {
        setContentSize(contentSize);
        startIndex = {1, UserDefaultManager::simpleCount+1, UserDefaultManager::simpleCount+UserDefaultManager::mediumCount+1};
        tableCounts = {UserDefaultManager::simpleCount, UserDefaultManager::mediumCount, UserDefaultManager::difficultCount};
        tablecellpaths = {"modify/simple.png", "modify/medium.png", "modify/difficult.png"};
        
        STSystemFunction st;
        float deltaRange = st.isTabletAvailable() == true ? 15:12;
        bool flag = false;
        for (colum = 4; colum < 10; ++colum) {
            float delta = contentSize.width * 1.0 / colum;
            delta -= 62;
            if (delta < 0) {
                continue;
            }
            if (fabs(delta - deltaRange) < 8) {
                flag = true;
                break;
            }
        }
        
        if (flag == false) {
            colum = 10;
        }
        float w = contentSize.width * 1.0/ colum;
        float h = (w - 62)/0.618 + 57;
        tableCellSize = Size(w, h);
        cellPoint = Vec2((w - 62) / 2.0 + 62/2.0, (h - 57) / 2.0 + 57 / 2.0);
        
        cocos2d::extension::ScrollView* pScrollView = cocos2d::extension::ScrollView::create(contentSize);
        pScrollView->setPosition(Vec2(0, 0));
        pScrollView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
        addChild(pScrollView, 3);
        
        Layer* _container = Layer::create();
        _container->setContentSize(contentSize);
        
        
        
        for (int i = 0; i < startIndex.size(); ++i) {
            SWTableView* pTableview = SWTableView::create(this, Size(contentSize));
            pTableview->ignoreAnchorPointForPosition(false);
            pTableview->setAnchorPoint(Vec2(0, 1.0));
            pTableview->setDelegate(this);
            pTableview->setPosition(Vec2(colum*(tableCellSize.width + 5) * i, contentSize.height));
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
    return tableCellSize;
}

TableViewCell* TableViewTest::tableCellAtIndex(SWTableView *table, ssize_t idx){
    TableViewCell* pCell = new TableViewCell();
    pCell->setContentSize(Size(tableCellSize.width*colum, tableCellSize.height));
    for (int i = 0; i < colum; ++i) {
        if ((int)idx*colum + i > tableCounts.at(atoi(table->getName().c_str()) - kSimple)) {
            break;
        }
        Sprite* image = Sprite::create(tablecellpaths.at(atoi(table->getName().c_str()) - kSimple));
        image->setPosition(Vec2(cellPoint.x + i * tableCellSize.width, cellPoint.y));
        pCell->addChild(image);
        image->setTag((int)idx*colum + i);
    }
    pCell->setIdx(idx);
    pCell->autorelease();
    return pCell;
}

ssize_t TableViewTest::numberOfCellsInTableView(SWTableView *table){
    int count = tableCounts.at(atoi(table->getName().c_str()) - kSimple);
    return (count - 1) / colum + 1;
}

void TableViewTest::tableCellTouched(SWTableView *table, cocos2d::extension::TableViewCell *cell, cocos2d::Touch *pTouch){
    for (int i = 0; i < cell->getChildrenCount(); ++i) {
        if (cell->getChildren().at(i)->getBoundingBox().containsPoint(cell->convertTouchToNodeSpace(pTouch))) {
            Sprite* pItem = (Sprite*)cell->getChildren().at(i);
            pItem->setColor(Color3B::GRAY);
            pItem->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=]{
                pItem->setColor(Color3B::WHITE);
            }), NULL));
            if (pDelegate != nullptr) {
                pDelegate->selectAtIndex(table->getTag() + cell->getChildren().at(i)->getTag());
            }
            log("the touch Idx is %d", table->getTag() + cell->getChildren().at(i)->getTag());
            break;
            
        }
    }
    
    ;
}