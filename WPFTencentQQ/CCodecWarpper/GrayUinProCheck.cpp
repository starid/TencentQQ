#include "StdAfx.h"
#include "GrayUinProCheck.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamOut.h"
#include"UinCheck.h"
#include"UniPacket.h"


CGrayUinProCheck::CGrayUinProCheck(void)
{
}


CGrayUinProCheck::~CGrayUinProCheck(void)
{
}

ByteBuffer CGrayUinProCheck::Encode()
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

void CGrayUinProCheck::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(sizeof(pConfig->tgt)+0x4));//Ìí¼Ótgt
	p.AddBuf((char*)pConfig->tgt,sizeof(pConfig->tgt));
	std::string str=STR_GrayUinPro_Check;
	p.AddDWord(htonl(0x4+str.size()));
	p.AddBuf(str.c_str(),str.size());
	p.AddDWord(htonl(0x4+pConfig->unknow1.size()));
	p.AddBuf(pConfig->unknow1.c_str(),pConfig->unknow1.size());
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

void CGrayUinProCheck::EncodeBody(CTXCommPack &p)
{
	//Ìí¼ÓUniPacket
	CStreamOut mStream1;
	//·â×°UinCheck
	CUinCheck mUinCheck;
	mUinCheck.a.value(CONST_FIXAPPID);
	std::string strQQ;
	char buf[0x20]={0};
	::ultoa(pConfig->qq_id,buf,10);
	strQQ=buf;
	mUinCheck.b.value(strQQ);
	mUinCheck.c.value("");
	mUinCheck.d.value("");
	mStream1.write(&mUinCheck,0);

	JCE::JCEString key1;
	key1.value("req");
	JCE::JCEByteArray *p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	JCE::JCEMap	Map1;
	Map1._value.insert(std::pair<JCE::JCEString,JCE::IObject*>(key1,p2));
	mStream1.clearbs();
	mStream1.write(&Map1,0);

	std::map<std::string,std::string> a;			//¿Õmap
	UniPacket mUniPacket(3,0,0,++mSeq,"KQQ.ConfigService.ConfigServantObj","ClientReq",mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}