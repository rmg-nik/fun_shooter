#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"
#include "Controller.h"

class HUDLayer : public cocos2d::Layer
{
public:

	virtual bool init();
    
	CREATE_FUNC(HUDLayer);

private:

	virtual void update(float dt);
	Controller* _controllerLeft;
	Controller* _controllerRight;
};

#endif // __HUD_LAYER_H__
