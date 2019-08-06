#include "StdAfx.h"
#include "LBSInfo.h"


CLBSInfo::CLBSInfo(void)
{
}


CLBSInfo::~CLBSInfo(void)
{
}

void CLBSInfo::readFrom(CJceInputStream& paramd)
{
}
void CLBSInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&stGps, 0);
	if(vWifis._value.size()!=0)
		paramJceOutputStream.write(&vWifis, 1);
	if(vCells._value.size()!=0)
		paramJceOutputStream.write(&vCells, 2);
	paramJceOutputStream.write(&stAttr, 3);
}