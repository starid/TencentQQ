#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CLoginTransemp
{
private:
	CLoginTransemp(void);
public:
	CLoginTransemp(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CLoginTransemp(void);
public:
	ByteBuffer Encode();
private:
	void EncodeHead(CTXCommPack&);
	void EncodeBody(CTXCommPack&);
private:
	CTXCommPack	mPack;
	CConfigData *pConfig;
	unsigned int mSeq;
public:
	static unsigned short wCmd;
};

