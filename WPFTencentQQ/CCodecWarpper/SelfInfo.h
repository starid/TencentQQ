#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"

class CSelfInfo:public JCE::CJceStruct
{
public:
	CSelfInfo(void);
	virtual ~CSelfInfo(void);
public:
	JCE::JCEChar cSex;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

