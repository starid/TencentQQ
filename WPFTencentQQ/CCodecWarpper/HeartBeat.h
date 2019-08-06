#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CHeartBeat
{
private:
	CHeartBeat(void);
public:
	CHeartBeat(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CHeartBeat(void);
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

