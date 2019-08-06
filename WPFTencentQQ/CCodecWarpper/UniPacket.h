#pragma once
#include"RequestPacket.h"
#include"StreamOut.h"

//Ô­ÐÍÎªcom.qq.jce.wup.UniPacket
class UniPacket
{
public:
	UniPacket(void);
	UniPacket(bool);
	UniPacket(short,char,int,int,std::string,std::string,ByteBuffer,int,
		std::map<std::string,std::string>,std::map<std::string,std::string>);
	virtual ~UniPacket(void);
public:
	RequestPacket _package;
public:
	void decode(char *,int);
	void encode(CStreamOut&);
	void parseBufferV2();
	void parseBufferV3();
	void useVersion3();
};

