#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "cocos2d.h"

class GameData
{
public:
	enum PlayType
	{
		NEW,
		LAST
	};

	void init(PlayType type);
	void save();

	int getTargetByStage(int s);
	

	inline void setScore(int score) { _score += score; if (_score > _bestScore){ _bestScore = _score; }}
	inline int getScore() { return _score; }
	inline int getBestScore() { return _bestScore; }
	inline int getStage() { return _stage; }
	inline int getTarget() { return getTargetByStage(_stage); }
	inline bool getTongGuanState() { return (_score >= getTargetByStage(_stage)); };
	inline void TongGuan() { _stage++; }


	static GameData* getInstance();
	virtual ~GameData();

protected:
	GameData();

private:
	PlayType _type;

	int _stage;		//关卡
	int _bestScore;	//最好成绩
	int _score;		//当前获取的总分数
};

#endif // __GAME_DATA_H__
