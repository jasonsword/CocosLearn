#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onEnter();

	void CreateBgParticle(cocos2d::Vec2 &position, const std::string &particleName);

	//加const限定才能传参引用
	static cocos2d::MenuItemImage* CreateMenuItem(const std::string& normalImage, const cocos2d::ccMenuCallback& callback);

	void exitMenuItem(cocos2d::Ref* pSender);
	void resumeMenuItem(cocos2d::Ref* pSender);
	void newMenuItem(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(MenuScene);

};

#endif // __MENU_SCENE_H__
