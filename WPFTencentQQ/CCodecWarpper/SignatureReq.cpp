#include "StdAfx.h"
#include "SignatureReq.h"


SignatureReq::SignatureReq(void)
{
}


SignatureReq::~SignatureReq(void)
{
}


void SignatureReq::readFrom(CJceInputStream& paramd)
{
}
void SignatureReq::writeTo(CJceOutputStream& paramJceOutputStream)
{
	paramJceOutputStream.write(&a,1);
    paramJceOutputStream.write(&b, 2);
	paramJceOutputStream.write(&c,3);
    paramJceOutputStream.write(&d, 4);
}
