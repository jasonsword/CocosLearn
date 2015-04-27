#ifndef __REQUEST_DATA_H__
#define __REQUEST_DATA_H__

#include "cocos2d.h"
#include "MessageBase.pb.h"

#define ByteReorder(value) ((((value) & 0x000000ff) << 24) | (((value) & 0x0000ff00) << 8) | (((value) & 0x00ff0000) >> 8) |  (((value) & 0xff000000) >> 24))

typedef struct{
	int opcode;
	int len;
} MessageHead;

class RequestData
{
public:
	RequestData(void);
	~RequestData(void);

	void setRequestMessage(const std::string& message);
	void setMessageHead(MessageBase_Opcode code);
	void sendMessage();

private:
	MessageHead msgHead;
	std::string strMsg;
};

#endif // __REQUEST_DATA_H__
