#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class COidbSvc_0x7a2_0
{
public:
	COidbSvc_0x7a2_0(void);
public:
	COidbSvc_0x7a2_0(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~COidbSvc_0x7a2_0(void);
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

