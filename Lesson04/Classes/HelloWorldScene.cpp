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
    
    label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	sprite->setName("back");
	auto test = this->getChildByName("back");

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	scheduleUpdate();//执行Node专用的update函数，每帧调用一次

	scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::update2), 0);//只执行一次

	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update2), 1);//设定了周期，单位秒
	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::update3), 1, 2, 0);//设定了周期，次数，以及延时多久开始执行
	//schedule([](float f){
	//	CCLOG("labmda functions 444 - %f", f);
	//}, "UPDATE4");//每绘制一帧就调用一次，相当夸张
	
	schedule([](float f){
		CCLOG("labmda functions 555 - %f", f);
	}, 1, "UPDATE5");//设定了周期，单位秒
	
	schedule([](float f){
		CCLOG("labmda functions 666 - %f", f);
	}, 1, CC_REPEAT_FOREVER, 0, "UPDATE6");//设定了周期，次数，以及延时多久开始执行

	scheduleOnce([](float f){
		CCLOG("labmda functions 777 - %f", f);
	}, 0, "UPDATE7");//只执行一次



    return true;
}

void HelloWorld::update(float delta)
{
	if (label->getPositionY() < label->getBoundingBox().size.height)
	{
		UserDefault::getInstance()->setStringForKey("data", "zwmeteor");//用户首选项数据保存读取
		CCLOG("%s", UserDefault::getInstance()->getStringForKey("data", "this").c_str());

		auto fu = FileUtils::getInstance();
		CCLOG("%s", fu->getWritablePath().c_str());



		FILE *f = fopen(fu->fullPathFromRelativeFile("data.txt", fu->getWritablePath()).c_str(), "w");
		fprintf(f, "this is a test");
		fclose(f);

		auto data = fu->getDataFromFile(fu->fullPathFromRelativeFile("data.txt", fu->getWritablePath()));
		CCLOG("%s", data.getBytes());


		CCLOG("down!");
		unscheduleUpdate();
		unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::update2));
		unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::update3));
		unschedule("UPDATE4");
		unschedule("UPDATE5");
		unschedule("UPDATE6");
		unscheduleAllCallbacks();
	}
	//CCLOG("%f", delta);
	label->setPosition(label->getPosition() + Vec2(0, -1));
}

void HelloWorld::update2(float delta)
{
	CCLOG("update2");
}

void HelloWorld::update3(float delta)
{
	CCLOG("update3");
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


