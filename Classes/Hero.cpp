#include "Hero.h"
#include "Weapon.h"
#include "Definitions.h"

USING_NS_CC;

bool Hero::init()
{
	if (!Node::init())
		return false;

	_moveDirection = 0;
	_shooteDirection = { 0, 1 };
	_heroHealth = HERO_HEALTH;

	setName("hero");

	_bottom = Sprite::create();	
	//створюємо анімацію руху
	{
		auto sfc = SpriteFrameCache::getInstance();	
		Vector<SpriteFrame*> animationFrames;
		char buffer[255];
		for (int i = 0; i < 4; ++i)
		{
			sprintf(buffer, "heroFeet%02d.png", i);
			auto frame = sfc->getSpriteFrameByName(buffer);
			animationFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animationFrames, 0.2f);
		auto movieBottom = Sprite::create();
		movieBottom->setTag(42077);
		_bottom->addChild(movieBottom);
		auto act = RepeatForever::create(Animate::create(animation));
		movieBottom->runAction(act);		
	}
	
	_top = Sprite::createWithSpriteFrameName("heroHead.png");
	auto hand = Sprite::createWithSpriteFrameName("heroHands.png");
	hand->setPosition(Point(_top->getContentSize().width / 2, _top->getContentSize().height / 2));
	_top->addChild(hand, -2);

	auto size = _top->getContentSize();
	this->setContentSize(size);
	this->setAnchorPoint(Point(0.5, 0.5));
	_bottom->setPosition(Point(size.width / 2, size.height / 2));
	_top->setPosition(Point(size.width / 2, size.height / 2));
	
	this->addChild(_bottom, 1);
	this->addChild(_top, 2);

	auto body = PhysicsBody::createCircle(MAX(size.width, size.height) / 2);
	body->setContactTestBitmask(true);
	body->setCollisionBitmask(collision_bitmask::HERO_COLLISION_BITMASK);

	body->setVelocityLimit(VELOSITY_LIMIT);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);	

	scheduleUpdate();	
	return true;
}

void Hero::update(float dt)
{
	static bool onceFlag = true;
	if (onceFlag)
	{
		onceFlag = false;
		applyDirection({ 0, 0 });
	}
	//TODO сам не знаю, чому тут мінус
	auto angl = CC_RADIANS_TO_DEGREES( -_shooteDirection.getAngle());
	if (angl < 0)
		angl = 360 + angl;
	_top->setRotation(angl);
}

void Hero::applyDirection(const cocos2d::Vect dir)
{
	auto body = getPhysicsBody();
	auto vect = dir * body->getVelocityLimit();
	body->setVelocity(vect);

	if (dir.length() != 0)
	{
		//TODO сам не знаю, чому тут мінус
		float angl = CC_RADIANS_TO_DEGREES(-dir.getAngle());
		if (angl < 0)
			angl = 360 + angl;
		auto rotateAction = RotateTo::create(ROTATION_TIME, angl);
		rotateAction->setTag(12345);
		_bottom->runAction(rotateAction);
		auto movieBottom = _bottom->getChildByTag(42077);
		movieBottom->getActionManager()->resumeTarget(movieBottom);
	}
	else
	{
		_bottom->stopActionByTag(12345);
		auto movieBottom = _bottom->getChildByTag(42077);
		movieBottom->getActionManager()->pauseTarget(movieBottom);
	}

}

void Hero::setWeapon(Weapon* weapon)
{
	if (!weapon)
		return;

	if (_weapon)
		_top->removeChild(_weapon, true);
	_weapon = weapon;
	auto heroSize = this->getContentSize();
	_weapon->setPosition(Point(0.75f * heroSize.width, 0.5f * heroSize.height));
	_top->addChild(_weapon, -1);
}

void Hero::applyDamage(float damage)
{
	_heroHealth -= damage;
	if (_heroHealth <= 0)
	{
		EventCustom event(EVENT_HERO_DIED);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
	else
	{
		EventCustom event(EVENT_HEALTH_PERCENT);
		float percent = 100 * _heroHealth / HERO_HEALTH;
		event.setUserData(&percent);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}
