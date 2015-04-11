#ifndef __BACK_TO_MENU_H__
#define __BACK_TO_MENU_H__

#include "cocos2d.h"

class BackToMenu : public cocos2d::LayerGradient
{
public:

    virtual bool init();

	void resumeMenuItem(cocos2d::Ref* pSender);
	void saveAndExitMenuItem(cocos2d::Ref* pSender);

	CREATE_FUNC(BackToMenu);
};

#endif // __BACK_TO_MENU_H__
