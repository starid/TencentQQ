#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CSummaryCardReqSearch_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CSummaryCardReqSearch_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍSummaryCard/ReqSearch
class DIPPEREXPORTS_CSummaryCardReqSearch_API CSummaryCardReqSearch:public JCE::CJceStruct
{
public:
	CSummaryCardReqSearch(void);
	~CSummaryCardReqSearch(void);
public:
	JCE::JCEString strKeyword;
	JCE::JCEString strCountryCode;
	JCE::JCEInt shVersion;
	JCE::JCEListArray	vvReqServices;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

