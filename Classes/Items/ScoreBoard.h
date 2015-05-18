//
//  ScoreBoard.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-12.
//
//

#ifndef __HuaRongStreet__ScoreBoard__
#define __HuaRongStreet__ScoreBoard__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class ScoreBoard : public Sprite{
public:
    static ScoreBoard* create();
    void setBestStep(int step);
    void initItems();
    void updateStepCount(int stepCount);
    int getstepCounts();
    
private:
    int currentStep;
    Label* _scroeLabel;
    Label* _stepLabel;
};

#endif /* defined(__HuaRongStreet__ScoreBoard__) */
