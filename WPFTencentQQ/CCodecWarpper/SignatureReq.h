#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"

//Ô­ÐÍcom.tencent.msf.service.protocol.e.h
class SignatureReq:public JCE::CJceStruct
{
public:
	SignatureReq(void);
	virtual ~SignatureReq(void);
public:
	JCE::JCEListArray	a;	//signatures
	JCE::JCEInt			b;	//lcid
	JCE::JCEListArray	c;	//uins
	JCE::JCEChar		d;	//base
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

