#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);



    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *t, Event *e)
	{
		auto target = e->getCurrentTarget();
		if (target->getBoundingBox().containsPoint(t->getLocation()))
		{
			//target->runAction(MoveTo::create(1, Vec2(random<float>(0, visibleSize.width), random<float>(0, visibleSize.height))));
			auto action = MoveBy::create(0.1, Vec2(random<float>(0, 20) - 10, random<float>(0, 20) - 10));
			auto rotalAction = RotateBy::create(0.1, 20);
			auto repeatAction = Repeat::create(action, 3);
			auto repeatForeverAction = RepeatForever::create(action);

			static int i = 0;
			i++;
			auto sp = Spawn::create(action, rotalAction, repeatAction, nullptr);//组合，动作同时开始
			auto seq = Sequence::create(action, //序列，CallFunc可用于动作完成的后续
				rotalAction, 
				rotalAction, 
				CallFunc::create([](){
				CCLOG("done%d", i);
			}), nullptr);
			//target->runAction(action);
			//target->runAction(repeatAction);
			target->runAction(seq);
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, label);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), sprite);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
