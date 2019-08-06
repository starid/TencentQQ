#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CClassFactory_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CClassFactory_API __declspec(dllimport)
#endif

#include<string>
#include"SummaryCardReqSearch.h"
#include"ReqGetEncounterV2.h"

class DIPPEREXPORTS_CClassFactory_API CClassFactory
{
public:
	CClassFactory(void);
	~CClassFactory(void);
public:
	void SetCSummaryCardReqSearch(CSummaryCardReqSearch &,std::string strKeyWord,std::string strCountryCode);
	void SetCReqGetEncounterV2(CReqGetEncounterV2 &);
};

