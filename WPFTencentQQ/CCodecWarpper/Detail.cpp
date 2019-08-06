#include "StdAfx.h"
#include "Detail.h"


CDetail::CDetail(void)
{
}


CDetail::~CDetail(void)
{
}


void CDetail::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,true);
	paramd.read(&c,2,true);
	paramd.read(&d,3,true);
	paramd.read(&e,4,true);
	paramd.read(&f,5,true);
	paramd.read(&g,6,true);
	paramd.read(&h,7,true);
	paramd.read(&i,8,true);
	paramd.read(&j,9,false);
	paramd.read(&k,10,false);
	paramd.read(&l,11,false);
}

void CDetail::writeTo(CJceOutputStream& paramd)
{
}
