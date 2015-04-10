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

	cocos2d::Color4F getColor4F();
	void playParticleEffect();

	virtual bool init();

	CREATE_FUNC(Star);

	inline StarColor getStarColor() const { return _starcolor; }
	inline void setStarColor(StarColor color) { _starcolor = color; }

	inline bool getStatus() const { return _selected; }
	inline void setStatus(bool selected) { _selected = selected; }

	inline void setX(int x) { _x = x; }
	inline int getX() const { return _x; }

	inline void setY(int y) { _y = y; }
	inline int getY() const { return _y; }

	inline void setXY(int x, int y) { _x = x; _y = y; }
	
	inline void setXOffset(int xoffset) { _xoffset = xoffset; }
	inline int getXOffset() const { return _xoffset; }
	
	inline void setYOffset(int yoffset) { _yoffset = yoffset; }
	inline int getYOffset() const { return _yoffset; }

	inline void setXYOffset(int xoffset, int yoffset) { _xoffset = xoffset; _yoffset = yoffset; }

	inline void setBoomDelay(float boomdelay) { _boomdelay = boomdelay; }
	inline float getBoomDelay() const { return _boomdelay; }
	

private:
	bool _selected;	//是否被选中
	StarColor _starcolor;
	int _x;
	int _y;
	int _xoffset;
	int _yoffset;
	float _boomdelay;//销毁的延时
};

#endif // __STAR_H__
