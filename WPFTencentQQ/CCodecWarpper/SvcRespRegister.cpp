#include "StdAfx.h"
#include "SvcRespRegister.h"


CSvcRespRegister::CSvcRespRegister(void)
{
}


CSvcRespRegister::~CSvcRespRegister(void)
{
}


void CSvcRespRegister::readFrom(CJceInputStream& paramd)
{
	paramd.read(&lUin, 0, true);
    paramd.read(&lBid, 1, true);
    paramd.read(&cReplyCode, 2, true);
    paramd.read(&strResult,3, true);
    paramd.read(&lServerTime, 4, false);
    paramd.read(&bLogQQ, 5, false);
    paramd.read(&bNeedKik, 6, false);
    paramd.read(&bUpdateFlag, 7, false);
    paramd.read(&timeStamp, 8, false);
    paramd.read(&bCrashFlag, 9, false);
    paramd.read(&strClientIP,10, false);
    paramd.read(&iClientPort, 11, false);
    paramd.read(&iHelloInterval, 12, false);
    paramd.read(&iLargeSeq, 13, false);
    paramd.read(&bLargeSeqUpdate, 14, false);
}
void CSvcRespRegister::writeTo(CJceOutputStream& paramJceOutputStream)
{
}