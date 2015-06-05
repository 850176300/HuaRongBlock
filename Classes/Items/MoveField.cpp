//
//  MoveField.cpp
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#include "MoveField.h"
#include "SoundPlayer.h"

#define \
log12String(twstring) \
({ \
    for (int i = 0; i < 5; i++) \
    { \
        log("%s", twstring.substr(i*4, 4).c_str()); \
    } \
}) \

MoveField* MoveField::createwithStirng(string itemString,string redoString, string undoString) {
    MoveField* pRet=new MoveField();
    if (pRet && pRet->initWithString(itemString, redoString, undoString)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool MoveField::initWithString(string itemString,string redoString, string undoString) {
    if (Sprite::initWithFile("game/bg.png")) {
        resetString = itemString;
        canMove = false;
        gameFinished = false;
        currentString = itemString;
        mytempString =  string(itemString.c_str());
        currentMovingDirection = kBoth;
        HImages = {"game/jlh.png","game/jlh.png","game/jlh.png","game/jlh.png","game/jlh.png"};
        VImages = {"game/jlv.png","game/jlv.png","game/jlv.png","game/jlv.png","game/jlv.png"};
        containRect = boundingBox();
        containRect.origin = Vec2(1, 1);
        containRect.size = Size(PerGridWidth*DataWidth, PerGridWidth*DataHeight);
        placeRoles();
        undoRecorder = SplitString(undoString);
        redoRecorder = SplitString(redoString);
        return true;
    }
    return false;
}

void MoveField::setMoveFieldDelegate(MoveFieldDelegate *delegate) {
    pDelegate = delegate;
}

void MoveField::placeRoles(){
    int vCount = 0;
    int hCount = 0;
    for (int i = 0; i < DataHeight; ++i) {
        for (int j = 0; j < DataWidth; ++j) {
            MoveItem* item = NULL;
            if (currentString.at(i*DataWidth + j) == 'S') {
                item = MoveItem::create("game/xb.png", "S");
            }else if (currentString.at(i*DataWidth + j) == 'C'){
                item = MoveItem::create("game/cc.png", "C");
            }else if (currentString.at(i*DataWidth + j) == 'V') {
                item = MoveItem::create(VImages[vCount++], "V");
            }else if (currentString.at(i*DataWidth + j) == 'H') {
                item = MoveItem::create(HImages[hCount++], "H");
            }else {
                continue;
            }
            item->setTag(i*DataWidth + j);
            item->setTouchDelegate(this);
            item->setTouchEnable(true);
            item->setAnchorPoint(Vec2(0, 1.0f));
            item->setPosition(Vec2(5.0+PerGridWidth*j, GridHeight  - PerGridWidth*i ));
            item->setStartLocation(item->getPosition());
            item->setPositionNow(item->getPosition());
            item->setOldTag(i*DataWidth + j);
            addChild(item);
        }
    }
//    for (auto c=currentString.begin(); c != currentString.end(); ++c) {
//        if (*c == 'S') {
//
//        }
//    }
}

void MoveField::reCaculateItem(MoveItem *pItem) {
    currentMovingDirection = kBoth;
    __String* userObj = dynamic_cast<__String*>( pItem->getUserObject());
    testDirection(currentString,pItem->getTag(), userObj->getCString()[0]);
    if (currentString.at(13) == 'C' && userObj->getCString()[0] == 'C') {
        if (currentMoveDirection == kNoneDirection) {
            currentMoveDirection = kDown;
        }else {
            currentMoveDirection2 = kDown;
        }
//        currentMoveDirection2 = kDown;
    }
    caculateSpace(pItem->getTag(), userObj->getCString()[0]);
}

void MoveField::touchItembegan(MoveItem *pItem) {
    if (pItem->getNumberOfRunningActions()  != 0 || gameFinished == true)
    {
        canMove = false;
        return;
    }
    
    reCaculateItem(pItem);
    if (currentMoveDirection != kNoneDirection) {
        pItem->setZOrder(10);
        canMove = true;
        
    }
}

void MoveField::touchItemMove(MoveItem *pItem, cocos2d::Vec2 delta) {
    if (canMove == true) {
        Vec2 afterP=pItem->getPosition() + delta;
        if (currentMovingDirection == kBoth) {
            if (fabs(delta.x) >= fabs(delta.y) ) {
                currentMovingDirection = kHorizontal;
            }else {
                currentMovingDirection = kVertical;
            }
        }else if (currentMovingDirection == kBoth2) {
            if (afterP.x >= xSpace.x && afterP.x <= xSpace.y) {
                currentMovingDirection = kHorizontal;
            }
            if (afterP.y >= ySpace.x && afterP.y <= ySpace.y) {
                currentMovingDirection=kVertical;
            }

        }
        if (currentMovingDirection == kHorizontal) {
            if (afterP.x >= xSpace.x && afterP.x <= xSpace.y) {
                pItem->setPositionX(afterP.x);
            }
        }
        if (currentMovingDirection == kVertical) {
            if (afterP.y >= ySpace.x && afterP.y <= ySpace.y) {
                pItem->setPositionY(afterP.y);
            }
        }
        if (currentMovingDirection != kBoth && currentMovingDirection != kBoth2) {
            __String* userObj = dynamic_cast<__String*>( pItem->getUserObject());
            if (currentString.at(13) == 'C' && userObj->getCString()[0] == 'C') {
                updateCCPosition(pItem);
            }else {
                updateDirection(pItem);
            }
        }
    }
}

void MoveField::touchItemEnd(MoveItem *pItem) {
    if (pItem->getNumberOfRunningActions() != 0) {
        pItem->stopAllActions();
        pItem->setPosition(pItem->getPositionNow());
        pItem->setTouchEnable(true);
    }
    __String* userObj = dynamic_cast<__String*>( pItem->getUserObject());
    if (currentString.at(13) == 'C' && userObj->getCString()[0] == 'C') {
        if (pItem->getTag() == 17) {
            checkIsFinished();
            log("move end!!!!!!");
            return;
        }
    }
    if (pItem->getPosition() != pItem->getStartLocation()) {
        canMove = false;
        currentMovingDirection = kBoth;
        Vec2 step = Vec2((int)((pItem->getPositionX() - pItem->getStartLocation().x)/PerGridWidth + sign(pItem->getPositionX() - pItem->getStartLocation().x)*0.5f), (int)((pItem->getPositionY() - pItem->getStartLocation().y)/PerGridWidth + sign(pItem->getPositionY() - pItem->getStartLocation().y)*0.5f));
        Vec2 deltaPos = step;
        deltaPos.x = deltaPos.x * PerGridWidth;
        deltaPos.y = deltaPos.y * PerGridWidth;
        deltaPos += pItem->getStartLocation();

        pItem->setTouchEnable(false);
        pItem->setStartLocation(deltaPos);
        pItem->setPositionNow(deltaPos);
        recorderSteps(pItem, step);
        mytempString = currentString;
        CallFunc* action1= CallFunc::create( std::bind( &MoveField::setitemTouchIsEnable, this, pItem));
        pItem->runAction(Sequence::create(MoveTo::create(0.1f, deltaPos), action1, NULL));
    }
}

void MoveField::setstateonBack(MoveItem *pItem){
    pItem->setTouchEnable(true);
    pItem->setZOrder(1);
}

void MoveField::setitemTouchIsEnable(MoveItem *pItem) {
    pItem->setTouchEnable(true);
}

void MoveField::testDirection(string current, int indexTag, const char tag) {
    currentMoveDirection = kNoneDirection;
    currentMoveDirection2 = kNoneDirection;
    caculateDirection(current,indexTag, tag);

    currentMoveDirection=testMoveDirection;
    currentMoveDirection2 = testMoveDirection2;
//    if (testMoveDirection != kNoneDirection && testMoveDirection2 == kNoneDirection){
//
//        refreshGridByMove(mytempString,testMoveDirection,caculatewhRowCol(indexTag, tag), true);
//        caculateDirection(mytempString,indexTag, tag);
//        if ((testMoveDirection == currentMoveDirection && testMoveDirection2 == calculateTheOppo(currentMoveDirection)) || (testMoveDirection2 == currentMoveDirection && testMoveDirection == calculateTheOppo(currentMoveDirection))) {
//            currentMoveDirection2 = currentMoveDirection;
//        }
//    }
}
int* MoveField::caculatewhRowCol(int indexTag, const char tag){
//    log("tag is %d", indexTag);
    int *detail = new int[4];
    int w,h;
	switch(tag) {
        case 'C':	//曹操
            w=2;
            h=2;
            break;
        case 'V':	//竖着的五虎将
            w=1;
            h=2;
            break;
        case 'H':	//横着的五虎将,关羽
            w=2;
            h=1;
            break;
        case 'S':	//卒
            w=1;
            h=1;
            break;
        case 'B':	//空格,nothing to do
            break;;
        default:
            break;
	}
    int row = indexTag / DataWidth;
    int col = indexTag % DataWidth;
    detail[0] = w;detail[1]=h;detail[2]=row;detail[3]=col;
//    log("col is %d", col);
    return detail;
}
void MoveField::caculateDirection(string currenStep,int indexTag,const char tag) {
    int w,h;
	switch(tag) {
        case 'C':	//曹操
            w=2;
            h=2;
            break;
        case 'V':	//竖着的五虎将
            w=1;
            h=2;
            break;
        case 'H':	//横着的五虎将,关羽
            w=2;
            h=1;
            break;
        case 'S':	//卒
            w=1;
            h=1;
            break;
        case 'B':	//空格,nothing to do
            break;;
        default:
            break;
	}
    testMoveDirection = kNoneDirection;
    testMoveDirection2 = kNoneDirection;
    int row = indexTag / DataWidth;
    int col = indexTag % DataWidth;
	//检测上边,如果上边还有一层
	if(row-1>=0)
	{
        int j;
		for(j=0;j<w;j++)
		{
			if(currenStep.at((row-1)*DataWidth+(col+j))!='B')
			{
				break;
			}
		}
		if(j==w){
            setDirection(kUp);
        }
	}
	
	//左边
	if(col-1>=0)
	{
        int j;
		for(j=0;j<h;j++)
		{
			if(currenStep.at((row+j)*DataWidth+(col-1))!='B')
			{
				break;
			}
		}
		if(j==h)
			setDirection(kLeft);
	}
	
	//下边
	if(row+h<DataHeight)
	{
        int j;
		for(j=0;j<w;j++)
		{
			if(currenStep.at((row+h)*DataWidth+(col+j))!='B')
			{
				break;
			}
		}
		if(j==w)
			setDirection(kDown);
	}
	
	//右边
	if(col+w<DataWidth)
	{
        int j;
		for(j=0;j<h;j++)
		{
			if(currenStep.at((row+j)*DataWidth+(col+w))!='B')
			{
				break;
			}
		}
		if(j==h)
			setDirection(kRight);
	}
}
void MoveField::setDirection(MoveField::MoveDirection direction) {
    if (testMoveDirection == kNoneDirection) {
        testMoveDirection = direction;
    }else {
        testMoveDirection2 = direction;
    }
}
void MoveField::copyToArray(string& stepString,unsigned char new_grid[][4]){
    for (int i =0; i < DataHeight; ++i){
        for (int j=0; j < DataWidth; ++j) {
            new_grid[i][j] = stepString.at(i*DataWidth + j);
        }
    }
//    log("%s", stepString.c_str());
}
void MoveField::copyToString(string& stepString,unsigned char (*new_grid)[4]) {
    for (int i =0; i < DataHeight; ++i){
        for (int j=0; j < DataWidth; ++j) {
            stepString.at(i*DataWidth + j)= new_grid[i][j];
        }
    }
//    log("%s", stepString.c_str());
}
void MoveField::refreshGridByMove(string& stepString,MoveField::MoveDirection direction, int* detail, bool copyData){
    int w = detail[0];
    int h = detail[1];
    int row=detail[2];
    int col = detail[3];
    if(direction!=kNoneDirection)
	{
        unsigned char new_grid[5][4];
		int i,j;
		//向上
		if(direction == kUp)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
			copyToArray(stepString,new_grid);
			for(i=0;i<h+1;i++)
			{
				for(j=0;j<w;j++)
				{
					if(i==h)
					{
						new_grid[row-1+i][col+j] = 'B';
						continue;
					}
					new_grid[row-1+i][col+j]=new_grid[row+i][col+j];
				}
			}
			
		}
		//向左
		if(direction == kLeft)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
			copyToArray(stepString,new_grid);
			for(i=0;i<w+1;i++)
			{
				for(j=0;j<h;j++)
				{
					if(i==w)
					{
						new_grid[row+j][col-1+i] = 'B';
						continue;
					}
					new_grid[row+j][col-1+i]=new_grid[row+j][col+i];
				}
			}
		}
		//向下
		if(direction == kDown)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
            copyToArray(stepString,new_grid);
			for(i=h;i>=0;i--)
			{
				for(j=0;j<w;j++)
				{
					if(i==0)
					{
						new_grid[row+i][col+j] = 'B';
						continue;
					}
					new_grid[row+i][col+j]=new_grid[row-1+i][col+j];
				}
			}
		}
		//向右
		if(direction == kRight)
		{
			//将旧的格局copy到新的格局,在新的格局中修改数据
            copyToArray(stepString,new_grid);
			for(i=w;i>=0;i--)
			{
				for(j=0;j<h;j++)
				{
					if(i==0)
					{
						new_grid[row+j][col+i] = 'B';
						continue;
					}
					new_grid[row+j][col+i]=new_grid[row+j][col+i-1];
				}
			}
		}
        
        if (copyData) {
            copyToString(stepString,new_grid);
        }
    }
    delete[] detail;
}
void MoveField::caculateSpace(int indexTag, const char tag) {
//    log("direction1 : %d",currentMoveDirection);
//    log("direction2 : %d",currentMoveDirection2);
    int *detail = caculatewhRowCol(indexTag, tag);
    Vec2 position = Vec2(1+PerGridWidth*detail[3], GridHeight - 1 - PerGridWidth*detail[2] );
    xSpace = Vec2::ZERO;
    ySpace = Vec2::ZERO;
    switch (currentMoveDirection) {
        case kUp:
            ySpace = Vec2(position.y, position.y + PerGridWidth);
            break;
        case kDown:
            ySpace = Vec2(position.y - PerGridWidth, position.y);
            break;
        case kLeft:
            xSpace = Vec2(position.x - PerGridWidth, position.x);
            break;
        case kRight:
            xSpace = Vec2( position.x,position.x + PerGridWidth);
            break;
        case kNoneDirection:
            return;
        default:
            break;
    }
    switch (currentMoveDirection2) {
        case kUp:
        {
            if (currentMoveDirection == kUp) {
                ySpace += Vec2(0, PerGridWidth);
            }else if (currentMoveDirection == kDown) {
                ySpace.y = position.x + PerGridWidth;
            }else {
                ySpace = Vec2(position.y, position.y + PerGridWidth);
            }
        }
            break;
        case kDown:
        {
            if (currentMoveDirection == kDown) {
                ySpace += Vec2(-PerGridWidth, 0);
            }else if (currentMoveDirection == kUp) {
                ySpace.x = position.x - PerGridWidth;
            }else {
                 ySpace = Vec2(position.y - PerGridWidth, position.y);
            }
        }
            break;
        case kLeft:
        {
            if (currentMoveDirection == kLeft) {
                xSpace += Vec2(-PerGridWidth, 0);
            }else if (currentMoveDirection == kRight) {
                xSpace.x = position.x - PerGridWidth;
            }else {
                xSpace = Vec2(position.x - PerGridWidth, position.x);
            }
        }
            break;
        case kRight:
        {
            if (currentMoveDirection == kRight) {
                xSpace += Vec2(0, PerGridWidth);
            }else if (currentMoveDirection == kLeft) {
                xSpace.y = position.x + PerGridWidth;
            }else {
                xSpace = Vec2( position.x,position.x + PerGridWidth);
            }
        }
            break;
        case kNoneDirection:
            return;
        default:
            break;
    }
    delete [] detail;
}

