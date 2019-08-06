#include "StdAfx.h"
#include "UserData.h"


CUserData::CUserData(void)
{
	iLat.value(900000000);
	iLon.value(900000000);
}


CUserData::~CUserData(void)
{
}

void CUserData::readFrom(CJceInputStream& paramd)
{
	paramd.read(&lTime,0,true);
	paramd.read(&iLat,1,true);
	paramd.read(&iLon,2,true);
	paramd.read(&lOriginGrid,3,true);
	paramd.read(&lNextGrid,4,true);
	paramd.read(&strProvince,5,false);
	paramd.read(&strCookie,6,false);
}
void CUserData::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&lTime, 0);
    paramJceOutputStream.write(&iLat, 1);
    paramJceOutputStream.write(&iLon, 2);
    paramJceOutputStream.write(&lOriginGrid, 3);
	paramJceOutputStream.write(&lNextGrid, 4);
	paramJceOutputStream.write(&strProvince, 5);
	if(strCookie.value().size()!=0)
		paramJceOutputStream.write(&strCookie, 6);
}
