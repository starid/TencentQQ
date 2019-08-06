#include "StdAfx.h"
#include <WinSock.h>
#include "CommonUnPack.h"
#include"Packet.h"
#include"LoginHead.h"
#include"protocol_type.h"
#include"..\Packet\CommHead.h"
#include"ClassModel.h"
#include"FolderList.h"


CCommonUnPack::CCommonUnPack(void)
{
}

CCommonUnPack::~CCommonUnPack(void)
{
}

unsigned int CCommonUnPack::UnPackHead()
{
	short version=pack.reverse(pack.read<short>());
	short packettype=pack.reverse(pack.read<short>());

	switch(packettype)
	{
	case Type00D1:
		{
			return -1;
		}break;
	default:
		{
			//其他数据包
			this->SetPacketType(packettype);
		}break;
	}
	//解析头部数据
	switch(GetPackType())
	{
		case Type0825:
		case Type0836:
		case Type0828:
		default:
			{
				CCommHeadResp *p=static_cast<CCommHeadResp *>(pHead);
				p->Hda.version=version;
				p->Hda.code=packettype;
				p->Hda.serial=pack.read<short>();
				p->Hda.qq_id=pack.read<int>();
				pack.read(p->Hda.fix,sizeof(p->Hda.fix));
				if(pConfig->net_type==NET_UDP)
				{
					p->_head_offset=1;
					p->_head_len=sizeof(p->Hda);
					p->_body_offset=p->_head_offset+p->_head_len;
					p->_body_len=pack.size()-p->_body_offset-1;   //减去末尾EndMark
				}
			}break;
	}
	return 0;
}

unsigned int CCommonUnPack::UnPackBody()
{
	unsigned char *dst=NULL;
	unsigned int bytes=0;
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	switch(GetPackType())
	{
	case Type0825:
		{
			CCommHeadResp *p = static_cast<CCommHeadResp *>(pHead);
			unsigned char *src=(unsigned char *)malloc(p->_body_len);
			if(src==NULL) return -1;
			pack.read(src,p->_body_len);
			mTea.Tea_decrypt(src,p->_body_len,pConfig->key0825,&dst,&bytes);
			free(src);
			src=NULL;
		}break;
	case Type0836:
		{
			CCommHeadResp *p = static_cast<CCommHeadResp *>(pHead);
			unsigned char *src=(unsigned char *)malloc(p->_body_len);
			if(src==NULL) return -1;
			pack.read(src,p->_body_len);
			mTea.Tea_decrypt(src,p->_body_len,pConfig->ecdh_key,&dst,&bytes);		//解密方式可能有变化，先ecdh_key解密，后vague_key解密
			free(src);
			src=NULL;

			pConfig->LoginVerifyCode=RESULT_UNKNOW;
			//第一次判断略
			if(*(short*)dst==0x0133)
			{
				//号码已被回收
				pConfig->LoginVerifyCode=ID_ALREADY_RECOVERY;
				break;
			}else if(*(short*)dst==0x0134)
			{
				if(*(short*)(dst+0xb)==0x1701)
				{
					pConfig->LoginVerifyCode=NEED_REINPUTPWD;
				}else if(*(short*)(dst+0xb)==0x0201)
				{
					pConfig->LoginVerifyCode=PWD_ERROR;
				}else
					pConfig->LoginVerifyCode=PWD_ERROR;
				break;
			}else if(*(short*)dst==0x01fb)
			{
				//输入验证码情况
				pConfig->LoginVerifyCode=NEED_CHECKCODE;
				break;
			}
			else if (*(short*)dst == 0x0534)
			{
				pConfig->LoginVerifyCode = ID_PWD_ERROR;
				break;
			}
			src=(unsigned char *)malloc(bytes);
			memset(src,0,bytes);
			memcpy(src,dst,bytes);
			free(dst);
			dst=NULL;
			mTea.Tea_decrypt(src,bytes,pConfig->vague_key,&dst,&bytes);		//解密方式可能有变化，先ecdh_key解密，后vague_key解密
			free(src);
			src=NULL;
		}break;
	case Type0104:
		{
			CCommHeadResp *p = static_cast<CCommHeadResp *>(pHead);
			unsigned char *src=(unsigned char *)malloc(p->_body_len);
			if(src==NULL) return -1;
			pack.read(src,p->_body_len);
			mTea.Tea_decrypt(src,p->_body_len,pConfig->key0104,&dst,&bytes);
			free(src);
			src=NULL;
			pConfig->LoginVerifyCode=RESULT_NORMAL;
		}break;
	case Type00BA:
		{
			CCommHeadResp *p = static_cast<CCommHeadResp *>(pHead);
			unsigned char *src=(unsigned char *)malloc(p->_body_len);
			if(src==NULL) return -1;
			pack.read(src,p->_body_len);
			mTea.Tea_decrypt(src,p->_body_len,pConfig->key00BA,&dst,&bytes);
			free(src);
			src=NULL;
			pConfig->LoginVerifyCode=RESULT_NORMAL;
		}break;
	case Type0828:
		{
			CCommHeadResp *p = static_cast<CCommHeadResp *>(pHead);
			unsigned char *src=(unsigned char *)malloc(p->_body_len);
			if(src==NULL) return -1;
			pack.read(src,p->_body_len);
			mTea.Tea_decrypt(src,p->_body_len,pConfig->key0836ret2,&dst,&bytes);
			free(src);
			src=NULL;
		}break;
	default:
		{
			//登陆之后的数据包
			CCommHeadResp *p=static_cast<CCommHeadResp *>(pHead);
			unsigned char *src=(unsigned char *)malloc(p->_body_len);
			if(src==NULL) return -1;
			pack.read(src,p->_body_len);
			mTea.Tea_decrypt(src,p->_body_len,pConfig->SessionKey,&dst,&bytes);
			free(src);
			src=NULL;
		}break;
	}
	pack.clear();
	pack.append(dst,bytes);
	free(dst);
	dst=NULL;
	return 0;
	
}

