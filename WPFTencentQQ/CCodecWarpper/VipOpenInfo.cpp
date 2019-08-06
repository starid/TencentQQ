#include "StdAfx.h"
#include "VipOpenInfo.h"


CVipOpenInfo::CVipOpenInfo(void)
{
}


CVipOpenInfo::~CVipOpenInfo(void)
{
}

void CVipOpenInfo::readFrom(CJceInputStream& paramd)
{
	paramd.read(&bOpen,0,true);
	paramd.read(&iVipType,1,true);
	paramd.read(&iVipLevel,2,true);
	paramd.read(&iVipFlag,3,false);

}
void CVipOpenInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
}