#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CRespondQueryQQBindingStat_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CRespondQueryQQBindingStat_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCELong.h"

//Ô­ÐÍSecurityAccountServer/RespondQueryQQBindingStat
class DIPPEREXPORTS_CRespondQueryQQBindingStat_API CRespondQueryQQBindingStat:public JCE::CJceStruct
{
public:
	CRespondQueryQQBindingStat(void);
	~CRespondQueryQQBindingStat(void);
public:
	JCE::JCEString nationCode;
	JCE::JCEString mobileNo;
	JCE::JCEString MobileUniqueNo;
	JCE::JCELong isRecommend;
	JCE::JCELong originBinder;
	JCE::JCELong bindingTime;
	JCE::JCELong lastUsedFlag;
	JCE::JCEInt type;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

