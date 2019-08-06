#include "StdAfx.h"
#include "RequestUploadAddressBookV2.h"


CRequestUploadAddressBookV2::CRequestUploadAddressBookV2(void)
{
}


CRequestUploadAddressBookV2::~CRequestUploadAddressBookV2(void)
{
}

void CRequestUploadAddressBookV2::readFrom(CJceInputStream& paramd)
{
}
void CRequestUploadAddressBookV2::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&nextFlag, 0);
    paramJceOutputStream.write(&MobileUniqueNo, 1);
    paramJceOutputStream.write(&sessionSid, 2);
    paramJceOutputStream.write(&AddressBookList, 3);
}