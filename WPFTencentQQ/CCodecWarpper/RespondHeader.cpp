#include "StdAfx.h"
#include "RespondHeader.h"


CRespondHeader::CRespondHeader(void)
{
}


CRespondHeader::~CRespondHeader(void)
{
}

void CRespondHeader::readFrom(CJceInputStream& paramd)
{
	paramd.read(&ver,0,true);
	paramd.read(&cmd,1,true);
	paramd.read(&requestID,2,true);
	paramd.read(&account,3,true);
	paramd.read(&svrSeqNo,4,true);
	paramd.read(&result,5,true);
	paramd.read(&ksid,6,true);
	paramd.read(&tips,7,true);
}
void CRespondHeader::writeTo(CJceOutputStream& paramJceOutputStream)
{
}
