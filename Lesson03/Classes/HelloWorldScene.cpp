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

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *t, Event *e)
	{
		CCLOG("onTouchBegan");
		return true;//����TRUE�ᴥ��move
	};
	listener->onTouchMoved = [](Touch *t, Event *e)
	{
		CCLOG("onTouchMoved");
	};
	listener->onTouchEnded = [](Touch *t, Event *e)
	{
		CCLOG("onTouchEnded");
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, label);

	auto listener2 = EventListenerTouchAllAtOnce::create();//��㴥��
	listener2->onTouchesBegan = [](std::vector<Touch*> ts, Event *e)
	{
		CCLOG("onTouchesBegan");
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	Device::setAccelerometerEnabled(true);
	auto listener3 = EventListenerAcceleration::create([](Acceleration *a, Event *e)
	{
		CCLOG("x:%g, y:%g, z:%g, timestamp:", a->x, a->y, a->z, a->timestamp);
	});//���ٶȴ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, this);

	//����������
	auto listener4 = EventListenerKeyboard::create();
	listener4->onKeyReleased = [](EventKeyboard::KeyCode code, Event *e)
	{
		CCLOG("key code %d", code);
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_BACK:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener4, this);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
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
