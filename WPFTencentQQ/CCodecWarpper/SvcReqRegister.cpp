#include "StdAfx.h"
#include "SvcReqRegister.h"


CSvcReqRegister::CSvcReqRegister(void)
{
}


CSvcReqRegister::~CSvcReqRegister(void)
{
}

void CSvcReqRegister::readFrom(CJceInputStream& paramd)
{
}
void CSvcReqRegister::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&lUin, 0);
    paramJceOutputStream.write(&lBid, 1);
    paramJceOutputStream.write(&cConnType, 2);
    paramJceOutputStream.write(&sOther, 3);
    paramJceOutputStream.write(&iStatus, 4);
    paramJceOutputStream.write(&bOnlinePush, 5);
    paramJceOutputStream.write(&bIsOnline, 6);
    paramJceOutputStream.write(&bIsShowOnline, 7);
    paramJceOutputStream.write(&bKikPC, 8);
    paramJceOutputStream.write(&bKikWeak, 9);
    paramJceOutputStream.write(&timeStamp, 10);
    paramJceOutputStream.write(&iOSVersion, 11);
    paramJceOutputStream.write(&cNetType, 12);
    paramJceOutputStream.write(&sBuildVer, 13);
    paramJceOutputStream.write(&bRegType, 14);
	if(vecDevParam.value().size()!=0)
		paramJceOutputStream.write(&vecDevParam, 15);
	if(vecGuid.value().size()!=0)
		paramJceOutputStream.write(&vecGuid, 16);
    paramJceOutputStream.write(&iLocaleID, 17);
    paramJceOutputStream.write(&bSlientPush, 18);
    paramJceOutputStream.write(&strDevName, 19);
    paramJceOutputStream.write(&strDevType, 20);
    paramJceOutputStream.write(&strOSVer, 21);
    paramJceOutputStream.write(&bOpenPush, 22);
    paramJceOutputStream.write(&iLargeSeq, 23);
}