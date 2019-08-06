#include "StdAfx.h"
#include "Strategy.h"
#include"PacketType.h"


CStrategy::CStrategy(void)
{
}


CStrategy::~CStrategy(void)
{
}

void CStrategy::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,true);
	paramd.read(&c,2,true);
	paramd.read(&d,3,false);
}

void CStrategy::writeTo(CJceOutputStream& paramd)
{
}