#include "StdAfx.h"
#include "PackReq.h"
#include <stdlib.h>
#include<WinSock2.h>
#include "../UtilLib/err_code.h"
#include"../MobileQQ/protocol_type.h"
#include"LoginPack.h"
#include"PhSigLcId.h"
#include"ConfigService.h"
#include"HeartBeat.h"
#include"CliLogSvc.h"
#include"LoginTransemp.h"
#include"GrayUinProCheck.h"
#include"CfriendlistGetTroopListReqV2.h"
#include"StatSvcRegister.h"
#include"OidbSvc_0x7a2_0.h"
#include"LBSService.h"
#include"ContactBindServlet.h"

CPackReq::CPackReq(void)
{
}

CPackReq::~CPackReq(void)
{
}

unsigned int CPackReq::PackHead(CTXCommPack *p,void *data)
{
	switch(GetPackType())
	{
		case TYPE_MSF:
			{
				p->AddDWord(htonl(CONST_MSF));
				p->AddDWord(htonl(0));
				std::string str=STR_MSF;
				p->AddByte(str.size());
				p->AddBuf(str.c_str(),str.size());
				p->AddByte(0);
				p->AddDWord(htonl(0));
			}break;
		case PhSigLcId_Check:
		case ConfigService_ClientReq:
		case CliLogSvc_UploadReq:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0x2);
				p->AddDWord(htonl(0x4));  //一个空的字符串字段
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				//::ultoa(pConfig->qq_id,buf,10);
				::ultoa(0,buf,10);//此处QQ为0
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case HeartBeat_Alive:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0);//此处为0
				p->AddDWord(htonl(0x4));  //一个空的字符串字段
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				//::ultoa(pConfig->qq_id,buf,10);
				::ultoa(0,buf,10);//此处QQ为0
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case wtlogin_login:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0x2);//此处为0
				p->AddDWord(htonl(0x4));  //一个空的字符串字段
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				::ultoa(pConfig->qq_id,buf,10);
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case wtlogin_trans_emp:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0x2);
				p->AddDWord(htonl(sizeof(pConfig->d2_key)+0x4));
				p->AddBuf((char*)pConfig->d2_key,sizeof(pConfig->d2_key));//添加d2_key  
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				::ultoa(pConfig->qq_id,buf,10);
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case GrayUinPro_Check:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0x2);
				p->AddDWord(htonl(sizeof(pConfig->d2_key)+0x4));
				p->AddBuf((char*)pConfig->d2_key,sizeof(pConfig->d2_key));//添加d2_key  
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				::ultoa(pConfig->qq_id,buf,10);
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case friendlist_GetTroopListReqV2:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0x1);
				p->AddDWord(htonl(sizeof(pConfig->d2_key)+0x4));
				p->AddBuf((char*)pConfig->d2_key,sizeof(pConfig->d2_key));//添加d2_key  
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				::ultoa(pConfig->qq_id,buf,10);
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case OidbSvc_0x7a2_0:
			{
				p->AddDWord(htonl(CONST_VERSION8));
				p->AddByte(0x1);
				p->AddDWord(htonl(sizeof(pConfig->d2_key)+0x4));
				p->AddBuf((char*)pConfig->d2_key,sizeof(pConfig->d2_key));//添加d2_key  
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				::ultoa(pConfig->qq_id,buf,10);
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
		case StatSvc_register:
		case account_RequestBindMobile:
		case account_RequestUploadAddressBookV2:
		case account_RequestQueryQQBindingStat:
		case account_RequestVerifyBindingSmscode:
		case account_RequestQueryQQMobileContactsV3:
		case account_RequestCancelBindMobile:
		case account_RequestUploadAddressBook:
		case account_RequestUpdateAddressBook:
		case SummaryCard_ReqSearch:
		case EncounterSvc_ReqGetEncounter:
			{
				p->AddDWord(htonl(CONST_VERSION9));
				p->AddByte(0x1);
				p->AddDWord(htonl(GetSeq()));
				p->AddByte(0);
				std::string strQQ;
				char buf[0x20]={0};
				::ultoa(pConfig->qq_id,buf,10);
				strQQ=buf;
				p->AddDWord(htonl(0x4+strQQ.size()));
				p->AddBuf(strQQ.c_str(),strQQ.size());
			}break;
	}
	return RESULT_SUCCESS;
}

