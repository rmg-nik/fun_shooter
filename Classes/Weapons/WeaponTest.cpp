#include "Weapons/WeaponTest.h"
#include "Definitions.h"

USING_NS_CC;

bool WeaponTest::BulletTest::init()
{
	if (!Sprite::initWithSpriteFrameName("bullet.png"))
		return false;

	auto bulletBody = PhysicsBody::createBox(getContentSize());
	bulletBody->setDynamic(false);
	bulletBody->setContactTestBitmask(true);
	bulletBody->setCollisionBitmask(collision_bitmask::BULLET_COLLISION_BITMASK);
	setPhysicsBody(bulletBody);
	setBulletDamage(100);
	setBulletSpeed(1);
	return true;
}

bool WeaponTest::init()
{
	setBulletInterval(0.5f);

	if (!Weapon::init())
		return false;

	return true;
}

Bullet* WeaponTest::getBullet() const
{
	return BulletTest::create();
}


