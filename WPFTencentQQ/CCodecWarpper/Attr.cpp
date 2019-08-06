#include "StdAfx.h"
#include "Attr.h"


CAttr::CAttr(void)
{
}


CAttr::~CAttr(void)
{
}

void CAttr::readFrom(CJceInputStream& paramd)
{
}
void CAttr::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&strImei, 0);
    paramJceOutputStream.write(&strImsi, 1);
	paramJceOutputStream.write(&strPhonenum, 2);
}