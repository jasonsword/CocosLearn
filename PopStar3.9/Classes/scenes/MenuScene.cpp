#include "MenuScene.h"
#include "GameScene.h"
#include "GameData.h"
#include "LogInScene.h"
#include "LSlog.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	if (!Layer::init())
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rootNode = CSLoader::createNode("MenuScene.csb");
	addChild(rootNode);
	
	//开始游戏
	auto startBtn = CreateMenuItem("newgame.png", CC_CALLBACK_1(MenuScene::newMenuItem, this));
	//继续上次的
	auto resumeBtn = CreateMenuItem("resume.png", CC_CALLBACK_1(MenuScene::resumeMenuItem, this));
	//退出
	auto rateBtn = CreateMenuItem("star_exit.png", CC_CALLBACK_1(MenuScene::exitMenuItem, this));

	auto menu = Menu::create(startBtn, resumeBtn, rateBtn, nullptr);
	//menu->alignItemsVertically();
	menu->alignItemsVerticallyWithPadding(30.0f);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 3);
	this->addChild(menu);

	auto login = Label::createWithTTF("fonts/Avenir-Roman.ttf", "LOGIN");
	login->setSystemFontSize(60);
	login->setTextColor(Color4B(255, 100, 0, 250));
	login->setPosition(visibleSize.width / 2, 150);
	this->addChild(login);

	auto lisenter = EventListenerTouchOneByOne::create();
	lisenter->onTouchBegan = [](Touch* t, Event* e)
	{
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(TransitionFlipX::create(1.0f, LogInScene::createScene(), TransitionScene::Orientation::LEFT_OVER));
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lisenter, login);
    
    return true;
}

void MenuScene::onEnter()
{
	Layer::onEnter();

	//LOG_DEBUG("MenuScene onEnter");
	//LOG_DEBUG("%s", UserDefault::getInstance()->getXMLFilePath().c_str());
	//GameData::getInstance()->reset();
}

void MenuScene::exitMenuItem(cocos2d::Ref* pSender)
{
	GameData::getInstance()->save();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MenuScene::resumeMenuItem(cocos2d::Ref* pSender)
{
	GameData::getInstance()->init(GameData::PlayType::LAST);
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void MenuScene::newMenuItem(cocos2d::Ref* pSender)
{
	GameData::getInstance()->init(GameData::PlayType::NEW);
	Director::getInstance()->replaceScene(GameScene::createScene());
}

MenuItemImage* MenuScene::CreateMenuItem(const std::string& normalImage, const ccMenuCallback& callback)
{
	auto menuitem = MenuItemImage::create();
	if (!menuitem)
	{
		LOG_DEBUG("menuitem create failed!");
		return nullptr;
	}
	menuitem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage));
	menuitem->setCallback(callback);
	return menuitem;
}