unsigned int CCommonUnPack::_check_packet()
{
	if(pack.read<char>(0)==(char)StartMark)
	{
		//udp
		unsigned char sch=pack.read<char>();
		unsigned char ech=pack.read<char>(pack.size()-1);
		if(sch==StartMark&&ech==EndMark)
		{
			//数据包正确,udp
			if(pConfig->net_type!=NET_UDP)
			{
				return -1;
			}

		}else
		{
			return -1;
		}

	}else if(pack.read<short>(0)==pack.size())
	{
		//tcp
		unsigned char sch=pack.read<char>(1);
		unsigned char ech=pack.read<char>(pack.size()-3);
		if(sch==StartMark&&ech==EndMark)
		{
			//数据包正确,udp
			if(pConfig->net_type!=NET_TCP)
			{
				return -1;
			}

		}else
		{
			return -1;
		}
	}
		//保存特征码
		//保存序列号
		//保存QQ号码
		//取word字
		//QQ号码与本地登录号码校验
		//长度-0xF（长度不包含03）
		//取出0xE偏移之后数据，共0x78字节
		//0x78跟0x100比较
		//0x78/4(右移两位)与0x8比较
		//0825与0x17比较，0xCE比较
	return 0;
}

unsigned int CCommonUnPack::UnPackData()
{	
	unsigned int ret=-1;
	ret=_check_packet();
	if(ret!=0)
	{
		return -1;
	}
	ret=UnPackHead();
	if(ret!=0)
	{
		return -1;
	}
	ret=UnPackBody();
	if(ret!=0)
	{
		return -1;
	}
	return 0;
}

