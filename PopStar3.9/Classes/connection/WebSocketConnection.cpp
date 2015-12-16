#include "WebSocketConnection.h"
#include "LSlog.h"

USING_NS_CC;
using namespace cocos2d::network;

static WebSocketConnection* _wsConnect = nullptr;

const std::string serverAddr = "192.168.3.3";
//const std::string serverAddr = "echo.websocket.org";

const int serverPort = 9029;
//const int serverPort = 80;

WebSocketConnection::WebSocketConnection()
	:_wsClient(nullptr)
{
	
}

WebSocketConnection* WebSocketConnection::getInstance()
{
	if (_wsConnect == nullptr)
	{
		_wsConnect = new WebSocketConnection();
	}
	return _wsConnect;
}

WebSocketConnection::~WebSocketConnection()
{
	CC_SAFE_DELETE(_wsConnect);
}

void WebSocketConnection::connect()
{
	if (_wsClient)
	{
		return;
	}
	std::stringstream strUrl;
	strUrl << "ws://" << serverAddr.c_str() << ":" << serverPort;
	_wsClient = new network::WebSocket();
	if (!_wsClient->init(*this, strUrl.str()))
	{
		CC_SAFE_DELETE(_wsClient);
		LOG_DEBUG("connect failed, please check!");
		return;
	}
}

void WebSocketConnection::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	if (!data.isBinary)
	{
		std::string textStr = std::string("response text msg: ") + data.bytes;
		LOG_DEBUG("%s", textStr.c_str());
	}
	else
	{
		std::string binaryStr = "response bin msg: ";

		for (int i = 0; i < data.len; ++i) {
			if (data.bytes[i] != '\0')
			{
				binaryStr += data.bytes[i];
			}
			else
			{
				binaryStr += "\'\\0\'";
			}
		}

		LOG_DEBUG("%s", binaryStr.c_str());
	}
}

void WebSocketConnection::onClose(cocos2d::network::WebSocket* ws)
{
	LOG_DEBUG("websocket instance (%p) closed.", ws);
	if (ws == _wsClient)
	{
		_wsClient = nullptr;
	}
	// Delete websocket instance.
	CC_SAFE_DELETE(ws);
}

void WebSocketConnection::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
	LOG_DEBUG("Error was fired, error code: %d", (int)error);
}

void WebSocketConnection::disconnect()
{
	if (_wsClient != nullptr)
	{
		_wsClient->close();
		CC_SAFE_DELETE(_wsClient);
	}
}

void WebSocketConnection::sendData(const std::string& data)
{
	if (!_wsClient)
	{
		return;
	}

	if (_wsClient->getReadyState() == network::WebSocket::State::OPEN)
	{
		LOG_DEBUG("now send data : %s", data.c_str());
		//字符串输出
		//_wsClient->send(data);
		//字节流输出
		_wsClient->send((unsigned char*)data.c_str(), data.length());
	}
	else
	{
		std::string warningStr = "send text websocket instance wasn't ready...";
		LOG_DEBUG("%s", warningStr.c_str());
	}
}

void WebSocketConnection::onOpen(cocos2d::network::WebSocket* ws)
{
	LOG_DEBUG("Websocket (%p) opened", ws);
	if (ws == _wsClient)
	{
		LOG_DEBUG("Send Text WS was opened.");
	}
	else
	{
		LOG_ERROR("error test will never go here.");
	}
}
