#include "StdAfx.h"
#include "ReqGetEncounterV2.h"


CReqGetEncounterV2::CReqGetEncounterV2(void)
{
}


CReqGetEncounterV2::~CReqGetEncounterV2(void)
{
}

void CReqGetEncounterV2::readFrom(CJceInputStream& paramd)
{
}
void CReqGetEncounterV2::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&stUserInfo, 0);
    paramJceOutputStream.write(&stUserData, 1);
    paramJceOutputStream.write(&eNewListType, 2);
    paramJceOutputStream.write(&iListSize, 3);
	if(vTagsID._value.size()!=0)
		paramJceOutputStream.write(&vTagsID, 4);
	if(strA2.value().size()==0)
	{
		strA2.ref_value().append(char(0));
	}
	paramJceOutputStream.write(&strA2, 5);
	paramJceOutputStream.write(&bTraversing, 6);
	paramJceOutputStream.write(&iRadius, 7);
	paramJceOutputStream.write(&iMaxSearchNum, 8);
	paramJceOutputStream.write(&iSimpleSort, 9);
	if(nearbyGroupReq.value().size()!=0)
		paramJceOutputStream.write(&nearbyGroupReq, 10);
	if(nearbyPublicAcctReq.value().size()!=0)
		paramJceOutputStream.write(&nearbyPublicAcctReq, 11);
	paramJceOutputStream.write(&random_trav_dis_level, 12);
	paramJceOutputStream.write(&encrypt_proto, 13);
	paramJceOutputStream.write(&constellation, 14);
	paramJceOutputStream.write(&age_lower, 15);
	paramJceOutputStream.write(&age_up, 16);
	paramJceOutputStream.write(&time_interval, 17);
	paramJceOutputStream.write(&profession_id, 18);
	paramJceOutputStream.write(&home_province, 19);
	paramJceOutputStream.write(&home_city, 20);
	paramJceOutputStream.write(&use_tinyid, 21);
	paramJceOutputStream.write(&home_country, 22);
	paramJceOutputStream.write(&stLocalUserInfo, 23);
	paramJceOutputStream.write(&support_entrace_type, 24);
	paramJceOutputStream.write(&appoint_params, 25);
	paramJceOutputStream.write(&use_watch, 26);
	paramJceOutputStream.write(&watch_color, 27);
	paramJceOutputStream.write(&interest_id, 28);
	paramJceOutputStream.write(&ad_extra, 29);
	paramJceOutputStream.write(&ad_ctrl, 30);
}
