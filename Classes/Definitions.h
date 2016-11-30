#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include "cocos2d.h"


extern const char* HERO_TAG_NAME;
extern const char* EVENT_CONTROLLER_LEFT;
extern const char* EVENT_CONTROLLER_RIGHT;
extern const char* EVENT_FIRE_EVENT;
extern const char* EVENT_HEALTH_PERCENT;
extern const char* EVENT_HERO_DIED;
extern const float HERO_HEALTH;

namespace collision_bitmask
{
	const int HERO_COLLISION_BITMASK = 0x001;
	const int BULLET_COLLISION_BITMASK = 0x002;
	const int ENEMY_TEST_COLLISION_BITMASK = 0x004;
}

#endif // __DEFINITIONS_H__
