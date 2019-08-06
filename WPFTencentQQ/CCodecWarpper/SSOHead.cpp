#include "StdAfx.h"
#include "SSOHead.h"


CSSOHead::CSSOHead(void)
{
}


CSSOHead::~CSSOHead(void)
{
}

void CSSOHead::init(char,std::string&)
{
}
void CSSOHead::serialize(std::string&,int)
{
}
void CSSOHead::deSerialize(ByteBuffer &mBuffer,int&)
{
	if(mBuffer.size()-mBuffer.rpos()<3)
		return;
	m_Version=mBuffer.reverse(mBuffer.read<int>());
	a=mBuffer.read<char>();
	b=mBuffer.read<char>();
	if(mBuffer.size()-mBuffer.rpos()<3)
		return;
	strQQ=readString(mBuffer);
}

void CSSOHead::serialize_ver8(std::string&)
{
}

void CSSOHead::serialize_ver9(std::string&,int)
{
}

std::string CSSOHead::readString(ByteBuffer &mBuffer)
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