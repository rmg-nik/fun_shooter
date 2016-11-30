#ifndef __LEVEL00_H__
#define __LEVEL00_H__

#include "Level.h"

class Level00 : public Level
{
public:

	CREATE_FUNC(Level00);
	
	virtual cocos2d::Size getLevelSize() const { return {2000, 2000}; }
	 
private:

	virtual bool init();
	virtual void update(float dt);
private:

	const float MONSTER_INTERVAL = 0.2;
};

#endif // __LEVEL00_H__
