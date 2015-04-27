#ifndef __WEB_SOCKET_CONNECTION_H__
#define __WEB_SOCKET_CONNECTION_H__

#include "cocos2d.h"

class WebSocketConnection : public cocos2d::network::WebSocket::Delegate
{
public:
	static WebSocketConnection* getInstance();
	virtual ~WebSocketConnection();

	void connect();
	void sendData(const std::string& data);
	void disconnect();

	virtual void onOpen(cocos2d::network::WebSocket* ws);
	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
	virtual void onClose(cocos2d::network::WebSocket* ws);
	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

protected:
	WebSocketConnection();

private:
	cocos2d::network::WebSocket *_wsClient;
};

#endif // __WEB_SOCKET_CONNECTION_H__