void MoveField::updateCCPosition(MoveItem *pItem) {
    Vec2 deltaPos = pItem->getPosition() - pItem->getPositionNow();
    int lastTag = pItem->getTag();
    MoveDirection tempDirect = kNoneDirection;
    if (fabs(deltaPos.x) >= PerGridWidth/2.0 || fabs(deltaPos.y) >= PerGridWidth/2.0) {
        if (fabs(deltaPos.x) >= PerGridWidth/2.0) {
            if (deltaPos.x <= 0) {
                tempDirect = kLeft;
                lastTag -= 1;
            }else {
                tempDirect= kRight;
                lastTag += 1;
            }
        }else {
            if (deltaPos.y <= 0) {
                tempDirect = kDown;
                lastTag += DataWidth;
            }else {
                tempDirect = kUp;
                lastTag -= DataWidth;
            }
        }
    }
    if (lastTag == pItem->getTag()) {
        return;
    }
     __String* userObj = dynamic_cast<__String*>( pItem->getUserObject());
    if (lastTag == 17) {
        Vec2 movetoPos = Vec2(1+PerGridWidth*(lastTag % DataWidth), GridHeight - 1 - PerGridWidth*(lastTag / DataWidth));
        pItem->setPositionNow(movetoPos);
        pItem->setTag(lastTag);
        pItem->setTouchEnable(false);
        currentMovingDirection = kBoth2;
        auto action2 = CallFunc::create( std::bind( &MoveField::checkIsFinished, this));
        
        currentMoveDirection2 = currentMoveDirection;
        currentMoveDirection = kUp;
        caculateSpace(pItem->getTag(), userObj->getCString()[0]);
        pItem->runAction(Sequence::create(MoveTo::create(0.1f, movetoPos), action2,NULL));
    }else {
        refreshGridByMove(mytempString,tempDirect, caculatewhRowCol(pItem->getTag(), userObj->getCString()[0]), true);
        //    log("%s", mytempString.c_str());
        Vec2 movetoPos = Vec2(1+PerGridWidth*(lastTag % DataWidth), GridHeight - 1 - PerGridWidth*(lastTag / DataWidth));
        pItem->setPositionNow(movetoPos);
        pItem->setTag(lastTag);
        pItem->setTouchEnable(false);
        currentMovingDirection = kBoth2;
        auto action2 = CallFunc::create( std::bind( &MoveField::setitemTouchIsEnable, this, pItem));
        testDirection(mytempString,pItem->getTag(), userObj->getCString()[0]);
        caculateSpace(pItem->getTag(), userObj->getCString()[0]);
        pItem->runAction(Sequence::create(MoveTo::create(0.1f, movetoPos), action2,NULL));
    }
}


