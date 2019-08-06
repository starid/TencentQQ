#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
#include"SummaryCardReqSearch.h"

//可以查看com.tencent.mobileqq.service.lbs/LBSService
class LBSService
{
public:
	LBSService(void);
	LBSService(CConfigData *p){pConfig=p;};
	virtual ~LBSService(void);
public:
	ByteBuffer Encode(unsigned int type,void *data=0);
private:
	void EncodeHead(CTXCommPack&,unsigned int type,void *data=0);
	void EncodeBody(CTXCommPack&,unsigned int type,void *data=0);
public:
	void DecodeBody(const ByteBuffer&,unsigned int type,JCE::CJceStruct*);
private:
	CTXCommPack	mPack;
	CConfigData *pConfig;
};

