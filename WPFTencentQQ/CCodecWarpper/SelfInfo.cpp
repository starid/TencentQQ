#include "StdAfx.h"
#include "SelfInfo.h"


CSelfInfo::CSelfInfo(void)
{
}


CSelfInfo::~CSelfInfo(void)
{
}

void CSelfInfo::readFrom(CJceInputStream& paramd)
{
}
void CSelfInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&cSex, 0);
}