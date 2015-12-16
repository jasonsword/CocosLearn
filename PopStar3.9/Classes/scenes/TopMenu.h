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

	void updateGameData(float delta = 0);
	void updateOne(const std::string& name, const int& number);

	CREATE_FUNC(TopMenu);

private:
	cocos2d::Node* rootNode;
};

#endif // __TOP_MENU_H__
