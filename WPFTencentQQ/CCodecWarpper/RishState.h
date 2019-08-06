#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"

class CRishState:public JCE::CJceStruct
{
public:
	CRishState(void);
	virtual ~CRishState(void);
public:
	JCE::JCEByteArray vState;
	JCE::JCELong uModifyTime;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

