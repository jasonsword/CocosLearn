#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    return true;
}
Sprite* BackgroundLayer::createBorder(Point pos)
{
    auto border = Sprite::create("border.png");

	auto body = PhysicsBody::createBox(border->getContentSize());
    body->setDynamic(false);
    body->setCategoryBitmask(1);    // 0001
    body->setCollisionBitmask(1);   // 0001
    body->setContactTestBitmask(1); // 0001
    border->setPhysicsBody(body);

    border->setPosition(pos);
    return border;
}

void BackgroundLayer::onEnter()
{
	Layer::onEnter();

	//addEdges();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 背景图片 */
	m_bg1 = Sprite::create("background.jpg");
	m_bg1->setPosition(Point(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
	this->addChild(m_bg1);

	m_bg2 = Sprite::create("background.jpg");
	m_bg2->setPosition(Point(visibleSize.width * 0.5f, -visibleSize.height * 0.5f));
	this->addChild(m_bg2);

	/* 创建边缘锯齿 */
	auto border = Sprite::create("border.png");
	Size borderSize = border->getContentSize();


	auto border1 = createBorder(Point(borderSize.width * 0.5f, borderSize.height * 0.5f));
	this->addChild(border1);

	auto border2 = createBorder(Point(visibleSize.width - borderSize.width * 0.5f, borderSize.height * 0.5f));
	border2->setFlippedX(true);
	this->addChild(border2);

	auto border3 = Sprite::create("border.png");
	border3->setPhysicsBody(PhysicsBody::createBox(border3->getContentSize()));
	border3->setPosition(Vec2(visibleSize.width/2, borderSize.height * 0.15f));
	border3->setRotation(90.0f);
	this->addChild(border3);
}

void BackgroundLayer::addEdges()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	auto edgeShape = Node::create();
	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(edgeShape);
}