void MoveField::updateDirection(MoveItem *pItem) {
//    log("==========run update ============");
    Vec2 deltaPos = pItem->getPosition() - pItem->getPositionNow();
    int lastTag = pItem->getTag();
    MoveDirection tempDirect = kNoneDirection;
    if (fabs(deltaPos.x) >= PerGridWidth/2.0 || fabs(deltaPos.y) >= PerGridWidth/2.0) {
        if (fabs(deltaPos.x) >= PerGridWidth/2.0) {
            if (deltaPos.x <= 0) {
                tempDirect = kLeft;
                lastTag -= 1;
            }else {
                tempDirect= kRight;
                lastTag += 1;
            }
        }else {
            if (deltaPos.y <= 0) {
                tempDirect = kDown;
                lastTag += DataWidth;
            }else {
                tempDirect = kUp;
                lastTag -= DataWidth;
            }
        }
    }
    if (lastTag == pItem->getTag()) {
        return;
    }
    __String* userObj = dynamic_cast<__String*>( pItem->getUserObject());
    refreshGridByMove(mytempString,tempDirect, caculatewhRowCol(pItem->getTag(), userObj->getCString()[0]), true);
//    log("%s", mytempString.c_str());
    Vec2 movetoPos = Vec2(1+PerGridWidth*(lastTag % DataWidth), GridHeight - 1 - PerGridWidth*(lastTag / DataWidth));
    pItem->setPositionNow(movetoPos);
    pItem->setTag(lastTag);
    pItem->setTouchEnable(false);
    currentMovingDirection = kBoth2;
    auto action2 = CallFunc::create( std::bind( &MoveField::setitemTouchIsEnable, this, pItem));
    testDirection(mytempString,pItem->getTag(), userObj->getCString()[0]);
    caculateSpace(pItem->getTag(), userObj->getCString()[0]);
    pItem->runAction(Sequence::create(MoveTo::create(0.1f, movetoPos), action2,NULL));
}
void MoveField::recorderSteps(MoveItem *pItem, cocos2d::Vec2 step) {
    __String* userObj = dynamic_cast<__String*>( pItem->getUserObject());
    if (fabs(step.x) + fabs(step.y) == 1) {
        SoundPlayer::getInstance()->playMoveEffect();
        log("改变位置！！！！！！");
        MoveEventRecorder tconfig = {pItem->getOldTag(), step};
        undoRecorder.push_back(tconfig);
        logMoveRecorde(tconfig);
        redoRecorder.clear();
        setButtonEnable(1);
        MoveDirection direction =judgeDirectioByVec2(step);
        refreshGridByMove(currentString,direction, caculatewhRowCol(pItem->getOldTag(), userObj->getCString()[0]), true);
        mytempString = currentString;
        float dd = step.dot(Vec2(1, -4));
        pItem->setTag(pItem->getOldTag() + dd);
        pItem->setOldTag(pItem->getTag());
//        checkIsFinished();

    }else if (fabs(step.x) + fabs(step.y) == 2) {
        if (userObj->compare("S") == 0) {
            log("移动两格！！！");
            vector<MoveEventRecorder> recorde = recorde2Steps(step, pItem->getOldTag());
            if (recorde.size() < 2) {
                log("统计失败~~");
            }else if (recorde.size() == 2) {
                SoundPlayer::getInstance()->playMoveEffect();
                redoRecorder.clear();
                for (int i = 0; i < 2; ++i) {
                    refreshGridByMove(currentString, judgeDirectioByVec2(recorde.at(i).movePoint), caculatewhRowCol(recorde.at(i).itemTag, userObj->getCString()[0]), true);
                }
                MoveEventRecorder tconfig2;
                int x = recorde.at(0).itemTag * 5 + judgeDirectioByVec2(recorde.at(0).movePoint);
                int y = recorde.at(1).itemTag * 5 + judgeDirectioByVec2(recorde.at(1).movePoint);
                tconfig2.movePoint = Vec2(x, y);
                tconfig2.itemTag = pItem->getOldTag();
                undoRecorder.push_back(tconfig2);
                setButtonEnable(1);
                pItem->setTag(recorde.at(1).itemTag + recorde.at(1).movePoint.dot(Vec2(1, -4)));
                pItem->setOldTag(pItem->getTag());
            }else {
                log("统计失败~~");
            }
        }else {
            SoundPlayer::getInstance()->playMoveEffect();
            caculateDirection(currentString, pItem->getOldTag(), userObj->getCString()[0]);
            MoveEventRecorder tconfig = {pItem->getOldTag(), judgeVec2ByDirection(testMoveDirection)};
            logMoveRecorde(tconfig);
            int x = tconfig.itemTag * 5 + judgeDirectioByVec2(tconfig.movePoint);
    //        undoRecorder.push_back(tconfig);
            redoRecorder.clear();
            int tempTag = pItem->getOldTag()+judgeVec2ByDirection(testMoveDirection).dot(Vec2(1, -4));
            refreshGridByMove(currentString,testMoveDirection, caculatewhRowCol(pItem->getOldTag(), userObj->getCString()[0]), true);
            step.subtract(judgeVec2ByDirection(testMoveDirection));
            MoveEventRecorder tconfig2 = {tempTag, step};
            int y = tempTag * 5 + judgeDirectioByVec2(step);
            tconfig2.movePoint = Vec2(x, y);
            undoRecorder.push_back(tconfig2);
            logMoveRecorde(tconfig2);
             setButtonEnable(1);
            refreshGridByMove(currentString,judgeDirectioByVec2(step), caculatewhRowCol(tempTag, userObj->getCString()[0]), true);
            mytempString = currentString;
            float dd = step.dot(Vec2(1, -4));
            pItem->setTag(tempTag+ dd);
            pItem->setOldTag(pItem->getTag());
    //        checkIsFinished();
        }

    }else if (fabs(step.x) + fabs(step.y) == 3){
        log("移动三格");
        vector<MoveEventRecorder> recorde = recorde3Steps(step, pItem->getOldTag());
        if (recorde.size() < 3) {
            log("统计失败~~");
        }else if (recorde.size() == 3) {
            SoundPlayer::getInstance()->playMoveEffect();
            redoRecorder.clear();
            for (int i = 0; i < 3; ++i) {
                refreshGridByMove(currentString, judgeDirectioByVec2(recorde.at(i).movePoint), caculatewhRowCol(recorde.at(i).itemTag, userObj->getCString()[0]), true);
            }
            MoveEventRecorder tconfig2;
            int x = recorde.at(0).itemTag * 5 + judgeDirectioByVec2(recorde.at(0).movePoint);
            int y = recorde.at(1).itemTag * 5 + judgeDirectioByVec2(recorde.at(1).movePoint);
            tconfig2.movePoint = Vec2(x, y);
            tconfig2.itemTag = judgeDirectioByVec2(recorde.at(2).movePoint) * 100 + recorde.at(2).itemTag;
            undoRecorder.push_back(tconfig2);
            setButtonEnable(1);
            pItem->setTag(recorde.at(2).itemTag + recorde.at(2).movePoint.dot(Vec2(1, -4)));
            pItem->setOldTag(pItem->getTag());
        }else {
            log("统计失败~~");
        }
        
    }else if (fabs(step.x) + fabs(step.y) == 3) {
        log("没有移动！！！！！");
        recorde3Steps(step, pItem->getOldTag());
    }
    log("%s",tempStep.c_str());
}

