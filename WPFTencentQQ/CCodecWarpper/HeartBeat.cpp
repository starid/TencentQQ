#include "StdAfx.h"
#include "HeartBeat.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamOut.h"
#include"SignatureReq.h"
#include"UniPacket.h"
#include"SDKConfReq.h"


CHeartBeat::CHeartBeat(void)
{
}


CHeartBeat::~CHeartBeat(void)
{
}

ByteBuffer CHeartBeat::Encode()
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

void CHeartBeat::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(0xFFFFFFFF)); //»òÕßCONST_FIXAPPID£¬ÔÝÊ±Î´Öª
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	std::string str=STR_HeartBeat_Alive;
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
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	p.AddBufLenDWord();
}

void CHeartBeat::EncodeBody(CTXCommPack &p)
{

}