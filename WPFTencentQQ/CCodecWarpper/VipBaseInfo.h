#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEMap.h"

class CVipBaseInfo:public JCE::CJceStruct
{
public:
	CVipBaseInfo(void);
	virtual ~CVipBaseInfo(void);
public:
	JCE::JCEMap mOpenInfo;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

