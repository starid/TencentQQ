#include "StdAfx.h"
#include "UniPacket.h"
#include"StreamIn.h"
#include"StreamOut.h"



UniPacket::UniPacket(void)
{
	_package.iVersion.value(2);
}

UniPacket::UniPacket(bool paramBoolean)
{
	if(paramBoolean)
	{
		useVersion3();
	}else
	{
		this->_package.iVersion.value(2);
	}
}

UniPacket::UniPacket(short a,char b,int c,int d,std::string e,std::string f,ByteBuffer g,int h,std::map<std::string,std::string> i,std::map<std::string,std::string> j)
{
	_package.iVersion.value(a);
	_package.cPacketType.value(b);
	_package.iMessageType.value(c);
	_package.iRequestId.value(d);
	_package.sServantName.value(e);
	_package.sFuncName.value(f);
	_package.sBuffer.value(g);
	_package.iTimeout.value(h);
}

UniPacket::~UniPacket(void)
{
}

void UniPacket::useVersion3()
{
	this->_package.iVersion.value(2);
}

void UniPacket::parseBufferV2()
{
}
void UniPacket::parseBufferV3()
{
}

void UniPacket::decode(char *paramArrayOfByte,int size)
{
	if(size<4)
	{
		return;
	}
	CStreamIn mStream1(JCE::JCEByteArray(paramArrayOfByte+4,size-4));
	mStream1.setServerEncoding("GBK");
	_package.readFrom(mStream1);
	if(_package.iVersion.value() == 3)
	{
		parseBufferV3();
	}else
	{
		parseBufferV2();
	}
}

void UniPacket::encode(CStreamOut &mStream1)
{
	mStream1.setServerEncoding("GBK");
	_package.writeTo(mStream1);
}