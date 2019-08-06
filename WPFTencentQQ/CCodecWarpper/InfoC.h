#pragma once
#include"PacketType.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEBoolean.h"
#include"../JceProtocol/JceStruct.h"
class InfoC:public JCE::CJceStruct
{
public:
	InfoC(void);
	virtual ~InfoC(void);
public:
	JCE::JCEString	a;
	JCE::JCEInt		b;
	JCE::JCEBoolean	c;
	JCE::JCEInt		d;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructInfoC;};
};

