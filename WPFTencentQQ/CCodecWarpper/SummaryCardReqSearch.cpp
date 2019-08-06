#include "StdAfx.h"
#include "SummaryCardReqSearch.h"


CSummaryCardReqSearch::CSummaryCardReqSearch(void)
{
}


CSummaryCardReqSearch::~CSummaryCardReqSearch(void)
{
}

void CSummaryCardReqSearch::readFrom(CJceInputStream& paramd)
{
}
void CSummaryCardReqSearch::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&strKeyword, 0);
    paramJceOutputStream.write(&strCountryCode, 1);
    paramJceOutputStream.write(&shVersion, 2);
    paramJceOutputStream.write(&vvReqServices, 3);
}