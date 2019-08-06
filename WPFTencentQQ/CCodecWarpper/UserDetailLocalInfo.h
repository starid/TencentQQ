#pragma once
#include"../JceProtocol/JceStruct.h"

class CUserDetailLocalInfo:public JCE::CJceStruct
{
public:
	CUserDetailLocalInfo(void);
	virtual ~CUserDetailLocalInfo(void);
public:
	JCE::JCEString strProvince;
	JCE::JCEString strCity;
	JCE::JCEString strDistrict;
	JCE::JCEString strTown;
	JCE::JCEString strRoad;
	JCE::JCEString strPremises;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

