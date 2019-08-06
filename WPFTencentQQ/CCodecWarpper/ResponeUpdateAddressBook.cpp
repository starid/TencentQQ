#include "StdAfx.h"
#include "ResponeUpdateAddressBook.h"


CResponeUpdateAddressBook::CResponeUpdateAddressBook(void)
{
}


CResponeUpdateAddressBook::~CResponeUpdateAddressBook(void)
{
}

void CResponeUpdateAddressBook::readFrom(CJceInputStream& paramd)
{
	paramd.read(&nextFlag,0,true);
	paramd.read(&sessionSid,1,true);
}
void CResponeUpdateAddressBook::writeTo(CJceOutputStream& paramJceOutputStream)
{
}