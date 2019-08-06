#include "StdAfx.h"
#include "TXCommPack.h"
#include<stdlib.h>
#include<WinSock.h>
#include<ObjBase.h>
#include "../UtilLib/err_code.h"
#include<shlobj.h>   
#include<Windows.h>
#include<WinIoCtl.h>

#pragma   comment(lib,"shell32.lib") 


CTXCommPack::CTXCommPack(void)
{
}

CTXCommPack::CTXCommPack(size_t size)
{
}

CTXCommPack::~CTXCommPack(void)
{
}

void CTXCommPack::AddByte(const char b)
{
	buffer.append(b);
}

void CTXCommPack::AddDWord(const int data)
{
	buffer.append<uint32>(data);
}

void CTXCommPack::AddWord(const short data)
{
	buffer.append<uint16>(data);
}

void CTXCommPack::AddBuf(const char *buf,const int buflen)
{
	buffer.append(buf,buflen);
}

void CTXCommPack::AddByteBuffer(ByteBuffer &b)
{
	if(b.size()==0) return;
	b.rpos(0);
	buffer.append(b.contents(),b.size());
}

void CTXCommPack::AddBufLenWord()
{
	unsigned short len=buffer.size();
	//应该前置插入
	buffer.insert<uint16>(0,htons(len));

}

void CTXCommPack::AddLenDWord()
{
	unsigned int len=buffer.size();
	len+=4;
	//应该前置插入
	buffer.insert<uint32>(0,htonl(len));

}

void CTXCommPack::AddBufLenDWord()
{
	unsigned int len=buffer.size();
	//应该前置插入
	buffer.insert<uint32>(0,htonl(len));
}

//插入前置特征码
void CTXCommPack::AddFieldCode(short value)
{
	buffer.insert<uint16>(0,value);
}

void CTXCommPack::GetBufferOut()
{
	buffer.clear();
}