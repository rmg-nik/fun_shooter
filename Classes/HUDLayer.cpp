#include "HUDLayer.h"
#include "Controller.h"
#include "HUD/HealthBar.h"
#include "Definitions.h"

USING_NS_CC;

bool HUDLayer::init()
{
	if (!Layer::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
	
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
	auto mlistener = EventListenerMouse::create();
	mlistener->onMouseDown = [&](Event*)
	{
		EventCustom event(EVENT_FIRE_EVENT);
		bool fire = true;
		event.setUserData(&fire);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	};
	mlistener->onMouseUp = [&](Event*)
	{
		EventCustom event(EVENT_FIRE_EVENT);
		bool fire = false;
		event.setUserData(&fire);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mlistener, this);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID	

	_controllerLeft = Controller::create();
	_controllerLeft->setPosition(Point(visibleOrigin.x + _controllerLeft->getContentSize().width / 2, visibleOrigin.y + _controllerLeft->getContentSize().height / 2));

	this->addChild(_controllerLeft);

	_controllerRight = Controller::create();
	_controllerRight->setAlwaysPressed(true);
	_controllerRight->setPosition(Point(visibleOrigin.x + visibleSize.width - _controllerRight->getContentSize().width / 2, visibleOrigin.y + _controllerRight->getContentSize().height / 2));

	this->addChild(_controllerRight);

	scheduleUpdate();
#endif


	//health init
	auto healthBar = HealthBar::create();
	healthBar->setAnchorPoint(Point(0.f, 1.f));
	healthBar->setPosition(Point(visibleOrigin.x, visibleOrigin.y + visibleSize.height));
	this->addChild(healthBar);


	return true;
}

void HUDLayer::update(float dt)
{
	//left controller
	{
		static Vect old_dir = { 0, 0 };
		Vect dir;
		auto a = _controllerLeft->getDirection().getAngle();
		if (_controllerLeft->getDirection().length() == 0)
			dir = { 0, 0 };		
		else if (a > (-M_PI / 8) && a < (M_PI / 8))
		{
			dir = { 1, 0 };
		}
		else if (a > (M_PI / 8) && a < (3 * M_PI / 8))
		{
			dir = { 1, 1 };
		}
		else if (a > (3 * M_PI / 8) && a < (5 * M_PI / 8))
		{
			dir = { 0, 1 };
		}
		else if (a > (5 * M_PI / 8) && a < (7 * M_PI / 8))
		{
			dir = { -1, 1 };
		}
		else if (a > (7 * M_PI / 8) || a < (-7 * M_PI / 8))
		{
			dir = { -1, 0 };
		}
		else if (a > (-7 * M_PI / 8) && a < (-5 * M_PI / 8))
		{
			dir = { -1, -1 };
		}
		else if (a > (-5 * M_PI / 8) && a < (-3 * M_PI / 8))
		{
			dir = { 0, -1 };
		}
		else if (a > (-3 * M_PI / 8) && a < (-M_PI / 8))
		{
			dir = { 1, -1 };
		}

		if (old_dir != dir)
		{
			old_dir = dir;
			dir.normalize();
			EventCustom event(EVENT_CONTROLLER_LEFT);
			event.setUserData(&dir);
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
	}
	
	//right controller
	{
		static bool pressed = !_controllerRight->getPressed();
		if (pressed != _controllerRight->getPressed())
		{
			pressed = _controllerRight->getPressed();
			EventCustom event(EVENT_FIRE_EVENT);			
			event.setUserData(&pressed);
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
		}
		
		auto dir = _controllerRight->getDirection();		
		EventCustom event(EVENT_CONTROLLER_RIGHT);
		event.setUserData(&dir);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}

