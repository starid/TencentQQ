#include "StdAfx.h"
#include "ResponeUploadAddressBookV2.h"
#include"MobileContactsFriendInfo.h"
#include"MobileContactsNotFriendInfo.h"


CResponeUploadAddressBookV2::CResponeUploadAddressBookV2(void)
{
}


CResponeUploadAddressBookV2::~CResponeUploadAddressBookV2(void)
{
}

void CResponeUploadAddressBookV2::readFrom(CJceInputStream& paramd)
{
	paramd.read(&nextFlag,0,true);
	paramd.read(&sessionSid,1,true);
	if(BindFriendContacts._value.size()==0)
	{
		BindFriendContacts._value.push_back(new CMobileContactsFriendInfo());
	}
	paramd.read(&BindFriendContacts,2,true);
	if(BindNotFriendContacts._value.size()==0)
	{
		BindNotFriendContacts._value.push_back(new CMobileContactsNotFriendInfo());
	}
	paramd.read(&BindNotFriendContacts,3,true);
	paramd.read(&MaxsignTimeStamp,4,false);
	paramd.read(&timeStamp,5,true);
}
void CResponeUploadAddressBookV2::writeTo(CJceOutputStream& paramJceOutputStream)
{
}
