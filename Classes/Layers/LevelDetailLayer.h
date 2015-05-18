//
//  LevelDetailLayer.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-11.
//
//

#ifndef __HuaRongStreet__LevelDetailLayer__
#define __HuaRongStreet__LevelDetailLayer__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "GameLayerBase.h"
#include "ScrollMenu.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
class LevelDetail : public GameLayerBase{
    enum LevelDetailTags{
        kPreBtn= 111,
        kNextBtn,
    };
private:
    ScrollMenu* m_pScrollView;
    ControlButton* preBtn ;
    ControlButton* nextBtn;
    Label* titleTip ;
    LevelTitle* currentLevel;
    int currentPage;
    float scrollviewXseperate;
    float scrollviewYseperate;
public:
    ~LevelDetail(){CC_SAFE_RELEASE(currentLevel);};
    static Scene* scene(LevelTitle* thetitle);
    static LevelDetail* createWithLevel(LevelTitle* thetitle);
    bool initWithLevel(LevelTitle* thetitle);
    virtual void onEnterTransitionDidFinish();
    void onBackKeyClicked();
protected:
    
    void refreshTipLabel();
    void addPageControl();
    void addScrollView();
    void createHeader(string title);
    void backButtonClicked(Ref* pSender, Control::EventType type);
    void pageControlButtonClicked(Ref* pSender, Control::EventType type);
    void loadlevelItemsInSchedule(float dt);
    void onChooseoneLevelItem(Ref* pSener);
};
#endif /* defined(__HuaRongStreet__LevelDetailLayer__) */
