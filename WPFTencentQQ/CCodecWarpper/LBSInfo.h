#pragma once
#include"../JceProtocol/JceStruct.h"
#include"GPS.h"
#include"Attr.h"

class CLBSInfo:public JCE::CJceStruct
{
public:
	CLBSInfo(void);
	virtual ~CLBSInfo(void);
public:
	CGPS stGps;
	JCE::JCEListArray vWifis;
	JCE::JCEListArray vCells;
    CAttr stAttr;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

