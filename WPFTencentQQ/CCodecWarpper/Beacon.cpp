#include "StdAfx.h"
#include "Beacon.h"


void Beacon::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,1,true);
	paramd.read(&f,2,true);
	paramd.read(&g,3,true);
	paramd.read(&b,4,true);
	paramd.read(&c,5,true);
	paramd.read(&d,6,true);
	paramd.read(&e,7,true);
	paramd.read(&h,8,true);
	paramd.read(&i,9,true);
	paramd.read(&i,10,true);
}
void Beacon::writeTo(CJceOutputStream& paramd)
{
}