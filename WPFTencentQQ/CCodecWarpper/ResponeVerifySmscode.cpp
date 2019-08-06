#include "StdAfx.h"
#include "ResponeVerifySmscode.h"


CResponeVerifySmscode::CResponeVerifySmscode(void)
{
}


CResponeVerifySmscode::~CResponeVerifySmscode(void)
{
}

void CResponeVerifySmscode::readFrom(CJceInputStream& paramd)
{
	paramd.read(&sessionSid,0,true);
}
void CResponeVerifySmscode::writeTo(CJceOutputStream& paramJceOutputStream)
{
}