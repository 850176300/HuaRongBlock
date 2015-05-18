//
//  MoveField.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#ifndef __HuaRongStreet__MoveField__
#define __HuaRongStreet__MoveField__

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include "cocos2d.h"
#include "MoveItem.h"
#include "extensions/cocos-ext.h"
#include "SuperGlobal.h"
using namespace std;
using namespace cocos2d;
USING_NS_CC_EXT;
class MoveField;
class MoveFieldDelegate {
public:
    virtual void onRedoChanged(bool addOrSub) = 0;
    virtual void onUndoChanged(bool addOrSub) = 0;
    virtual void onAddStep(int stepCount) = 0;
    virtual void onFinishedTheGame() = 0;

};

class MoveField : public Sprite, public MoveItemDelegate{
public:
    enum MoveDirection{
        kNoneDirection = 0,
        kLeft,
        kRight,
        kUp,
        kDown,
    };
    enum MovingDirection{
        kVertical = 10,
        kHorizontal,
        kBoth,
        kBoth2,
    };
public:
    static MoveField* createwithStirng(string itemString, string redoString, string undoString);
    bool initWithString(string itemString, string redoString, string undoString);
    virtual void touchItembegan(MoveItem* pItem);
    virtual void touchItemMove(MoveItem* pItem, Vec2 delta);
    virtual void touchItemEnd(MoveItem* pItem);
    void onplayerOperationClicked(Ref* pSender, Control::EventType type);
    void setMoveFieldDelegate(MoveFieldDelegate* delegate);
    string returncurrentState();
    void resetTheGame();
    
private:
    MoveFieldDelegate* pDelegate;
    vector<MoveEventRecorder> undoRecorder;
    vector<MoveEventRecorder> redoRecorder;
    bool canMove;
    bool gameFinished;
    Vec2 xSpace;
    Vec2 ySpace;
    Rect containRect;
    MovingDirection currentMovingDirection;
    MoveDirection currentMoveDirection;
    MoveDirection currentMoveDirection2;//人物移动有可能有两个方向
    MoveDirection testMoveDirection;
    MoveDirection testMoveDirection2;//人物移动有可能有两个方向
    string currentString;
    string mytempString;
    string resetString;
    vector<string> HImages;
    vector<string> VImages;
    string tempStep;//记录每次移动的步骤，方便统一记录
    void placeRoles();
    void testDirection(string current, int indexTag,const char tag);
    void reCaculateItem(MoveItem* pItem);
    int* caculatewhRowCol(int indexTag,const char tag);
    void caculateDirection(string currenStep,int indexTag,const char tag);
    void setstateonBack(MoveItem* pItem);
    void setDirection(MoveDirection direction);
    void refreshGridByMove(string& stepString,MoveDirection direction, int *detail, bool copyData = false);
    void copyToArray(string& stepString,unsigned char new_grid[][4]);
    void copyToString(string& stepString,unsigned char new_grid[][4]);
    void caculateSpace(int indexTag,const char tag);
    void updateDirection(MoveItem* pItem);
    void setitemTouchIsEnable(MoveItem* pItem);
    void recorderSteps(MoveItem* pItem, Vec2 step);
    int sign(float x){if (x>=0) return 1;else return -1; }
    MoveDirection judgeDirectioByVec2(Vec2 pos);
    Vec2 judgeVec2ByDirection(MoveDirection direction);
//    vector<MoveEventRecorder> SplitString(string tempStr);
    void setButtonEnable(int addCount);
    void performRecorder(MoveEventRecorder recorder, bool undoRoredo);
    void logMoveRecorde(MoveEventRecorder recorde);
    void checkIsFinished();
    void updateCCPosition(MoveItem* pItem);
    MoveDirection calculateTheOppo(MoveDirection direc);
    vector<MoveEventRecorder> recorde3Steps(Vec2 step, int itemtag);
    vector<Vec2> product3Steps(vector<Vec2> steps, int tags, bool isSame = true);
    bool check3StepIsExist(vector<Vec2> steps, int tags);
    
    vector<MoveEventRecorder> recorde2Steps(Vec2 step, int itemtag);
    vector<Vec2> product2Steps(vector<Vec2> steps, int tags, bool isSame = true);
    bool check2StepIsExist(vector<Vec2> steps, int tags);
};
#endif /* defined(__HuaRongStreet__MoveField__) */
