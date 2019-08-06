#include "StdAfx.h"
#include "CommReq.h"
#include"CommHead.h"
#include <WinSock.h>
#include"ClassModel.h"
#include"SeqSerial.h"
#include"Protocol.h"


CCommReq::CCommReq(void)
{
}

CCommReq::~CCommReq(void)
{
}

unsigned int CCommReq::PackHead(CTXCommPack *p)
{
	Protocol *pProtocol = Protocol::GetInstance();
	CSeqSerial mSeqSerial;
	switch(GetPackType())
	{
		case Type001D:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type001D);
				hda.Hda.serial = htons(mSeqSerial.GetSeqSerial(Type001D));     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type01BB:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type01BB);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0134:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0134);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0002:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0002);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type00EC:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type00EC);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type00B9:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type00B9);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type00D1:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type00D1);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0001:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0001);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0058:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0058);
				hda.Hda.serial = htons(mSeqSerial.GetSeqSerial(Type0058));
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0062:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0062);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0027:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0027);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0195:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0195);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type019B:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type019B);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type01A5:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type01A5);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type01AE:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type01AE);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type07FF:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type07FF);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type00D4:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type00D4);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type005C:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type005C);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type000D:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type000D);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type00CD:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type00CD);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0017:
			{
				CCommHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code = htons(Type00CD);
				hda.Hda.serial = htons(ptoPackArgus->seq());     //随机序号
				hda.Hda.qq_id = htonl(pConfig->qq_id);
				hda.Hda.fix[0] = 0x2;
				hda.Hda.fix[1] = 0;
				hda.Hda.fix[2] = 0;
				hda.Hda.unknown1 = htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				p->AddBuf((char*)&hda.Hda, sizeof(hda.Hda));
			}break;
	}
	return 0;
}

