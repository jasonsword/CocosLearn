#ifndef __STAR_MATRIX_H__
#define __STAR_MATRIX_H__

#include "cocos2d.h"
#include "Star.h"

#define COL_NUM    10
#define ROW_NUM    10

class StarMatrix : public cocos2d::Layer
{
public:
	virtual bool init();
	virtual void onEnter();

	void consumeSelectedStar(Star* original);
	void findOtherSelectedStar(Star* original);
	void findOneDirection(Star* original, int x, int y);
	void deleteSelectedStar();
	void updateLeftStarPosition();

	void updateScore();

	void updateCheck(float delta = 0);
	bool checkEnded();
	bool checkOne(int x, int y);
	int getLeftCount();

	CREATE_FUNC(StarMatrix);

private:
	void createMatrix();

private:
	Star* _star[ROW_NUM][COL_NUM];
	int selectedCount;   //已选择的星星数量
	

};

#endif // __STAR_MATRIX_H__