vector<MoveEventRecorder> MoveField::recorde2Steps(cocos2d::Vec2 step, int itemtag) {
    vector<MoveEventRecorder> events = {MoveEventRecorder{-1, Vec2::ZERO}};
    vector<Vec2> vecItems;
    bool isSame = true;
    if (fabs(step.x) == 1 || fabs(step.y) == 1) {
        isSame = false;
        if (fabs(step.x) == 1) {
            vecItems.push_back(Vec2(sign(step.x), 0));
            vecItems.push_back(Vec2(0, sign(step.y)));
        }else {
            vecItems.push_back(Vec2(0, sign(step.y)));
            vecItems.push_back(Vec2(sign(step.x), 0));
        }
    }else {
        if (step.y == 0) {
            vecItems.push_back(Vec2(sign(step.x), 0));
            vecItems.push_back(Vec2(sign(step.x), 0));
        }else {
            vecItems.push_back(Vec2(0,sign(step.y)));
            vecItems.push_back(Vec2(0,sign(step.y)));
        }
    }
    vector<Vec2> rightStep = product2Steps(vecItems, itemtag, isSame);
    CCASSERT(rightStep.size() == 2, "判断错误");
    if (rightStep.at(0).equals(Vec2(-1, -1)) == true){
        return events;
    }else {
        
        MoveEventRecorder rconfig1 = MoveEventRecorder{itemtag, rightStep.at(0)};
        MoveEventRecorder rconfig2 = MoveEventRecorder{itemtag + (int)rightStep.at(0).dot(Vec2(1, -4)),rightStep.at(1)};
        events.clear();
        events.push_back(rconfig1);
        events.push_back(rconfig2);
        return events;
        
    }
}

