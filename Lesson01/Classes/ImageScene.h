#ifndef __IMAGE_SCENE_H__
#define __IMAGE_SCENE_H__

#include "cocos2d.h"

class ImageScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* getInstance();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(ImageScene);
};

#endif // __IMAGE_SCENE_H__
