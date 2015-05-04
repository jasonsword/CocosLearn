#include "GameConnection.h"
#include "scenes/LogInScene.h"

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
	_socketMessageQueue = new std::list<socketMessage*>();

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
	disconnect();
	unscheduleUpdate();

	delete _socketMessageQueue;
	CC_SAFE_DELETE(_gameConnect);
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
		_threadhandle = new std::thread(&GameConnection::ResponseProc, this);
		//_threadhandle->detach();
		scheduleUpdate();
	}
	else
	{
		CCLOG("conect failed");
		CC_SAFE_DELETE(_odsocket);
	}
}

void GameConnection::sendData(const MessageBase_Opcode& code, const std::string& data)
{
	//check that the socket is != nullptr before sending or emitting events
	//the client should be nullptr either before initialization and connection or after disconnect
	if (_odsocket)
	{
		//传输的数据结构
		//操作码： int
		//总长度： int
		//数据：   std::string
		int totalLen = data.length() + 8;

		char* chsend = new char[totalLen];

		int opcode = ByteReorder(code);//连接JAVA服务器需要进行大小端转换
		int msgLen = data.length();
		msgLen = ByteReorder(msgLen);

		memcpy(chsend, (char *)&opcode, sizeof(int));
		memcpy(chsend + sizeof(int), (char *)&msgLen, sizeof(int));
		memcpy(chsend + sizeof(int) * 2, data.c_str(), data.length());

		_odsocket->Send(chsend, totalLen);
	}
}

void GameConnection::ResponseProc()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (!getConnectionState())
		{
			break;
		}
		recvMsg();
	}
	CCLOG("thread ended");	
}

void GameConnection::sleepMS(int nanosec)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(nanosec));
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

	//传输的数据结构
	//操作码： int
	//总长度： int
	//数据：   std::string
	char recvBuf[8];// 获取请求头的 数据
	int recvLen = _odsocket->Recv(recvBuf, 8, 0);
	if (8 != recvLen)
	{
		CCLOG("recv head failed");
		if (recvLen <= 0)
		{
			disconnect();
		}
		return;
	}
	int code = *(int*)&recvBuf[0];
	code = ByteReorder(code);//JAVA传过来的int数据要进行大小端的转换
	int len = *(int*)&recvBuf[4];
	len = ByteReorder(len);
	
	if (len <= 0)
	{
		CCLOG("len error %d", len);
		return;
	}

	char* msgBody = new char[len];
	recvLen = _odsocket->Recv(msgBody, len, 0);
	if (len != recvLen)
	{
		CCLOG("recv msgbody failed recvLen %d", recvLen);
		delete msgBody;
		if (recvLen <= 0)
		{
			disconnect();
		}
		return;
	}

	saveReceivedMsg((MessageBase_Opcode)code, msgBody, len);

	delete msgBody;//don't forgot it
}

void GameConnection::disconnect()
{
	if (_odsocket)
	{
		_online = false;
		_odsocket->Close();
		CC_SAFE_DELETE(_odsocket);
		CC_SAFE_DELETE(_threadhandle);
	}
}

void GameConnection::saveReceivedMsg(const MessageBase_Opcode& opcode, char* buffer, const int& len)
{
	socketMessage* msg = new (std::nothrow) socketMessage();
	msg->opcode = opcode;
	msg->buffer = new char[len];
	memcpy(msg->buffer, buffer, len);
	msg->len = len;

	std::lock_guard<std::mutex> lk(_socketMessageQueueMutex);
	_socketMessageQueue->push_back(msg);
}

void GameConnection::scheduleUpdate()
{
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

void GameConnection::update(float delta)
{
	socketMessage *msg = nullptr;

	/* Avoid locking if, in most cases, the queue is empty. This could be a little faster.
	size() is not thread-safe, it might return a strange value, but it should be OK in our scenario.
	*/
	if (0 == _socketMessageQueue->size())
		return;

	// Returns quickly if no message
	_socketMessageQueueMutex.lock();

	if (0 == _socketMessageQueue->size())
	{
		_socketMessageQueueMutex.unlock();
		return;
	}

	// Gets message
	msg = *(_socketMessageQueue->begin());
	_socketMessageQueue->pop_front();

	_socketMessageQueueMutex.unlock();

	resumeReceivedMsg(msg);

	CC_SAFE_DELETE(msg);
}

void GameConnection::unscheduleUpdate()
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void GameConnection::resumeReceivedMsg(socketMessage* msg)
{
	if (msg == nullptr)
	{
		CCLOG("null msg detected!");
		return;
	}
	switch (msg->opcode)
	{
	case MessageBase_Opcode_UNKNOWN:
		break;
	case MessageBase_Opcode_REGISTER:
	{
		std::stringstream ss;
		ss.write(msg->buffer, msg->len);
		CCLOG("服务器返回消息：%s", ss.str().c_str());
		auto loginscene = dynamic_cast<LogInScene*>(Director::getInstance()->getRunningScene()->getChildByName("login"));
		if (loginscene)
		{
			loginscene->updateErrorInfo(ss.str());
		}
		break;
	}
	case MessageBase_Opcode_LOGIN:
		break;
	case MessageBase_Opcode_LOGOUT:
		break;
	default:
		break;
	}
}

