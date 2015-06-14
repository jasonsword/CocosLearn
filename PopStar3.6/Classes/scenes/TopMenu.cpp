#include "TopMenu.h"
#include "BackToMenu.h"
#include "GameData.h"
#include "ui/UITextBMFont.h"
#include "LSlog.h"

USING_NS_CC;

using namespace ui;

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

	rootNode = CSLoader::createNode("TopMenu.csb");
	//rootNode->setAnchorPoint(Vec2(0.5f, 0.5f));
	rootNode->setPosition(Vec2(0, visibleSize.height - rootNode->getContentSize().height));
	addChild(rootNode);

	auto backtomenu = rootNode->getChildByName("backToMenu");
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t, Event *e){

		Rect rect = e->getCurrentTarget()->getBoundingBox();
		Vec2 pos = t->getLocation();

		Vec2 pos2 = rootNode->convertToNodeSpace(pos);

		LOG_DEBUG("rect x=%f y=%f width=%f height=%f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
		LOG_DEBUG("x=%f y=%f", pos2.x, pos2.y);

		if (rect.containsPoint(pos2))
		{
			LOG_DEBUG("back to menu creat!");
			this->getParent()->addChild(BackToMenu::create(), 10);//优先级设置成10，以保证能吞并层下的事件
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, backtomenu);

	updateGameData();
	schedule(schedule_selector(TopMenu::updateGameData), 0.5f);

    return true;
}

void TopMenu::updateGameData(float delta)
{
	updateOne("bestScore", GameData::getInstance()->getBestScore());
	updateOne("score", GameData::getInstance()->getScore());
	updateOne("target", GameData::getInstance()->getTarget());
	updateOne("stage", GameData::getInstance()->getStage());
}

void TopMenu::updateOne(const std::string& name, const int& number)
{
	TextBMFont* text = dynamic_cast<TextBMFont *>(rootNode->getChildByName(name));
	if (text)
	{
		text->setString(String::createWithFormat("%d", number)->_string);
	}
}

