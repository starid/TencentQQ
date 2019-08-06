#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"

class CGPS:public JCE::CJceStruct
{
public:
	CGPS(void);
	virtual ~CGPS(void);
public:
	JCE::JCEInt iLat;
	JCE::JCEInt iLon;
	JCE::JCEInt iAlt;
	JCE::JCEInt eType;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

