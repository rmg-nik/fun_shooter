#ifndef __ENEMY_TEST_H__
#define __ENEMY_TEST_H__

#include "Enemy.h"


class EnemyTest : public Enemy
{
public:

	CREATE_FUNC(EnemyTest);

	bool init();

	virtual float getHealth() const { return 100; }
	virtual float getEnergy() const { return 100; }
	virtual float getDamage() const { return 10; }

private:

	void update(float dt);
};

#endif // __ENEMY_TEST_H__
