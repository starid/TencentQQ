#include "StdAfx.h"
#include "MobileContactsNotFriendInfo.h"


CMobileContactsNotFriendInfo::CMobileContactsNotFriendInfo(void)
{
}


CMobileContactsNotFriendInfo::~CMobileContactsNotFriendInfo(void)
{
}

void CMobileContactsNotFriendInfo::readFrom(CJceInputStream& paramd)
{
	paramd.read(&bindingDate, 0,false);
    paramd.read(&isRecommend, 1,false);
    paramd.read(&nickname, 2,false);
    paramd.read(&contactsInfoEncrypt, 3,true);
	paramd.read(&MobileNoMask, 4,true);
	paramd.read(&originBinder, 5,false);
	paramd.read(&accountAbi, 6,false);
	paramd.read(&conType, 7,false);
	paramd.read(&detalStatusFlag, 8,false);
	paramd.read(&iTermType, 9,false);
	paramd.read(&eNetworkType, 10,false);
	paramd.read(&strTermDesc, 11,false);
	paramd.read(&uAbiFlag, 12,false);
	paramd.read(&personalSign, 13,false);
	paramd.read(&isUpdateSign, 14,false);
	paramd.read(&richTime, 15,false);
	paramd.read(&isNew, 16,false);
}
void CMobileContactsNotFriendInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
}