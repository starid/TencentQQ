#include "StdAfx.h"
#include "SummaryCardRespHead.h"


CSummaryCardRespHead::CSummaryCardRespHead(void)
{
}


CSummaryCardRespHead::~CSummaryCardRespHead(void)
{
}

void CSummaryCardRespHead::readFrom(CJceInputStream& paramd)
{
}
void CSummaryCardRespHead::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&iVersion, 0);
	paramJceOutputStream.write(&iResult, 1);
	paramJceOutputStream.write(&strErrorMsg, 2);
	paramJceOutputStream.write(&vCookies, 3);
}