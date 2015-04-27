#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "cocos2d.h"
#include "StarMatrix.h"

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
	

	void setScore(int score);
	inline int getScore() { return _score; }

	inline int getBestScore() { return _bestScore; }

	inline int getStage() { return _stage; }

	inline int getTarget() { return getTargetByStage(_stage); }

	inline bool getTongGuanState() { return (_score >= getTargetByStage(_stage)); };

	inline void TongGuan() { _stage++; _type = PlayType::NEW; }

	inline void setPlayType(PlayType type) { _type = type; }
	inline PlayType getPlayType() { return _type; }

	void setStarInfo(int x, int y, bool bExists, Star::StarColor color = Star::StarColor::RED);
	bool getStar(int x, int y);
	Star::StarColor getStarColor(int x, int y);

	void reset();

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
