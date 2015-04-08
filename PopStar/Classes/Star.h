#ifndef __STAR_H__
#define __STAR_H__

#include "cocos2d.h"

class Star : public cocos2d::Sprite
{
public:
	enum StarColor
	{
		RED,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE
	};
	static Star* createStar();

	static std::string getImage(StarColor color);
	static StarColor generateColor();

	virtual bool init();

	CREATE_FUNC(Star);

	inline StarColor getStarColor() const { return _starcolor; }
	inline void setStarColor(StarColor color) { _starcolor = color; }

	inline bool getStatus() const { return _selected; }
	inline void setStatus(bool selected) { _selected = selected; }

	inline int getY() const { return _y; }
	inline int getX() const { return _x; }
	inline void setXY(int x, int y) { _x = x; _y = y; }
	inline void setX(int x) { _x = x; }
	inline void setY(int y) { _y = y; }

	inline int getYOffset() const { return _yoffset; }
	inline int getXOffset() const { return _xoffset; }
	inline void setXOffset(int xoffset) { _xoffset = xoffset; }
	inline void setYOffset(int yoffset) { _yoffset = yoffset; }

private:
	bool _selected;	//是否被选中
	StarColor _starcolor;
	int _x;
	int _y;
	int _xoffset;
	int _yoffset;
};

#endif // __STAR_H__
