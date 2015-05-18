

#include "ScrollMenu.h"

USING_NS_CC;
USING_NS_CC_EXT;


ScrollMenu::ScrollMenu():m_Menu(NULL)
	,m_TouchBeginAtPoint(Vec2(0,0))
	,m_TouchEndAtPoint(Vec2(0,0))
	,m_ScrollEnable(true)
{

}

ScrollMenu::~ScrollMenu()
{

}

bool ScrollMenu::init()
{
	ScrollView::init();

	Layer* pContainer = Layer::create();
	pContainer->setAnchorPoint(Vec2(0,0));

// 	CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(200,0,0,255));
// 	pContainer->addChild(pLayerColor);
// 	pLayerColor->setPosition(Vec2(0,0));

	this->setContainer(pContainer);
	//
	m_Menu = Menu::create();
	m_Menu->setPosition(Vec2(0,0));
	m_Menu->setEnabled(true);
	pContainer->addChild(m_Menu);


	return true;
}


bool ScrollMenu::onTouchBegan( Touch* touch, Event* event )
{
	m_Menu->setEnabled(false);
	m_TouchBeginAtPoint = touch->getLocation();
//    m_Menu->TouchBegan(touch,event);
	return ScrollView::onTouchBegan(touch,event);
}

void ScrollMenu::onTouchCancelled( Touch *touch, Event* event )
{
	ScrollView::onTouchCancelled(touch,event);
}

void ScrollMenu::onTouchEnded( Touch* touch, Event* event )
{
	m_Menu->setEnabled(false);
	ScrollView::onTouchEnded(touch,event);
	m_TouchEndAtPoint = touch->getLocation();

	switch ( getDirection() )
	{
        case  ScrollView::Direction::HORIZONTAL:
		{
			float distance = fabsf(m_TouchBeginAtPoint.x-m_TouchEndAtPoint.x);
 			if ( distance < 10 )
 			{
                m_Menu->setEnabled(true);
 				bool isBeenTouch = m_Menu->onTouchBegan(touch,event);

  				if ( isBeenTouch )
  				{
 					this->scheduleOnce(SEL_SCHEDULE(&ScrollMenu::touchEnd),0.2f);
 				}
                m_Menu->setEnabled(false);
 			}
		}
		break;
	case ScrollView::Direction::VERTICAL:
		{
			float distance = fabsf(m_TouchBeginAtPoint.y - m_TouchEndAtPoint.y);
			if ( distance < 10 )
			{
                m_Menu->setEnabled(true);
				bool isBeenTouch = m_Menu->onTouchBegan(touch,event);
				if ( isBeenTouch )
				{
					this->scheduleOnce(SEL_SCHEDULE(&ScrollMenu::touchEnd),0.2f);
				}
                m_Menu->setEnabled(false);
			}
		}
		break;
	default:
		CCAssert(0,"ScrollMenu support kScrollViewDirectionHorizontal or kScrollViewDirectionVertical only !");
		break;
	}

}

void ScrollMenu::onTouchMoved( Touch* touch, Event* event )
{
	if ( m_ScrollEnable == false )
	{
		return ;
	}
	ScrollView::onTouchMoved(touch,event);
}

// 
 void ScrollMenu::touchEnd( float delta )
 {
 	m_Menu->onTouchEnded(NULL,NULL);
 }

 void ScrollMenu::setMenu( cocos2d::Menu* pMenu )
 {
	 if ( m_Menu != NULL )
	 {
		 pMenu->setEnabled(false);
		 m_Menu->removeFromParent();
		 m_Menu = pMenu;
		 m_Menu->setEnabled(false);
		 m_Menu->setPosition(Vec2(0,0));
		 getContainer()->addChild(m_Menu);
	 }
 }

 // 
