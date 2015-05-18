

#ifndef comment_ScrollMenu
#define comment_ScrollMenu

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ScrollMenu:public cocos2d::extension::ScrollView
{
public:
	ScrollMenu();
	~ScrollMenu();
	virtual bool init();

	CREATE_FUNC(ScrollMenu);
	void setMenu(cocos2d::Menu* pMenu);
	CC_SYNTHESIZE(bool,m_ScrollEnable,ScrollEnable);
public:
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	void touchEnd(float delta);
	cocos2d::Menu* m_Menu;
	cocos2d::Point m_TouchBeginAtPoint;
	cocos2d::Point m_TouchEndAtPoint;
};
#endif