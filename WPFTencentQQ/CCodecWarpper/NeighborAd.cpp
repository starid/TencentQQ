#include "StdAfx.h"
#include "NeighborAd.h"


CNeighborAd::CNeighborAd(void)
{
}


CNeighborAd::~CNeighborAd(void)
{
}

void CNeighborAd::readFrom(CJceInputStream& paramd)
{
	paramd.read(&ad_item,0,true);
	paramd.read(&ad_postion,1,true);
	paramd.read(&ad_source,2,false);
}
void CNeighborAd::writeTo(CJceOutputStream& paramJceOutputStream)
{
}