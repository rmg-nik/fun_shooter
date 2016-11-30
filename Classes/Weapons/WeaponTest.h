#ifndef __WEAPON_TEST_H__
#define __WEAPON_TEST_H__

#include "Weapon.h"


class WeaponTest : public Weapon
{
	class BulletTest : public Bullet
	{
	public:
		CREATE_FUNC(BulletTest)
	private:
		virtual bool init();
	};

public:

	CREATE_FUNC(WeaponTest);
	
private:
	bool init();	
	virtual Bullet* getBullet() const;

private:

	Bullet* _bullet;
};

#endif // __WEAPON_TEST_H__
