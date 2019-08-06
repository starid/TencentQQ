#include "StdAfx.h"
#include "CodecWarpper.h"
#include "../UtilLib/ByteBuffer.h"
#include "UniPacket.h"



CCodecWarpper::CCodecWarpper(void)
{
}


CCodecWarpper::~CCodecWarpper(void)
{
}

void CCodecWarpper::encodeRequest()
{
	FixAppid();

	//CreatePhSigLcIdCheckPacket

	//mSSOData.init();

	//mSSOData.serialize("");
}

void CCodecWarpper::FixAppid(void)
{
}

void CCodecWarpper::onReceData(ByteBuffer &b)
{
	ParseRecvData(b);
}

void CCodecWarpper::ParseRecvData(ByteBuffer &mBuffer)
{
	if(mBuffer.size()-mBuffer.rpos()<3)
		return;
	int len=mBuffer.reverse(mBuffer.read<int>());
	if(len>0x100000||len<0x21)
		return;
	mSSOData.deSerialize(mBuffer,true);

	//判断某个数据是否为0
	//判断条件ParsePhSigCheck或者ParseOtherResp(OnResponse函数)处理
	ParsePhSigCheck(mBuffer);
}

void CCodecWarpper::ParsePhSigCheck(ByteBuffer &mBuffer)
{
	readString(mBuffer);
	UniPacket mUniPacket;
	mUniPacket.decode((char*)mBuffer.contents(),mBuffer.size()-mBuffer.rpos());
}

void CCodecWarpper::ParseOtherResp(ByteBuffer &mBuffer)
{
	//onResponse()
}

std::string CCodecWarpper::readString(ByteBuffer &mBuffer)
{
	int len=mBuffer.reverse(mBuffer.read<int>());
	if(mBuffer.size()-mBuffer.rpos()<len-4||len-4==0)
		return "";
	unsigned char *dst=(unsigned char*)malloc(len-4);
	mBuffer.read(dst,len-4);
	std::string str;
	str.append((char*)dst,len-4);
	free(dst);
	dst=NULL;
	return str;
}