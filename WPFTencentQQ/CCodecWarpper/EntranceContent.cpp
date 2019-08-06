#include "StdAfx.h"
#include "EntranceContent.h"


CEntranceContent::CEntranceContent(void)
{
}


CEntranceContent::~CEntranceContent(void)
{
}

void CEntranceContent::readFrom(CJceInputStream& paramd)
{
	paramd.read(&type,0,true);
	paramd.read(&content_buff,1,true);
}
void CEntranceContent::writeTo(CJceOutputStream& paramJceOutputStream)
{
}