unsigned int  CCommonUnPack::Analysis(void *pModel)
{
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	switch(GetPackType())
	{
		case Type0825:
		{
			unsigned char cResult = pack.read<char>();
			if (cResult == 0xFE)
			{
				pConfig->isTurnIp = TRUE;
			}
			else
				pConfig->isTurnIp = FALSE;
			do
			{
				unsigned short wCode = pack.reverse(pack.read<short>());
				unsigned short wSize = 0;
				switch (wCode)
				{
				case 0x0112:
				{
							wSize = pack.reverse(pack.read<short>());
							pack.read(pConfig->token25ret, SIZE_TOKEN);
				}break;
				case 0x000C:
				{
							//此时IP需要中转时有此数据结构
							wSize = pack.reverse(pack.read<short>());
							pack.mpos(0xc);
							pConfig->ServerIp = pack.reverse(pack.read<int>());
				}break;
				case 0x0017:
				{
							wSize = pack.reverse(pack.read<short>());
							pack.read<short>();
							pConfig->ServerTime = pack.reverse(pack.read<int>());
							pConfig->ClientIp = pack.reverse(pack.read<int>());
							pack.mpos(0x4);
				}break;
				case 0x0310:
				{
							wSize = pack.reverse(pack.read<short>());
							pConfig->ServerIp = pack.reverse(pack.read<int>());
				}break;
				default:
				{
				}break;
				}
			} while (!pack.btail());
			pConfig->LoginVerifyCode = RESULT_NORMAL;
			return 0;
		}break;
		case Type0836:
		{
			if (pConfig->LoginVerifyCode == RESULT_UNKNOW)
			{
				unsigned char cResult = pack.read<char>();
				if (cResult == 0x00)
				{
					pConfig->LoginVerifyCode = RESULT_NORMAL;
				}
				else if (cResult==0x01)
				{
					pConfig->LoginVerifyCode = NEED_LOGINVERIFYAGAIN;
				}
				else if (cResult == 0x3F)
				{
					pConfig->LoginVerifyCode = NEED_DEVICE_UNLOCKED;
					return 0;
				}

				do
				{
					unsigned short wCode = pack.reverse(pack.read<short>());
					unsigned short wSize = 0;
					switch (wCode)
					{
					case 0x0109:
					{
								wSize = pack.reverse(pack.read<short>());
								pack.read<short>();
								pack.read(pConfig->key0836ret1, sizeof(pConfig->key0836ret1));
								pack.read<short>();
								memset(pConfig->token36ret, 0, sizeof(pConfig->token36ret));
								pack.read(pConfig->token36ret, sizeof(pConfig->token36ret));      //覆盖0x38 token字段
								pack.read<short>();
								pack.mpos(0x20);//0x20不明数据
								pack.read<short>();
					}break;
					case 0x0103:
					{
								wSize = pack.reverse(pack.read<short>());
								pack.mpos(wSize);
					}break;
					case 0x0110:
					{
								//是否覆盖token36ret
								if (pConfig->LoginVerifyCode == RESULT_NORMAL)
								{
									//不覆盖
									wSize = pack.reverse(pack.read<short>());
									pack.mpos(wSize);//特征码
								}
								else
								{
									wSize = pack.reverse(pack.read<short>());
									pack.read<short>();//特征码
									wSize = pack.reverse(pack.read<short>());
									pack.read(pConfig->token36ret, sizeof(pConfig->token36ret));
								}

					}break;
					case 0x0033:
					{
								wSize = pack.reverse(pack.read<short>());
								pack.mpos(wSize);
					}break;
					case 0x0107:
					{
								wSize = pack.reverse(pack.read<short>());//长度
								pack.read<short>();//特征码
								wSize = pack.reverse(pack.read<short>());//长度
								pack.mpos(wSize);
								pack.read(pConfig->key0836ret2, sizeof(pConfig->key0836ret2));
								pack.read<short>();//特征码
								wSize = pack.reverse(pack.read<short>());//长度
								pConfig->ServerTime = pack.reverse(pack.read<int>());
								pack.read<int>();	//clientip
								pack.read<int>();
								wSize = pack.reverse(pack.read<short>());//长度
								memset(pConfig->verify36ret, 0, sizeof(pConfig->verify36ret));
								pack.read(pConfig->verify36ret, sizeof(pConfig->verify36ret));          //覆盖0x78数据
								pack.mpos(0x10);
								wSize = pack.reverse(pack.read<short>());//长度
								pack.mpos(wSize);
								wSize = pack.reverse(pack.read<short>());//长度
								pack.mpos(wSize);
					}break;
					case 0x0108:
					{
								wSize = pack.reverse(pack.read<short>());//长度
								pack.mpos(0x8);
								pConfig->UserName[0] = pack.read<char>();
								pack.read(&(pConfig->UserName[1]), pConfig->UserName[0]);
								pack.mpos(0xC);
					}break;
					case 0x0115:
					{
								wSize = pack.reverse(pack.read<short>());//长度
								pack.mpos(wSize);
					}break;
					case 0x001E:
					{
								wSize = pack.reverse(pack.read<short>());//长度
								pack.mpos(wSize);
					}break;
					case 0x0006:
					{
								wSize = pack.reverse(pack.read<short>());//长度
								pack.read(pConfig->verify36ret, sizeof(pConfig->verify36ret));

								//解密
								unsigned char *dst = NULL;;
								unsigned int bytes = 0;
								mTea.Tea_decrypt(pConfig->verify36ret, sizeof(pConfig->verify36ret), pConfig->pwd_key, &dst, &bytes);
								//取出返回来的vaguekey
								memcpy(pConfig->vague_key, dst + 0x58, 0x10);             //覆盖了vague_key
								free(dst);
								dst = NULL;
					}break;
					default:
					{
					}break;
					}
				} while (!pack.btail());
			}
			else if (pConfig->LoginVerifyCode == ID_ALREADY_RECOVERY)
			{
				//号码已经被回收
			}
			else if (pConfig->LoginVerifyCode == NEED_CHECKCODE)
			{
				//需要验证码
				if (pack.reverse(pack.read<short>()) != short(0xFB01)) return -1;
				pack.read<char>();
				pack.mpos(0x4);
				if (pack.reverse(pack.read<short>()) != 0x00BA) return -1;
				pack.mpos(0x3);

				int code_type = pack.reverse(pack.read<int>());
				if (code_type == 0x13000501)
				{
					//旧版本验证码
					pack.mpos(0x2);
					if (pack.reverse(pack.read<short>()) != 0x0123) return -1;
					if (pack.reverse(pack.read<short>()) != 0x0038) return -1;
					pack.mpos(0x38);
					unsigned short l = pack.reverse(pack.read<unsigned short>());		//第一部分验证码
					pConfig->mCodePngData.clear();
					pConfig->mCodePngData.append(pack.contents(), l);
					pack.mpos(l);
					if (pack.reverse(pack.read<short>()) != 0x0001) return -1;
					if (pack.reverse(pack.read<short>()) != 0x0028) return -1;
					pack.read(pConfig->data0036ret28, sizeof(pConfig->data0036ret28));
				}
				else if (code_type == 0x15000507)
				{
					//新版验证码
				}
			}
			else if (pConfig->LoginVerifyCode == PWD_ERROR)
			{
				//密码错误
			}
			else if (pConfig->LoginVerifyCode == NEED_REINPUTPWD)
			{
				//"抱歉，请重新输入密码"
			}
			else if (pConfig->LoginVerifyCode == ID_PWD_ERROR)
			{
				//账号或者密码错误
			}
			return 0;
		}break;
		case Type0104:
			{
				//tip数据不分析
				pConfig->LoginVerifyCode=RESULT_NORMAL;
				return 0;
			}break;
		case Type00BA:
			{
				int i=pack.reverse(pack.read<int>());
				if(i==0x13000501)
				{
					//取出0x38字节数据
					pack.mpos(0x2);
					if (pack.reverse(pack.read<short>()) != 0x0123) return -1;
					if (pack.reverse(pack.read<short>()) != 0x0038) return -1;
					pack.read(pConfig->tokenBAret,sizeof(pConfig->tokenBAret));

					//取出第二部分验证码数据
					unsigned short l=pack.reverse(pack.read<unsigned short>());
					pConfig->mCodePngData.append(pack.contents(),l);
				}else if(i==0x14000501)
				{
					//验证码输入错误,需要重新发送验证码
					pack.mpos(0x2);
					if (pack.reverse(pack.read<short>()) != 0x0123) return -1;
					if (pack.reverse(pack.read<short>()) != 0x0038) return -1;
					pack.read(pConfig->tokenBAret,sizeof(pConfig->tokenBAret));

					unsigned short l=pack.reverse(pack.read<unsigned short>());
					pConfig->mCodePngData.clear();
					pConfig->mCodePngData.append(pack.contents(),l);
					pack.mpos(l);
					if (pack.reverse(pack.read<short>()) != 0x0001) return -1;
					if (pack.reverse(pack.read<short>()) != 0x0028) return -1;
					pack.read(pConfig->data0036ret28,sizeof(pConfig->data0036ret28));

				}else if(i==0x14000500)
				{
					//验证通过
					pack.mpos(0x2);
					if (pack.reverse(pack.read<short>()) != 0x0000) return -1;
					if (pack.reverse(pack.read<short>()) != 0x0038) return -1;
					pack.read(pConfig->tokenBAret,sizeof(pConfig->tokenBAret));  //附在0x0836中发送
				}
				pConfig->LoginVerifyCode=RESULT_NORMAL;
				return 0;
			}break;
		case Type0828:
		{
				if (pack.read<char>() != 0x0)
				{
					pConfig->LoginVerifyCode = LOGIN_FAILED;
					return 0;
				}
				if (pack.reverse(pack.read<short>()) == 0x000d)
				{
					if (pack.reverse(pack.read<short>()) != 0x06) return -1;
					pack.mpos(0x06);
				}
				if (pack.reverse(pack.read<short>()) == 0x001f)
				{
					if (pack.reverse(pack.read<short>()) != 0x22) return -1;
					pack.mpos(0x22);
				}
				if (pack.reverse(pack.read<short>()) == 0x0014)
				{
					if (pack.reverse(pack.read<short>()) != 0x04) return -1;
					pack.mpos(0x04);
				}
				if (pack.reverse(pack.read<short>()) == 0x010c)
				{
					if (pack.reverse(pack.read<short>()) != 0x73) return -1;
					ByteBuffer tmp = pack;
					pack.mpos(0x73);

					if (tmp.reverse(tmp.read<short>()) != 0x01) return -1;
					tmp.read(pConfig->SessionKey, sizeof(pConfig->SessionKey));
				}
				if (pack.reverse(pack.read<short>()) == 0x010e)
				{
					if (pack.reverse(pack.read<short>()) != 0x56) return -1;
					pack.read<short>();
					if (pack.reverse(pack.read<short>()) != 0x52) return -1;
					pack.read<unsigned int>();
					pack.read<unsigned int>();
					if (pack.reverse(pack.read<short>()) != 0x18) return -1;
					pack.mpos(0x18);
					if (pack.reverse(pack.read<short>()) != 0x20) return -1;
					pack.read(pConfig->ClientKey, sizeof(pConfig->ClientKey));
				}
				pConfig->LoginVerifyCode = RESULT_NORMAL;
				return 0;
		}break;
		case Type0027:
			{
				if (pModel == NULL) return -1;
				FolderList* pFriendsList=static_cast<FolderList*>(pModel);
				if (pConfig->net_type != NET_UDP) return -1;

				PacketRet0027 mPacketRet={0};
				mPacketRet.cResult=pack.read<char>();
				//第一个字节0xFF表示此列表一个数据包返回完毕

				//解析
				int num=(pack.size()-pack.rpos())/sizeof(PacketRet0027_Friend);
				for(int i=0;i<num;i++)
				{
					PacketRet0027_Friend mFriends;
					mFriends.dwUin=htonl(pack.read<unsigned int>());
					mFriends.cType=pack.read<char>();
					mFriends.dwIp=htonl(pack.read<unsigned int>());
					mFriends.wPort=htons(pack.read<short>());
					mFriends.wStatus=htons(pack.read<short>());
					mFriends.wProtocol=htons(pack.read<short>());
					mFriends.cMode=pack.read<char>();
					mFriends.dwClientType=htonl(pack.read<unsigned int>());
					mFriends.cStatusFlag=pack.read<char>();
					mFriends.cMicroMsgStatus=pack.read<char>();
					mFriends.cNetType=pack.read<char>();
					mFriends.cAudioDevFlag=pack.read<char>();
					mFriends.cNetWorkStatusExFlag=pack.read<char>();
					pack.read(mFriends.buffReserved,sizeof(mFriends.buffReserved));
					mFriends.dwUinLevel=htonl(pack.read<unsigned int>());
					mFriends.wRsSeq=htons(pack.read<short>());
					mFriends.cRsRefresh=pack.read<char>();
					mFriends.wStatusSeq=htons(pack.read<short>());
					mFriends.wReserve=htons(pack.read<short>());
					mPacketRet.FriendsList.push_back(mFriends);
				}
				//初始化好友状态信息
				pFriendsList->InitFriendsStatus(mPacketRet);
				return 0;
			}break;
		case Type0001:
			{
				if(pModel==NULL) return -1;
				FolderList* pFolderList=static_cast<FolderList*>(pModel);
				if (pConfig->net_type != NET_UDP) return -1;

				PacketRet0001 mPacketRet={0};
				mPacketRet.cSubCmd=pack.read<char>();
				mPacketRet.cResult=pack.read<char>();
				mPacketRet.cVer=pack.read<char>();
				mPacketRet.cTotal=pack.read<char>();
				mPacketRet.dwSeq=pack.reverse(pack.read<unsigned int>());
				mPacketRet.cTotalPageNum=pack.read<char>();
				mPacketRet.cPageNum=pack.read<char>();
				mPacketRet.cFolderNum=pack.read<char>();

				for(int i=0;i<mPacketRet.cFolderNum;i++)
				{
					PacketRet0001_FriendsFolder mFolder;
					mFolder.wLen=pack.reverse(pack.read<short>());
					mFolder.cFolderSvrIndex=pack.read<char>();
					mFolder.cGroupSeq=pack.read<char>();
					mFolder.cFolderLen=pack.read<char>();
					unsigned char *dst=(unsigned char*)malloc(mFolder.cFolderLen+1);
					if (dst == NULL) return -1;
					memset(dst,0,mFolder.cFolderLen+1);
					pack.read(dst,mFolder.cFolderLen);
					mFolder.strFolderName.append((char*)dst,mFolder.cFolderLen);
					free(dst);dst=NULL;
					mPacketRet.FriendsFolderList.push_back(mFolder);
				}
				//加载分组信息
				pFolderList->InsertCluster(mPacketRet);
				return 0;
			}break;
		case Type00CE:
			{
				if (pModel == NULL) return -1;
				PTextMsg pTextMsg=static_cast<PTextMsg>(pModel);

				pTextMsg->Uin=htonl(pack.read<unsigned int>());
				//pack.mpos(0x76);
				pTextMsg->Time=htonl(pack.read<unsigned int>());
				pTextMsg->MsgContent="111111111111";
				return 0;
			}break;
		case Type0134:
			{
				if (pModel == NULL) return -1;
				FolderList* pFolderList=static_cast<FolderList*>(pModel);

				PacketRet0134 mPacketRet;
				mPacketRet.cResult=pack.read<char>();
				mPacketRet.wFriendNum=pack.reverse(pack.read<short>());
				mPacketRet.dwNewFriendListSeq=pack.reverse(pack.read<unsigned int>());
				mPacketRet.dwNewTime=pack.reverse(pack.read<unsigned int>());
				mPacketRet.dwRefreshTime=pack.reverse(pack.read<unsigned int>());
				mPacketRet.cOver=pack.read<char>();
				mPacketRet.wIndex=pack.reverse(pack.read<short>());
				mPacketRet.arstUin=pack.reverse(pack.read<short>());
				for(int i=0;i<mPacketRet.wFriendNum;i++)
				{
					PacketRet0134_FriendsFolder mFriendsFolder={0};
					mFriendsFolder.dwUin=pack.reverse(pack.read<unsigned int>());
					mFriendsFolder.cUinType=pack.read<char>();
					mFriendsFolder.cUinFlags1=pack.read<char>();
					mFriendsFolder.cUinFlags2=pack.read<char>();
					mFriendsFolder.cUinFlags3=pack.read<char>();
					mFriendsFolder.cUinFlags4=pack.read<char>();
					mFriendsFolder.arrFolderIDList=pack.reverse(pack.read<short>());
					if(mFriendsFolder.arrFolderIDList==0x0001) 
					{
						//好友
						mFriendsFolder.arrFolderIndex=pack.reverse(pack.read<short>());
					}else
					{
						//群
						mFriendsFolder.arrFolderIndex=0x00;
					}
					mPacketRet.FriendsFolderList.push_back(mFriendsFolder);
				}
				//加载好友信息
				pFolderList->InsertFolder(mPacketRet);
				return 0;
			}break;
		default:
			{
				return 0;
			}break;
	}
}

void CCommonUnPack::SetPacketType(const unsigned short type)
{
	CIUnPackData::SetPacketType(type);
	switch(type)
	{
		case Type0825:
		case Type0836:
		case Type0104:
		case Type00BA:
		case Type0828:
		default:
			{
				this->pHead=new CCommHeadResp();
			}break;
	}
}