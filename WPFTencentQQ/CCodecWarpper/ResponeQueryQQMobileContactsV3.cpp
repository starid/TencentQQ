#include "StdAfx.h"
#include "ResponeQueryQQMobileContactsV3.h"
#include "MobileContactsFriendInfo.h"
#include"MobileContactsNotFriendInfo.h"


CResponeQueryQQMobileContactsV3::CResponeQueryQQMobileContactsV3(void)
{
}


CResponeQueryQQMobileContactsV3::~CResponeQueryQQMobileContactsV3(void)
{
}


void CResponeQueryQQMobileContactsV3::readFrom(CJceInputStream& paramd)
{
	paramd.read(&nextFlag,0,true);
	paramd.read(&timeStamp,1,true);
	paramd.read(&sessionSid,2,true);
	paramd.read(&queryFlag,3,true);
	if(BindFriendContacts._value.size()==0)
	{
		BindFriendContacts._value.push_back(new CMobileContactsFriendInfo());
	}
	paramd.read(&BindFriendContacts,4,true);
	if(BindNotFriendContacts._value.size()==0)
	{
		BindNotFriendContacts._value.push_back(new CMobileContactsNotFriendInfo());
	}
	paramd.read(&BindNotFriendContacts,5,true);
	paramd.read(&nationCode,6,true);
	paramd.read(&mobileNo,7,true);
	paramd.read(&MobileUniqueNo,8,true);
	paramd.read(&isRecommend,9,true);
	paramd.read(&originBinder,10,true);
	paramd.read(&bindingTime,11,false);
	paramd.read(&lastUsedFlag,12,false);
	paramd.read(&type,13,false);
	paramd.read(&ConfigVersion,14,false);
	paramd.read(&PopWindowsCount,15,false);
	paramd.read(&PopWindowsTime,16,false);
	paramd.read(&PopCloseCount,17,false);
	paramd.read(&ForcePopSwitch,18,false);
	paramd.read(&nextQueryTimeInterval,19,false);
	paramd.read(&MaxsignTimeStamp,20,false);
}
void CResponeQueryQQMobileContactsV3::writeTo(CJceOutputStream& paramJceOutputStream)
{
}
