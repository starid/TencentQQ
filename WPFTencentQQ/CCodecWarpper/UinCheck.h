#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"PacketType.h"

//Ô­ÐÍcom/tencent/msf/service/protocol/e/c
class CUinCheck:public JCE::CJceStruct
{
public:
	CUinCheck(void);
	virtual ~CUinCheck(void);
public:
	JCE::JCEInt		a;
	JCE::JCEString	b;
	JCE::JCEString	c;
	JCE::JCEString	d;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructUinCheck;};
};

