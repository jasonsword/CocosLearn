#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

    virtual bool init();

	void CreateBgParticle(cocos2d::Vec2 &position, const std::string &particleName);

    // implement the "static create()" method manually
	CREATE_FUNC(MenuScene);

protected:

private:

};

#endif // __MENU_SCENE_H__
