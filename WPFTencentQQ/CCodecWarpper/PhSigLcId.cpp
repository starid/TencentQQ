#include "StdAfx.h"
#include "PhSigLcId.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamOut.h"
#include"SignatureReq.h"
#include"UniPacket.h"


CPhSigLcId::CPhSigLcId(void)
{
}


CPhSigLcId::~CPhSigLcId(void)
{
}

ByteBuffer CPhSigLcId::Encode()
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

void CPhSigLcId::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(0xFFFFFFFF));
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	std::string str=STR_PhSigLcId_Check;
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

void CPhSigLcId::EncodeBody(CTXCommPack &p)
{
	//Ìí¼ÓUniPacket
	CStreamOut mStream1;
	//·â×°SignatureReq
	SignatureReq mSigReq;
	JCE::JCEString *p1=static_cast<JCE::JCEString *>(mStream1.ObjectAlloc(JCETypeJCEString));
	p1->value(SIG_HASH);
	mSigReq.a._value.push_back(p1);
	mSigReq.b=JCE::JCEInt(htonl(CONST_FIXAPPID));
	p1=static_cast<JCE::JCEString *>(mStream1.ObjectAlloc(JCETypeJCEString));
	std::string str;
	str.push_back(0x30);
	p1->value(str);
	mSigReq.c._value.push_back(p1);
	mSigReq.d=JCE::JCEChar(0);
	mStream1.write(&mSigReq,0);

	JCE::JCEString key1;
	key1.value("KQQConfig.SignatureReq");
	JCE::JCEByteArray *p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	JCE::JCEMap*	pMap;
	pMap=static_cast<JCE::JCEMap *>(mStream1.ObjectAlloc(JCETypeJCEMap));
	pMap->_value.insert(std::pair<JCE::JCEString,JCE::IObject*>(key1,p2));
	key1.value("req");
	JCE::JCEMap		 map2;
	map2._value.insert(std::pair<JCE::JCEString,JCE::IObject*>(key1,pMap));
	mStream1.clearbs();
	mStream1.write(&map2,0);

	std::map<std::string,std::string> a;			//¿Õmap
	UniPacket mUniPacket(2,0,0,0,"KQQConfig","SignatureReq",mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}