#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"


class GameScene : public cocos2d::Layer
{
public:
	void TongGuan();

public:
	static cocos2d::Scene* createScene();

    virtual bool init();
	void onEnter();
	
	void createGameByStage(int stage);
	void save();

	void floatWords(const std::string &text, float time = 1.0f, cocos2d::CallFunc* callfunc = nullptr);
	void floatGameOver(cocos2d::CallFunc* callfunc = nullptr);


	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
