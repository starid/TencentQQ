#include "StdAfx.h"
#include "SOSO_Cell.h"


CSOSO_Cell::CSOSO_Cell(void)
{
	shMcc.value(-1);
	shMnc.value(-1);
	iLac.value(-1);
	iCellId.value(-1);
	shRssi.value(0);
}


CSOSO_Cell::~CSOSO_Cell(void)
{
}

void CSOSO_Cell::readFrom(CJceInputStream& paramd)
{
}
void CSOSO_Cell::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&shMcc, 0);
    paramJceOutputStream.write(&shMnc, 1);
	paramJceOutputStream.write(&iLac, 2);
	paramJceOutputStream.write(&iCellId, 3);
	paramJceOutputStream.write(&shRssi, 4);
}