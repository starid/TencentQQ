#include "StdAfx.h"
#include "InfoC.h"


InfoC::InfoC(void)
{
}


InfoC::~InfoC(void)
{
}

void InfoC::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,true);
	paramd.read(&c,2,true);
	paramd.read(&d,3,true);
}

void InfoC::writeTo(CJceOutputStream& paramd)
{
}