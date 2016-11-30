#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
public:
	enum NextScene_t
	{
		GAME_SCENE,
		MENU_SCENE
	};
    static cocos2d::Scene* createScene(NextScene_t nextScene);

   virtual bool init();  

	CREATE_FUNC(SplashScene);

private:
	void setNextScene(NextScene_t nextScene) { _nextScene = nextScene; }
	void createNexteScene(float dt);
	NextScene_t _nextScene;
};

#endif // __SPLASH_SCENE_H__
