#include "StdAfx.h"
#include "RequestUpdateAddressBook.h"


CRequestUpdateAddressBook::CRequestUpdateAddressBook(void)
{
}


CRequestUpdateAddressBook::~CRequestUpdateAddressBook(void)
{
}

void CRequestUpdateAddressBook::readFrom(CJceInputStream& paramd)
{
}
void CRequestUpdateAddressBook::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&nextFlag, 0);
    paramJceOutputStream.write(&MobileUniqueNo, 1);
    paramJceOutputStream.write(&sessionSid, 2);
    paramJceOutputStream.write(&AddressBookAddList, 3);
	 paramJceOutputStream.write(&AddressBookDelList, 4);
}