#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Hero;
class Level;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	void setPhysicsWorld(cocos2d::PhysicsWorld* world){ _world = world; }

private:

	bool collissionResolve(const cocos2d::PhysicsContact& contact);

	void update(float dt);

	void desktopControls();

	void touchControls();
	const float MULTIPLIER_OF_WORLD = 2;
	const float BORDER_ZONE = 100;

	cocos2d::PhysicsWorld* _world;

	Level* _game_world;

	Hero* _hero;



};

#endif // __GAME_SCENE_H__
