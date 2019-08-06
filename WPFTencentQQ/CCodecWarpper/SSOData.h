#pragma once
#include"SSOReqHead.h"
#include"SSOHead.h"
class CSSOData
{
public:
	CSSOData(void);		//占用0x148字节
	virtual ~CSSOData(void);
private:
	CSSOHead	mSSOHead;
	CSSOReqHead	mSSOReqHead;
public:
	void init(int,char const *,char,int,int,int,char const *,char const *,char const *,char const *,std::string&,
		char const *,char const *,int,char const *,int,int,int);
	void serialize(std::string&);
	/*
	*数据包
	*数据包长度
	*1
	*/
	void deSerialize(ByteBuffer&,bool);
};

