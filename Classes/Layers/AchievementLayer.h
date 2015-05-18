//
//  AchievementLayer.h
//  HuaRongBlock
//
//  Created by liuwei on 14-12-13.
//
//

#ifndef __HuaRongBlock__AchievementLayer__
#define __HuaRongBlock__AchievementLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "extensions/cocos-ext.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;



class ArchievementLayer;
class ArchieveItem;
class ArchieveDelegate{
public:
    virtual void clickedTheAchieveItem(ArchieveItem* item,bool boolen, int coinCount) = 0;
};
class ArchieveItem :public Layer{
private:
    ArchieveDelegate *pDelegate;
    Label* content;
    Label* num;
    int _coinCount;
public:
    static ArchieveItem* createWith(int leastCount, int coinCount);
    bool initWith(int leastCount, int coinCount);
    void settheClickeDelegate(ArchieveDelegate* delegate);
protected:
    void onClicked(Ref* pRef);
};

class ArchievementLayer : public GameLayerBase, public ArchieveDelegate{
public:
    static Scene* scene();
    virtual bool init();
    CREATE_FUNC(ArchievementLayer);
protected:
    void backButtonClicked(Ref* pSender, Control::EventType type);
    void createHeader();
    void addStarCount();
    void addEveryDayArchieve();
    void oneveryDayClicked(Ref* pRef);
    void createDiamondLayer();
    void addstarArchieve();
    virtual void clickedTheAchieveItem(ArchieveItem* item,bool boolen, int coinCount);
private:
    ArchieveItem* _secondItem;
    Layer* diamondLayer;
    Sprite* frameBg;
    Sprite* headercoin;
    Label* headernum;
    Label* title2;
    Label* num;
    Sprite* coin;
};

#endif /* defined(__HuaRongBlock__AchievementLayer__) */
