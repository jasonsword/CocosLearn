#include "MenuScene.h"
#include "GameScene.h"

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

	//加特效
	CreateBgParticle(Vec2(visibleSize.width * 3 / 4, visibleSize.height * 3 / 4 + 50), "leaf_open");
	CreateBgParticle(Vec2(visibleSize.width * 2 / 4, visibleSize.height * 3 / 4), "quanquan");

	//Pop背景
	auto backgroundPop = Sprite::createWithSpriteFrameName("pop.png");
	backgroundPop->setPosition(visibleSize.width / 3, visibleSize.height * 3 / 4 + 100);
	this->addChild(backgroundPop);

	//Star背景
	auto backgroundStar = Sprite::createWithSpriteFrameName("star.png");
	backgroundStar->setPosition(visibleSize.width * 2 / 3, visibleSize.height * 3 / 4 - 100);
	this->addChild(backgroundStar);

	//开始游戏
	auto startBtn = MenuItemImage::create("", "", [](Ref* pSender){
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	startBtn->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("newgame.png"));

	//继续上次的
	auto resumeBtn = MenuItemImage::create("", "", [](Ref* pSender){
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	resumeBtn->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("resume.png"));

	//排行
	auto rateBtn = MenuItemImage::create("", "", [](Ref* pSender){
		Director::getInstance()->replaceScene(GameScene::createScene());
	});
	rateBtn->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("rate.png"));

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
