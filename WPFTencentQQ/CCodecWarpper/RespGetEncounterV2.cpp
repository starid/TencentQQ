#include "StdAfx.h"
#include "RespGetEncounterV2.h"
#include"RespEncounterInfo.h"
#include"EntranceContent.h"
#include"NeighborBanner.h"
#include"NeighborAd.h"


CRespGetEncounterV2::CRespGetEncounterV2(void)
{
}


CRespGetEncounterV2::~CRespGetEncounterV2(void)
{
}

void CRespGetEncounterV2::readFrom(CJceInputStream& paramd)
{
	paramd.read(&RespTime,0,true);
	paramd.read(&stUserData,1,true);
	if(vEncounterInfos._value.size()==0)
	{
		vEncounterInfos._value.push_back(new CRespEncounterInfo());
	}
	paramd.read(&vEncounterInfos,2,false);
	paramd.read(&stUDLinfo,3,false);
	paramd.read(&stPYInfo,4,false);
	paramd.read(&stEctFmt,5,false);
	paramd.read(&iSessionTotalNumber,6,false);
	paramd.read(&iEncounterNumber,7,false);
	paramd.read(&nearbyGroupResp,8,false);
	paramd.read(&nearbyPublicAcctResp,9,false);
	paramd.read(&strSecurityTips,10,false);
	paramd.read(&strSecurityDetailUrl,11,false);
	if(entrance_list._value.size()==0)
	{
		vEncounterInfos._value.push_back(new CEntranceContent());
	}
	paramd.read(&vEncounterInfos,12,false);
	if(neighbor_banners._value.size()==0)
	{
		neighbor_banners._value.push_back(new CNeighborBanner());
	}
	paramd.read(&neighbor_banners,13,false);
	paramd.read(&system_pic,14,false);
	paramd.read(&watch_color,15,false);
	paramd.read(&useInterestTag,16,false);
	if(ad_list._value.size()==0)
	{
		ad_list._value.push_back(new CNeighborAd());
	}
	paramd.read(&ad_list,17,false);
	paramd.read(&self_info,18,false);
	paramd.read(&end,19,false);
}
void CRespGetEncounterV2::writeTo(CJceOutputStream& paramJceOutputStream)
{
}