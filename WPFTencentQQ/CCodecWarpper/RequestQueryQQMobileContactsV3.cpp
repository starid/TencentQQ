#include "StdAfx.h"
#include "RequestQueryQQMobileContactsV3.h"


CRequestQueryQQMobileContactsV3::CRequestQueryQQMobileContactsV3(void)
{
}


CRequestQueryQQMobileContactsV3::~CRequestQueryQQMobileContactsV3(void)
{
}

void CRequestQueryQQMobileContactsV3::readFrom(CJceInputStream& paramd)
{
}
void CRequestQueryQQMobileContactsV3::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&nextFlag, 0);
	paramJceOutputStream.write(&timeStamp, 1);
	paramJceOutputStream.write(&sessionSid, 2);
	paramJceOutputStream.write(&queryFlag, 3);
	paramJceOutputStream.write(&Compressd, 4);
	paramJceOutputStream.write(&MaxsignTimeStamp, 5);
	paramJceOutputStream.write(&MobileUniqueNo, 6);
	paramJceOutputStream.write(&OmitOffline, 7);
}