#include "StdAfx.h"
#include "OidbSvc_0x7a2_0.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamOut.h"
#include"SvcReqRegister.h"
#include"UniPacket.h"
#include<time.h>
#include"../CipherLib/Md5.h"


COidbSvc_0x7a2_0::COidbSvc_0x7a2_0(void)
{
}


COidbSvc_0x7a2_0::~COidbSvc_0x7a2_0(void)
{
}

ByteBuffer COidbSvc_0x7a2_0::Encode()
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

void COidbSvc_0x7a2_0::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddByte(0x67);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(sizeof(pConfig->tgt)+0x4));//Ìí¼Ótgt
	p.AddBuf((char*)pConfig->tgt,sizeof(pConfig->tgt));

	std::string str=STR_OidbSvc_0x7a2_0;
	p.AddDWord(htonl(0x4+str.size()));
	p.AddBuf(str.c_str(),str.size());
	p.AddDWord(htonl(0x4+pConfig->unknow1.size()));
	p.AddBuf(pConfig->unknow1.c_str(),pConfig->unknow1.size());
	p.AddDWord(htonl(0x4+pConfig->mHardware.DEFAULT_DEVICE_ID.size()));
	p.AddBuf(pConfig->mHardware.DEFAULT_DEVICE_ID.c_str(),pConfig->mHardware.DEFAULT_DEVICE_ID.size());
	p.AddDWord(htonl(0x14));

	std::string strImeiMac;
	strImeiMac.append(pConfig->mHardware.DEFAULT_DEVICE_ID);
	strImeiMac.append(pConfig->mHardware.DEFAULT_WIFI_MAC);
	unsigned char md5buf[0x10]={0};
	CMd5 md5;
	md5.GetMd5(md5buf,sizeof(md5buf),(unsigned char*)strImeiMac.c_str(),strImeiMac.size());

	p.AddBuf((char*)md5buf,sizeof(md5buf));
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

void COidbSvc_0x7a2_0::EncodeBody(CTXCommPack &p)
{
		char buf[]={0x00,
0x00,0x00,0x0f,0x08,0xa2,0x0f,0x10,0x00,0x18,0x00,0x22,0x02,0x28,0x01};
		p.AddBuf(buf,sizeof(buf));
}