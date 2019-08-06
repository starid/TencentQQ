#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CCliLogSvc
{
private:
	CCliLogSvc(void);
public:
	CCliLogSvc(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CCliLogSvc(void);
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

