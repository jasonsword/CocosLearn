#include "HelloWorldScene.h"
#include "BackgroundLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto back = BackgroundLayer::create();
	scene->addChild(back);


	//auto layer = HelloWorld::create();
	//scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	return true;
}


void HelloWorld::onEnter(){
	Layer::onEnter();

	addBall(visibleSize.width / 2, visibleSize.height / 2);
	addEdges();


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *){
		this->addBall(t->getLocation());

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::addBall(cocos2d::Vec2 position){
	addBall(position.x, position.y);
}

void HelloWorld::addEdges(){

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgeShape = Node::create();
	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(edgeShape);
}


void HelloWorld::addBall(float positionX, float positionY){

	auto b = Sprite::create("border2.png");
	b->setPhysicsBody(PhysicsBody::createBox(b->getContentSize()));
	b->cocos2d::Node::setPosition(positionX, positionY);
	b->setRotation(90.0f);
	addChild(b);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
