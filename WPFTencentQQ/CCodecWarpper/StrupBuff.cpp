#include "StdAfx.h"
#include "StrupBuff.h"


StrupBuff::StrupBuff(void)
{
}


StrupBuff::~StrupBuff(void)
{
}

void StrupBuff::readFrom(CJceInputStream& paramd)
{
}
void StrupBuff::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&a,0);
    paramJceOutputStream.write(&b, 1);
	paramJceOutputStream.write(&c,2);
}