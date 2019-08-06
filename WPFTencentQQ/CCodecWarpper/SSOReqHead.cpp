#include "StdAfx.h"
#include "SSOReqHead.h"


CSSOReqHead::CSSOReqHead(void)
{
}


CSSOReqHead::~CSSOReqHead(void)
{
}

void CSSOReqHead::init(int,int,int,char,std::string &,std::string &,char const*,int,std::string &,
		std::string &,std::string &,std::string &,std::string &,int)
{
}
int	CSSOReqHead::Length()
{
	return 0;
}
int CSSOReqHead::Length_ver9()
{
	return 0;
}

void CSSOReqHead::deSerialize(ByteBuffer &mBuffer,int&)
{
	if(mBuffer.size()-mBuffer.rpos()<=3) return;
	int headlen=mBuffer.reverse(mBuffer.read<int>());
	m_Seq=mBuffer.reverse(mBuffer.read<int>());
	m_RetCode=mBuffer.reverse(mBuffer.read<int>());
	a=readString(mBuffer);
	b=readString(mBuffer);
	c=readString(mBuffer);
	m_Flag=mBuffer.reverse(mBuffer.read<int>());
}
void CSSOReqHead::serialize(std::string&)
{
}
void CSSOReqHead::serialize_ver8(std::string&)
{
}
void CSSOReqHead::serialize_ver9(std::string&)
{
}

std::string CSSOReqHead::readString(ByteBuffer &mBuffer)
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