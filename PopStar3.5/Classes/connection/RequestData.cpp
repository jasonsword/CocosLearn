#include "RequestData.h"
#include "GameConnection.h"

USING_NS_CC;

RequestData::RequestData(void)
	:strMsg("")
{
}

RequestData::~RequestData(void)
{
}

void RequestData::setRequestMessage(const std::string& message)
{
	strMsg = message;
	msgHead.len = sizeof(msgHead) + strMsg.length();
}

void RequestData::setMessageHead(MessageBase_Opcode code)
{
	msgHead.opcode = code;
}

void RequestData::sendMessage()
{
	char* chsend = new char[msgHead.len];

	int opcode = ByteReorder(msgHead.opcode);
	int len = ByteReorder(msgHead.len);
	
	memcpy(chsend, (char *)&opcode, sizeof(int));
	memcpy(chsend + sizeof(int), (char *)&len, sizeof(int));

	memcpy(chsend + sizeof(msgHead), strMsg.c_str(), strMsg.length());

	GameConnection::getInstance()->sendData(chsend, msgHead.len);

}

