#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"


class LogInScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onEnter();

	static bool StringVerification(const std::string& src, const std::string& regular);
	static bool is_email_valid(const std::string& email);
	static bool is_password_valid(const std::string& strPassword);

	void SignInBtnClick(cocos2d::Ref* pSender);

	void updateErrorInfo(const std::string& info);

	CREATE_FUNC(LogInScene);

private:
	cocos2d::ui::TextField* _account;
	cocos2d::ui::TextField* _password;
	cocos2d::ui::Text* _errorInfo;
};

#endif // __LOGIN_SCENE_H__
