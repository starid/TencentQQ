#include "StdAfx.h"
#include "SummaryCardReqHead.h"


CSummaryCardReqHead::CSummaryCardReqHead(void)
{
}


CSummaryCardReqHead::~CSummaryCardReqHead(void)
{
}

void CSummaryCardReqHead::readFrom(CJceInputStream& paramd)
{
}
void CSummaryCardReqHead::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&iVersion, 0);
}