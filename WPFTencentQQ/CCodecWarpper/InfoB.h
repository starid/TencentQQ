#pragma once
#include"PacketType.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEBoolean.h"
#include"../JceProtocol/JceStruct.h"
class InfoB:public JCE::CJceStruct
{
public:
	InfoB(void);
	virtual ~InfoB(void);
public:
	JCE::JCEString	a;
	JCE::JCEBoolean	b;
	JCE::JCEBoolean	c;
	JCE::JCEInt		d;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructInfoB;};
};

