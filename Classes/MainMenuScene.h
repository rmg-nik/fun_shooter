#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();  

    void menuNewGameCallback(cocos2d::Ref* pSender);
	void menuOptionsCallback(cocos2d::Ref* pSender);
	void menuQuitCallback(cocos2d::Ref* pSender);
    
	CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
