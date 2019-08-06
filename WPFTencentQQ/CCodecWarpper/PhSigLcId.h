#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CPhSigLcId
{
private:
	CPhSigLcId(void);
public:
	CPhSigLcId(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CPhSigLcId(void);
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

