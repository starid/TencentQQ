#include "StdAfx.h"
#include "ResponeBindMobile.h"


CResponeBindMobile::CResponeBindMobile(void)
{
}


CResponeBindMobile::~CResponeBindMobile(void)
{
}

void CResponeBindMobile::readFrom(CJceInputStream& paramd)
{
	paramd.read(&sessionSid,0,true);
	paramd.read(&alreadyBindedUin,1,false);
}
void CResponeBindMobile::writeTo(CJceOutputStream& paramJceOutputStream)
{
}
