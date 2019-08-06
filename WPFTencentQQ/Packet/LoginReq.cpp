#include "StdAfx.h"
#include "LoginReq.h"
#include <stdlib.h>
#include <WinSock.h>
#include<ctime>
#include "Packet.h"
#include"..\UtilLib\HelpFunc.h"
#include"..\CipherLib\Md5.h"
#include"SeqSerial.h"
#include"Protocol.h"

CLoginReq::CLoginReq(void)
{
}

CLoginReq::~CLoginReq(void)
{
}

unsigned int CLoginReq::PackHead(CTXCommPack *p)
{
	Protocol *pProtocol = Protocol::GetInstance();
	unsigned int len=0;	
	CSeqSerial mSeqSerial;
	switch(this->GetPackType())
	{
		case Type0825:
			{
				CLoginPingHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0825);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x3;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);   //dwClientType
				int ll = htonl(pProtocol->dwPubNo);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				hda.Hda.unknown3=0;
				memcpy(hda.Hda.key,pConfig->key0825,sizeof(hda.Hda.key));
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0836:
			{
				CLoginVerifyHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0836);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x3;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				hda.Hda.unknown3=0;
				len=sizeof(hda.Hda);
				p->AddBuf((char*)&(hda.Hda),len);

				p->AddWord(htons(0x0001));
				p->AddWord(htons(0x0103));
				
				CTXCommPack *pTmp=new CTXCommPack();
				pTmp->AddBuf((char*)(pConfig->stKey),sizeof(pConfig->stKey));
				pTmp->AddBufLenWord();
				p->AddBuf((char*)pTmp->buffer.contents(),pTmp->buffer.size());
				delete pTmp;
				pTmp=NULL;

				p->AddWord(htons(0x0000));

				pTmp=new CTXCommPack();
				pTmp->AddBuf((char*)this->pConfig->key0836,sizeof(this->pConfig->key0836));
				pTmp->AddBufLenWord();
				p->AddBuf((char*)pTmp->buffer.contents(),pTmp->buffer.size());
				delete pTmp;
				pTmp=NULL;

			}break;
		case Type0104:
			{
				CLoginTipHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0104);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x3;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				hda.Hda.unknown3=0;
				memcpy(hda.Hda.key,pConfig->key0104,sizeof(hda.Hda.key));
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type00BA:
			{
				CLoginCodeHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type00BA);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());     //随机序号
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x3;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				hda.Hda.unknown3=0;
				memcpy(hda.Hda.key,pConfig->key00BA,sizeof(hda.Hda.key));
				p->AddBuf((char*)&hda.Hda,sizeof(hda.Hda));
			}break;
		case Type0828:
			{
				COnlineHeadReq hda;
				hda.Hda.version = htons(pProtocol->wMainVersion);
				hda.Hda.code=htons(Type0828);
				hda.Hda.serial=htons(mSeqSerial.GetSeqSerial());
				hda.Hda.qq_id=htonl(pConfig->qq_id);
				hda.Hda.fix[0]=0x2;
				hda.Hda.fix[1]=0;
				hda.Hda.fix[2]=0;
				hda.Hda.unknown1=htonl(0x00010101);
				hda.Hda.unknown2 = htonl(pProtocol->dwPubNo);
				len=sizeof(hda.Hda);
				p->AddBuf((char*)&(hda.Hda),len);
				p->AddWord(htons(0x0030));

				//添加token数据
				CTXCommPack *pTmp=new CTXCommPack();
				pTmp->AddBuf((char*)pConfig->token36ret,sizeof(pConfig->token36ret));
				pTmp->AddBufLenWord();
				pTmp->AddBufLenWord();
				p->AddBuf((char*)pTmp->buffer.contents(),pTmp->buffer.size());
				delete pTmp;
				pTmp=NULL;
			}break;
	}
	return 0;
}

