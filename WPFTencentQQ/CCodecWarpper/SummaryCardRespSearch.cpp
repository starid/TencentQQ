#include "StdAfx.h"
#include "SummaryCardRespSearch.h"


CSummaryCardRespSearch::CSummaryCardRespSearch(void)
{
}


CSummaryCardRespSearch::~CSummaryCardRespSearch(void)
{
}

void CSummaryCardRespSearch::readFrom(CJceInputStream& paramd)
{
	paramd.read(&vRecords,0,true);
	paramd.read(&vSecureSig,1,false);
	paramd.read(&vvRespServices,2,false);
}
void CSummaryCardRespSearch::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&vRecords, 0);
    paramJceOutputStream.write(&vSecureSig, 1);
    paramJceOutputStream.write(&vvRespServices, 2);
}