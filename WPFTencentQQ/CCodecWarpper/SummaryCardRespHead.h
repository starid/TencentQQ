#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"

//Ô­ÐÍSummaryCard/RespHead
class CSummaryCardRespHead:public JCE::CJceStruct
{
public:
	CSummaryCardRespHead(void);
	~CSummaryCardRespHead(void);
public:
	JCE::JCEInt iVersion;
	JCE::JCEInt iResult;
	JCE::JCEString strErrorMsg;
	JCE::JCEByteArray vCookies;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