unsigned int CLoginReq::PackBody(CTXCommPack *p)
{
	Protocol *pProtocol = Protocol::GetInstance();
	CTXCommPack *p1=NULL,*p2=NULL,*p3=NULL,*p4=NULL;
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	switch(GetPackType())
	{
		case Type0825:
			{
				/******************添加00 18 00 16字段开始*************************************/
				p1=new CTXCommPack();
				p1->AddWord(htons(0x01));
				p1->AddDWord(htonl(pProtocol->wSSOVersion));
				p1->AddDWord(htonl(0x01));
				p1->AddDWord(htonl(pProtocol->wClientVersion));
				p1->AddDWord(htonl(pConfig->qq_id));   //增加qq号码
				p1->AddWord(htons(0x0));
				p1->AddWord(htons(0x0));

				p1->AddBufLenWord();
				p1->AddFieldCode(htons(0x18));        //特征码0x18
				/******************添加00 18 00 16字段结束***********************************/

				/******************添加0309字段开始*************************************/
				p2=new CTXCommPack();
				p2->AddWord(htons(0x01));
				p2->AddDWord(htonl(pConfig->ServerIp));
				p2->AddWord(htons(0x2));
				p2->AddBufLenWord();
				p2->AddFieldCode(htons(0x0309));        //固定字段数据0x0309
				/******************添加0309字段结束*************************************/

				/******************添加0036字段开始*************************************/
				p3=new CTXCommPack();
				p3->AddWord(htons(0x02));
				p3->AddWord(htons(0x01));
				p3->AddDWord(htonl(0x0));
				p3->AddWord(htons(0x00));
				p3->AddWord(htons(0x00));
				p3->AddDWord(htonl(0x00));
				p3->AddByte(0x00);
				p3->AddByte(0x00);
				p3->AddBufLenWord();
				p3->AddFieldCode(htons(0x0036));        //固定字段0x0036
				/******************添加0036字段结束*************************************/

				/******************添加0114字段开始*************************************/
				p4=new CTXCommPack();
				p4->AddBuf((char*)(pConfig->stKey),sizeof(pConfig->stKey));
				p4->AddBufLenWord();
				p4->AddFieldCode(htons(pProtocol->wDHVersion));
				p4->AddBufLenWord();
				p4->AddFieldCode(htons(0x0114));         //固定字段01 14
				/******************添加0114字段结束*************************************/

				/******************合并到第一个数据*************************************/
				p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
				delete p2;p2=NULL;
				p1->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
				delete p3;p3=NULL;
				p1->AddBuf((char*)p4->buffer.contents(),p4->buffer.size());
				delete p4;p4=NULL;
				/******************合并到第一个数据*************************************/
			}break;
		case Type0836:
			{
				//******************添加0112字段数据*************************************/
				{
					p1=new CTXCommPack();
					p1->AddWord(0x1201);                 
					p2=new CTXCommPack();
					p2->AddBuf((char*)pConfig->token25ret,sizeof(pConfig->token25ret));
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加0112字段数据*************************************/

				/******************添加030F字段数据*************************************/
				{
					p1->AddWord(htons(0x030F));
					p2=new CTXCommPack();
					p2->AddBuf((char*)pProtocol->STR_COMPUTER_ID.c_str(), strlen((char*)pProtocol->STR_COMPUTER_ID.c_str()));
					p2->AddBufLenWord();
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				/******************添加030F字段数据*************************************/

				/******************添加0005字段数据*************************************/
				{
					p1->AddWord(htons(0x0005)); 
					p1->AddWord(htons(0x0006));
					p1->AddWord(htons(0x0002));
					p1->AddDWord(htonl(pConfig->qq_id));
				}
				/******************添加0005字段数据*************************************/
				
				/******************添加0006字段数据*************************************/
				p1->AddWord(htons(0x0006));

				if(pConfig->LoginVerifyCode==NEED_LOGINVERIFYAGAIN)
				{
					p2=new CTXCommPack();
					p2->AddBuf((char*)pConfig->verify36ret,sizeof(pConfig->verify36ret));
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}else
				{
					p2=new CTXCommPack();
					p2->AddDWord(htonl(0x95e21fa7));   //四字节随机数字,暂时固定
					p2->AddWord(htons(0x0002));           //固定数据
					p2->AddDWord(htonl(pConfig->qq_id));
					p2->AddDWord(htonl(pProtocol->wSSOVersion));
					p2->AddDWord(htonl(0x00000001));
					p2->AddDWord(htonl(pProtocol->wClientVersion));               //某种未知版本
					p2->AddWord(0x0000);
					p2->AddByte(0x0);               //0或者1
					//添加QQ号密码MD5值
					unsigned char _dst_md5[0x10]={0};
					CMd5 md5;
					md5.GetMd5(_dst_md5,sizeof(_dst_md5),pConfig->qq_pwd,strlen((char*)pConfig->qq_pwd));
					p2->AddBuf((char*)_dst_md5,sizeof(_dst_md5));
					//添加时间戳
					p2->AddDWord(htonl(pConfig->ServerTime));
					p2->AddByte(0x00);                   //固定
					p2->AddDWord(0x00000000);            //固定
					p2->AddDWord(0x00000000);            //固定
					p2->AddDWord(0x00000000);            //固定
					p2->AddDWord(htonl(pConfig->ClientIp));

					p2->AddDWord(0x00000000);
					p2->AddDWord(0x00000000);

					p3=new CTXCommPack();
					p3->AddBuf((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size());           //AddCaculteGuid
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;

					//vague数据随机
					p2->AddBuf((char*)pProtocol->DEFAULT_VAGUE.data(), pProtocol->DEFAULT_VAGUE.size());
					memcpy(pConfig->vague_key, pProtocol->DEFAULT_VAGUE.data(), pProtocol->DEFAULT_VAGUE.size());

					//对明文求MD5
					memset(_dst_md5,0,sizeof(_dst_md5));
					md5.GetMd5(_dst_md5,sizeof(_dst_md5),(unsigned char*)p2->buffer.contents(),p2->buffer.size());
					memcpy(pConfig->login_verify,_dst_md5,sizeof(pConfig->login_verify));

					//对数据进行加密（密钥为密码的MD5+QQ号码后取MD5）
					unsigned int bytes=0;
					unsigned char key[TEA_KEY_LEN]={0};
					md5.GetMd5(key,sizeof(key),pConfig->qq_pwd,strlen((const char *)pConfig->qq_pwd));
					p3=new CTXCommPack();
					p3->AddBuf((char*)key,sizeof(key));
					p3->AddDWord(0);
					p3->AddDWord(htonl(pConfig->qq_id));
					md5.GetMd5(key,sizeof(key),(unsigned char *)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;
					memcpy(pConfig->pwd_key,key,sizeof(key));

					unsigned int datalen=p2->buffer.size()+0x12;
					unsigned char *data=(unsigned char *)malloc(datalen);
					memset(data,0,datalen);
					mTea.Tea_encrypt((unsigned char*)p2->buffer.contents(),p2->buffer.size(),key,data,&datalen);
					p1->AddWord(htons(datalen));
					p1->AddBuf((char*)data,datalen);
					delete p2;
					p2=NULL;
					free(data);
					data=NULL;
				}
				/******************添加0006字段数据*************************************/

				/******************添加0015数据*************************************/
				{
					//添加AddComputerIdGenerateG
					p2=new CTXCommPack();
					p2->AddByte(0x1);
					p2->AddDWord(htonl(CalculatebufCrc((char*)pProtocol->COMPUTER_GENERATEG_ID.data(), pProtocol->COMPUTER_GENERATEG_ID.size())));
					p2->AddWord(htons(0x10));
					p2->AddBuf((char*)pProtocol->COMPUTER_GENERATEG_ID.data(), pProtocol->COMPUTER_GENERATEG_ID.size());
					
					//添加guid
					p2->AddByte(0x2);
					p2->AddDWord(htonl(CalculatebufCrc((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size())));
					p2->AddWord(htons(0x10));
					p2->AddBuf((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size());
					//添加前置数据
					p2->AddFieldCode(htons(0x0001));
					p2->AddFieldCode(htons(0x0030));
					p2->AddFieldCode(htons(0x0015));

					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
				}
				/******************最新添加00 15字段数据结束*************************************/

				/******************添加001A数据*************************************/
				{
					unsigned int datalen=p2->buffer.size()+0x12;
					unsigned char *data=(unsigned char *)malloc(datalen);
					memset(data,0,datalen);
					mTea.Tea_encrypt((unsigned char*)p2->buffer.contents(),p2->buffer.size(),pConfig->vague_key,data,&datalen);
					delete p2;
					p2=NULL;

					p2=new CTXCommPack();
					p2->AddWord(htons(0x001A));       

					p3=new CTXCommPack();
					p3->AddBuf((char*)data,datalen);
					free(data);
					data=NULL;
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;
	
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				/******************添加001A数据*************************************/

				///******************添加0018数据*************************************/
				{
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0018));
					p3=new CTXCommPack();
					p3->AddWord(htons(0x0001));
					p3->AddDWord(htonl(pProtocol->wSSOVersion));
					p3->AddDWord(htonl(0x00000001));
					p3->AddDWord(htonl(pProtocol->wClientVersion));
					p3->AddDWord(htonl(pConfig->qq_id));
					p3->AddWord(htons(0x00));
					p3->AddWord(htons(0x00));
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;

					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				///******************添加0018数据*************************************/
				
				///******************添加0103数据*************************************/
				//注：此字段在本电脑第一次登陆时，可不用添加，之后会在0836包中返回
				if (false)
				{
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0103));         //固定字段01 03
					p3=new CTXCommPack();
					p3->AddWord(htons(0x0001));
					p4=new CTXCommPack();
					p4->AddBuf((char*)pProtocol->DEFAULT_SID.data(), pProtocol->DEFAULT_SID.size());
					p4->AddBufLenWord();
					p3->AddBuf((char*)p4->buffer.contents(),p4->buffer.size());
					delete p4;
					p4=NULL;
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				///******************添加0103数据*************************************/

				/**************************验证码部分数据*******0110，0032**********************/

				{
					if(pConfig->isNeedCode/*||pConfig->LoginVerifyCode==NEED_LOGINVERIFYAGAIN*/)
					{
						p2=new CTXCommPack();
						p2->AddWord(htons(0x0110));				//0110段数据
						p2->AddWord(htons(0x003c));
						p2->AddWord(htons(0x0001));
						p2->AddWord(htons(0x0038));
						p2->AddBuf((char*)pConfig->tokenBAret,sizeof(pConfig->tokenBAret));
						p2->AddWord(htons(0x0032));				//0032数据

						p2->AddWord(htons(0x0063));
						p2->AddByte(0x3E);
						p2->AddWord(htons(0x0063));
						p2->AddByte(0x02);
						p2->AddDWord(htonl(pProtocol->dwQDVersion));
						p2->AddWord(htons(pProtocol->wQdCsSubNo));
						p2->AddByte(pProtocol->cQdCsSubNo);
						p2->AddWord(htons(0x6F4D));
						p2->AddDWord(0x00000000);
						p2->AddBuf((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size());
						p2->AddByte(pProtocol->cOsType);
						p2->AddByte(pProtocol->bIsWOW64);
						p2->AddWord(htons(0x0000));
						p2->AddWord(htons(pProtocol->dwPubNo));
						p2->AddWord(htons(pProtocol->wClientVersion));
						p2->AddDWord(htonl(pProtocol->dwDrvVersionInfoHight));
						p2->AddDWord(htonl(pProtocol->dwDrvVersionInfoLow));
						p2->AddBuf((char*)pProtocol->bufVersion_TSSafeEdit.data(), pProtocol->bufVersion_TSSafeEdit.size());
						p2->AddBuf((char*)pProtocol->bufVersion_QScanEngine.data(), pProtocol->bufVersion_QScanEngine.size());
						p2->AddByte(0x00);
						//添加QDData
						p3=new CTXCommPack();
						p3->AddDWord(pProtocol->dwQDVersion);//添加QQ号码
						p3->AddDWord(pProtocol->dwPubNo);//添加版本
						p3->AddDWord(pConfig->qq_id);//添加QQ号码,大端模式
						p3->AddDWord(htonl(pConfig->ServerIp));//添加QQ号码,大端模式
						
						unsigned int datalen=p3->buffer.size()+0x12;
						unsigned char *data=(unsigned char *)malloc(datalen);
						memset(data,0,datalen);
						CTeaCrypt mTeaTwo;
						mTeaTwo.InitTeaTwo();
						mTeaTwo.Tea_encrypt((unsigned char*)p3->buffer.contents(), (int)p3->buffer.size(),pProtocol->QD_KEY.data(), data, &datalen);
						delete p3;
						p3=NULL;
						p2->AddBuf((char*)data,datalen);
						free(data);
						datalen=0;
						p2->AddByte(pProtocol->cQdSubFixed);
						p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
						delete p2;
						p2=NULL;
					}
				}
				/**************************验证码部分数据*****************************/

				///******************添加0312数据*************************************/
				{
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0312));
					p3=new CTXCommPack();
					p3->AddByte(0x1);
					p3->AddDWord(htonl(0x00000000));             //此处是否记住密码
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				///******************添加0508数据*************************************/
				{
					p2 = new CTXCommPack();
					p2->AddWord(htons(0x0508));
					p3 = new CTXCommPack();
					p3->AddByte(0x1);
					p3->AddDWord(htonl(0x00000002));             //此处是否记住密码
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(), p3->buffer.size());
					delete p3;
					p3 = NULL;
					p1->AddBuf((char*)p2->buffer.contents(), p2->buffer.size());
					delete p2;
					p2 = NULL;
				}

				///******************添加0313数据*************************************/
				{
					p1->AddWord(htons(0x0313));
					p2=new CTXCommPack();
					p2->AddByte(0x1);
					p2->AddWord(htons(0x0102));
					p2->AddWord(htons(0x0010));
					p2->AddBuf((char*)pProtocol->DEFAULT_GUID2.data(), pProtocol->DEFAULT_GUID2.size());
					p2->AddDWord(htonl(0x0000002F));  //未知
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				///******************添加0313数据*************************************/

				///******************添加0102数据*************************************/
				{
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0102));         //固定字段01 02
					p3=new CTXCommPack();
					p3->AddWord(htons(0x0001));
					unsigned char _random1[0x10]={0xC9,0xCF,0xC7,0xF5,0xA2,0x6C,0xFE,0x3C,0x40,0x21,0x73,0x3A,0x3B,0x6F,0x9B,0xED};
					p3->AddBuf((char*)_random1,sizeof(_random1));      //0x10随机数据

					//求0x10随机数据MD5
					unsigned char _dst_md5[0x10]={0};
					CMd5 md5;
					md5.GetMd5(_dst_md5,sizeof(_dst_md5),_random1,sizeof(_random1));
					memcpy(pConfig->_random_10,_dst_md5,sizeof(pConfig->_random_10));

					p4=new CTXCommPack();                        //0x38随机数据
					unsigned char _random2[0x10]={0xEB,0x3E,0xBD,0xF8,0x85,0x26,0x17,0x57,0x71,0x43,0x3B,0xFE,0x65,0x0D,0xEA,0xDC};
					p4->AddBuf((char*)_random2,sizeof(_random2));
					unsigned char _random3[0x10]={0x11,0x3E,0x77,0xB5,0x8F,0xC8,0x43,0xCA,0xDB,0xF2,0x2B,0x7F,0xD6,0xCB,0x16,0x24};
					p4->AddBuf((char*)_random3,sizeof(_random3));
					unsigned char _random4[0x10]={0x9A,0xCD,0x4A,0xC6,0x6A,0x89,0xFA,0x03,0x81,0x3F,0xEB,0x32,0x66,0x53,0xE8,0xF5};
					p4->AddBuf((char*)_random4,sizeof(_random4));
					unsigned char _random5[0x10]={0x49,0x58,0xC9,0x23,0x1E,0xD2,0x9D,0x53,0x84,0x02,0xFA,0xA9,0xFE,0x93,0x67,0xB8};
					p4->AddBuf((char*)_random5,0x8);

					//添加0x38字节数据MD5
					memset(_dst_md5,0,sizeof(_dst_md5));
					md5.GetMd5(_dst_md5,sizeof(_dst_md5),(unsigned char*)p4->buffer.contents(),p4->buffer.size());
					memcpy(pConfig->_random_38,_dst_md5,sizeof(pConfig->_random_38));

					p4->AddBufLenWord();

					p3->AddBuf((char*)p4->buffer.contents(),p4->buffer.size());
					delete p4;
					p4=NULL;
				
					//增加TGTGTdata,暂时以随机数据添加(可能包含了以上0x38数据的MD5计算)
					p4=new CTXCommPack(); 
					//0x14 TGTGT数据
					unsigned char tgtgt[0x14]={0};

					GetTGTGT(pConfig->_random_10,pConfig->_random_38,pConfig->login_verify,tgtgt);        //验证正确
					p4->AddBuf((char*)tgtgt,sizeof(tgtgt));
					p4->AddBufLenWord();
				
					p3->AddBuf((char*)p4->buffer.contents(),p4->buffer.size());
					delete p4;
					p4=NULL;
					p3->AddBufLenWord();

					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;

					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				///******************添加添加0102数据*************************************/
			}break;
		case Type0104:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x80000001));
				p1->AddDWord(htonl(0x23080401));
				p1->AddDWord(htonl(0xe0000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddDWord(htonl(0x00000000));
				p1->AddWord(htons(0x0000));
				p1->AddByte(0x00);
			}break;
		case Type00BA:
			{
				p1=new CTXCommPack();
				p1->AddDWord(htonl(0x00020000));
				p1->AddDWord(htonl(0x080401e0));
				p1->AddWord(htons(0x0000));
				p1->AddWord(htons(pProtocol->wSSOVersion));
				p1->AddDWord(htonl(0x00000001));
				p1->AddDWord(htonl(0x00001525));
				p1->AddByte(0x00);
				p1->AddWord(htons(0x0038));
				p1->AddBuf((char*)pConfig->token25ret,sizeof(pConfig->token25ret));
				p1->AddWord(htons(0x0102));
				p1->AddWord(htons(0x0019));
				p1->AddBuf((char*)pConfig->stKey,sizeof(pConfig->stKey));

				if(pConfig->isNeedCode)
				{
					//需要验证码
					p1->AddDWord(htonl(0x14000500));
					p1->AddDWord(htonl(0x00000000));
					p1->AddByte(0x4);
					p1->AddBuf((char*)pConfig->IndetifyCode,sizeof(pConfig->IndetifyCode));
					p1->AddWord(htons(0x0038));
					p1->AddBuf((char*)pConfig->tokenBAret,sizeof(pConfig->tokenBAret));
					p1->AddWord(htons(0x0010));
					p1->AddBuf((char*)pProtocol->DEFAULT_SID.data(), pProtocol->DEFAULT_SID.size());
				}else
				{
					//不需要验证码
					p1->AddDWord(htonl(0x13000500));
					p1->AddDWord(htonl(0x00000001));
					p1->AddWord(htons(0x0028));
					p1->AddBuf((char*)pConfig->data0036ret28,sizeof(pConfig->data0036ret28));
					p1->AddWord(htons(0x0010));
					p1->AddBuf((char*)pProtocol->DEFAULT_SID.data(), pProtocol->DEFAULT_SID.size());
				}


			}break;
		case Type0828:
			{
				p1=new CTXCommPack();
				unsigned char cQDLoginFlag=0;
				//******************添加00 07 00 88字段*************************************/
				{
					p1->AddWord(htons(0x0007));
					p2=new CTXCommPack();
					p2->AddDWord(htonl(pConfig->ServerTime));
					p2->AddBufLenWord();
					p2->AddDWord(htonl(pConfig->ClientIp));
					p2->AddDWord(htonl(0x0));
					p3=new CTXCommPack();
					p3->AddBuf((char*)pConfig->verify36ret,sizeof(pConfig->verify36ret));
					p3->AddBufLenWord();
					p2->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;
					//计算QDLoginFlag
					unsigned char c = (pProtocol->dwQDVersion & 0x0000FF00) >> 0x8;
					cQDLoginFlag = CalcRound(c, (unsigned char*)pProtocol->DEFAULT_QQEXE_MD5.data(), (unsigned char*)p2->buffer.contents());
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加00 07 00 88字段*************************************/

				//******************添加00 0c 00 16字段*************************************/
				{
					p1->AddWord(htons(0x000c));
					p3=new CTXCommPack();
					p3->AddWord(htons(0x0002));
					p3->AddDWord(htonl(0));
					p3->AddDWord(htonl(0));
					p3->AddWord(htons(0));
					p3->AddDWord(htonl(pConfig->ServerIp));
					p3->AddWord(htons(pConfig->port));
					p3->AddDWord(htonl(0));
					p3->AddBufLenWord();
					p1->AddBuf((char*)p3->buffer.contents(),p3->buffer.size());
					delete p3;
					p3=NULL;
				}
				//******************添加00 0c 00 16字段*************************************/

				//******************添加00 15 00 30字段*************************************/
				{
					p2=new CTXCommPack();
					p2->AddByte(0x1);
					p2->AddDWord(htonl(CalculatebufCrc((char*)pProtocol->COMPUTER_GENERATEG_ID.data(), pProtocol->COMPUTER_GENERATEG_ID.size())));
					p2->AddWord(htons(0x10));
					p2->AddBuf((char*)pProtocol->COMPUTER_GENERATEG_ID.data(), pProtocol->COMPUTER_GENERATEG_ID.size());
					
					p2->AddByte(0x2);
					p2->AddDWord(htonl(CalculatebufCrc((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size())));
					p2->AddWord(htons(0x10));
					p2->AddBuf((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size());
					p2->AddFieldCode(0x0);
					p2->AddFieldCode(htons(0x0030));
					p2->AddFieldCode(htons(0x0015));

					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
				}
				//******************添加00 15 00 30字段*************************************/

				//******************添加00 36 00 12字段*************************************/
				{
					p1->AddWord(htons(0x0036));
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0002));
					p2->AddWord(htons(0x0001));
					p2->AddDWord(htonl(0x00000000));
					p2->AddDWord(htonl(0x00000000));
					p2->AddDWord(htonl(0x00000000));
					p2->AddWord(htons(0x0000));
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加00 36 00 12字段*************************************/

				//******************添加00 18 00 16字段*************************************/
				{
					p1->AddWord(htons(0x0018));
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0001));
					p2->AddDWord(htonl(pProtocol->wSSOVersion));
					p2->AddDWord(htonl(0x00000001));
					p2->AddDWord(htonl(pProtocol->wClientVersion));
					p2->AddDWord(htonl(pConfig->qq_id));
					p2->AddWord(htons(0x00));
					p2->AddWord(htons(0x00));
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加00 18 00 16字段*************************************/

				//******************添加00 1f 00 22字段*************************************/
				if(false){
					p1->AddWord(htons(0x001f));
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0001));
					unsigned char _randombuf[]={0x86,0xCC,0x23,0x15,0x37,0x9C,0xED,0xEE,0x26,0xEA,0xEE,0x99,0x73,0x1E,0x59,0x14,0x6D,0x41,0x36,0xE6,0xF2,0xA6,0xDC,0xF3,0xFC,0x62,0xC9,0xB7,0x5C,0xB4,0x6B,0x50};
					p2->AddBuf((char*)_randombuf,sizeof(_randombuf));
					p2->AddBufLenWord();
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加00 1f 00 22字段*************************************/

				//******************添加01 05 00 88字段*************************************/
				{
					p1->AddWord(htons(0x0105));
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0030));
					p2->AddWord(htons(0x0001));
					p2->AddWord(htons(0x0102));
					p2->AddWord(htons(0x0014));
					p2->AddWord(htons(0x0101));
					p2->AddWord(htons(0x0010));
					unsigned char data1[]={0xDD,0xA0,0x97,0x9F,0x35,0x5E,0xF9,0x17,0x5D,0xC2,0x55,0xCF,0xB9,0xA2,0xC3,0xDC};
					p2->AddBuf((char*)data1,sizeof(data1));
					p2->AddWord(htons(0x0014));
					p2->AddWord(htons(0x0102));
					p2->AddWord(htons(0x0010));
					unsigned char data2[]={0xFE,0x3E,0xE5,0x41,0xBF,0x22,0xAB,0x11,0x4B,0xB3,0x48,0x2D,0x9F,0x60,0xA4,0x5A};
					p2->AddBuf((char*)data2,sizeof(data2));

//					p2->AddWord(htons(0x0088));
//					p2->AddWord(htons(0x0001));
//					p2->AddWord(htons(0x0102));
//					unsigned char data1[]={0x00,0x40,0x02,0x01,0x03,0x3c,0x01,0x03,0x00,0x00};
//					p2->AddBuf((char*)data1,sizeof(data1));
//					unsigned char data2[]={
//						0xd2,0x5b,0x5b,0x35,0x68,0x60,0xa7,0xbb,0x97,0xbd,0x4f,0x6f,0xd7,0x39,
//0x70,0x00,0xa6,0xa8,0x0d,0x78,0xbd,0x55,0x4d,0x58,0xa0,0xab,0xdf,0xe3,0x97,0x07,
//0xed,0xe2,0x3d,0x98,0x55,0xa9,0xd6,0xcd,0x0f,0xf6,0xa6,0x6c,0x17,0xcd,0x48,0x78,
//0x4c,0x0a,0xe0,0x18,0x35,0x04,0x7b,0xab,0x35,0x9c,
//};
//					p2->AddBuf((char*)data2,sizeof(data2));
//					unsigned char data3[]={0x00,0x40,0x02,0x02,0x03,0x3c,0x01,0x03,0x00,0x00};
//					p2->AddBuf((char*)data3,sizeof(data3));
//
//					unsigned char data4[]={
//					0x66,0x6e,0xa2,0xa1,0xa0,0x79,0x3d,0x0c,0xce,0x88,0xd1,0x72,
//0x8b,0xfe,0x94,0x71,0xe5,0xe0,0x9e,0x82,0xd5,0xe8,0x40,0xe2,0x07,0xe5,0x0e,0x77,
//0xe3,0xa8,0x8c,0xef,0xac,0xf6,0xdc,0xec,0xff,0xac,0x40,0xd6,0x54,0xa4,0xdd,0x09,
//0x2d,0x30,0xd4,0x91,0x9b,0xcd,0x5a,0x5c,0x29,0x11,0xc5,0xbe,
//					};
//					p2->AddBuf((char*)data4,sizeof(data4));

					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加01 05 00 46字段*************************************/
				
				//******************添加01 0B 00 85字段*************************************/
				{
					p1->AddWord(htons(0x010B));
					p2=new CTXCommPack();
					p2->AddWord(htons(0x0085));
					p2->AddWord(htons(0x0002));
					p2->AddBuf((char*)pProtocol->DEFAULT_QQEXE_MD5.data(), pProtocol->DEFAULT_QQEXE_MD5.size());
					p2->AddByte(cQDLoginFlag);
					p2->AddByte(0x10);
					p2->AddDWord(htonl(0x00000000));
					p2->AddDWord(htonl(0x00000002));

					//添加QDdata
					p2->AddWord(htons(0x0063));
					p2->AddByte(0x3E);
					p2->AddWord(htons(0x0063));
					p2->AddByte(0x02);
					p2->AddDWord(htonl(pProtocol->dwQDVersion));
					p2->AddWord(htons(pProtocol->wQdCsSubNo));
					p2->AddByte(pProtocol->cQdCsSubNo);
					p2->AddWord(htons(0x6F4D));
					p2->AddDWord(0x00000000);
					p2->AddBuf((char*)pProtocol->DEFAULT_GUID.data(), pProtocol->DEFAULT_GUID.size());
					p2->AddByte(pProtocol->cOsType);
					p2->AddByte(pProtocol->bIsWOW64);
					p2->AddDWord(htonl(pProtocol->dwPubNo));
					p2->AddWord(htons(pProtocol->wClientVersion));
					p2->AddDWord(htonl(pProtocol->dwDrvVersionInfoHight));
					p2->AddDWord(htonl(pProtocol->dwDrvVersionInfoLow));
					p2->AddBuf((char*)pProtocol->bufVersion_TSSafeEdit.data(), pProtocol->bufVersion_TSSafeEdit.size());
					p2->AddBuf((char*)pProtocol->bufVersion_QScanEngine.data(), pProtocol->bufVersion_QScanEngine.size());
					p2->AddByte(0x00);
					//添加QDData
					p3=new CTXCommPack();
					p3->AddDWord(pProtocol->dwQDVersion);//添加QQ号码
					p3->AddDWord(pProtocol->dwPubNo);//添加版本
					p3->AddDWord(pConfig->qq_id);//添加QQ号码,大端模式
					p3->AddDWord(htonl(pConfig->ServerIp));//添加QQ号码,大端模式
						
					unsigned int datalen=p3->buffer.size()+0x12;
					unsigned char *data=(unsigned char *)malloc(datalen);
					memset(data,0,datalen);
					CTeaCrypt mTeaTwo;
					mTeaTwo.InitTeaTwo();
					mTeaTwo.Tea_encrypt((unsigned char*)p3->buffer.contents(), (int)p3->buffer.size(), pProtocol->QD_KEY.data(), data, &datalen);
					delete p3;
					p3=NULL;
					p2->AddBuf((char*)data,datalen);
					free(data);
					datalen=0;
					p2->AddByte(pProtocol->cQdSubFixed);
					p2->AddDWord(htonl(0x00000000));
					p1->AddBuf((char*)p2->buffer.contents(),p2->buffer.size());
					delete p2;
					p2=NULL;
				}
				//******************添加01 0B 00 85字段*************************************/

				//******************添加末尾字段*************************************/
				{
					p1->AddDWord(htonl(0x002d0006));
					p1->AddWord(htons(0x0001));
					p1->AddBuf((char*)pProtocol->DEFAULT_LAN_IP.data(), pProtocol->DEFAULT_LAN_IP.size());  //局域网内网IP
				}
				//******************添加末尾字段*************************************/

			}break;
	}
	p->AddBuf((char*)p1->buffer.contents(),p1->buffer.size());
	delete p1;
	p1=NULL;
	return 0;
}

unsigned int CLoginReq::PackData()
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
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	switch(GetPackType())
	{
	case Type0825:
		{
			unsigned int dstlen=p2.buffer.size()+0x12;              //添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->key0825,dst,&bytes);
		}break;
	case Type0836:
		{
			unsigned int dstlen=p2.buffer.size()+0x12;				//添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->ecdh_key,dst,&bytes);
		}break;
	case Type0104:
		{
			unsigned int dstlen=p2.buffer.size()+0x12;				//添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->key0104,dst,&bytes);
		}break;
	case Type00BA:
		{
			unsigned int dstlen=p2.buffer.size()+0x12;				//添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->key00BA,dst,&bytes);
		}break;
	case Type0828:
		{
			unsigned int dstlen=p2.buffer.size()+0x12;				//添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->key0836ret1,dst,&bytes);
		}break;
	}
	pack.append(dst,bytes);
	free(dst);
	dst=NULL;
	//封装EndMark
	pack.append((char)EndMark);
	return 0;
}



