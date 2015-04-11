#include "BackToMenu.h"
#include "GameData.h"
#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool BackToMenu::init()
{
	if (!LayerGradient::initWithColor(Color4B(0, 0, 0, 127), Color4B(255, 255, 255, 127)))
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//重新开始
	auto resumeBtn = MenuScene::CreateMenuItem("resume.png", CC_CALLBACK_1(BackToMenu::resumeMenuItem, this));

	//退出并保存
	auto saveAndExitBtn = MenuScene::CreateMenuItem("save_exit.png", CC_CALLBACK_1(BackToMenu::saveAndExitMenuItem, this));

	auto menu = Menu::create(resumeBtn, saveAndExitBtn, nullptr);
	//menu->alignItemsVertically();
	menu->alignItemsVerticallyWithPadding(30.0f);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(menu);

	//吞并屏蔽下层的点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *t, Event *e){
		//CCLOG("ping bi success");
		return true;
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void BackToMenu::resumeMenuItem(cocos2d::Ref* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->save();
	GameData::getInstance()->init(GameData::PlayType::NEW);
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void BackToMenu::saveAndExitMenuItem(cocos2d::Ref* pSender)
{
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->save();
	Director::getInstance()->replaceScene(MenuScene::createScene());
}


