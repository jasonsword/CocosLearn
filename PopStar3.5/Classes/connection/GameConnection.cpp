#include "GameConnection.h"
#include "RequestData.h"
#include "Register.pb.h"

USING_NS_CC;

static GameConnection* _gameConnect = nullptr;

const std::string serverAddr = "192.168.3.3";
//const std::string serverAddr = "echo.websocket.org";

const int serverPort = 9029;
//const int serverPort = 80;

#pragma execution_character_set("utf-8")

GameConnection::GameConnection()
	:_odsocket(nullptr),
	_online(false),
	_threadhandle(nullptr)
{
	
}

GameConnection* GameConnection::getInstance()
{
	if (_gameConnect == nullptr)
	{
		_gameConnect = new GameConnection();
	}
	return _gameConnect;
}

GameConnection::~GameConnection()
{
	CC_SAFE_DELETE(_gameConnect);

	if (_odsocket)
	{
		_online = false;
		_odsocket->Close();
		CC_SAFE_DELETE(_odsocket);
		CC_SAFE_DELETE(_threadhandle);
	}
}

void GameConnection::connect()
{
	if (_odsocket)
	{
		CCLOG("do not connect again!");
		return;
	}

	_odsocket = new ODSocket();
	_odsocket->Init();

	bool isok = _odsocket->Create(AF_INET, SOCK_STREAM, 0);
	if (!isok)
	{
		CCLOG("socket create failed!");
		CC_SAFE_DELETE(_odsocket);
		return;
	}

	_online = _odsocket->Connect(serverAddr.c_str(), serverPort);
	if (_online)
	{
		CCLOG("conect succeed, recvProc started");
		_threadhandle = new std::thread(GameConnection::ResponseProc);
		//_threadhandle->detach();
	}
	else
	{
		CCLOG("conect failed");
		CC_SAFE_DELETE(_odsocket);
	}
}

void GameConnection::sendData(const std::string& data)
{
	//check that the socket is != nullptr before sending or emitting events
	//the client should be nullptr either before initialization and connection or after disconnect
	if (_odsocket)
	{
		_odsocket->Send(data.c_str(), data.length());
	}
}

void GameConnection::sendData(const char* data, int length)
{
	if (_odsocket)
	{
		_odsocket->Send(data, length, 0);
	}
}

void GameConnection::ResponseProc()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		if (!GameConnection::getInstance()->getConnectionState())
		{
			break;
		}
		GameConnection::getInstance()->recvMsg();
	}
	CCLOG("thread ended");	
}

void GameConnection::sleepNS(int nanosec)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(nanosec));
}

bool GameConnection::newMsgCome()
{
	if (_odsocket)
	{
		if (_odsocket->Select() == -2)
		{
			return true;
		}
		else
		{
			CCLOG("error happened,error code: %d", _odsocket->GetError());
		}
	}
	return false;
}

void GameConnection::recvMsg()
{
	if (!newMsgCome())
	{
		return;
	}

	const int headLen = sizeof(MessageHead);
	char recvBuf[headLen];// 获取请求头的 数据

	if (headLen != _odsocket->Recv(recvBuf, headLen, 0))
	{
		CCLOG("recv head failed");
		return;
	}
	int code = *(int*)&recvBuf[0];
	code = ByteReorder(code);
	int len = *(int*)&recvBuf[4];
	len = ByteReorder(len);
	
	if (len <= headLen)
	{
		CCLOG("total len %d headLen %d", len, headLen);
		return;
	}

	int msgLen = len - headLen;
	CCLOG("msgLen %d", msgLen);
	char* msgBody = new char[msgLen + 1];
	memset(msgBody, 0, msgLen + 1);
	if (msgLen != _odsocket->Recv(msgBody, msgLen, 0))
	{
		CCLOG("recv msgbody failed");
		return;
	}

	std::stringstream ss;
	ss << msgBody;

	MessageBase_Opcode opcode = (MessageBase_Opcode)code;
	switch (opcode)
	{
	case MessageBase_Opcode_UNKNOWN:
		break;
	case MessageBase_Opcode_REGISTER:
		CCLOG("服务器返回消息：%s", ss.str().c_str());
		CCLOG("register back msg received!");
		break;
	case MessageBase_Opcode_LOGIN:
		break;
	case MessageBase_Opcode_LOGOUT:
		break;
	default:
		break;
	}
}

