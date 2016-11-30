#include "GameScene.h"
#include "HUDLayer.h"
#include "Hero.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Level.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point::ZERO);
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	//layer->setScale(0.5);
    // add layer as a child to scene
    scene->addChild(layer);

	auto hud = HUDLayer::create();
	scene->addChild(hud);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	SpriteBatchNode* spritebatch = SpriteBatchNode::create("texture.png");
	addChild(spritebatch, 0);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist");

    Size visibleSize = Director::getInstance()->getVisibleSize();
	_game_world = Level::createLevel(Level::LEVEL_0);

	this->addChild(_game_world);



	_hero = Hero::create();		
	_hero->setPosition(_game_world->getContentSize().width / 2, _game_world->getContentSize().height / 2);
	_game_world->addChild(_hero, 100);

	auto weapon = Weapon::createWeapon(Weapon::WeaponType::WEAPON_TEST, _game_world);
	_hero->setWeapon(weapon);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
	desktopControls();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	touchControls();
#endif
	auto clistener = EventListenerPhysicsContact::create();
	clistener->onContactBegin = CC_CALLBACK_1(GameScene::collissionResolve, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(clistener, this);

	//примусово викликаємо, щоб усунути скачок на початку (розкоментувати для усунення)
	//update(0);
	scheduleUpdate();  

    return true;
}

