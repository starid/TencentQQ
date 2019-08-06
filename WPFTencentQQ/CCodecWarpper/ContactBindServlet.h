#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"

//可以查看com.tencent.mobileqq.phonecontact/ContactBindServlet
class CContactBindServlet
{
public:
	CContactBindServlet(void);
	CContactBindServlet(CConfigData *p){pConfig=p;};
	virtual ~CContactBindServlet(void);
public:
	ByteBuffer Encode(unsigned int type);
private:
	void EncodeHead(CTXCommPack&,unsigned int type);
	void EncodeBody(CTXCommPack&,unsigned int type);
public:
	void DecodeBody(const ByteBuffer&,unsigned int type,JCE::CJceStruct*);
private:
	CTXCommPack	mPack;
	CConfigData *pConfig;
};

