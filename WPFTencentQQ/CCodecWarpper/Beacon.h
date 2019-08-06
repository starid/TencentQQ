#pragma once
#include"../JceProtocol/JceInputStream.h"
#include"../JceProtocol/JceOutputStream.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEType.h"
#include"StreamIn.h"
#include"StreamOut.h"
#include"../JceProtocol/JceInputStream.h"
#include"../JceProtocol/JceStruct.h"

//原型为com.tencent.beacon.e.e
class Beacon: public JCE::CJceStruct
{
public:
	Beacon(void)
	{
	}
	virtual ~Beacon(void)
	{
	}
public:
	JCE::JCEShort	a;	//固定值3
	JCE::JCEInt		b;
	JCE::JCEString	c;
	JCE::JCEString	d;
	JCE::JCEByteArray	e;//原型为byte[]
	JCE::JCEChar	f;
	JCE::JCEInt		g;
	JCE::JCEInt		h;
	JCE::JCEMap		i;
	JCE::JCEMap		j;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

