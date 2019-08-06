#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEMap.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEListArray.h"
#include"LogInfo.h"
#include"PacketType.h"

//Ô­ÐÍcom.tencent.beacon.c.e.d
class CEventLog:public JCE::CJceStruct
{
public:
	CEventLog(void);
	virtual ~CEventLog(void);
public:
	JCE::JCEChar	a;
	JCE::JCEChar	b;
	JCE::JCEString	c;
	JCE::JCEMap		d;
	JCE::JCEListArray	e;
	LogInfo				f;
	JCE::JCEListArray	g;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructEventLog;};
};

