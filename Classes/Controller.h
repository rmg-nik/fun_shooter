#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"

class Controller : public cocos2d::Sprite
{
public:

	CREATE_FUNC(Controller);

	cocos2d::Point getDirection();
	bool getPressed() const { return _pressed; }
	void setAlwaysPressed(bool alwaysPressed){ _alwaysPressed = alwaysPressed; }
private:

	virtual bool init();
	virtual void update(float dt);

private:

	bool _pressed;
	bool _alwaysPressed;
	float _radius;
	cocos2d::Sprite* _controllPosition;
};


#endif // __CONTROLLER_H__
