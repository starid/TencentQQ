#include "StdAfx.h"
#include "ReqUserInfo.h"


CReqUserInfo::CReqUserInfo(void)
{
}


CReqUserInfo::~CReqUserInfo(void)
{
}

void CReqUserInfo::readFrom(CJceInputStream& paramd)
{
}
void CReqUserInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&stGps, 0);
	if(vMacs._value.size()!=0)
		paramJceOutputStream.write(&vMacs, 1);
	if(vCells._value.size()!=0)
		paramJceOutputStream.write(&vCells, 2);
    paramJceOutputStream.write(&strAuthName, 3);
	paramJceOutputStream.write(&strAuthPassword, 4);
	paramJceOutputStream.write(&eListType, 5);
	paramJceOutputStream.write(&eLocalInfo, 6);
	if(vLBSKeyData.value().size()!=0)
		paramJceOutputStream.write(&vLBSKeyData, 7);
	if(vSOSOMac._value.size()!=0)
		paramJceOutputStream.write(&vSOSOMac, 8);
	if(vSOSOCells._value.size()!=0)
		paramJceOutputStream.write(&vSOSOCells, 9);
}