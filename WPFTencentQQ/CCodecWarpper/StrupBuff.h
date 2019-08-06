#pragma once
#include"../JceProtocol/JCEMap.h"
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"

//Ô­ÐÍcom.tencent.qphone.base.report.StrupBuff
class StrupBuff:public JCE::CJceStruct
{
public:
	StrupBuff(void);
	virtual ~StrupBuff(void);
public:
	JCE::JCEMap			a;
	JCE::JCEString		b;
	JCE::JCEChar		c;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};


#define STR_LOG_FORMAT "Vip_login_upload|null||upload|report|0|1|0|%s/mobileQQ/%s/10000049/////0/%d/N/Lan998/Lan998/740/WIFI///0/||||"
