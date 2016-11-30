#include "Weapon.h"
#include "Definitions.h"
#include "Weapons/WeaponTest.h"

USING_NS_CC;

Weapon* Weapon::createWeapon(WeaponType weaponType, cocos2d::Node* world)
{
	Weapon* weapon;
	switch (weaponType)
	{
	case Weapon::WEAPON_TEST:
		weapon = WeaponTest::create();
		break;
	default:
		break;
	}

	weapon->setWorld(world);
	return weapon;
}


bool Weapon::init()
{
	if (!Sprite::initWithSpriteFrameName("weapon.png"))
		return false;

	_fire = false;
	_prevBulletTime = getBulletInterval();
	
	_emitter = Node::create();
	_emitter->setContentSize(Size(1, 1));
	_emitter->setPosition(Point(getContentSize().width, getContentSize().height / 2));
	addChild(_emitter, 0);

	_aim = Sprite::createWithSpriteFrameName("aim.png");
	_aim->setPosition(Point(getContentSize().width * 2, getContentSize().height / 2));
	addChild(_aim);

	auto cFireListener = EventListenerCustom::create(EVENT_FIRE_EVENT, [&](EventCustom* event)
	{
		if (*reinterpret_cast<bool*>(event->getUserData()))
			_fire = true;
		else
			_fire = false;
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cFireListener, this);
	
	scheduleUpdate();
	return true;
}

void Weapon::update(float dt)
{
	if (_fire)
	{
		if (_prevBulletTime >= getBulletInterval())
		{
			auto* bullet = getBullet();
			_prevBulletTime = 0;
			auto world = getWorld();		
			auto weaponSize = this->getContentSize();

			auto  bulletPos = this->convertToWorldSpace(_emitter->getPosition());
			bulletPos = world->convertToNodeSpace(bulletPos);
			bullet->setPosition(bulletPos);


			auto dstPos = this->convertToWorldSpace(_aim->getPosition());
			dstPos = world->convertToNodeSpace(dstPos);
			dstPos = dstPos - bulletPos;
			float angl = dstPos.getAngle();
			auto maxDst = MAX(_world->getContentSize().width, _world->getContentSize().height);
			dstPos = { maxDst * cosf(angl), maxDst * sinf(angl) };

			bullet->setRotation(CC_RADIANS_TO_DEGREES(-angl));
			world->addChild(bullet);
			bullet->runAction(Sequence::create(MoveBy::create(bullet->getBulletSpeed(), dstPos), RemoveSelf::create(true), nullptr));			
		}
		else
			_prevBulletTime += dt;
	}
	else
		_prevBulletTime += dt;
}
