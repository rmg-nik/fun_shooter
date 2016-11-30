#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"

class Weapon;

class Hero : public cocos2d::Node
{
public:

	virtual bool init();

	CREATE_FUNC(Hero);
	

	inline void setShooteDirection(const cocos2d::Vect& dir){ _shooteDirection = dir; }

	void applyDirection(const cocos2d::Vect dir);

	void setWeapon(Weapon* weapon);

	void applyDamage(float damage);

private:
	
	void update(float dt);

private:

	const float VELOSITY_LIMIT = 200.f;
	const float ROTATION_TIME = 0.2f;
	float _heroHealth;
	cocos2d::Vect _shooteDirection;
	char _moveDirection;
	cocos2d::Sprite* _top;
	cocos2d::Sprite* _bottom;
	cocos2d::Action* _bottomAction;
	Weapon* _weapon;
};

#endif // __HERO_H__
