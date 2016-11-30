#ifndef __HEALTH_BAR_H__
#define __HEALTH_BAR_H__

#include "cocos2d.h"

class HealthBar : public cocos2d::Sprite
{

public:
	
	CREATE_FUNC(HealthBar);

private:
	bool init();

private:

	cocos2d::Node* _healthBar;
};

#endif // __HEALTH_BAR_H__
