#pragma once
#include"PacketType.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JceStruct.h"
class InfoF:public JCE::CJceStruct
{
public:
	InfoF(void);
	virtual ~InfoF(void);
public:
	JCE::JCEString	a;
	JCE::JCEInt		b;
	JCE::JCEString	c;
	JCE::JCEString	d;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructInfoF;};
};

