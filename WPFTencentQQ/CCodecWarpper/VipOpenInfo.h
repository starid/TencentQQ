#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEBoolean.h"

class CVipOpenInfo:public JCE::CJceStruct
{
public:
	CVipOpenInfo(void);
	virtual ~CVipOpenInfo(void);
public:
	JCE::JCEBoolean bOpen;
	JCE::JCEInt iVipFlag;
	JCE::JCEInt iVipLevel;
	JCE::JCEInt iVipType;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

