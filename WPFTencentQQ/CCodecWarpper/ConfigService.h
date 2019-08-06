#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CConfigService
{
public:
	CConfigService(void);
public:
	CConfigService(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CConfigService(void);
public:
	ByteBuffer Encode();
private:
	void EncodeHead(CTXCommPack&);
	void EncodeBody(CTXCommPack&);
private:
	CTXCommPack	mPack;
	CConfigData *pConfig;
	unsigned int mSeq;
};

