#include "MainMenuScene.h"
#include "SplashScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto newGameItem = MenuItemImage::create(
		"menuItemNewGame.png",
		"menuItemNewGamePressed.png",
		CC_CALLBACK_1(MainMenuScene::menuNewGameCallback, this));

	auto optionsItem = MenuItemImage::create(
		"menuItemOptions.png",
		"menuItemOptionsPressed.png",
		CC_CALLBACK_1(MainMenuScene::menuOptionsCallback, this));

	auto quitItem = MenuItemImage::create(
		"menuItemQuit.png",
		"menuItemQuitPressed.png",
		CC_CALLBACK_1(MainMenuScene::menuQuitCallback, this));
    
// 	quitItem->setPosition(Vec2(origin.x + visibleSize.width - quitItem->getContentSize().width/2 ,
//                                 origin.y + quitItem->getContentSize().height/2));

    // create menu, it's an autorelease object
	auto menu = Menu::create(newGameItem, optionsItem, quitItem, NULL);
	menu->alignItemsVerticallyWithPadding(30);
    menu->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(menu, 1);

    return true;
}

void MainMenuScene::menuNewGameCallback(Ref* pSender)
{
	auto scene = SplashScene::createScene(SplashScene::GAME_SCENE);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void MainMenuScene::menuOptionsCallback(Ref* pSender)
{

}

void MainMenuScene::menuQuitCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

