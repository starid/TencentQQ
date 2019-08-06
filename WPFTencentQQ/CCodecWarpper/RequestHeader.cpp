#include "StdAfx.h"
#include "RequestHeader.h"


CRequestHeader::CRequestHeader(void)
{
}

CRequestHeader::CRequestHeader(int paramInt1, int paramInt2, int paramInt3, int paramInt4, std::string paramString1, int paramInt5, 
		std::string paramString2, std::string paramString3, std::string paramString4, long paramLong, int paramInt6)
{
	ver.value(paramInt1);
	cmd.value(paramInt2);
	requestID.value(paramInt3);
    svrSeqNo.value(paramInt4);
	account.value(paramString1);
	appid.value(paramInt5);
	sbid.value(paramString2);
	channel_id.value(paramString3);
	ksid.value(paramString4);
	uin.value(paramLong);
	assistImport.value(paramInt6);
}

CRequestHeader::~CRequestHeader(void)
{
}

void CRequestHeader::readFrom(CJceInputStream& paramd)
{
}
void CRequestHeader::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&ver, 0);
    paramJceOutputStream.write(&cmd, 1);
    paramJceOutputStream.write(&requestID, 2);
    paramJceOutputStream.write(&svrSeqNo, 3);
    paramJceOutputStream.write(&account, 4);
    paramJceOutputStream.write(&appid, 5);
    paramJceOutputStream.write(&sbid, 6);
    paramJceOutputStream.write(&channel_id, 7);
    paramJceOutputStream.write(&ksid, 8);
    paramJceOutputStream.write(&uin, 9);
    paramJceOutputStream.write(&assistImport, 10);
}