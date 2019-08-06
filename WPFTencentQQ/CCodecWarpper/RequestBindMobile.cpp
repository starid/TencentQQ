#include "StdAfx.h"
#include "RequestBindMobile.h"


CRequestBindMobile::CRequestBindMobile(void)
{
}


CRequestBindMobile::~CRequestBindMobile(void)
{
}

void CRequestBindMobile::readFrom(CJceInputStream& paramd)
{
}
void CRequestBindMobile::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&mobileNo, 0);
    paramJceOutputStream.write(&nationCode, 1);
    paramJceOutputStream.write(&originBinder, 2);
    paramJceOutputStream.write(&type, 3);
}