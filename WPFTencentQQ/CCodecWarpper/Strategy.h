#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEMap.h"
#include"../JceProtocol/JCEListArray.h"
#include"StreamIn.h"
#include"StreamOut.h"
#include"PacketType.h"

//Ô­ÐÍcom.tencent.beacon.c.e.a
class CStrategy:public JCE::CJceStruct
{
public:
	CStrategy(void);
	virtual ~CStrategy(void);
public:
	JCE::JCEListArray	a;
	JCE::JCEInt			b;
	JCE::JCEString		c;
	JCE::JCEMap			d;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructStrategy;};
};

