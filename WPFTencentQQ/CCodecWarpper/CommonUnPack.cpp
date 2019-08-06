#include "StdAfx.h"
#include <WinSock.h>
#include "CommonUnPack.h"
#include"Packet.h"
#include"../MobileQQ/protocol_type.h"
#include "../UtilLib/err_code.h"
#include"UniPacket.h"
#include"StatSvcRegister.h"
#include"ResponeBindMobile.h"
#include"ResponeUploadAddressBookV2.h"
#include"ContactBindServlet.h"
#include"RespondQueryQQBindingStat.h"
#include"ResponeQueryQQMobileContactsV3.h"
#include"ResponeVerifySmscode.h"
#include"SummaryCardRespSearch.h"
#include"RespGetEncounterV2.h"
#include"LBSService.h"
#include"../UtilLib/inflate.h"


CCommonUnPack::CCommonUnPack(void)
{
}

CCommonUnPack::~CCommonUnPack(void)
{
}

unsigned int CCommonUnPack::UnPackHead()
{
	unsigned int version=pack.reverse(pack.read<int>());
	if(version==CONST_MSF)
	{
		if(pack.read<int>()!=0)
			return ERR_ANALYSIS_PACKET;
		char l=pack.read<char>();
		if(l!=3) return ERR_ANALYSIS_PACKET;
		unsigned char *dst=(unsigned char*)malloc(l+1);
		if(dst==NULL) return ERR_ANALYSIS_PACKET;
		memset(dst,0,l+1);
		pack.read(dst,l);
		if(strcmp((char*)dst,STR_MSF)!=0)
		{
			return ERR_ANALYSIS_PACKET;
		}
		char c=pack.read<char>();
		if(c!=0) return ERR_ANALYSIS_PACKET;
		if(pack.read<int>()!=0) return ERR_ANALYSIS_PACKET;
		SetPacketType(TYPE_MSF);
		return RESULT_SUCCESS;
	}
	if(version==CONST_VERSION8||version==CONST_VERSION9)
	{
		pack.read<char>();
		pack.read<char>();
		std::string strQQ=ReadString();
		return RESULT_SUCCESS;
	}else
	{
		return ERR_ANALYSIS_PACKET;
	}
	return RESULT_SUCCESS;
}

unsigned int CCommonUnPack::UnPackBody()
{
	if(GetPackType()==TYPE_MSF||GetPackType()==HeartBeat_Alive) return RESULT_SUCCESS;
	if(pack.btail()) return RESULT_SUCCESS;

	//初次判断是否需要解密
	int bodylen=pack.reverse(pack.read<int>());
	if(bodylen==pack.size()-pack.rpos())
	{
		//明文数据包
		pack.mpos(-4);
		return RESULT_SUCCESS;
	}else
	{
		//解密数据包
		pack.mpos(-4);//后退4字节

		unsigned char *dst=NULL;
		unsigned int bytes=0;
		CTeaCrypt mTea;
		mTea.InitTeaOne();
		//采用尝试解密
		//首先使用Key0解密
		unsigned int len=pack.size()-pack.rpos();
		unsigned char *src=(unsigned char *)malloc(len);
		if(src==NULL) return ERR_NOENOUGHBUF;
		pack.read(src,len);
		mTea.Tea_decrypt(src,len,Key0,&dst,&bytes);

		//判断解密是否成功
		bodylen=pack.reverse(*(int*)dst);
		if(bytes>bodylen+4)
		{
			int bodylen2=pack.reverse(*(int*)(dst+bodylen));
			if(bodylen2==0x4)
			{
				bodylen2=pack.reverse(*(int*)(dst+bodylen+4));
				if(bodylen+bodylen2+4==bytes)
				{
					//解密成功
					pack.clear();
					pack.append(dst,bytes);
					free(src);
					src=NULL;
					free(dst);
					dst=NULL;
					return RESULT_SUCCESS;
				}
			}else
			{
				if(bodylen+bodylen2==bytes)
				{
					//解密成功
					pack.clear();
					pack.append(dst,bytes);
					free(src);
					src=NULL;
					free(dst);
					dst=NULL;
					return RESULT_SUCCESS;
				}
			}

		}

		free(dst);
		dst=NULL;
		if(pConfig->isSidFill)
		{
			//使用sid继续解密
			mTea.Tea_decrypt(src,len,pConfig->sid,&dst,&bytes);
			bodylen=pack.reverse(*(int*)dst);
			if(bytes>bodylen+4)
			{
				int bodylen2=pack.reverse(*(int*)(dst+bodylen));
				if(bodylen2==0x4)
				{
					bodylen2=pack.reverse(*(int*)(dst+bodylen+4));
					if(bodylen+bodylen2+4==bytes)
					{
						//解密成功
						pack.clear();
						pack.append(dst,bytes);
						free(src);
						src=NULL;
						free(dst);
						dst=NULL;
						return RESULT_SUCCESS;
					}
				}else
				{
					if(bodylen+bodylen2==bytes)
					{
						//解密成功
						pack.clear();
						pack.append(dst,bytes);
						free(src);
						src=NULL;
						free(dst);
						dst=NULL;
						return RESULT_SUCCESS;
					}
				}

			}
		}else
		{
			free(src);
			src=NULL;
			return ERR_CHECK_PACKET;
		}
	}
	return RESULT_SUCCESS;
	
}

