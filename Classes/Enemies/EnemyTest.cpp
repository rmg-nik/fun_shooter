#include "Enemies/EnemyTest.h"
#include "Definitions.h"

USING_NS_CC;

bool EnemyTest::init()
{
	static int count = 0;
	CCLOG("enemy = %d", ++count);

	if (!Sprite::initWithSpriteFrameName("enemyTest00.png"))
		return false;

	auto sfc = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animationFrames;
	char buffer[255];
	for (int i = 0; i < 4; ++i)
	{
		sprintf(buffer, "enemyTest%02d.png", i);
		auto frame = sfc->getSpriteFrameByName(buffer);
		animationFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animationFrames, 0.2f);
	auto act = RepeatForever::create(Animate::create(animation));
	runAction(act);
	
	auto body = PhysicsBody::createCircle(this->getContentSize().width / 2);	
	body->setContactTestBitmask(true);
	body->setCollisionBitmask(collision_bitmask::ENEMY_TEST_COLLISION_BITMASK);

	setPhysicsBody(body);
	scheduleUpdate();
	return true;
}

void EnemyTest::update(float dt)
{
	auto world = getWorld();
	if (world)
	{
		auto hero = world->getChildByName("hero");
		if (hero)
		{
			auto dir = hero->getPosition() - getPosition();
			if (dir.length() < 1)
			{
				getPhysicsBody()->setVelocity({ 0, 0 });
				return;
			}
			float angl = CC_RADIANS_TO_DEGREES(-dir.getAngle());
			if (angl < 0)
				angl = 360 + angl;

			Vect newVel = { cosf(dir.getAngle()) * 100, sinf(dir.getAngle()) * 100 };
			if ((newVel - getPhysicsBody()->getVelocity()).length() < 0.01)
				return;
			getPhysicsBody()->setVelocity(newVel);
			this->setRotation(angl);
		}
	}
}
