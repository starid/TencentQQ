#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CGrayUinProCheck
{
public:
	CGrayUinProCheck(void);
public:
	CGrayUinProCheck(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CGrayUinProCheck(void);
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

