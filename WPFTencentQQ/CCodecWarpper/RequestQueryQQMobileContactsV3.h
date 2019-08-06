#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEBoolean.h"

//Ô­ÐÍSecurityAccountServer/RequestQueryQQMobileContactsV3
class CRequestQueryQQMobileContactsV3:public JCE::CJceStruct
{
public:
	CRequestQueryQQMobileContactsV3(void);
	~CRequestQueryQQMobileContactsV3(void);
public:
	JCE::JCELong nextFlag;
	JCE::JCELong timeStamp;
	JCE::JCEByteArray sessionSid;
	JCE::JCEInt queryFlag;
	JCE::JCEBoolean Compressd;
	JCE::JCELong MaxsignTimeStamp;
	JCE::JCEString MobileUniqueNo;
	JCE::JCEBoolean OmitOffline;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

