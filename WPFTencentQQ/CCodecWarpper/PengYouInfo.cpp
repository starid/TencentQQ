#include "StdAfx.h"
#include "PengYouInfo.h"


CPengYouInfo::CPengYouInfo(void)
{
}


CPengYouInfo::~CPengYouInfo(void)
{
}

void CPengYouInfo::readFrom(CJceInputStream& paramd)
{
}

void CPengYouInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&strPYName, 0);
    paramJceOutputStream.write(&strPYFaceUrl, 1);
}
