#include "StdAfx.h"
#include "ConfigService.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamOut.h"
#include"SignatureReq.h"
#include"UniPacket.h"
#include"SDKConfReq.h"


CConfigService::CConfigService(void)
{
}


CConfigService::~CConfigService(void)
{
}

ByteBuffer CConfigService::Encode()
{
	CTXCommPack p1;
	EncodeHead(p1);
	CTXCommPack p2;
	EncodeBody(p2);

	mPack.AddByteBuffer(p1.buffer);
	p1.GetBufferOut();
	mPack.AddByteBuffer(p2.buffer);
	p2.GetBufferOut();

	return mPack.buffer;
}

void CConfigService::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(0xFFFFFFFF));
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	std::string str=SRT_ConfigService_ClientReq;
	p.AddDWord(htonl(0x4+str.size()));
	p.AddBuf(str.c_str(),str.size());
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	p.AddDWord(htonl(0x4+pConfig->mHardware.DEFAULT_DEVICE_ID.size()));
	p.AddBuf(pConfig->mHardware.DEFAULT_DEVICE_ID.c_str(),pConfig->mHardware.DEFAULT_DEVICE_ID.size());
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	CTXCommPack pack;
	pack.AddByte('|');
	pack.AddBuf(pConfig->mHardware.DEFAULT_IMSI.c_str(),pConfig->mHardware.DEFAULT_IMSI.size());
	pack.AddByte('|');
	str=CONST_QQ_VERSION;
	pack.AddBuf(str.c_str(),str.size());
	p.AddWord(htons(0x2+pack.buffer.size()));
	p.AddBuf((char*)pack.buffer.contents(),pack.buffer.size());
	pack.GetBufferOut();
	p.AddLenDWord();
}

void CConfigService::EncodeBody(CTXCommPack &p)
{
	//Ìí¼ÓUniPacket
	CStreamOut mStream1;
	//·â×°iCmdType
	JCE::JCEMap		 map1;
	JCE::JCEString key1;
	key1.value("iCmdType");
	JCE::JCEShort *p1=static_cast<JCE::JCEShort *>(mStream1.ObjectAlloc(JCETypeJCEShort));
	p1->value(0x20);
	JCE::JCEByteArray *p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	ByteBuffer b;
	b.append(htons(p1->value()));
	p2->value(b);
	map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&key1,p2));
	//·â×°SDKConfReq
	SDKConfReq	mSdkReq;
	mSdkReq.a.value(0);
	mSdkReq.b.value(0);
	mSdkReq.c._value.clear();
	mSdkReq.d.value(0);
	mSdkReq.e.value(1);
	mStream1.write(&mSdkReq,0);
	key1.value("SDKConfReq");
	p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&key1,p2));
	mStream1.clearbs();
	mStream1.write(&map1,0);

	std::map<std::string,std::string> a;			//¿Õmap
	UniPacket mUniPacket(3,0,0,0,"KQQ.ConfigService.ConfigServantObj","ClientReq",mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}