#include "TopMenu.h"
#include "BackToMenu.h"
#include "GameData.h"

USING_NS_CC;

static std::string SMALL_NUM_FONT = "fonts/s_number_member_small.fnt";
static std::string TITLE_FONT     = "fonts/titleinfo.fnt";

// on "init" you need to initialize your instance
bool TopMenu::init()
{
	if (!Layer::init())
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createOne(HORIZONTAL, Vec2(140, visibleSize.height - 30),  "a", "ui3.png", "2000",  "bestScore", 15, 2.0f);
	createOne(HORIZONTAL, Vec2(80,  visibleSize.height - 100), "b", "ui2.png", "1",     "stage",     20);
	createOne(HORIZONTAL, Vec2(400, visibleSize.height - 100), "c", "ui2.png", "34900", "target",    20, 1.2f);
	createOne(VERTICAL,   Vec2(360, visibleSize.height - 250), "d", "ui1.png", "200",   "score",     40, 2.0f);

	auto backtomenu = Sprite::createWithSpriteFrameName("pause.png");
	backtomenu->setPosition(visibleSize.width - backtomenu->getContentSize().width, visibleSize.height - backtomenu->getContentSize().height);
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch *t, Event *e){
		if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
		{
			//CCLOG("back to menu creat!");
			this->getParent()->addChild(BackToMenu::getInstance(), 10);//优先级设置成10，以保证能吞并层下的事件
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, backtomenu);
	this->addChild(backtomenu);

	schedule(schedule_selector(TopMenu::updateGameData), 0.5);

    return true;
}

void TopMenu::createOne(TM_ORIENTTATION tm, 
	Vec2 &titlePosition,
	const std::string &titleName, 
	const std::string &backgroundFile, 
	const std::string &numberDefault, 
	const std::string &nodeName, 
	float bgOffsetY,
	float scaleX)
{
	auto title = Label::createWithBMFont(TITLE_FONT, titleName);
	title->setPosition(titlePosition);
	this->addChild(title);

	auto background = Sprite::createWithSpriteFrameName(backgroundFile);
	background->setScaleX(scaleX);
	background->setContentSize(Size(background->getContentSize().width * scaleX, background->getContentSize().height));
	if (tm == HORIZONTAL)
	{
		background->setPosition(title->getPositionX() + title->getContentSize().width / 2 + background->getContentSize().width / 2 * scaleX + 20, 
			title->getPositionY() - bgOffsetY);
	}
	else
	{
		background->setPosition(title->getPositionX() + background->getContentSize().width / 2 * (scaleX - 1.0f),
			title->getPositionY() - title->getContentSize().height / 2 - background->getContentSize().height - bgOffsetY);
	}
	this->addChild(background);

	auto number = Label::createWithBMFont(SMALL_NUM_FONT, numberDefault);
	number->setName(nodeName);
	number->setPosition(background->getPositionX() - background->getContentSize().width / 2 * (scaleX - 1.0f), 
		background->getPositionY() + 10);
	this->addChild(number);
}

void TopMenu::updateGameData(float delta)
{
	Label* bestScore = (Label *)this->getChildByName("bestScore");
	bestScore->setString(cocos2d::String::createWithFormat("%d", GameData::getInstance()->getBestScore())->_string);

	Label* score = (Label *)this->getChildByName("score");
	score->setString(cocos2d::String::createWithFormat("%d", GameData::getInstance()->getScore())->_string);

	Label* target = (Label *)this->getChildByName("target");
	target->setString(cocos2d::String::createWithFormat("%d", GameData::getInstance()->getTarget())->_string);

	Label* stage = (Label *)this->getChildByName("stage");
	stage->setString(cocos2d::String::createWithFormat("%d", GameData::getInstance()->getStage())->_string);
}

