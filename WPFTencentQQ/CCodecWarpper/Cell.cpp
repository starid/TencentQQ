#include "StdAfx.h"
#include "Cell.h"


CCell::CCell(void)
{
	shMcc.value(-1);
	shMnc.value(-1);
	iLac.value(-1);
	iCellId.value(-1);
}


CCell::~CCell(void)
{
}


void CCell::readFrom(CJceInputStream& paramd)
{
}

void CCell::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&shMcc, 0);
    paramJceOutputStream.write(&shMnc, 1);
    paramJceOutputStream.write(&iLac, 2);
    paramJceOutputStream.write(&iCellId, 3);
}