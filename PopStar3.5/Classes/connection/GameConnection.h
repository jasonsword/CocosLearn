#ifndef __GAME_CONNECTION_H__
#define __GAME_CONNECTION_H__

#include "cocos2d.h"
#include <thread>
#include "ODSocket.h"

class GameConnection
{
public:
	static GameConnection* getInstance();
	virtual ~GameConnection();

	void connect();
	void sendData(const std::string& data);
	void sendData(const char* data, int length);

private:
	inline bool getConnectionState(){ return _online; }

	static void ResponseProc();//接收消息线程
	void sleepNS(int nanosec);
	bool newMsgCome();
	void recvMsg();

protected:
	GameConnection();

private:
	ODSocket* _odsocket;
	std::thread* _threadhandle;
	bool _online;
};

#endif // __GAME_CONNECTION_H__
