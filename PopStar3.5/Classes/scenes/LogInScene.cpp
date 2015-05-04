#include "LogInScene.h"
#include <regex>
#include "connection/GameConnection.h"
#include "connection/WebSocketConnection.h"
#include "connection/Register.pb.h"

USING_NS_CC;

#pragma execution_character_set("utf-8")

Scene* LogInScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogInScene::create();
	layer->setName("login");

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LogInScene::init()
{
	if (!Layer::init())
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto rootNode = CSLoader::createNode("LogIn.csb");
	addChild(rootNode);

	auto signin = dynamic_cast<ui::Button*>(rootNode->getChildByName("signin"));
	signin->addClickEventListener(CC_CALLBACK_1(LogInScene::SignInBtnClick, this));


	_account = dynamic_cast<ui::TextField*>(rootNode->getChildByName("account"));
	_account->setTextVerticalAlignment(TextVAlignment::CENTER);
	_password = dynamic_cast<ui::TextField*>(rootNode->getChildByName("password"));
	_password->setTextVerticalAlignment(TextVAlignment::CENTER);
	_errorInfo = dynamic_cast<ui::Text*>(rootNode->getChildByName("error"));
	//updateErrorInfo("register success");
	//_errorInfo->setVisible(false);
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event *e){
		auto imeNode = dynamic_cast<TextField*>(e->getCurrentTarget());
		if (imeNode && imeNode->getBoundingBox().containsPoint(t->getLocation()))
		{
			CCLOG("oh you touched me !");
			imeNode->setDetachWithIME(true);
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, account);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), password);*/

	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* t, Event *e){
		CCLOG("oh you touched me !");
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

    return true;
}

void LogInScene::SignInBtnClick(cocos2d::Ref* pSender)
{
	//GameConnection::getInstance()->connect();
	//GameConnection::getInstance()->sendData("hello");
	//WebSocketConnection::getInstance()->connect();
	//WebSocketConnection::getInstance()->sendData("hello");
	//GameConnection::getInstance()->sendData(MessageBase_Opcode_REGISTER, "中英文混合测试消息！at last you did it!!!");
	//return;

	//检查参数
	/*std::string strAccount = _account->getString();
	std::string strPassword = _password->getString();
	
	if (!is_email_valid(strAccount))
	{
		CCLOG("account invalid : %s", strAccount.c_str());
		return;
	}
	if (!is_password_valid(strPassword))
	{
		CCLOG("password invalid : %s", strPassword.c_str());
		return;
	}*/
	auto reg = new RegisterMsg();
	reg->mutable_msgbase()->set_majorversion(0);
	reg->mutable_msgbase()->set_minurversion(0);
	reg->mutable_msgbase()->set_buildversion(1);
	reg->mutable_msgbase()->set_code(MessageBase_Opcode::MessageBase_Opcode_REGISTER);

	reg->set_account("test123@163.com");
	reg->set_password("123456");
	reg->set_telephone("13355556666");
	reg->set_name("张三");
	reg->set_sex(0);
	reg->set_age(12);
	reg->set_idcard("500111444777888555");

	GameConnection::getInstance()->sendData(reg->mutable_msgbase()->code(), reg->SerializeAsString());

}

bool LogInScene::is_password_valid(const std::string& strPassword)
{
	if (strPassword.length() > 20)
	{
		return false;
	}
	const std::string passwordReg = "^[a - zA - Z0 - 9]+$";
	return StringVerification(strPassword, passwordReg);
}

bool LogInScene::is_email_valid(const std::string& email)
{
	const std::string emailReg = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
	return StringVerification(email, emailReg);
}

bool LogInScene::StringVerification(const std::string& src, const std::string& regular)
{
	std::regex pattern(regular.c_str());
	if (!std::regex_match(src, pattern))
	{
		return false;
	}
	return true;
}

void LogInScene::onEnter()
{
	Layer::onEnter();
	GameConnection::getInstance()->connect();
}

void LogInScene::updateErrorInfo(const std::string& info)
{
	_errorInfo->setString(info);
	auto seq = Sequence::create(
		FadeIn::create(0.5f),
		DelayTime::create(0.5f),
		Blink::create(2.0f, 4),
		DelayTime::create(2.0f),
		FadeOut::create(0.5f),
		nullptr
	);
	_errorInfo->runAction(seq);
}