unsigned int CCommonUnPack::_check_packet()
{
	unsigned size=pack.reverse(pack.read<int>());
	if(size!=pack.size())
		return ERR_CHECK_PACKET;
	return RESULT_SUCCESS;
}

unsigned int CCommonUnPack::UnPackData()
{	
	unsigned int ret=RESULT_SUCCESS;
	ret=_check_packet();
	if(ret!=RESULT_SUCCESS)
	{
		return ret;
	}
	ret=UnPackHead();
	if(ret!=RESULT_SUCCESS)
	{
		return ret;
	}
	ret=UnPackBody();
	if(ret!=RESULT_SUCCESS)
	{
		return ret;
	}
	return RESULT_SUCCESS;
}

unsigned int  CCommonUnPack::Analysis()
{
	switch(GetPackType())
	{
	case TYPE_MSF:
	case HeartBeat_Alive:
		{
			return RESULT_SUCCESS;
		}break;
	default:
		{
			//继续判断类型
			int headLen=htonl(pack.read<int>());
			SetSeq(htonl(pack.read<int>()));
			int m_RetCode=pack.reverse(pack.read<int>());
			//读字符串
			ReadString();
			std::string strCmd=ReadString();
			pConfig->strServiceCmd=strCmd;
			if(strCmd.compare(STR_PhSigLcId_Check)==0)
			{
				this->SetPacketType(PhSigLcId_Check);
			}else if(strCmd.compare(SRT_ConfigService_ClientReq)==0)
			{
				this->SetPacketType(ConfigService_ClientReq);
			}else if(strCmd.compare(STR_wtlogin_login)==0)
			{
				this->SetPacketType(wtlogin_login);
			}else if(strCmd.compare(STR_wtlogin_trans_emp)==0)
			{
				this->SetPacketType(wtlogin_trans_emp);
			}else if(strCmd.compare(STR_GrayUinPro_Check)==0)
			{
				this->SetPacketType(GrayUinPro_Check);
			}else if(strCmd.compare(STR_friendlist_GetTroopListReqV2)==0)
			{
				this->SetPacketType(friendlist_GetTroopListReqV2);
			}else if(strCmd.compare(STR_OidbSvc_0x7a2_0)==0)
			{
				this->SetPacketType(OidbSvc_0x7a2_0);
			}else if(strCmd.compare(STR_StatSvc_register)==0)
			{
				this->SetPacketType(StatSvc_register);
			}else if(strCmd.compare(STR_account_RequestBindMobile)==0)
			{
				this->SetPacketType(account_RequestBindMobile);
			}else if(strCmd.compare(STR_account_RequestUploadAddressBookV2)==0)
			{
				this->SetPacketType(account_RequestUploadAddressBookV2);
			}else if(strCmd.compare(STR_account_RequestQueryQQBindingStat)==0)
			{
				this->SetPacketType(account_RequestQueryQQBindingStat);
			}else if(strCmd.compare(STR_account_RequestVerifyBindingSmscode)==0)
			{
				this->SetPacketType(account_RequestVerifyBindingSmscode);
			}else if(strCmd.compare(STR_account_RequestQueryQQMobileContactsV3)==0)
			{
				this->SetPacketType(account_RequestQueryQQMobileContactsV3);
			}else if(strCmd.compare(STR_account_RequestCancelBindMobile)==0)
			{
				this->SetPacketType(account_RequestCancelBindMobile);
			}else if(strCmd.compare(STR_account_RequestUploadAddressBook)==0)
			{
				this->SetPacketType(account_RequestUploadAddressBook);
			}else if(strCmd.compare(STR_account_RequestUpdateAddressBook)==0)
			{
				this->SetPacketType(account_RequestUpdateAddressBook);
			}else if(strCmd.compare(STR_SummaryCard_ReqSearch)==0)
			{
				this->SetPacketType(SummaryCard_ReqSearch);
			}else if(strCmd.compare(STR_EncounterSvc_ReqGetEncounter)==0)
			{
				this->SetPacketType(EncounterSvc_ReqGetEncounter);
			}
			else
			{
				this->SetPacketType(TYPE_HULUE);
			}
			return RESULT_SUCCESS;
		}break;
	}
	return ERR_ANALYSIS_PACKET;
}

