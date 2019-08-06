#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
#include"SvcRespRegister.h"
class CStatSvcRegister
{
public:
	CStatSvcRegister(void);
	CStatSvcRegister(unsigned int seq,CConfigData *p){mSeq=seq,pConfig=p;};
	virtual ~CStatSvcRegister(void);
public:
	ByteBuffer Encode();
	void DecodeBody(const ByteBuffer&,CSvcRespRegister&);
private:
	void EncodeHead(CTXCommPack&);
	void EncodeBody(CTXCommPack&);
private:
	CTXCommPack	mPack;
	CConfigData *pConfig;
	unsigned int mSeq;
};

