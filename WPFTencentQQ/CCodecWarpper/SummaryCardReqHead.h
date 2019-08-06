#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"

//Ô­ÐÍSummaryCard/ReqHead
class CSummaryCardReqHead:public JCE::CJceStruct
{
public:
	CSummaryCardReqHead(void);
	~CSummaryCardReqHead(void);
public:
	JCE::JCEInt iVersion;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

