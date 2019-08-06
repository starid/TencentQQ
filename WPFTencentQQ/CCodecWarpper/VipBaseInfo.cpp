#include "StdAfx.h"
#include "VipBaseInfo.h"


CVipBaseInfo::CVipBaseInfo(void)
{
}


CVipBaseInfo::~CVipBaseInfo(void)
{
}

void CVipBaseInfo::readFrom(CJceInputStream& paramd)
{
	paramd.read(&mOpenInfo,0,true);

}
void CVipBaseInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
}