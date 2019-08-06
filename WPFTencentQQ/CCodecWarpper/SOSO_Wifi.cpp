#include "StdAfx.h"
#include "SOSO_Wifi.h"


CSOSO_Wifi::CSOSO_Wifi(void)
{
	lMac.value(-1);
	shRssi.value(0);
}


CSOSO_Wifi::~CSOSO_Wifi(void)
{
}

void CSOSO_Wifi::readFrom(CJceInputStream& paramd)
{
}
void CSOSO_Wifi::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&lMac, 0);
    paramJceOutputStream.write(&shRssi, 1);
}