vector<Vec2> MoveField::product2Steps(vector<Vec2> steps, int tags, bool isSame /*= true*/){
    if (isSame == true){
        if (check2StepIsExist(steps, tags) == true){
            return steps;
        }else {
            steps.at(0) = Vec2(-1, -1);
            return steps;
        }
    }else {
        Vec2 temp = steps.at(0);
        if (check2StepIsExist(steps, tags) == true){
            return steps;
        }
        steps.at(0) = steps.at(1);
        steps.at(1) = temp;
        if (check2StepIsExist(steps, tags) == true){
            return steps;
        }
        steps.at(0) = Vec2(-1, -1);
        return steps;
    }
}

bool MoveField::check2StepIsExist(vector<cocos2d::Vec2> steps, int tags) {
    CCASSERT(steps.size() == 2, "个数必须为3");
    int tag1 = tags + Vec2(1, -4).dot(steps.at(0));
    int tag2 = tag1 + Vec2(1, -4).dot(steps.at(1));
    if (currentString.at(tag1) != 'B' || currentString.at(tag2) != 'B') {
        return false;
    }
    return true;
}

vector<MoveEventRecorder> MoveField::recorde3Steps(cocos2d::Vec2 step, int itemtag) {
    vector<MoveEventRecorder> events = {MoveEventRecorder{-1, Vec2::ZERO}};
    vector<Vec2> vecItems;
    bool isSame = true;
    if (fabs(step.x) == 1 || fabs(step.y) == 1) {
        isSame = false;
        if (fabs(step.x) == 1) {
            vecItems.push_back(Vec2(sign(step.x), 0));
            vecItems.push_back(Vec2(0, sign(step.y)));
            vecItems.push_back(Vec2(0, sign(step.y)));
        }else {
            vecItems.push_back(Vec2(0, sign(step.y)));
            vecItems.push_back(Vec2(sign(step.x), 0));
            vecItems.push_back(Vec2(sign(step.x), 0));
        }
    }else {
        if (step.y == 0) {
            vecItems.push_back(Vec2(sign(step.x), 0));
            vecItems.push_back(Vec2(sign(step.x), 0));
            vecItems.push_back(Vec2(sign(step.x), 0));
        }else {
            vecItems.push_back(Vec2(sign(step.y), 0));
            vecItems.push_back(Vec2(sign(step.y), 0));
            vecItems.push_back(Vec2(sign(step.y), 0));
        }
    }
    vector<Vec2> rightStep = product3Steps(vecItems, itemtag, isSame);
    CCASSERT(rightStep.size() == 3, "判断错误");
    if (rightStep.at(0).equals(Vec2(-1, -1)) == true){
        return events;
    }else {
        
        MoveEventRecorder rconfig1 = MoveEventRecorder{itemtag,rightStep.at(0)};
        MoveEventRecorder rconfig2 = MoveEventRecorder{itemtag + (int)rightStep.at(0).dot(Vec2(1, -4)),rightStep.at(1)};
        MoveEventRecorder rconfig3 = MoveEventRecorder{itemtag + (int)rightStep.at(0).dot(Vec2(1, -4)) + (int)rightStep.at(1).dot(Vec2(1, -4)) ,rightStep.at(2)};
        events.clear();
        events.push_back(rconfig1);
        events.push_back(rconfig2);
        events.push_back(rconfig3);
        return events;
        
    }
}

