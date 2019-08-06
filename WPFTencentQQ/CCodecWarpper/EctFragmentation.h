#pragma once
#include"../JceProtocol/JceStruct.h"

class CEctFragmentation:public JCE::CJceStruct
{
public:
	CEctFragmentation(void);
	virtual ~CEctFragmentation(void);
public:
	JCE::JCEInt iTotalNum;
	JCE::JCEInt iSelfIndex;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