unsigned int CCommReq::PackBody(CTXCommPack *p)
{
	CTXCommPack *p1=NULL;
	switch(GetPackType())
	{
		case Type001D:
		case Type01BB:
			{
				p1 = new CTXCommPack();
				p1->AddBuf(ptoPackArgus->msg().c_str(), ptoPackArgus->msg().size());
			}break;
		case Type0134:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x000001A0));
				p1->AddDWord(htonl(0x59BB31CE));
				p1->AddByte(0x00);
				p1->AddByte(0x00);
				p1->AddWord(htons(0x03E8));
				p1->AddWord(htons(0x0010));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
			}break;
		case Type0017:
			{
				p1 = new CTXCommPack();
				p1->AddBuf(ptoPackArgus->msg().c_str(), ptoPackArgus->msg().size());
			}break;
		case Type0002:
			{
				//e3 90 36 cf(F7 09 BF B1)为0134返回数据包中数据
				//if(this->pAttach==NULL) return -1;
				//int *m=static_cast<int*>(this->pAttach);		//0134返回数据
				//p1=new CTXCommPack();
				//p1->AddByte(0x72);
				//p1->AddDWord(htonl(*m));
				//p1->AddDWord(htonl(0x00000000));
			}break;
		case Type00EC:
			{
				p1=new CTXCommPack();
				p1->AddByte(0x01);
				p1->AddByte(0x00);
				p1->AddByte(BeCallMeValue);    //此处首次登陆默认为"Q我吧"状态
				p1->AddDWord(htonl(0x00010001));
				p1->AddDWord(htonl(0x00040000));
				p1->AddWord(htons(0x0000));
			}break;
		case Type00B9:
			{
				unsigned char s[]={
				0x13,0x44,0x00,0x00,0x00,0x00,0x3c,0x00,0x0e,0xff,0xb1,0x00,0x00,0x00,0x3e,0x01,
0x00,0xff,0xb1,0x00,0x00,0x00,0x3e,0x02,0x00,0x08,0x25,0x00,0x00,0x00,0x6d,0x01,
0x00,0x08,0x25,0x00,0x00,0x00,0x8c,0x02,0x00,0x08,0x36,0x00,0x00,0x00,0x9c,0x01,
0x00,0x08,0x36,0x00,0x00,0x00,0xbb,0x02,0x00,0x08,0x36,0x00,0x00,0x00,0xbb,0x01,
0x00,0x08,0x36,0x00,0x00,0x00,0xdb,0x02,0x00,0x08,0x28,0x00,0x00,0x01,0xa6,0x01,
0x00,0x08,0x28,0x00,0x00,0x01,0xd5,0x02,0x00,0x01,0x34,0x00,0x00,0x01,0xf4,0x01,
0x00,0x01,0x34,0x00,0x00,0x02,0x32,0x02,0x00,0x00,0xec,0x00,0x00,0x02,0x32,0x01,
0x00,0x00,0xec,0x00,0x00,0x02,0x61,0x02,0x00,0xfb,0x2b,0x42,0x49
				};
				p1=new CTXCommPack();
				p1->AddBuf((char*)s,sizeof(s));
			}break;
	/*	case Type00B9:
			{
				unsigned char s[]={
					0x13,0x85,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x6f,0xa1,0x58,0x0b,
0x1f,0x40,0x01,0x00,0x23,0xca,0xf7,0x85
				};
				p1=new CTXCommPack();
				p1->AddBuf((char*)s,sizeof(s));
			}break;*/
		case Type00D1:
			{
				p1=new CTXCommPack();
				//0D 03 04 06 07 08 0A 0B 0C 0D 0E 0F 10 24
				p1->AddDWord(htonl(0x0D030406));
				p1->AddDWord(htonl(0x07080A0B));
				p1->AddDWord(htonl(0x0C0D0E0F));
				p1->AddWord(htons(0x1024));
			}break;
		case Type0001:
			{
				p1=new CTXCommPack();
				//20 01 00 00 00 00 01 00 00
				p1->AddByte(0x20);
				p1->AddDWord(htonl(0x01000000));
				p1->AddDWord(htonl(0x00010000));
			}break;
		case Type0058:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(pConfig->qq_id));	//此数据包存在问题，封包数据不确定
				//p1->AddByte(0x01);
				//p1->AddByte(0x02);
				//p1->AddDWord(htonl(0x00000000));
				//p1->AddDWord(htonl(0x00000000));
			}break;
		case Type0062:
			{
				p1=new CTXCommPack();
				//00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
			}break;
		case Type0027:
			{
				p1=new CTXCommPack();
				//02 00 00 00 00
				p1->AddByte(0x02);
				p1->AddDWord(htonl(0x00000000));
			}break;
		case Type0195:
			{
				p1=new CTXCommPack();
				//01 01 00 00 00 00 01 00 00
				p1->AddByte(0x01);
				p1->AddDWord(htonl(0x01000000));
				p1->AddDWord(htonl(0x00010000));
			}break;
		case Type019B:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x01000000));
				p1->AddDWord(htonl(0x00010000));
			}break;
		case Type01A5:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x01000000));
				p1->AddDWord(htonl(0x00010000));
			}break;
		case Type01AE:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x19000000));
				p1->AddDWord(htonl(0x00000102));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
			}break;
		case Type07FF:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x01000000));
				p1->AddDWord(htonl(0x00010008));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
			}break;
		case Type00D4:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(pConfig->qq_id));
			}break;
		//case Type00D4:
		//	{
		//		p1=new CTXCommPack();
		//		p1->AddDWord(htonl(pConfig->qq_id));
		//		p1->AddDWord(htonl(0x000B000C));
		//		p1->AddDWord(htonl(0x000D000E));
		//		p1->AddWord(htons(0x000F));
		//	}break;
		//case Type00D4:
		//	{
		//		p1=new CTXCommPack();
		//		p1->AddDWord(htonl(pConfig->qq_id));
		//		p1->AddWord(htons(0x0010));
		//	}break;
		case Type005C:
			{
				p1=new CTXCommPack();
				p1->AddByte(0x88);
				p1->AddDWord(htonl(pConfig->qq_id));
				p1->AddByte(0x00);       //或01
			}break;
		case Type003E:
			{
				p1=new CTXCommPack();
				p1->AddByte(0x0E);
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddWord(htons(0x0000));
			}break;
		case Type000D:
			{
				p1=new CTXCommPack();
				switch(pConfig->mStatus)
				{
				case BeOnLine:
					{
						p1->AddByte(BeOnLineValue);
					}break;
				case BeCallMe:
					{
						p1->AddByte(BeCallMeValue);
					}break;
				case BeLeave:
					{
						p1->AddByte(BeLeaveValue);
					}break;
				case BeBusy:
					{
						p1->AddByte(BeBusyValue);
					}break;
				case BeNoTrouble:
					{
						p1->AddByte(BeNoTroubleValue);
					}break;
				case BeInvisible:
					{
						p1->AddByte(BeInvisibleValue);
					}break;
				default:
					{
					}break;
				}
				p1->AddWord(htons(0x0000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
			}break;
		case Type00CD:
			{
			}break;
		default:
		{
			return -1;
		}break;
	}
	p->AddBuf((char*)p1->buffer.contents(),p1->buffer.size());
	delete p1;
	p1=NULL;
	return 0;
}

unsigned int CCommReq::PackData()
{
	//封装StarMark
	pack.clear();
	pack.append((char)StartMark);

	//封装头部数据
	CTXCommPack p1;
	unsigned int ret=PackHead(&p1);
	if(ret!=0)
	{
		return ret;
	}
	pack.append<ByteBuffer>(p1.buffer);


	//封装body数据
	CTXCommPack p2;
	ret=PackBody(&p2);
	if(ret!=0)
	{
		return ret;
	}
	//对body加密
	unsigned char *dst=NULL;
	unsigned int bytes=0;

	unsigned int dstlen=p2.buffer.size()+0x12;              //添加0x12固定长度
	dst=(unsigned char *)malloc(dstlen);
	memset(dst,0,dstlen);
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->SessionKey,dst,&bytes);

	pack.append(dst,bytes);
	free(dst);
	dst=NULL;
	//封装EndMark
	pack.append((char)EndMark);
	return 0;
}
