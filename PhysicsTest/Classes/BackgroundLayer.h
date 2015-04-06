#ifndef BackgroundLayer_H
#define BackgroundLayer_H
#include "cocos2d.h"
USING_NS_CC;
class BackgroundLayer : public Layer
{
public:
    CREATE_FUNC(BackgroundLayer);
    virtual bool init();
	virtual void onEnter();

	void addEdges();

private:
    Sprite* m_bg1;
    Sprite* m_bg2;
    Sprite* createBorder(Point pos);
};
#endif