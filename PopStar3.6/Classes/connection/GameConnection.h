#ifndef __GAME_CONNECTION_H__
#define __GAME_CONNECTION_H__

#include "cocos2d.h"
#include <thread>
#include "ODSocket.h"
#include "MessageBase.pb.h"

#define ByteReorder(value) ((((value) & 0x000000ff) << 24) | (((value) & 0x0000ff00) << 8) | (((value) & 0x00ff0000) >> 8) |  (((value) & 0xff000000) >> 24))

class socketMessage
{
public:
	socketMessage() : opcode(MessageBase_Opcode::MessageBase_Opcode_UNKNOWN), buffer(nullptr), len(0){}
	MessageBase_Opcode opcode; // message type
	char* buffer;
	int len;
};

class GameConnection
{
public:
	static GameConnection* getInstance();
	virtual ~GameConnection();

	void connect();
	void disconnect();
	void sendData(const MessageBase_Opcode& code, const std::string& data);

	void scheduleUpdate();
	void unscheduleUpdate();
	virtual void update(float delta);

	inline bool getConnectionState(){ return _online; }

private:
	void ResponseProc();//接收消息线程
	void sleepMS(int nanosec);
	bool newMsgCome();
	void recvMsg();
	void saveReceivedMsg(const MessageBase_Opcode& opcode, char* buffer, const int& len);
	void resumeReceivedMsg(socketMessage* msg);

protected:
	GameConnection();

private:
	ODSocket* _odsocket;
	std::thread* _threadhandle;
	bool _online;
	std::list<socketMessage*>* _socketMessageQueue;
	std::mutex   _socketMessageQueueMutex;
};

#endif // __GAME_CONNECTION_H__
