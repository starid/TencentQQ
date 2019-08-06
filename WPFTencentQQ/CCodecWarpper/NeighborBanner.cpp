#include "StdAfx.h"
#include "NeighborBanner.h"


CNeighborBanner::CNeighborBanner(void)
{
}


CNeighborBanner::~CNeighborBanner(void)
{
}

void CNeighborBanner::readFrom(CJceInputStream& paramd)
{
	paramd.read(&description,0,true);
	paramd.read(&pic_url,1,true);
	paramd.read(&skip_url,2,true);
	paramd.read(&postion,3,true);
}
void CNeighborBanner::writeTo(CJceOutputStream& paramJceOutputStream)
{
}