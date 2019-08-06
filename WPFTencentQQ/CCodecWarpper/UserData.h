#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCELong.h"


class CUserData:public JCE::CJceStruct
{
public:
	CUserData(void);
	virtual ~CUserData(void);
public:
	JCE::JCEInt lTime;
	JCE::JCEInt iLat;
	JCE::JCEInt iLon;
	JCE::JCELong lOriginGrid;
	JCE::JCELong lNextGrid;
	JCE::JCEString strProvince;
	JCE::JCEByteArray strCookie;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