unsigned int CPackReq::PackBody(CTXCommPack *p,void *data)
{
	switch(GetPackType())
	{
		case TYPE_MSF:
			{
				break;
			}break;
		case PhSigLcId_Check:
			{
				CPhSigLcId PhSigLcId(GetSeq(),pConfig);
				p->AddByteBuffer(PhSigLcId.Encode());
			}break;
		case ConfigService_ClientReq:
			{
				CConfigService mConfigService(GetSeq(),pConfig);
				p->AddByteBuffer(mConfigService.Encode());
			}break;
		case HeartBeat_Alive:
			{
				CHeartBeat mHeartBeat(GetSeq(),pConfig);
				p->AddByteBuffer(mHeartBeat.Encode());
			}break;
		case CliLogSvc_UploadReq:
			{
				CCliLogSvc mCliLogSvc(GetSeq(),pConfig);
				p->AddByteBuffer(mCliLogSvc.Encode());
			}break;
		case wtlogin_login:
			{
				CLoginPack mPack(GetSeq(),pConfig);
				p->AddByteBuffer(mPack.Encode());
			}break;
		case wtlogin_trans_emp:
			{
				CLoginTransemp mPack(GetSeq(),pConfig);
				p->AddByteBuffer(mPack.Encode());
			}break;
		case GrayUinPro_Check:
			{
				CGrayUinProCheck mPack(GetSeq(),pConfig);
				p->AddByteBuffer(mPack.Encode());
			}break;
		case friendlist_GetTroopListReqV2:
			{
				CfriendlistGetTroopListReqV2 mPack(GetSeq(),pConfig);
				p->AddByteBuffer(mPack.Encode());
			}break;
		case StatSvc_register:
			{
				CStatSvcRegister mPack(GetSeq(),pConfig);
				p->AddByteBuffer(mPack.Encode());
			}break;
		case OidbSvc_0x7a2_0:
			{
				COidbSvc_0x7a2_0 mPack(GetSeq(),pConfig);
				p->AddByteBuffer(mPack.Encode());
			}break;
		case account_RequestBindMobile:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestBindMobile));
			}break;
		case account_RequestUploadAddressBookV2:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestUploadAddressBookV2));
			}break;
		case account_RequestQueryQQBindingStat:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestQueryQQBindingStat));
			}break;
		case account_RequestVerifyBindingSmscode:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestVerifyBindingSmscode));
			}break;
		case account_RequestQueryQQMobileContactsV3:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestQueryQQMobileContactsV3));
			}break;
		case account_RequestCancelBindMobile:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestCancelBindMobile));
			}break;
		case account_RequestUploadAddressBook:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestUploadAddressBook));
			}break;
		case account_RequestUpdateAddressBook:
			{
				CContactBindServlet mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(account_RequestUpdateAddressBook));
			}break;
		case SummaryCard_ReqSearch:
			{
				LBSService mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(SummaryCard_ReqSearch));
			}break;
		case EncounterSvc_ReqGetEncounter:
			{
				LBSService mPack(pConfig);
				p->AddByteBuffer(mPack.Encode(EncounterSvc_ReqGetEncounter,data));
			}break;
	}
	return RESULT_SUCCESS;
}

unsigned int CPackReq::PackData(void *data)
{
	pack.clear();

	//封装头部数据
	CTXCommPack p1;
	unsigned int ret=PackHead(&p1,data);
	if(ret!=RESULT_SUCCESS)
	{
		return ret;
	}
	pack.append<ByteBuffer>(p1.buffer);
	p1.GetBufferOut();

	//封装body数据
	CTXCommPack p2;
	ret=PackBody(&p2,data);
	if(ret!=RESULT_SUCCESS)
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
	case TYPE_MSF:
	case HeartBeat_Alive:
		{
			if(p2.buffer.size()!=0)
			{
				pack.append(p2.buffer.contents(),p2.buffer.size());
			}
		}break;
	case PhSigLcId_Check:
	case ConfigService_ClientReq:
	case CliLogSvc_UploadReq:
	case wtlogin_login:
	case wtlogin_trans_emp:
	case GrayUinPro_Check:
		{
			//key0加密
			unsigned int dstlen=p2.buffer.size()+0x12;              //添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),Key0,dst,&bytes);
			p2.GetBufferOut();
			pack.append(dst,bytes);
			free(dst);
			dst=NULL;
		}break;
	case friendlist_GetTroopListReqV2:
	case OidbSvc_0x7a2_0:
	case StatSvc_register:
	case account_RequestBindMobile:
	case account_RequestUploadAddressBookV2:
	case account_RequestQueryQQBindingStat:
	case account_RequestVerifyBindingSmscode:
	case account_RequestQueryQQMobileContactsV3:
	case account_RequestCancelBindMobile:
	case account_RequestUploadAddressBook:
	case account_RequestUpdateAddressBook:
	case SummaryCard_ReqSearch:
	case EncounterSvc_ReqGetEncounter:
		{
			//sid加密
			unsigned int dstlen=p2.buffer.size()+0x12;              //添加0x12固定长度
			dst=(unsigned char *)malloc(dstlen);
			memset(dst,0,dstlen);
			mTea.Tea_encrypt((unsigned char*)p2.buffer.contents(),p2.buffer.size(),pConfig->sid,dst,&bytes);
			p2.GetBufferOut();
			pack.append(dst,bytes);
			free(dst);
			dst=NULL;
		}break;
	}
	//增加头部字节
	pack.insert(0,pack.reverse(pack.size()+4));
	return RESULT_SUCCESS;
}

void	CPackReq::Merge(const ByteBuffer &a)
{
	this->pack.append(a.contents(),a.size());
}

