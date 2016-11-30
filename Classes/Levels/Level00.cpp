#include "Level00.h"
#include "Enemy.h"
#include "Definitions.h"

USING_NS_CC;

bool Level00::init()
{
	if (!Level::init())
		return false;


	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	this->setAnchorPoint(Point(0.5, 0.5));
	this->setContentSize(getLevelSize());
	this->setPosition(visibleSize.width / 2, visibleSize.height / 2);


	auto texture = TextureCache::getInstance()->addImage("bg512.png");

	Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	texture->setTexParameters(params);
	auto bg = Sprite::createWithTexture(texture, Rect(0, 0, getLevelSize().width, getLevelSize().height));
	bg->setPosition(getLevelSize().width / 2, getLevelSize().height / 2);
	this->addChild(bg);	

	scheduleUpdate();
	return true;
}

void Level00::update(float dt)
{
	static float prevTime = 0;
	if (prevTime >= MONSTER_INTERVAL)
	{
		prevTime = 0;

		auto hero = getChildByName(HERO_TAG_NAME);
		auto hsize = hero->getContentSize();
		auto hpos = hero->getNormalizedPosition();
		auto rect = Rect(hpos.x - hero->getAnchorPoint().x * hsize.width, hpos.y - hero->getAnchorPoint().y * hsize.height, hsize.width, hsize.height);
		
		float x, y;
		do 
		{
			x = CCRANDOM_0_1() * getLevelSize().width;
			y = CCRANDOM_0_1() * getLevelSize().height;
			if (!rect.containsPoint(Point(x, y)))
				break;
		} while (true);
	
		auto enemy = Enemy::createEnemy(Enemy::ENEMY_FIRST_AND_TEST, this);
		enemy->setPosition(Point(x, y));
		addChild(enemy);
	}
	else
	{
		prevTime += dt;
	}
}
