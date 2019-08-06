#include "StdAfx.h"
#include "RequestPacket.h"
#include"../JceProtocol/JCEType.h"


RequestPacket::RequestPacket(void)
{
}

RequestPacket::RequestPacket(short paramShort, char paramByte, int paramInt1, int paramInt2, std::string paramString1, 
	std::string paramString2, char *paramArrayOfByte, int paramInt3, std::map<std::string, std::string> paramMap1, 
	std::map<std::string, std::string> paramMap2)
{
    //iVersion = paramShort;
    //cPacketType = paramByte;
    //iMessageType = paramInt1;
    //iRequestId = paramInt2;
    //sServantName = paramString1;
    //sFuncName = paramString2;
    //sBuffer = paramArrayOfByte;
    //iTimeout = paramInt3;
    //context = paramMap1;
    //status = paramMap2;
}

RequestPacket::~RequestPacket(void)
{
}


void RequestPacket::readFrom(CJceInputStream &paramJceInputStream)
{
	paramJceInputStream.read(&iVersion,1,true);
	paramJceInputStream.read(&cPacketType,2,true);
	paramJceInputStream.read(&iMessageType,3,true);
	paramJceInputStream.read(&iRequestId,4,true);
	paramJceInputStream.read(&sServantName,5,true);
	paramJceInputStream.read(&sFuncName,6,true);
	paramJceInputStream.read(&sBuffer,7,true);
	paramJceInputStream.read(&iTimeout,8,true);
	paramJceInputStream.read(&context,9,true);
	paramJceInputStream.read(&status,10,true);
}
void RequestPacket::writeTo(CJceOutputStream &paramJceOutputStream)
{
	paramJceOutputStream.write(&iVersion,1);
	paramJceOutputStream.write(&cPacketType,2);
	paramJceOutputStream.write(&iMessageType,3);
	paramJceOutputStream.write(&iRequestId,4);
	paramJceOutputStream.write(&sServantName,5);
	paramJceOutputStream.write(&sFuncName,6);
	paramJceOutputStream.write(&sBuffer,7);
	paramJceOutputStream.write(&iTimeout,8);
	paramJceOutputStream.write(&context,9);
	paramJceOutputStream.write(&status,10);
}