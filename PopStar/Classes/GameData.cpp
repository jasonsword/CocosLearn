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

void GameData::newGame()
{

}

void GameData::lastGame()
{

}

void GameData::loadHistory()
{

}

void GameData::save()
{

}
