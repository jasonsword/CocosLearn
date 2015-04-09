#include "BackToMenu.h"
#include "GameData.h"
#include "MenuScene.h"

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

	//继续刚才的
	auto resumeBtn = MenuItemImage::create("", "", [this](Ref* pSender){
		//CCLOG("go on!");
		this->getParent()->removeChild(this);
	});
	resumeBtn->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("resume.png"));

	//退出并保存
	auto saveAndExitBtn = MenuItemImage::create("", "", [](Ref* pSender){
		GameData::getInstance()->save();
		Director::getInstance()->replaceScene(MenuScene::createScene());
	});
	saveAndExitBtn->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("save_exit.png"));

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


