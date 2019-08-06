#include "StdAfx.h"
#include "RespondQueryQQBindingStat.h"


CRespondQueryQQBindingStat::CRespondQueryQQBindingStat(void)
{
}


CRespondQueryQQBindingStat::~CRespondQueryQQBindingStat(void)
{
}

void CRespondQueryQQBindingStat::readFrom(CJceInputStream& paramd)
{
	paramd.read(&nationCode,0,true);
	paramd.read(&mobileNo,1,true);
	paramd.read(&MobileUniqueNo,2,true);
	paramd.read(&isRecommend,3,true);
	paramd.read(&originBinder,4,true);
	paramd.read(&bindingTime,5,false);
	paramd.read(&lastUsedFlag,6,false);
	paramd.read(&type,7,false);
}
void CRespondQueryQQBindingStat::writeTo(CJceOutputStream& paramJceOutputStream)
{
}