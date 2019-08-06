#include "StdAfx.h"
#include "SDKConfReq.h"


SDKConfReq::SDKConfReq(void)
{
}


SDKConfReq::~SDKConfReq(void)
{
}

void SDKConfReq::readFrom(CJceInputStream& paramd)
{
}
void SDKConfReq::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&a,1);
    paramJceOutputStream.write(&b, 2);
	paramJceOutputStream.write(&c,3);
    paramJceOutputStream.write(&d, 4);
	paramJceOutputStream.write(&e, 5);
}