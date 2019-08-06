#include "StdAfx.h"
#include "EventLog.h"
#include "../JceProtocol/JCEType.h"


CEventLog::CEventLog(void)
{
}


CEventLog::~CEventLog(void)
{
}

void CEventLog::readFrom(CJceInputStream& paramd)
{
	paramd.read(&a,0,true);
	paramd.read(&b,1,true);
	paramd.read(&c,2,true);
	paramd.read(&d,3,true);
	paramd.read(&e,4,false);
	paramd.read(&f,5,false);
	paramd.read(&g,6,false);
}

void CEventLog::writeTo(CJceOutputStream& paramd)
{
}