void GameScene::desktopControls()
{
	auto klistener = EventListenerKeyboard::create();
	static Vect dir = { 0, 0 };
	klistener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* event)
	{
		bool neededKey = false;
		if ((key == EventKeyboard::KeyCode::KEY_LEFT_ARROW) || (key == EventKeyboard::KeyCode::KEY_A))
		{
			dir += {-1, 0};
			neededKey = true;
		}
		else if ((key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || (key == EventKeyboard::KeyCode::KEY_D))
		{
			dir += {1, 0};
			neededKey = true;
		}
		else if ((key == EventKeyboard::KeyCode::KEY_UP_ARROW) || (key == EventKeyboard::KeyCode::KEY_W))
		{
			dir += {0, 1};
			neededKey = true;
		}
		else if ((key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) || (key == EventKeyboard::KeyCode::KEY_S))
		{
			dir += {0, -1};
			neededKey = true;
		}
		if (neededKey)
		{			
			_hero->applyDirection(dir.getNormalized());
		}
	};
	klistener->onKeyReleased = [&](EventKeyboard::KeyCode key, Event* event)
	{
		bool neededKey = false;
		if ((key == EventKeyboard::KeyCode::KEY_LEFT_ARROW) || (key == EventKeyboard::KeyCode::KEY_A))
		{
			dir += {1, 0};
			neededKey = true;
		}
		else if ((key == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || (key == EventKeyboard::KeyCode::KEY_D))
		{
			dir += {-1, 0};
			neededKey = true;
		}
		else if ((key == EventKeyboard::KeyCode::KEY_UP_ARROW) || (key == EventKeyboard::KeyCode::KEY_W))
		{
			dir += {0, -1};
			neededKey = true;
		}
		else if ((key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) || (key == EventKeyboard::KeyCode::KEY_S))
		{
			dir += {0, 1};
			neededKey = true;
		}
		if (neededKey)
		{
			_hero->applyDirection(dir.getNormalized());
		}
	};

	auto mlistener = EventListenerMouse::create();
	mlistener->onMouseMove = [&](Event* event)
	{
		auto ev = static_cast<EventMouse*>(event);
		auto hero_pos = _game_world->convertToWorldSpace(_hero->getPosition());
		Vect v = { ev->getCursorX() - hero_pos.x, ev->getCursorY() - hero_pos.y };
		v.normalize();
		_hero->setShooteDirection(v);
	};	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(klistener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mlistener, this);
}


void GameScene::touchControls()
{
	auto cLeftControllerListener = EventListenerCustom::create(EVENT_CONTROLLER_LEFT, [&](EventCustom* event)
	{
		auto dir = reinterpret_cast<Vect*>(event->getUserData());
		_hero->applyDirection(*dir);
	});

	auto cRightControllerListener = EventListenerCustom::create(EVENT_CONTROLLER_RIGHT, [&](EventCustom* event)
	{
		auto dir = reinterpret_cast<Vect*>(event->getUserData());
		_hero->setShooteDirection(*dir);
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cLeftControllerListener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cRightControllerListener, this);
}

void GameScene::update(float dt)
{
	//TODO розібратися з позицією world при масштабуванні
	auto worldSize = _game_world->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto centerScreen = Point(visibleSize.width / 2, visibleSize.height / 2);
	auto heroPosOnScreen = _game_world->convertToWorldSpace(_hero->getPosition());	
	auto worldPosOnScreen = _game_world->getPosition();

	// BEGIN не даємо герою наблизитися до краю ближче, ніж на BORDER_ZONE
	auto heroPosInWorld = _hero->getPosition();
	const float border = BORDER_ZONE + _hero->getContentSize().width / 2;
	if (heroPosInWorld.x < border)
		heroPosInWorld.x = border;
	else if (heroPosInWorld.x > worldSize.width - border) 
		heroPosInWorld.x = worldSize.width - border;
	if (heroPosInWorld.y < border)
		heroPosInWorld.y = border;
	else if (heroPosInWorld.y > worldSize.height - border)
		heroPosInWorld.y = worldSize.height - border;
	_hero->setPosition(heroPosInWorld);
	// END не даємо герою наблизитися до краю ближче, ніж на BORDER_ZONE

	// BEGIN розміщуємо карту так, щоб герой був посередині
	auto diff = heroPosOnScreen - centerScreen;
	worldPosOnScreen -= diff;
	if (worldPosOnScreen.x > worldSize.width / 2)
		worldPosOnScreen.x = worldSize.width / 2;
	else if (worldPosOnScreen.x < -worldSize.width / 2 + visibleSize.width)	
		worldPosOnScreen.x = -worldSize.width / 2 + visibleSize.width;	
	if (worldPosOnScreen.y > worldSize.height / 2)
		worldPosOnScreen.y = worldSize.height / 2;
	else if (worldPosOnScreen.y < -worldSize.height / 2 + visibleSize.height)
		worldPosOnScreen.y = -worldSize.height / 2 + visibleSize.height;
	_game_world->setPosition(worldPosOnScreen);
	// END розміщуємо карту так, щоб герой був посередині	

}

bool GameScene::collissionResolve(const cocos2d::PhysicsContact& contact)
{
	auto a = contact.getShapeA();
	auto b = contact.getShapeB();
	if (((a->getCollisionBitmask() == collision_bitmask::BULLET_COLLISION_BITMASK) && (b->getCollisionBitmask() == collision_bitmask::ENEMY_TEST_COLLISION_BITMASK))
		||
		((a->getCollisionBitmask() == collision_bitmask::ENEMY_TEST_COLLISION_BITMASK) && (b->getCollisionBitmask() == collision_bitmask::BULLET_COLLISION_BITMASK)
		))
	{
		_game_world->removeChild(a->getBody()->getNode());
		_game_world->removeChild(b->getBody()->getNode());
		return true;
	}
	else if (((a->getCollisionBitmask() == collision_bitmask::HERO_COLLISION_BITMASK) && (b->getCollisionBitmask() == collision_bitmask::ENEMY_TEST_COLLISION_BITMASK))
		||
		((a->getCollisionBitmask() == collision_bitmask::ENEMY_TEST_COLLISION_BITMASK) && (b->getCollisionBitmask() == collision_bitmask::HERO_COLLISION_BITMASK)
		))
	{
		Hero* hero = nullptr;
		Enemy* enemy = nullptr;
		if (a->getCollisionBitmask() == collision_bitmask::ENEMY_TEST_COLLISION_BITMASK)
		{
			hero = dynamic_cast<Hero*>(b->getBody()->getNode());
			enemy = dynamic_cast<Enemy*>(a->getBody()->getNode());
		}
		else
		{
			hero = dynamic_cast<Hero*>(a->getBody()->getNode());
			enemy = dynamic_cast<Enemy*>(b->getBody()->getNode());
		}
		hero->applyDamage(enemy->getDamage());
		return false;
	}
	return false;
}
