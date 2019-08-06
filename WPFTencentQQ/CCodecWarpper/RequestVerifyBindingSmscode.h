#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEInt.h"

//Ô­ÐÍSecurityAccountServer/RequestVerifyBindingSmscode
class CRequestVerifyBindingSmscode:public JCE::CJceStruct
{
public:
	CRequestVerifyBindingSmscode(void);
	~CRequestVerifyBindingSmscode(void);
public:
	JCE::JCEString smsCode;
	JCE::JCEByteArray sessionSid;
	JCE::JCEInt type;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

