#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"

//Ô­ÐÍcom.tencent.msf.service.protocol.e.e
class SDKConfReq:public JCE::CJceStruct
{
public:
	SDKConfReq(void);
	virtual ~SDKConfReq(void);
public:
	JCE::JCEInt			a;
	JCE::JCEInt			b;
	JCE::JCEListArray	c;
	JCE::JCEInt			d;
	JCE::JCEInt			e;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

