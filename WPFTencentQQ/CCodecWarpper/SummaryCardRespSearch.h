#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CSummaryCardRespSearch_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CSummaryCardRespSearch_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍSummaryCard/RespSearch
class DIPPEREXPORTS_CSummaryCardRespSearch_API CSummaryCardRespSearch:public JCE::CJceStruct
{
public:
	CSummaryCardRespSearch(void);
	~CSummaryCardRespSearch(void);
public:
	JCE::JCEListArray vRecords;
	JCE::JCEByteArray vSecureSig;
	JCE::JCEListArray	vvRespServices;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

