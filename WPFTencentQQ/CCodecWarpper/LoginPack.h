#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"

//原型：oicq.wlogin_sdk.request/m.class(k.class)
class CLoginPack
{
private:
	CLoginPack(void);
public:
	CLoginPack(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CLoginPack(void);
public:
	ByteBuffer Encode();
private:
	void EncodeHead(CTXCommPack&);
	void EncodeBody(CTXCommPack&);//（添加验证码：oicq.wlogin_sdk.request/o.class）
private:
	CTXCommPack	mPack;
	CConfigData *pConfig;
	unsigned int mSeq;
public:
	static unsigned short wCmd;
};

