#include "Level.h"
#include "Levels/Level00.h"

USING_NS_CC;

Level* Level::createLevel(Level::Levels level)
{
	Level* levelNode = nullptr;
	switch (level)
	{
	case Level::LEVEL_0:
		levelNode = Level00::create();
		break;
	default:
		break;
	}
	return levelNode;
}

bool Level::init()
{
	return Node::init();
}
