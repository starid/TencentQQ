#include "StdAfx.h"
#include "NeighborCommReqHeader.h"


CNeighborCommReqHeader::CNeighborCommReqHeader(void)
{
}


CNeighborCommReqHeader::~CNeighborCommReqHeader(void)
{
}

void CNeighborCommReqHeader::readFrom(CJceInputStream& paramd)
{
}
void CNeighborCommReqHeader::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&shVersion, 0);
	paramJceOutputStream.write(&lMID, 1);
	paramJceOutputStream.write(&iAppID, 2);
	paramJceOutputStream.write(&eBusiType, 3);
	paramJceOutputStream.write(&eMqqSysType, 4);
	paramJceOutputStream.write(&uClientIp, 5);
	paramJceOutputStream.write(&uClientPort, 6);
}