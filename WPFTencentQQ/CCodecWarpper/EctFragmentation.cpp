#include "StdAfx.h"
#include "EctFragmentation.h"


CEctFragmentation::CEctFragmentation(void)
{
}


CEctFragmentation::~CEctFragmentation(void)
{
}

void CEctFragmentation::readFrom(CJceInputStream& paramd)
{
}
void CEctFragmentation::writeTo(CJceOutputStream& paramJceOutputStream)
{
    paramJceOutputStream.write(&iTotalNum, 0);
    paramJceOutputStream.write(&iSelfIndex, 1);
}