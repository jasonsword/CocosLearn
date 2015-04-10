#include "GameData.h"

USING_NS_CC;

static GameData* _gameData = nullptr;

GameData::GameData()
{

}

GameData* GameData::getInstance()
{
	if (_gameData == nullptr)
	{
		_gameData = new GameData();
	}
	return _gameData;
}

GameData::~GameData()
{
	CC_SAFE_DELETE(_gameData);
}

void GameData::save()
{
	if (_bestScore > UserDefault::getInstance()->getIntegerForKey("bestScore", 0))
	{
		UserDefault::getInstance()->setIntegerForKey("bestScore", _bestScore);
	}
	UserDefault::getInstance()->setIntegerForKey("stage", _stage);
	UserDefault::getInstance()->setIntegerForKey("score", _score);
}

int GameData::getTargetByStage(int s)
{
	int score = 0;
	if (s == 1)
	{
		score = 1000;
	}
	else if (s == 2)
	{
		score = 3000;
	}
	else if ((s >= 3) && (s <= 10))
	{
		score = 3000 + 3000 * (s - 2);
	}
	else
	{
		score = 27000 + 4000 * (s - 10);
	}
	return score;
}

void GameData::init(PlayType type)
{
	_bestScore = UserDefault::getInstance()->getIntegerForKey("bestScore", 0);
	if (type == PlayType::NEW)
	{
		_stage = 1;
		_score = 0;
	}
	else if (type == PlayType::LAST)
	{
		_score = UserDefault::getInstance()->getIntegerForKey("score", 0);
		_stage = UserDefault::getInstance()->getIntegerForKey("stage", 1);
	}
}
