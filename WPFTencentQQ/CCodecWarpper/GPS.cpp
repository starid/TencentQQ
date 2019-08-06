#include "StdAfx.h"
#include "GPS.h"


CGPS::CGPS(void)
{
	iLat.value(900000000);
	iLon.value(900000000);
	iAlt.value(-10000000);
	eType.value(0);
}


CGPS::~CGPS(void)
{
}

void CGPS::readFrom(CJceInputStream& paramd)
{
}
void CGPS::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&iLat, 0);
    paramJceOutputStream.write(&iLon, 1);
    paramJceOutputStream.write(&iAlt, 2);
    paramJceOutputStream.write(&eType, 3);
}
