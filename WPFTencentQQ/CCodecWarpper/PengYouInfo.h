#pragma once
#include"../JceProtocol/JceStruct.h"

class CPengYouInfo:public JCE::CJceStruct
{
public:
	CPengYouInfo(void);
	virtual ~CPengYouInfo(void);
public:
	JCE::JCEString strPYName;
	JCE::JCEString strPYFaceUrl;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

