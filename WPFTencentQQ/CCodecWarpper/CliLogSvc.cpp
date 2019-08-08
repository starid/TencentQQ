#include "StdAfx.h"
#include "CliLogSvc.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamOut.h"
#include"SignatureReq.h"
#include"UniPacket.h"
#include"SDKConfReq.h"
#include"StrupBuff.h"

CCliLogSvc::CCliLogSvc(void)
{
}


CCliLogSvc::~CCliLogSvc(void)
{
}

ByteBuffer CCliLogSvc::Encode()
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

void CCliLogSvc::EncodeHead(CTXCommPack &p)
{
	p.AddDWord(htonl(mSeq));//Seq
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddDWord(htonl(CONST_FIXAPPID));
	p.AddByte(0x1);
	char buf[0xB]={0};
	p.AddBuf(buf,sizeof(buf));
	p.AddDWord(htonl(0x4));//¿Õ×Ö·û´®
	std::string str=STR_CliLogSvc_UploadReq;
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

void CCliLogSvc::EncodeBody(CTXCommPack &p)
{
	//Ìí¼ÓUniPacket
	CStreamOut mStream1;
	//·â×°StrupBuff
	StrupBuff	mStrupBuff;
	//·â×°ÈÕÖ¾
	SYSTEMTIME stUTC;
	GetLocalTime(&stUTC);
	char chBuf[0x100]={0};
	sprintf(chBuf,"%u-%02u-%02u %02u:%02u:%02u",             
    stUTC.wYear, stUTC.wMonth, stUTC.wDay,
    stUTC.wHour, stUTC.wMinute, stUTC.wSecond);
	char bufFormat[0x200]={0};
	sprintf(bufFormat,STR_LOG_FORMAT,chBuf,pConfig->mHardware.DEFAULT_DEVICE_ID.c_str(),CONST_FIXAPPID);

	JCE::JCEByteArray *p1=new JCE::JCEByteArray();
	ByteBuffer b;
	b.append(bufFormat,strlen(bufFormat));
	p1->value(b);
	JCE::JCEListArray *p2=new JCE::JCEListArray();
	p2->_value.push_back(p1);

	JCE::JCEString	key1;
	key1.value("P_CliOper");
	mStrupBuff.a._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&key1,p2));
	mStrupBuff.b.value("");
	mStrupBuff.c.value(0x2);
	mStream1.write(&mStrupBuff,0);
	p1=new JCE::JCEByteArray();
	p1->value(mStream1.getByteBuffer());
	JCE::JCEMap map1;
	key1.value("Data");
	map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&key1,p1));
	mStream1.clearbs();
	mStream1.write(&map1,0);

	std::map<std::string,std::string> a;			//¿Õmap
	UniPacket mUniPacket(3,0,0,0,"QQService.CliLogSvc.MainServantObj","UploadReq",mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}