#include "StdAfx.h"
#include "RequestVerifyBindingSmscode.h"


CRequestVerifyBindingSmscode::CRequestVerifyBindingSmscode(void)
{
}


CRequestVerifyBindingSmscode::~CRequestVerifyBindingSmscode(void)
{
}

void CRequestVerifyBindingSmscode::readFrom(CJceInputStream& paramd)
{
}
void CRequestVerifyBindingSmscode::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&smsCode, 0);
	paramJceOutputStream.write(&sessionSid, 1);
	paramJceOutputStream.write(&type, 2);
}