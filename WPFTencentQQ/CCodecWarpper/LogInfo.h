#pragma once
#include"PacketType.h"
#include"../JceProtocol/JCEListArray.h"
#include"../JceProtocol/JceStruct.h"
class LogInfo:public JCE::CJceStruct
{
public:
	LogInfo(void);
	virtual ~LogInfo(void);
public:
	JCE::JCEListArray	a;
	JCE::JCEListArray	b;
	JCE::JCEListArray	c;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructLogInfo;};
};