unsigned int CCommonUnPack::DispatchCmd(void *pModel)
{
	switch(GetPackType())
	{
		case TYPE_MSF:
		case HeartBeat_Alive:
			{
				return RESULT_SUCCESS;
			}break;
		case PhSigLcId_Check:
			{
				this->pConfig->unknow1=ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				ReadString();
			}break;
		case ConfigService_ClientReq:
			{
				//暂不处理
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
			}break;
		case wtlogin_login:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				int l=pack.reverse(pack.read<int>());
				if(pack.read<char>()!=0x2)
					return ERR_ANALYSIS_PACKET;
				pack.read<short>();
				if(pack.reverse(pack.read<short>())!=CONST_wUnKnow2)
					return ERR_ANALYSIS_PACKET;
				pack.read<short>();
				pack.read<short>();
				if(pack.reverse(pack.read<int>())!=pConfig->qq_id)
					return ERR_ANALYSIS_PACKET;
				pack.read<short>();
				pack.read<char>();
				unsigned int dstlen=l-0x15;
				unsigned char *dst=(unsigned char *)malloc(dstlen);
				CTeaCrypt mTea;
				mTea.InitTeaOne();
				mTea.Tea_decrypt((unsigned char*)pack.contents(),dstlen,pConfig->ecdh_key,&dst,&dstlen);
				pack.mpos(l-0x15);
				if(pack.read<char>()!=0x3)
					return ERR_ANALYSIS_PACKET;
				pack.clear();
				pack.append(dst,dstlen);
				free(dst);
				dstlen=0;
				pack.read<short>();//此处0x0009(0x0002）暂时不明
				char cFlag=pack.read<char>();//返回状态
				switch(cFlag)
				{
				case 0://密码正确
					{
						TLV_Decode(pack.reverse(pack.read<short>()));
					}break;
				case 1://密码错误
					{
						return ERR_LOGIN_PASSWORD;
					}break;
				case 2://需要验证码
					{
						TLV_Decode(pack.reverse(pack.read<short>()));
						return ERR_LOGIN_CHECK;
					}break;
				default:
					{
						//登陆失败，原因未知
						return ERR_LOGIN_FAILED;
					}break;
				}
				
			}break;
		case wtlogin_trans_emp:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				int l=pack.reverse(pack.read<int>());
				if(pack.read<char>()!=0x2)
					return ERR_ANALYSIS_PACKET;
				pack.read<short>();
				if(pack.reverse(pack.read<short>())!=CONST_wUnKnow2)
					return ERR_ANALYSIS_PACKET;
				pack.read<short>();
				pack.read<short>();
				if(pack.reverse(pack.read<int>())!=pConfig->qq_id)
					return ERR_ANALYSIS_PACKET;
				pack.read<short>();
				pack.read<char>();
				unsigned int dstlen=l-0x15;
				unsigned char *dst=(unsigned char *)malloc(dstlen);
				CTeaCrypt mTea;
				mTea.InitTeaOne();
				mTea.Tea_decrypt((unsigned char*)pack.contents(),dstlen,pConfig->ecdh_key,&dst,&dstlen);
				pack.mpos(l-0x15);
				if(pack.read<char>()!=0x3)
					return ERR_ANALYSIS_PACKET;
				pack.clear();
				pack.append(dst,dstlen);
				free(dst);
				dstlen=0;
				//分析数据
				pack.read<short>();
				if(pack.reverse(pack.read<short>())!=0x10)
					return ERR_ANALYSIS_PACKET;
				pack.mpos(0x10);
			}break;
		case GrayUinPro_Check:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
			}break;
		case friendlist_GetTroopListReqV2:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
			}break;
		case OidbSvc_0x7a2_0:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
			}break;
		case StatSvc_register:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回包,只解析上线时的返回
				if(pConfig->mRegisterCmd==CmdOnLine)
				{
					ByteBuffer bt;
					bt.append(pack.contents(),pack.size()-pack.rpos());
					CStatSvcRegister mStatSvcRegister;
					mStatSvcRegister.DecodeBody(bt,pConfig->mSvcRespRegister);
				}
			}break;
		case account_RequestBindMobile:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CResponeBindMobile *p=static_cast<CResponeBindMobile*>(pModel);
					CContactBindServlet  mDecodePack;
					mDecodePack.DecodeBody(bt,account_RequestBindMobile,p);
				}
			}break;
		case account_RequestCancelBindMobile:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
			}break;
		case account_RequestUploadAddressBookV2:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CResponeUploadAddressBookV2 *p=static_cast<CResponeUploadAddressBookV2*>(pModel);
					CContactBindServlet  mDecodePack;
					mDecodePack.DecodeBody(bt,account_RequestUploadAddressBookV2,p);
				}
			}break;
		case account_RequestQueryQQBindingStat:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CRespondQueryQQBindingStat *p=static_cast<CRespondQueryQQBindingStat*>(pModel);
					CContactBindServlet  mDecodePack;
					mDecodePack.DecodeBody(bt,account_RequestQueryQQBindingStat,p);
				}
			}break;
		case account_RequestVerifyBindingSmscode:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CResponeVerifySmscode *p=static_cast<CResponeVerifySmscode*>(pModel);
					CContactBindServlet  mDecodePack;
					mDecodePack.DecodeBody(bt,account_RequestVerifyBindingSmscode,p);
				}
			}break;
		case account_RequestQueryQQMobileContactsV3:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CResponeQueryQQMobileContactsV3 *p=static_cast<CResponeQueryQQMobileContactsV3*>(pModel);
					CContactBindServlet  mDecodePack;
					mDecodePack.DecodeBody(bt,account_RequestQueryQQMobileContactsV3,p);
				}
			}break;
		case account_RequestUploadAddressBook:
		case account_RequestUpdateAddressBook:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
			}break;
		case SummaryCard_ReqSearch:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CSummaryCardRespSearch *p=static_cast<CSummaryCardRespSearch*>(pModel);
					LBSService  mDecodePack;
					mDecodePack.DecodeBody(bt,SummaryCard_ReqSearch,p);
				}
			}break;
		case EncounterSvc_ReqGetEncounter:
			{
				ReadString();
				unsigned int m_Flag=pack.reverse(pack.read<int>());
				Deflate(m_Flag,pack);
				//解析返回数据
				ByteBuffer bt;
				bt.append(pack.contents(),pack.size()-pack.rpos());
				if(pModel!=NULL)
				{
					CRespGetEncounterV2 *p=static_cast<CRespGetEncounterV2*>(pModel);
					LBSService  mDecodePack;
					mDecodePack.DecodeBody(bt,EncounterSvc_ReqGetEncounter,p);
				}
			}break;
		default:
			{
				ReadString();
				int m_Flag=pack.reverse(pack.read<int>());
			}break;
	}
	return RESULT_SUCCESS;
}

