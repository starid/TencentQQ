#include "StdAfx.h"
#include "BeaconUploadResp.h"
#include "Beacon.h"
#include "QImei.h"
#include "../CipherLib/DesCrypt.h"
#include "StreamIn.h"
#include "Strategy.h"

BeaconUploadResp::BeaconUploadResp(void)
{
}


BeaconUploadResp::~BeaconUploadResp(void)
{
}

void BeaconUploadResp::encode()
{
}

void BeaconUploadResp::decode(char*p,int cnt)
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

	CStreamIn mStream3(*static_cast<JCE::JCEByteArray*>(map._value[strDetail]));
	delete strDetail;
	QImei mImei;
	mStream3.read(&mImei,0,false);

	CDesCrypt mDes(MODE_CBC);
	mDes.SetKey((unsigned char*)mImei.Geti().value().c_str(),mImei.Geti().value().length());
	mDes.SetIv((unsigned char*)mImei.Geti().value().c_str(),mImei.Geti().value().length());
	char *dst=new char[mImei.Getc().value().size()];
	mDes.Decrypt((unsigned char*)mImei.Getc().value().contents(),mImei.Getc().value().size(),(unsigned char*)dst);

	CStreamIn mStream4;
	mStream4.wrap((unsigned char*)dst,mImei.Getc().value().size());
	delete []dst;
	//∂¡»°list
	CStrategy mCStrategy;
	mCStrategy.readFrom(mStream4);
}