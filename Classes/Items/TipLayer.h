//
//  TipLayer.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-19.
//
//

#ifndef __HuaRongStreet__TipLayer__
#define __HuaRongStreet__TipLayer__

#include <iostream>
#include "cocos2d.h"
#include "SuperGlobal.h"
#include "extensions/cocos-ext.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;
class TipLayer : public LayerColor{
public:
    static TipLayer* createWithStrings(std::string originString, std::string tipString);
    bool initWithStrings(std::string originString, std::string tipString);
    void showInNode(Node* parent);
protected:
    void replaySchedule();
    void onButtonsClicked(Ref* pRef, Control::EventType type);
private:
    Label* tipLabel;
    string theoriginString;
    ControlButton* replay;
    int performCount;
    vector<MoveEventRecorder> allRecorders;
    vector<string> HImages;
    vector<string> VImages;
    void putallitems(string originString);
    Sprite* gridView;
    void startSchedule();
    void update(float dt);
    void performRecorde(MoveEventRecorder recorde);
};
#endif /* defined(__HuaRongStreet__TipLayer__) */
