#include "Controller.h"

USING_NS_CC;


bool Controller::init()
{
	if (!Sprite::initWithFile("controllerArea.png"))
		return false;

	_pressed = false;
	_alwaysPressed = false;
	_radius = getContentSize().width / 2;
	_controllPosition = Sprite::create("controllerPosition.png");

	_controllPosition->setPosition(Point(_radius, _radius));

	addChild(_controllPosition);
	
	auto tlistener = EventListenerTouchOneByOne::create();
	tlistener->onTouchBegan = [&](Touch* touch, Event* event) -> bool
	{
		if (this->getBoundingBox().containsPoint(touch->getLocation()))
		{
			_pressed = true;
			auto pos = this->convertToNodeSpace(touch->getLocation());			
			_controllPosition->setPosition(pos);
			return true;
		}
			
		return false;
	};

	tlistener->onTouchMoved = [&](Touch* touch, Event* event) 
	{
		if (!this->getBoundingBox().containsPoint(touch->getLocation()))
			return;
		auto pos = this->convertToNodeSpace(touch->getLocation());
		_controllPosition->setPosition(pos);
	};

	tlistener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		_pressed = false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tlistener, this);

	scheduleUpdate();
	return true;
}

void Controller::update(float dt)
{
	auto pos = _controllPosition->getPosition() - Point(_radius, _radius);
	if (pos.length() > _radius)
	{
		pos.normalize();
		pos *= _radius;
		pos += {_radius, _radius};
		_controllPosition->setPosition(pos);
	}
}

Point Controller::getDirection()
{
	auto pos = _controllPosition->getPosition() - Point(_radius, _radius);
	if (!_alwaysPressed && (pos.length() < (_radius / 3) || !_pressed))
		return { 0, 0 };

	pos.normalize();
	return pos;
}
