#include "StdAfx.h"
#include "ReqGetNearbyPubAcctInfo.h"


CReqGetNearbyPubAcctInfo::CReqGetNearbyPubAcctInfo(void)
{
}


CReqGetNearbyPubAcctInfo::~CReqGetNearbyPubAcctInfo(void)
{
}

void CReqGetNearbyPubAcctInfo::readFrom(CJceInputStream& paramd)
{
}
void CReqGetNearbyPubAcctInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&shVersion, 0);
    paramJceOutputStream.write(&vContext, 1);
	paramJceOutputStream.write(&iCount, 2);
	paramJceOutputStream.write(&stLBSInfo, 3);
}