#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CReqGetEncounterV2_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CReqGetEncounterV2_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEInt.h"
#include"ReqUserInfo.h"
#include"UserData.h"


class DIPPEREXPORTS_CReqGetEncounterV2_API CReqGetEncounterV2:public JCE::CJceStruct
{
public:
	CReqGetEncounterV2(void);
	virtual ~CReqGetEncounterV2(void);
public:
	CReqUserInfo stUserInfo;
	CUserData	stUserData;
	JCE::JCEInt eNewListType;
	JCE::JCEInt iListSize;
	JCE::JCEListArray vTagsID;//long
	JCE::JCEByteArray strA2;
	JCE::JCEChar bTraversing;
	JCE::JCEInt iRadius;
	JCE::JCEInt iMaxSearchNum;
	JCE::JCEInt iSimpleSort;
	JCE::JCEByteArray nearbyGroupReq;
	JCE::JCEByteArray nearbyPublicAcctReq;
	JCE::JCEInt random_trav_dis_level;
	JCE::JCEChar encrypt_proto;
	JCE::JCEChar constellation;
	JCE::JCEChar age_lower;
	JCE::JCEChar age_up;
	JCE::JCEInt time_interval;
	JCE::JCEInt profession_id;
	JCE::JCEInt home_province;
	JCE::JCEInt home_city;
	JCE::JCEChar use_tinyid;
	JCE::JCEInt home_country;
	CReqUserInfo stLocalUserInfo;
	JCE::JCEInt support_entrace_type;
	JCE::JCEByteArray appoint_params;
	JCE::JCEChar use_watch;
	JCE::JCEChar watch_color;
	JCE::JCEChar interest_id;
	JCE::JCEString ad_extra;
	JCE::JCELong ad_ctrl;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