void CCommonUnPack::SetPacketType(const unsigned short type)
{
	CIUnPackData::SetPacketType(type);
}

std::string CCommonUnPack::ReadString()
{
	std::string str;
	int l=pack.reverse(pack.read<int>());
	if(l-4<=0)
		return str;
	else
	{
		unsigned char *dst=new unsigned char[l-4];
		pack.read(dst,l-4);
		str.append((char*)dst,l-4);
		delete []dst;
		return str;
	}
}

void CCommonUnPack::TLV_Decode(unsigned int n)
{
	if(n==0) return;
	for(int i=0;i<n;i++)
	{
		if(pack.btail()) break;
		unsigned short wCode=pack.reverse(pack.read<short>());
		unsigned short wSize=0;
		switch(wCode)
		{
		case 0x0119:
			{
				wSize=pack.reverse(pack.read<short>());
				unsigned int dstlen=0;
				unsigned char *dst=NULL;
				CTeaCrypt mTea;
				mTea.InitTeaOne();
				mTea.Tea_decrypt((unsigned char*)pack.contents(),wSize,TGTGT_KEY,&dst,&dstlen);
				pack.clear();
				pack.append(dst,dstlen);
				free(dst);
				dstlen=0;
				TLV_Decode(pack.reverse(pack.read<short>()));
			}break;
		case 0x0104:
			{
				wSize=pack.reverse(pack.read<short>());
				unsigned char *dst=(unsigned char*)malloc(wSize);
				if(dst==NULL) return;
				pack.read(dst,wSize);
				pConfig->mCodePngData.sBuf_TLV104.clear();
				pConfig->mCodePngData.sBuf_TLV104.append(dst,wSize);
				free(dst);
				dst=NULL;
			}break;
		case 0x0105:
			{
				pack.read<short>();
				wSize=pack.reverse(pack.read<short>());
				unsigned char *dst=(unsigned char*)malloc(wSize);
				if(dst==NULL) return;
				pack.read(dst,wSize);
				pConfig->mCodePngData.sBuf_TLV105.clear();
				pConfig->mCodePngData.sBuf_TLV105.append(dst,wSize);
				free(dst);
				dst=NULL;
				wSize=pack.reverse(pack.read<short>());
				dst=(unsigned char*)malloc(wSize);
				if(dst==NULL) return;
				pack.read(dst,wSize);
				pConfig->mCodePngData.verifyimage.clear();
				pConfig->mCodePngData.verifyimage.append(dst,wSize);
				free(dst);
				dst=NULL;
			}break;
		case 0x0108:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->ksid,wSize);
			}break;
		case 0x016a:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->no_pic_sig,wSize);
			}break;
		case 0x0106:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->encrypt_a1,wSize);
			}break;
		case 0x010c:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->encrypt_a1+0x70,wSize);
			}break;
		case 0x10a:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->tgt,wSize);
			}break;
		case 0x10d:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->tgt_key,wSize);
			}break;
		case 0x114:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->st,wSize);
			}break;
		case 0x10e:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->st_key,wSize);
			}break;
		case 0x103:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->stwx_web,wSize);
			}break;
		case 0x11f:
			{
				pack.mpos(0x8);
				pConfig->app_pri=pack.reverse(pack.read<int>());
			}break;
		case 0x138:
			{
				wSize=pack.reverse(pack.read<short>());
				int l=pack.reverse(pack.read<int>());
				for(int i=0;i<l;i++)
				{
					short code=pack.reverse(pack.read<short>());
					__int64   value=pack.reverse(pack.read<__int64>());
					pConfig->validList.insert(std::pair<short,__int64>(code,value));
				}
			}break;
		case 0x11a:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.mpos(0x4);
				pConfig->UserName[0]=pack.read<char>();
				pack.read(&(pConfig->UserName[1]),pConfig->UserName[0]);
			}break;
		case 0x120:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->skey,wSize);
			}break;
		case 0x16d:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->paytoken,wSize);
			}break;
		case 0x16c:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->super_key,wSize);
			}break;
		case 0x136:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->openid,wSize);
			}break;
		case 0x305:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->sid,wSize);
				pConfig->isSidFill=true;
			}break;
		case 0x143:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->d2_key,wSize);
			}break;
		case 0x164:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.read(pConfig->aq_sig,wSize);
			}break;
		case 0x118:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.mpos(wSize);
			}break;
		case 0x163:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.mpos(wSize);
			}break;
		case 0x130:
			{
				wSize=pack.reverse(pack.read<short>());
				pack.mpos(0x2);
				pConfig->ServerTime=pack.reverse(pack.read<int>());
				pack.mpos(0x8);
			}break;
		default:
			{
				//跳过此字段解析
				wSize=pack.reverse(pack.read<short>());
				pack.rpos(wSize);
			}break;
		}
	}
}

void CCommonUnPack::Deflate(unsigned int mFlag,ByteBuffer &buffer)
{
	if(mFlag!=0)
	{
		unsigned int len=buffer.reverse(buffer.read<int>());
		len-=4;
		unsigned char *idata=(unsigned char *)malloc(len);
		if(idata==NULL) return;
		memcpy(idata,buffer.contents(),len);
		uLong nodata = len*16;
		unsigned char *odata=(unsigned char *)malloc(nodata);
		if(odata==NULL) return;
		if(zdecompress(idata, len, odata, &nodata) == 0)
		{
			//成功
			buffer.clear();
			buffer.append(odata,nodata);
		}else
		{
			//失败，暂不处理，此处为BUG
		}
		free(idata);
		free(odata);
	}
}