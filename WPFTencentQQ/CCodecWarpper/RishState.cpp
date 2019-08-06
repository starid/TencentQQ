#include "StdAfx.h"
#include "RishState.h"


CRishState::CRishState(void)
{
}


CRishState::~CRishState(void)
{
}


void CRishState::readFrom(CJceInputStream& paramd)
{
	paramd.read(&vState,0,true);
	paramd.read(&uModifyTime,1,false);
}

void CRishState::writeTo(CJceOutputStream& paramJceOutputStream)
{
}
