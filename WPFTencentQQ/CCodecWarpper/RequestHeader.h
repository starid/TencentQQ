#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍSecurityAccountServer/RequestHeader
class CRequestHeader:public JCE::CJceStruct
{
public:
	CRequestHeader(void);
	CRequestHeader(int paramInt1, int paramInt2, int paramInt3, int paramInt4, std::string paramString1, int paramInt5, 
		std::string paramString2, std::string paramString3, std::string paramString4, long paramLong, int paramInt6);
	virtual ~CRequestHeader(void);
public:
	JCE::JCEString account;
	JCE::JCEInt appid;
	JCE::JCEInt assistImport;
	JCE::JCEString channel_id;
	JCE::JCEInt cmd;
	JCE::JCEString ksid;
	JCE::JCEInt requestID;
	JCE::JCEString sbid;
	JCE::JCEInt svrSeqNo;
	JCE::JCELong uin;
	JCE::JCEInt ver;		//Ä¬ÈÏ100
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

