#include "CircleRunScene.h"

USING_NS_CC;



Scene* CircleRun::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CircleRun::create();

	scene->addChild(layer);

	return scene;
}

bool CircleRun::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void CircleRun::onEnter()
{
	Layer::onEnter();
	CCLOG("onEnter");
}

void CircleRun::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	CCLOG("onEnterTransitionDidFinish");
}

void CircleRun::onExit()
{
	Layer::onExit();
	CCLOG("onExit");
}

void CircleRun::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	CCLOG("onExitTransitionDidStart");
}

void CircleRun::cleanup()
{
	Layer::cleanup();
	CCLOG("cleanup");
}
