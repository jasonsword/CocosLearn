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

	virtual void update(float delta);

	virtual void onEnter();

	int selectedCount;
	void genSelectedStar();
	Star* getFirstSelectedStar();
	void findOtherSelectedStar(Star* original);
	void findOneDirection(Star::StarColor color, int x, int y);
	void deleteSelectedStar();
	void updateLeftStarPosition();

	CREATE_FUNC(StarMatrix);

private:
	void createMatrix();

private:
	Star* _star[ROW_NUM][COL_NUM];
	

};

#endif // __STAR_MATRIX_H__
