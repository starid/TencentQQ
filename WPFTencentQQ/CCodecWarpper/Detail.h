#pragma once
#include"../JceProtocol/JceInputStream.h"
#include"../JceProtocol/JceOutputStream.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JceStruct.h"

//Ô­ÐÍÎª£ºcom.tencent.beacon.c.a.b
class CDetail: public JCE::CJceStruct
{
public:
	CDetail(void);
	virtual ~CDetail(void);
public:
	JCE::JCEChar	a;
	JCE::JCEString	b;		//appkey
	JCE::JCEString	c;		//appVersion
	JCE::JCEString	d;		//sdkid
	JCE::JCEString	e;
	JCE::JCEInt		f;		//cmd
	JCE::JCEByteArray	g;
	JCE::JCEChar	h;
	JCE::JCEChar	i;
	JCE::JCEString	j;
	JCE::JCEString	k;
	JCE::JCEString	l;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

