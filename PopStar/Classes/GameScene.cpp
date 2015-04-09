#include "GameScene.h"
#include "TopMenu.h"
#include "StarMatrix.h"
#include "GameData.h"
#include "BackToMenu.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if (!Layer::init())
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*初始化背景*/
	auto background = Sprite::create("bg_main.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background, -1);
    
	auto topmenu = TopMenu::create();
	topmenu->setName("topmenu");
	this->addChild(topmenu);

	auto matrix = StarMatrix::create();
	matrix->setName(cocos2d::String::createWithFormat("stage%d", GameData::getInstance()->getStage())->_string);
	this->addChild(matrix);

    return true;
}

void GameScene::TongGuan()
{
	if (!GameData::getInstance()->getTongGuanState())
	{
		//移除旧的层
		auto oldmatrix = this->getChildByName(cocos2d::String::createWithFormat("stage%d", GameData::getInstance()->getStage())->_string);
		oldmatrix->unscheduleAllCallbacks();

		this->addChild(BackToMenu::getInstance(), 10);

		CCLOG("you died!");
		return;
	}
	CCLOG("congratulations ! you passed stage %d", GameData::getInstance()->getStage());
	//移除旧的层
	auto oldmatrix = this->getChildByName(cocos2d::String::createWithFormat("stage%d", GameData::getInstance()->getStage())->_string);
	removeChild(oldmatrix);
	//关数加1
	GameData::getInstance()->TongGuan();
	//创建新的层
	auto matrix = StarMatrix::create();
	matrix->setName(cocos2d::String::createWithFormat("stage%d", GameData::getInstance()->getStage())->_string);
	this->addChild(matrix);
}