vector<Vec2> MoveField::product3Steps(vector<Vec2> steps, int tags, bool isSame /*= true*/){
    if (isSame == true){
        if (check3StepIsExist(steps, tags) == true){
            return steps;
        }else {
            steps.at(0) = Vec2(-1, -1);
            return steps;
        }
    }else {
        Vec2 temp = steps.at(0);
        if (check3StepIsExist(steps, tags) == true){
            return steps;
        }
        steps.at(0) = steps.at(1);
        steps.at(1) = temp;
        if (check3StepIsExist(steps, tags) == true){
            return steps;
        }
        steps.at(1) = steps.at(2);
        steps.at(2) = temp;
        if (check3StepIsExist(steps, tags) == true){
            return steps;
        }
        steps.at(0) = Vec2(-1, -1);
        return steps;
    }
}

bool MoveField::check3StepIsExist(vector<cocos2d::Vec2> steps, int tags) {
    CCASSERT(steps.size() == 3, "个数必须为3");
    int tag1 = tags + Vec2(1, -4).dot(steps.at(0));
    int tag2 = tag1 + Vec2(1, -4).dot(steps.at(1));
    int tag3 = tag2 + Vec2(1, -4).dot(steps.at(2));
    if (currentString.at(tag1) != 'B' || currentString.at(tag2) != 'B' || currentString.at(tag3) != 'B') {
        return false;
    }
    return true;
}

MoveField::MoveDirection MoveField::judgeDirectioByVec2(Vec2 pos){
    if (pos == LEFTDIRECTION) {
        return kLeft;
    }else if (pos == RIGHTDIRECTION){
        return kRight;
    }else if (pos == UPDIRECTION) {
        return kUp;
    }else if (pos == DOWNDIRECTION) {
        return kDown;
    }else {
        return kNoneDirection;
    }
}

