#include "ImageScene.h"

USING_NS_CC;

// singleton stuff
static Scene *s_ImageScene = nullptr;


cocos2d::Scene* ImageScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ImageScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ImageScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();



	auto s = Sprite::create("win8.1.png");
	s->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(s);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (s->getBoundingBox().containsPoint(t->getLocation()))
		{
			//Director::getInstance()->replaceScene(ImageScene::createScene());//原场景销毁

			Director::getInstance()->popScene();//切换回原场景，此场景被移除
		}
		return false;//是否吞噬此事件，如果true，则不向上传递此事件
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, s);


	return true;
}

 Scene* ImageScene::getInstance()
 {
 	if (!s_ImageScene)
	{
		s_ImageScene = ImageScene::createScene();
 		//CCASSERT(s_ImageScene, "FATAL: Not enough memory");
	}

	return s_ImageScene;
 }
