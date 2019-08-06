#include "StdAfx.h"
#include "MobileContactsFriendInfo.h"


CMobileContactsFriendInfo::CMobileContactsFriendInfo(void)
{
}


CMobileContactsFriendInfo::~CMobileContactsFriendInfo(void)
{
}

void CMobileContactsFriendInfo::readFrom(CJceInputStream& paramd)
{
	paramd.read(&QQ, 0,true);
    paramd.read(&bindingDate, 1,false);
    paramd.read(&isRecommend, 2,false);
    paramd.read(&contactsInfoEncrypt, 3,true);
	paramd.read(&MobileNoMask, 4,true);
	paramd.read(&originBinder, 5,false);
	paramd.read(&accountAbi, 6,false);
}
void CMobileContactsFriendInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
}