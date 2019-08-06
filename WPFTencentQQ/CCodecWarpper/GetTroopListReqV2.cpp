#include "StdAfx.h"
#include "GetTroopListReqV2.h"


CGetTroopListReqV2::CGetTroopListReqV2(void)
{
}


CGetTroopListReqV2::~CGetTroopListReqV2(void)
{
}

void CGetTroopListReqV2::readFrom(CJceInputStream& paramd)
{
}

void CGetTroopListReqV2::writeTo(CJceOutputStream& paramd)
{
	paramd.write(&uin,0);
	paramd.write(&bGetMSFMsgFlag,1);
	if(vecCookies.value().size()!=0)
		paramd.write(&vecCookies,2);
	if(vecGroupInfo._value.size()!=0)
		paramd.write(&vecGroupInfo,3);
	paramd.write(&bGroupFlagExt,4);
	paramd.write(&shVersion,5);
}