#include "StdAfx.h"
#include "ResponeUploadAddressBook.h"


CResponeUploadAddressBook::CResponeUploadAddressBook(void)
{
}


CResponeUploadAddressBook::~CResponeUploadAddressBook(void)
{
}
void CResponeUploadAddressBook::readFrom(CJceInputStream& paramd)
{
	paramd.read(&nextFlag,0,true);
	paramd.read(&sessionSid,1,true);
}
void CResponeUploadAddressBook::writeTo(CJceOutputStream& paramJceOutputStream)
{
}
