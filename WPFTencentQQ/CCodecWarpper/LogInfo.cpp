#include "StdAfx.h"
#include "LogInfo.h"
#include "PacketType.h"


LogInfo::LogInfo(void)
{
}


LogInfo::~LogInfo(void)
{
}

void LogInfo::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,true);
	paramd.read(&c,2,true);
}

void LogInfo::writeTo(CJceOutputStream& paramd)
{
}