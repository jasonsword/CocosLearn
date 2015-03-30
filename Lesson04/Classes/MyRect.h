#ifndef __MYRECT_H__
#define __MYRECT_H__

#include "cocos2d.h"

class MyRect : public cocos2d::Node
{
public:
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MyRect);
};

#endif // __MYRECT_H__
