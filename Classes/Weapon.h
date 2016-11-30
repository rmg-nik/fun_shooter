#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:

	
	float getBulletSpeed() const { return (1.f / _speed); }
	float getBulletDamage() const { return _damage; }

protected:
	virtual bool init() = 0;

	void setBulletDamage(float damage) { _damage = damage; }

	//оптимально від 0.1 до 2
	void setBulletSpeed(float speed) { _speed = speed; }
private:
	float _damage;
	float _speed;
};


class Weapon : public cocos2d::Sprite
{

public:

	enum WeaponType
	{
		WEAPON_TEST = 42077
	};

	static Weapon* createWeapon(WeaponType weaponType, cocos2d::Node* world);
	
	inline cocos2d::Node* getWorld() const { return _world; }

	float getBulletInterval() const { return _bulletInterval; }
	void setBulletInterval(float interval) { _bulletInterval = interval; }


	virtual Bullet* getBullet() const = 0;

protected:


	inline void setWorld(cocos2d::Node* world){ _world = world; }	
	
	bool init();
	void update(float dt);

private:

	float _bulletInterval;
	float _prevBulletTime;
	cocos2d::Node* _world;
	bool _fire;
	cocos2d::Node* _emitter;
	cocos2d::Sprite* _aim;
	cocos2d::Point _dst;

};

#endif // __WEAPON_H__
