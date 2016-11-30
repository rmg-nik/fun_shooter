#include "HUD/HealthBar.h"
#include "cocos2d/cocos/ui/UILoadingBar.h"
#include "Definitions.h"

USING_NS_CC;

bool HealthBar::init()
{
	if (!Sprite::initWithFile("healthElementsBackground.png"))
		return false;

	_healthBar = ui::LoadingBar::create("healthElementsProgressBar.png", 100);
	_healthBar->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_healthBar->setPosition(Point(269, 46));
	addChild(_healthBar);
	auto cHealthListener = EventListenerCustom::create(EVENT_HEALTH_PERCENT, [&](EventCustom* event)
	{
		float percent = *reinterpret_cast<float*>(event->getUserData());
		dynamic_cast<ui::LoadingBar*>(_healthBar)->setPercent(percent);
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cHealthListener, this);
	return true;
}
