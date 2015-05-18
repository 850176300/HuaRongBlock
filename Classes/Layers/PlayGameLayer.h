//
//  PlayGameLayer.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#ifndef __HuaRongStreet__PlayGameLayer__
#define __HuaRongStreet__PlayGameLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "ScoreBoard.h"
#include "extensions/cocos-ext.h"
#include "MoveField.h"
#include "WellDoneLayer.h"
#include "ConfirmDialog.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
class PlayGameLayer : public GameLayerBase, public MoveFieldDelegate, public WellDoneLayerAbstact, public ConfirmDialogDelegate{
    enum ButtonTags{
        kRedoTags = 112,
        kUndoTags,
        kTipGame,
        kTipToShop,
        kTipToVedio,
        kResetTip,
    };
public:
    ~PlayGameLayer(){CC_SAFE_RELEASE(_currentDescripe);};
    static Scene* scene(LevelDescripe* descripe);
    static PlayGameLayer* createWith(LevelDescripe* descripe);
    bool initWith(LevelDescripe* descripe);
    virtual void onRedoChanged(bool addOrSub);
    virtual void onUndoChanged(bool addOrSub);
    virtual void onAddStep(int stepCount);
    virtual void onFinishedTheGame();
    virtual void onNextBtnClicked();
    virtual void onSharetoWeChat() {};
private:
    ControlButton* redo;
    ControlButton* undo;
    LevelDescripe* _currentDescripe;
    ScoreBoard* _scoreBoard;
    MoveField* movefield ;
    Label* coinCount;
protected:
    virtual void onEnter();
    virtual void onConfirmed(ConfirmDialog* target, bool yesOrNo);
    void addhandlerbuttons();
    void createHeader();
    void createButtonLayer();
    void backButtonClicked(Ref* pSender, Control::EventType type);
    void soundBtnClick(Ref* pSender, Control::EventType type);
    void coinBtnClick(Ref* pSender, Control::EventType type);
    int getStarBysteps(int step);
    void resetBtnClicked(Ref* pRef, Control::EventType type);
};
#endif /* defined(__HuaRongStreet__PlayGameLayer__) */
