#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEShort.h"

class CCell:public JCE::CJceStruct
{
public:
	CCell(void);
	virtual ~CCell(void);
public:
	JCE::JCEShort shMcc;
	JCE::JCEShort shMnc;
	JCE::JCEInt iLac;
	JCE::JCEInt iCellId;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

