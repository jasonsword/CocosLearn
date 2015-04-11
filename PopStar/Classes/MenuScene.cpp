#include "MenuScene.h"
#include "GameScene.h"
#include "GameData.h"

USING_NS_CC;

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

	//整体背景
	auto background = Sprite::create("bg_main.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background, -1);

	//加特效DUANG
	CreateBgParticle(Vec2(visibleSize.width / 4 + 40, visibleSize.height * 3 / 4 - 100), "leaf_open");
	CreateBgParticle(Vec2(visibleSize.width *3 / 4, visibleSize.height * 3 / 4 + 50), "quanquan");

	//Pop背景
	auto backgroundPop = Sprite::createWithSpriteFrameName("pop.png");
	
	//Star背景
	auto backgroundStar = Sprite::createWithSpriteFrameName("star.png");
	backgroundStar->setAnchorPoint(Vec2(-0.6f, 0.7f));
	backgroundPop->addChild(backgroundStar);

	float xoffset = visibleSize.width / 2 - (backgroundPop->getContentSize().width / 2 + backgroundStar->getContentSize().width / 10) / 2 + 15;
	backgroundPop->setPosition(xoffset, visibleSize.height- backgroundPop->getContentSize().height);

	this->addChild(backgroundPop);
	
	//开始游戏
	auto startBtn = CreateMenuItem("newgame.png", CC_CALLBACK_1(MenuScene::newMenuItem, this));
	//继续上次的
	auto resumeBtn = CreateMenuItem("resume.png", CC_CALLBACK_1(MenuScene::resumeMenuItem, this));
	//退出
	auto rateBtn = CreateMenuItem("save_exit.png", CC_CALLBACK_1(MenuScene::exitMenuItem, this));

	auto menu = Menu::create(startBtn, resumeBtn, rateBtn, nullptr);
	//menu->alignItemsVertically();
	menu->alignItemsVerticallyWithPadding(30.0f);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 3);
	this->addChild(menu);
    
    return true;
}

void MenuScene::CreateBgParticle(cocos2d::Vec2 &position, const std::string &particleName)
{
	auto particle = ParticleSystemQuad::create("particles/" + particleName + ".plist");
	particle->setAnchorPoint(Vec2(0.5f, 0.5f));
	particle->setPosition(position);
	this->addChild(particle);
}

void MenuScene::onEnter()
{
	Layer::onEnter();

	//CCLOG("MenuScene onEnter");
	//CCLOG("%s", UserDefault::getInstance()->getXMLFilePath().c_str());
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
		CCLOG("menuitem create failed!");
		return nullptr;
	}
	menuitem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage));
	menuitem->setCallback(callback);
	return menuitem;
}
