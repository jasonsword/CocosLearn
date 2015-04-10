#ifndef __GAME_RESOURCE_H__
#define __GAME_RESOURCE_H__

#include "cocos2d.h"

class GameResource
{
public:
	static void Load();
};

class GameAudio
{
public:

	static GameAudio* getInstance();

	~GameAudio();

	void PreLoad();

	void PlayWin();
	void PlayClick();
	void PlaySelect();
	void PlayGameOver();
	void PlayStageClear();
	void PlayBoom();
	void PlayFire();

protected:
	GameAudio();

};

#endif // __GAME_RESOURCE_H__
