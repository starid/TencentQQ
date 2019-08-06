#include "StdAfx.h"
#include "BeaconUploadReq.h"
#include"Beacon.h"
#include"Detail.h"
#include"StreamIn.h"

BeaconUploadReq::BeaconUploadReq(void)
{
}


BeaconUploadReq::~BeaconUploadReq(void)
{
}

void BeaconUploadReq::encode()
{
}

void BeaconUploadReq::decode(char*p,int cnt)
{
	if(cnt<4)
		return;
	CStreamIn mStream1(JCE::JCEByteArray(p+4,cnt-4));
	mStream1.setServerEncoding("GBK");
	Beacon mb;
	mb.readFrom(mStream1);
	CStreamIn mStream2(mb.e);
	JCE::JCEMap map;
	mStream2.read(&map,0,false);

	JCE::JCEString *strDetail=new JCE::JCEString();
	strDetail->value("detail");
	
	CStreamIn mStream3(*dynamic_cast<JCE::JCEByteArray*>(map._value[strDetail]));
	CDetail mDetail;
	mStream3.read(&mDetail,0,false);
	delete strDetail;
}