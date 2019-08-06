#include "StdAfx.h"
#include "InfoB.h"


InfoB::InfoB(void)
{
}


InfoB::~InfoB(void)
{
}

void InfoB::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,false);
	paramd.read(&c,2,false);
	paramd.read(&d,3,false);
}

void InfoB::writeTo(CJceOutputStream& paramd)
{
}