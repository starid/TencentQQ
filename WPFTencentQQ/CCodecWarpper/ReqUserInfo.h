#pragma once
#include"../JceProtocol/JceStruct.h"
#include"GPS.h"


class CReqUserInfo:public JCE::CJceStruct
{
public:
	CReqUserInfo(void);
	virtual ~CReqUserInfo(void);
public:
	CGPS stGps;
	JCE::JCEListArray vMacs;
	JCE::JCEListArray vCells;
	JCE::JCEString strAuthName;
	JCE::JCEString strAuthPassword;
	JCE::JCEInt eListType;
	JCE::JCEInt eLocalInfo;
	JCE::JCEByteArray vLBSKeyData;
	JCE::JCEListArray vSOSOMac;
	JCE::JCEListArray vSOSOCells;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

