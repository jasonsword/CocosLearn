#ifndef __TOP_MENU_H__
#define __TOP_MENU_H__

#include "cocos2d.h"

enum TM_ORIENTTATION
{
	HORIZONTAL,
	VERTICAL
};


class TopMenu : public cocos2d::Layer
{
public:

    virtual bool init();

	//tm 方向是水平还是垂直
	//titlePosition title的起始位置
	//bgOffsetY 背景的垂直偏移
	void createOne(TM_ORIENTTATION tm,
		cocos2d::Vec2 &titlePosition,
		const std::string &titleName, 
		const std::string &backgroundFile,
		const std::string &numberDefault,
		const std::string &nodeName, 
		float bgOffsetY = 0.0f,
		float scaleX = 1.0f);

	CREATE_FUNC(TopMenu);
};

#endif // __TOP_MENU_H__
