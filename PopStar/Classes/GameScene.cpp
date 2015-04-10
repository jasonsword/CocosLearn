#include "GameScene.h"
#include "TopMenu.h"
#include "StarMatrix.h"
#include "GameData.h"
#include "BackToMenu.h"
#include "GameResource.h"

USING_NS_CC;

#pragma execution_character_set("utf-8")

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

    return true;
}

void GameScene::TongGuan()
{
	if (!GameData::getInstance()->getTongGuanState())
	{
		auto callfunc = CallFunc::create([this](){
			this->addChild(BackToMenu::create(), 11);
		});
		
		GameAudio::getInstance()->PlayGameOver();
		this->floatGameOver(callfunc);
		CCLOG("you died!");
		return;
	}
	CCLOG("congratulations ! you passed stage %d", GameData::getInstance()->getStage());

	//关数加1
	GameData::getInstance()->TongGuan();
	
	auto callfunc = CallFunc::create([=](){
		//创建新游戏
		this->createGameByStage(GameData::getInstance()->getStage());
	});

	GameAudio::getInstance()->PlayWin();
	floatWords("恭喜通关！", 1.0f, callfunc);
}

void GameScene::onEnter()
{
	Layer::onEnter();

	createGameByStage(GameData::getInstance()->getStage());
}

void GameScene::createGameByStage(int stage)
{
	if (stage > 1)
	{
		//移除旧的层
		auto oldmatrix = this->getChildByName(String::createWithFormat("stage%d", stage - 1)->_string);
		removeChild(oldmatrix);
	}

	auto callfunc = CallFunc::create([=](){
		//创建新游戏
		auto matrix = StarMatrix::create();
		matrix->setName(String::createWithFormat("stage%d", stage)->_string);
		this->addChild(matrix);
	});

	floatWords(String::createWithFormat("第%d关", GameData::getInstance()->getStage())->_string, 1.0f, callfunc);
}

void GameScene::floatWords(const std::string &text, float time, cocos2d::CallFunc* callfunc)
{
	//浮动特效，显示关卡
	auto words = Label::createWithTTF("fonts/arial.ttf", text);
	words->setSystemFontSize(100);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	int posY = visibleSize.height / 2 + 200;
	words->setPosition(-words->getContentSize().width / 2, posY);
	this->addChild(words);

	auto moveToMiddle = MoveTo::create(0.5f, Vec2(visibleSize.width / 2, posY));
	auto moveToEdge = MoveTo::create(0.5f, Vec2(visibleSize.width + words->getContentSize().width / 2, posY));
	auto removeSelf = CallFunc::create([words](){
		words->removeFromParent();
	});

	words->runAction(
		Sequence::create(
			moveToMiddle, DelayTime::create(0.5f + time),//移到中间并显示1s
			moveToEdge, DelayTime::create(0.5f),//移到边界之外
			callfunc,//执行回调
			removeSelf,//移除自己
			nullptr
		)
	);
}

void GameScene::floatGameOver(cocos2d::CallFunc* callfunc /*= nullptr*/)
{
	auto words = Label::createWithTTF("fonts/arial.ttf", "Game Over");
	words->setSystemFontSize(100);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	words->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
	this->addChild(words);

	auto moveToMiddle = MoveTo::create(0.5f, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	auto removeSelf = CallFunc::create([words](){
		words->removeFromParent();
	});

	words->runAction(
		Sequence::create(
			moveToMiddle, DelayTime::create(2.0f),//移到中间并显示1s
			callfunc,//执行回调
			removeSelf,//移除自己
			nullptr
		)
	);
}

