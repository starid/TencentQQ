#pragma once
#include"TXCommPack.h"
#include"ConfigData.h"
class CfriendlistGetTroopListReqV2
{
private:
	CfriendlistGetTroopListReqV2(void);
public:
	CfriendlistGetTroopListReqV2(unsigned int seq,CConfigData *p){mSeq=seq;pConfig=p;};
	virtual ~CfriendlistGetTroopListReqV2(void);
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

