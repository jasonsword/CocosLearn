#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add layer as a child to scene
    scene->addChild(layer);

	auto gradientLayer = LayerGradient::create(Color4B(255, 0, 255, 255), Color4B(0, 0, 255, 255));
	//gradientLayer->setContentSize(Size(200, 200));
	gradientLayer->setContentSize(Size(visibleSize.width / 4, visibleSize.height / 4));

	gradientLayer->ignoreAnchorPointForPosition(false);
	gradientLayer->setAnchorPoint(Point(0, 0));

	//gradientLayer->setPosition(200, 100);
	scene->addChild(gradientLayer);

	auto colocLayer = LayerColor::create(Color4B(255, 255, 0, 128), visibleSize.width / 2, visibleSize.height / 2);

	//在Cocos2d-x中Layer的Anchor Point为默认值(0, 0)，其他Node的默认值为(0.5, 0.5)。
	//因为Layer比较特殊，它默认忽略锚点，所以要调用ignoreAnchorPointForPosition()接口来改变锚点
	colocLayer->ignoreAnchorPointForPosition(false);
	colocLayer->setAnchorPoint(Point(0.5, 0.5));

	//colocLayer->setContentSize(Size(200, 200));
	//colocLayer->setPosition(100 + 250, 100);
	colocLayer->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//colocLayer->addChild(gradientLayer);

	scene->addChild(colocLayer);

	auto gradientLayer1 = LayerGradient::create(Color4B(255, 0, 255, 255), Color4B(0, 0, 255, 255));
	//gradientLayer1->setContentSize(Size(200, 200));
	gradientLayer1->setContentSize(Size(visibleSize.width / 4, visibleSize.height / 4));
	auto colocLayer1 = LayerColor::create(Color4B(255, 255, 0, 128));
	//colocLayer1->setContentSize(Size(200, 200));
	colocLayer1->setContentSize(Size(visibleSize.width / 4, visibleSize.height / 4));
	auto multiLayer = LayerMultiplex::create();
	multiLayer->addLayer(gradientLayer1);
	multiLayer->addLayer(colocLayer1);

	multiLayer->switchTo(0);//可任意切换

	//multiLayer->setContentSize(Size(200, 200));
	multiLayer->setContentSize(Size(visibleSize.width / 4, visibleSize.height / 4));
	//multiLayer->setPosition(100 + 250 + 250, 100);
	multiLayer->setPosition(Point(visibleSize.width * 3 / 4 + origin.x, origin.y));


	scene->addChild(multiLayer);

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

void HelloWorld::onEnter()
{
	Layer::onEnter();
	CCLOG("onEnter");
}

void HelloWorld::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	CCLOG("onEnterTransitionDidFinish");
}

void HelloWorld::onExit()
{
	Layer::onExit();
	CCLOG("onExit");
}

void HelloWorld::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	CCLOG("onExitTransitionDidStart");
}

void HelloWorld::cleanup()
{
	Layer::cleanup();
	CCLOG("cleanup");
}
