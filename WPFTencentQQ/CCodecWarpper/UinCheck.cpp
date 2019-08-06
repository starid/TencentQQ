#include "StdAfx.h"
#include "UinCheck.h"


CUinCheck::CUinCheck(void)
{
}


CUinCheck::~CUinCheck(void)
{
}

void CUinCheck::readFrom(CJceInputStream& paramd)
{
}

void CUinCheck::writeTo(CJceOutputStream& paramd)
{
	paramd.write(&a,1);
	paramd.write(&b,2);
	paramd.write(&c,3);
	paramd.write(&d,4);
}