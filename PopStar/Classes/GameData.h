#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "cocos2d.h"

class GameData
{
public:
	static GameData* getInstance();
	virtual ~GameData();

protected:
	GameData();

public:
	void newGame();
	void lastGame();
	void loadHistory();
	void save();
	
};

#endif // __GAME_DATA_H__