Vec2 MoveField::judgeVec2ByDirection(MoveField::MoveDirection direction) {
    if (direction == kLeft) {
        return LEFTDIRECTION;
    }else if (direction == kRight){
        return RIGHTDIRECTION;
    }else if (direction == kUp) {
        return UPDIRECTION;
    }else if (direction == kDown) {
        return DOWNDIRECTION;
    }else {
        return Vec2(0,0);
    }
}

void MoveField::onplayerOperationClicked(cocos2d::Ref *pSender, Control::EventType type) {
    SoundPlayer::getInstance()->playclickeffect();
    ControlButton* button = dynamic_cast<ControlButton*>(pSender);
    __String* useObj = dynamic_cast<__String*>(button->getUserObject());
    
    if (useObj->compare("undo") == 0) {
        button->setEnabled(false);
        if (undoRecorder.size() < 1) {
            return;
        }else {
            if (pDelegate) {
                pDelegate->onRedoChanged(false);
            }
            MoveEventRecorder tconfig = undoRecorder.at(undoRecorder.size() - 1);
            if (tconfig.movePoint.dot(Vec2(1, 1)) > 2 && tconfig.itemTag > 100) {
                redoRecorder.push_back(tconfig);
                MoveEventRecorder tRecorder = {tconfig.itemTag % 100, judgeVec2ByDirection( MoveDirection(tconfig.itemTag / 100))};
                tconfig.itemTag  = 0;
                performRecorder(tRecorder, true);
                MoveEventRecorder tRecorder1 = {(int)tconfig.movePoint.y / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.y % 5))};
                tconfig = {(int)tconfig.movePoint.x / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.x % 5))};
                CallFunc* action1= CallFunc::create( std::bind( &MoveField::setButtonEnable, this, -1));
                button->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create(std::bind(&MoveField::performRecorder, this, tRecorder1, true)),DelayTime::create(0.5f),CallFunc::create(std::bind(&MoveField::performRecorder, this, tconfig, true)),DelayTime::create(0.3f), action1, NULL));
                
                undoRecorder.erase(undoRecorder.begin() + undoRecorder.size() - 1);
            }else if (tconfig.movePoint.dot(Vec2(1, 1)) >= 2 && tconfig.itemTag < 100) {
                redoRecorder.push_back(tconfig);
                MoveEventRecorder tRecorder = {(int)tconfig.movePoint.y / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.y % 5))};
                tconfig = {(int)tconfig.movePoint.x / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.x % 5))};
                performRecorder(tRecorder, true);
                CallFunc* action1= CallFunc::create( std::bind( &MoveField::setButtonEnable, this, -1));
                button->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create(std::bind(&MoveField::performRecorder, this, tconfig, true)),DelayTime::create(0.3f), action1, NULL));
                
                undoRecorder.erase(undoRecorder.begin() + undoRecorder.size() - 1);
            }else {
                performRecorder(tconfig, true);
                CallFunc* action1= CallFunc::create( std::bind( &MoveField::setButtonEnable, this, -1));
                button->runAction(Sequence::create(DelayTime::create(0.3f), action1, NULL));
                redoRecorder.push_back(tconfig);
                undoRecorder.erase(undoRecorder.begin() + undoRecorder.size() - 1);
            }
        }
    }else if (useObj->compare("redo") == 0) {
         button->setEnabled(false);
        if (redoRecorder.size() < 1) {
            return;
        }else {
            if (pDelegate) {
                pDelegate->onUndoChanged(false);
            }
            
            MoveEventRecorder tconfig = redoRecorder.at(redoRecorder.size() - 1);
            if (tconfig.movePoint.dot(Vec2(1, 1)) >= 2 && tconfig.itemTag > 100) {
                undoRecorder.push_back(tconfig);
                MoveEventRecorder tRecorder1 = {(int)tconfig.itemTag % 100, judgeVec2ByDirection((MoveDirection)((int)tconfig.itemTag / 100))};
                MoveEventRecorder tRecorder = {(int)tconfig.movePoint.y / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.y % 5))};
                tconfig = {(int)tconfig.movePoint.x / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.x % 5))};
                performRecorder(tconfig, false);
                CallFunc* action1= CallFunc::create( std::bind( &MoveField::setButtonEnable, this, 1));
                button->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create(std::bind(&MoveField::performRecorder, this, tRecorder, false)),DelayTime::create(0.5f),CallFunc::create(std::bind(&MoveField::performRecorder, this, tRecorder1, false)),DelayTime::create(0.3f), action1, NULL));
                
                redoRecorder.erase(redoRecorder.begin() + redoRecorder.size() - 1);
            }
            else if (tconfig.movePoint.dot(Vec2(1, 1)) >= 2 && tconfig.itemTag < 100) {
                undoRecorder.push_back(tconfig);
                MoveEventRecorder tRecorder = {(int)tconfig.movePoint.y / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.y % 5))};
                tconfig = {(int)tconfig.movePoint.x / 5, judgeVec2ByDirection((MoveDirection)((int)tconfig.movePoint.x % 5))};
                performRecorder(tconfig, false);
                CallFunc* action1= CallFunc::create( std::bind( &MoveField::setButtonEnable, this, 1));
                button->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create(std::bind(&MoveField::performRecorder, this, tRecorder, false)),DelayTime::create(0.3f), action1, NULL));
                
                redoRecorder.erase(redoRecorder.begin() + redoRecorder.size() - 1);
            }else {
                performRecorder(tconfig, false);
                CallFunc* action1= CallFunc::create( std::bind( &MoveField::setButtonEnable, this, 1));
                button->runAction(Sequence::create(DelayTime::create(0.3f*(abs(tconfig.movePoint.dot(Vec2(1, 1))) > 1 ? 2 : 1)), action1, NULL));
                undoRecorder.push_back(tconfig);
                redoRecorder.erase(redoRecorder.begin() + redoRecorder.size() - 1);
            }
        }
    }
}
void MoveField::performRecorder(MoveEventRecorder recorder, bool undoRoredo) {
    
    if (undoRoredo == true) {
        log("undo the action %d->>>>%s", recorder.itemTag, Vec2String(recorder.movePoint).c_str());
        int tag = recorder.movePoint.dot(Vec2(1, -4)) + recorder.itemTag;
        Vec2 moveStep = recorder.movePoint*-1;
        moveStep = Vec2(PerGridWidth*moveStep.x, PerGridWidth*moveStep.y);
        
        
        if (getChildByTag(tag)) {
            log("move the items!! get tag %d", tag);
            MoveItem* pItem = (MoveItem*)getChildByTag(tag);
            pItem->setStartLocation(pItem->getPosition() + moveStep);
            pItem->setPositionNow(pItem->getPosition()+ moveStep);
            pItem->setOldTag(recorder.itemTag);
            __String* userString = dynamic_cast<__String*>(getChildByTag(tag)->getUserObject());
            CallFunc* action1= CallFunc::create( std::bind( &Node::setTag, getChildByTag(tag), recorder.itemTag));
            
            getChildByTag(tag)->runAction(Sequence::create(MoveBy::create(0.3f, moveStep), action1, NULL));
            refreshGridByMove(currentString, judgeDirectioByVec2(recorder.movePoint*-1), caculatewhRowCol(tag, userString->getCString()[0]), true);
            log12String(currentString);
            mytempString = currentString;
            log("tag is %d", recorder.itemTag);
        }
    }else {
        log("redo the action %d->>>>%s", recorder.itemTag, Vec2String(recorder.movePoint).c_str());
        Vec2 moveStep = recorder.movePoint;
        moveStep = Vec2(PerGridWidth*moveStep.x, PerGridWidth*moveStep.y);
        if (getChildByTag(recorder.itemTag)) {
            MoveItem* pItem = (MoveItem*)getChildByTag(recorder.itemTag);
            pItem->setStartLocation(pItem->getPosition() + moveStep);
            pItem->setPositionNow(pItem->getPosition()+ moveStep);
            pItem->setOldTag(recorder.itemTag+recorder.movePoint.dot(Vec2(1, -4)));
            __String* userString = dynamic_cast<__String*>(getChildByTag(recorder.itemTag)->getUserObject());
            CallFunc* action1= CallFunc::create( std::bind( &Node::setTag, getChildByTag(recorder.itemTag), recorder.itemTag+recorder.movePoint.dot(Vec2(1, -4))));
             getChildByTag(recorder.itemTag)->runAction(Sequence::create(MoveBy::create(0.3f, moveStep), action1, NULL));
            refreshGridByMove(currentString, judgeDirectioByVec2(recorder.movePoint), caculatewhRowCol(recorder.itemTag, userString->getCString()[0]), true);
            mytempString = currentString;
            log12String(currentString);
            log("tag is %.2f", recorder.itemTag+recorder.movePoint.dot(Vec2(1, -4)));
        }
    }
}
void MoveField::setButtonEnable(int addCount) {
//    button->setEnabled(true);
    if (pDelegate) {
        pDelegate->onAddStep(addCount);
    }
    if (pDelegate) {
        pDelegate->onRedoChanged(redoRecorder.size() >= 1 ? true : false);
    }
    if (pDelegate) {
        pDelegate->onUndoChanged(undoRecorder.size() >= 1 ? true : false);
    }
}

