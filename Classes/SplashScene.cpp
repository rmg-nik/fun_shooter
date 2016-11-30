#include "SplashScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* SplashScene::createScene(NextScene_t nextScene)
{
    auto scene = Scene::create();
	auto layer = SplashScene::create();
	layer->setNextScene(nextScene);
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();    
	auto logo = Sprite::create("Logo.png");
	logo->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));	
	addChild(logo);

	auto loadingLabel = Label::createWithTTF("LOADING...", "fonts/Marker Felt.ttf", 32);
	loadingLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 8 + origin.y));
	addChild(loadingLabel);

	scheduleOnce(schedule_selector(SplashScene::createNexteScene), 1);

    return true;
}

void SplashScene::createNexteScene(float dt)
{
	Scene* scene = nullptr;
	switch (_nextScene)
	{
	case SplashScene::GAME_SCENE:
		scene = GameScene::createScene();
		break;
	case SplashScene::MENU_SCENE:
		scene = MainMenuScene::createScene();
		break;
	default:
		break;
	}

	if (scene)
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}
