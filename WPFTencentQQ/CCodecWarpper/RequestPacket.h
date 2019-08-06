#pragma once
#include"../JceProtocol/JCEMap.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JceStruct.h"

//Ô­ÐÍÎªcom.qq.taf.RequestPacket
class RequestPacket:public JCE::CJceStruct
{
public:
	RequestPacket(void);
	RequestPacket(short paramShort, char paramByte, int paramInt1, int paramInt2, std::string paramString1, 
	std::string paramString2, char *paramArrayOfByte, int paramInt3, std::map<std::string, std::string> paramMap1, 
	std::map<std::string, std::string> paramMap2);
	virtual ~RequestPacket(void);
public:
	JCE::JCEShort	iVersion;
	JCE::JCEChar	cPacketType;
	JCE::JCEInt		iMessageType;
	JCE::JCEInt		iRequestId;
	JCE::JCEString	sFuncName;
	JCE::JCEString	sServantName;
	JCE::JCEByteArray	sBuffer;
	JCE::JCEInt		iTimeout;
	JCE::JCEMap		context;
	JCE::JCEMap		status;
public:
	void readFrom(CJceInputStream &paramJceInputStream);
	void writeTo(CJceOutputStream &paramJceOutputStream);
};

