#include "StdAfx.h"
#include "RequestQueryQQBindingStat.h"


CRequestQueryQQBindingStat::CRequestQueryQQBindingStat(void)
{
}


CRequestQueryQQBindingStat::~CRequestQueryQQBindingStat(void)
{
}

void CRequestQueryQQBindingStat::readFrom(CJceInputStream& paramd)
{
}
void CRequestQueryQQBindingStat::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&MobileUniqueNo, 0);
}