#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:

	enum Enemies_t
	{
		ENEMY_FIRST_AND_TEST = 41077
	};

	static Enemy* createEnemy(Enemies_t enemyType, cocos2d::Node* world);

	virtual float getHealth() const = 0;
	virtual float getEnergy() const = 0;
	virtual float getDamage() const = 0;

	inline cocos2d::Node* getWorld() const { return _world; }

private:

	void setWorld(cocos2d::Node* world){ _world = world; }

private:

	cocos2d::Node* _world;

};

#endif // __ENEMY_H__
