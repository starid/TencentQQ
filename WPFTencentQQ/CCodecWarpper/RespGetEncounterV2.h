#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CRespGetEncounterV2_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CRespGetEncounterV2_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"UserData.h"
#include"UserDetailLocalInfo.h"
#include"PengYouInfo.h"
#include"EctFragmentation.h"
#include"SelfInfo.h"

class DIPPEREXPORTS_CRespGetEncounterV2_API CRespGetEncounterV2:public JCE::CJceStruct
{
public:
	CRespGetEncounterV2(void);
	virtual ~CRespGetEncounterV2(void);
public:
	JCE::JCELong RespTime;
	CUserData	stUserData;
	JCE::JCEListArray vEncounterInfos;//CRespEncounterInfo
	CUserDetailLocalInfo stUDLinfo;
	CPengYouInfo stPYInfo;
	CEctFragmentation stEctFmt;
	JCE::JCEInt iSessionTotalNumber;
	JCE::JCEInt iEncounterNumber;
	JCE::JCEByteArray nearbyGroupResp;
	JCE::JCEByteArray nearbyPublicAcctResp;
	JCE::JCEString strSecurityTips;
	JCE::JCEString strSecurityDetailUrl;
	JCE::JCEListArray entrance_list;
	JCE::JCEListArray neighbor_banners;
	JCE::JCEChar system_pic;
	JCE::JCEChar watch_color;
	JCE::JCEChar useInterestTag;
	JCE::JCEListArray ad_list;
	CSelfInfo self_info;
	JCE::JCEByteArray end;//注意，旧版本此处没有该字段
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

