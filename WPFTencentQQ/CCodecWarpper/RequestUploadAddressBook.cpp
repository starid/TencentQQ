#include "StdAfx.h"
#include "RequestUploadAddressBook.h"


CRequestUploadAddressBook::CRequestUploadAddressBook(void)
{
}


CRequestUploadAddressBook::~CRequestUploadAddressBook(void)
{
}

void CRequestUploadAddressBook::readFrom(CJceInputStream& paramd)
{
}
void CRequestUploadAddressBook::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&nextFlag, 0);
    paramJceOutputStream.write(&MobileUniqueNo, 1);
    paramJceOutputStream.write(&sessionSid, 2);
    paramJceOutputStream.write(&AddressBookList, 3);
}