#include "StdAfx.h"
#include "InfoF.h"


InfoF::InfoF(void)
{
}


InfoF::~InfoF(void)
{
}

void InfoF::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,true);
	paramd.read(&c,2,true);
	paramd.read(&d,3,true);
}

void InfoF::writeTo(CJceOutputStream& paramd)
{
}