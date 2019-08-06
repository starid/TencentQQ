#pragma once
#include"../JceProtocol/JceStruct.h"

class CAttr:public JCE::CJceStruct
{
public:
	CAttr(void);
	virtual ~CAttr(void);
public:
	JCE::JCEString strImei;
	JCE::JCEString strImsi;
	JCE::JCEString strPhonenum;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

