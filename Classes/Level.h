#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"

class Level : public cocos2d::Node
{
public:
	enum Levels
	{
		LEVEL_0 = 0
	};

	static Level* createLevel(Levels level);
	
	virtual cocos2d::Size getLevelSize() const = 0;
	
protected:
	bool init();

};

#endif // __LEVEL00_H__
