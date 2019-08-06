#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEShort.h"
#include"LBSInfo.h"

class CReqGetNearbyPubAcctInfo:public JCE::CJceStruct
{
public:
	CReqGetNearbyPubAcctInfo(void);
	virtual ~CReqGetNearbyPubAcctInfo(void);
public:
	JCE::JCEShort shVersion;
	JCE::JCEByteArray vContext;
	JCE::JCEInt iCount;
	CLBSInfo stLBSInfo;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

