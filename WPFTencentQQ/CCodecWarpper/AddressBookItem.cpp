#include "StdAfx.h"
#include "AddressBookItem.h"


CAddressBookItem::CAddressBookItem(void)
{
}


CAddressBookItem::~CAddressBookItem(void)
{
}

void CAddressBookItem::readFrom(CJceInputStream& paramd)
{
}
void CAddressBookItem::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&mobileNo, 0);
    paramJceOutputStream.write(&name, 1);
}
