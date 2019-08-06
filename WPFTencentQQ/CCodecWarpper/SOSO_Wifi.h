#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEShort.h"

class CSOSO_Wifi:public JCE::CJceStruct
{
public:
	CSOSO_Wifi(void);
	virtual ~CSOSO_Wifi(void);
public:
	JCE::JCELong lMac;
	JCE::JCEShort shRssi;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

