#include "Enemy.h"
#include "Enemies/EnemyTest.h"

USING_NS_CC;


Enemy* Enemy::createEnemy(Enemy::Enemies_t enemyType, cocos2d::Node* world)
{
	Enemy* enemy = nullptr;
	switch (enemyType)
	{
	case Enemy::ENEMY_FIRST_AND_TEST:
		enemy = EnemyTest::create();
		break;
	default:
		break;
	}
	if (enemy)
		enemy->setWorld(world);
	return enemy;
}