void MoveField::logMoveRecorde(MoveEventRecorder recorde) {
    log("%d->%s", recorde.itemTag, Vec2String(recorde.movePoint).c_str());
}

string MoveField::returncurrentState(){
    return currentString;
}

void MoveField::checkIsFinished(){
//    if (currentString.at(13) == 'C') {
//        gameFinished = true;
//        if (getChildByTag(13)) {
//            getChildByTag(13)->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(0, -PerGridWidth)), CallFunc::create([=]( ){
//                if (pDelegate) {
//                    pDelegate->onFinishedTheGame();
//                }
//            }), NULL));
//        }
//        
//    }
//    if (currentString.at(17) == 'C') {
    if (gameFinished == true) {
        return;
    }
        gameFinished = true;
        if (getChildByTag(17)) {
            getChildByTag(17)->runAction(Sequence::create( CallFunc::create([=]( ){
                if (pDelegate) {
                    pDelegate->onFinishedTheGame();
                }
            }), NULL));
        }
        
//    }
}

void MoveField::resetTheGame(){
    removeAllChildren();
    currentString = resetString;
    mytempString = resetString;
    placeRoles();
    undoRecorder.clear();
    redoRecorder.clear();
    setButtonEnable(3);
}


MoveField::MoveDirection MoveField::calculateTheOppo(MoveField::MoveDirection direc) {
    MoveDirection thedic = direc;
    switch (direc) {
        case kUp:
            thedic = kDown;
            break;
        case kDown:
            thedic = kUp;
            break;
        case kLeft:
            direc = kRight;
            break;
        case kRight:
            direc = kLeft;
            break;
        default:
            break;
    }
    return thedic;
}