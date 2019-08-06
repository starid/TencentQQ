#include "StdAfx.h"
#include "UserDetailLocalInfo.h"


CUserDetailLocalInfo::CUserDetailLocalInfo(void)
{
}


CUserDetailLocalInfo::~CUserDetailLocalInfo(void)
{
}

void CUserDetailLocalInfo::readFrom(CJceInputStream& paramd)
{
}

void CUserDetailLocalInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&strProvince, 0);
    paramJceOutputStream.write(&strCity, 1);
    paramJceOutputStream.write(&strDistrict, 2);
    paramJceOutputStream.write(&strTown, 3);
	paramJceOutputStream.write(&strRoad, 4);
	paramJceOutputStream.write(&strPremises, 5);
}
