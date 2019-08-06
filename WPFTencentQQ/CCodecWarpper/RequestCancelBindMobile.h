#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍSecurityAccountServer/RequestCancelBindMobile
class CRequestCancelBindMobile:public JCE::CJceStruct
{
public:
	CRequestCancelBindMobile(void);
	~CRequestCancelBindMobile(void);
public:
	JCE::JCEString mobileNo;
	JCE::JCEString nationCode;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

