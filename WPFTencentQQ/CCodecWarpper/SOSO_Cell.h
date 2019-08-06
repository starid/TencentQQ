#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEShort.h"

class CSOSO_Cell:public JCE::CJceStruct
{
public:
	CSOSO_Cell(void);
	virtual ~CSOSO_Cell(void);
public:
	JCE::JCEShort shMcc;
	JCE::JCEShort shMnc;
	JCE::JCEInt iLac;
	JCE::JCEInt iCellId;
	JCE::JCEShort shRssi;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

