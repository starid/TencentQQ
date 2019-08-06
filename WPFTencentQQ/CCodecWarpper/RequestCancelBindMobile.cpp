#include "StdAfx.h"
#include "RequestCancelBindMobile.h"


CRequestCancelBindMobile::CRequestCancelBindMobile(void)
{
}


CRequestCancelBindMobile::~CRequestCancelBindMobile(void)
{
}

void CRequestCancelBindMobile::readFrom(CJceInputStream& paramd)
{
}
void CRequestCancelBindMobile::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&mobileNo, 0);
    paramJceOutputStream.write(&nationCode, 1);
}