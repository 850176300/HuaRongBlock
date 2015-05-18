//
//  LeaderboardLayer.h
//  HuaRongBlock
//
//  Created by liuwei on 14-12-14.
//
//

#ifndef __HuaRongBlock__LeaderboardLayer__
#define __HuaRongBlock__LeaderboardLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "KKLeaderboardAPI.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class RankItem : public cocos2d::ui::Widget{
public:
    static RankItem* createWith(int rank, int score, const string& name, bool isSlef = false);
    bool init(int rank, int score, const string& name, bool isSlef);
};

class Leaderboard : public GameLayerBase, public KKLeaderboardAPIDelegate{
public:
    static Scene* scene();
    virtual bool init();
    CREATE_FUNC(Leaderboard);
protected:
    void createHeader();
    void backButtonClicked(Ref* pRef, Control::EventType type);
    void runloadingAnimate();
    virtual void onLoadedSuccessfully(Ref* result, kRequestResourceType type);
    virtual void onLoadedFailure(int errorCode);
    void loadData(unsigned int dataType);
    void createAllTitiles();
private:
    ControlButton* backButton;
    Sprite* frameBg;
    Label* centerLabel;
    Sprite* loadingImage;
    KKLeaderboardAPI* api;
    
};

#endif /* defined(__HuaRongBlock__LeaderboardLayer__) */
