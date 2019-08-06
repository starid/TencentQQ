#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCELong.h"

//Ô­ÐÍNeighborComm/ReqHeader
class CNeighborCommReqHeader:public JCE::CJceStruct
{
public:
	CNeighborCommReqHeader(void);
	virtual ~CNeighborCommReqHeader(void);
public:
	JCE::JCEShort shVersion;
	JCE::JCELong lMID;
	JCE::JCELong iAppID;
	JCE::JCEInt eBusiType;
	JCE::JCEInt eMqqSysType;
	JCE::JCELong uClientIp;
	JCE::JCELong uClientPort;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

