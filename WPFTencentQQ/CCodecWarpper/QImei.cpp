#include "StdAfx.h"
#include "QImei.h"


QImei::QImei(void)
{
}


QImei::~QImei(void)
{
}


void QImei::readFrom(CJceInputStream& paramd)
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
}

void QImei::writeTo(CJceOutputStream& paramd)
{
}