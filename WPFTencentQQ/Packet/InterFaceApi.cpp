#include<Windows.h>
#include"InterFaceApi.h"
#include"LoginReq.h"
#include"CommReq.h"
#include"ConfigData.h"
#include"CommonUnPack.h"
#include"CallArgus.pb.h"
#include"CommHead.h"


void __stdcall _InitId(unsigned int _id)
{
	CConfigData *pConfig = CConfigData::GetInstance();
	pConfig->SetID(_id);
}

void __stdcall _InitPassword(unsigned char *password, unsigned int size)
{
	CConfigData *pConfig = CConfigData::GetInstance();
	pConfig->SetPassword(password,size);
}

void __stdcall _InitServer(unsigned int ip,unsigned int p,unsigned int net_type)
{
	CConfigData *pConfig = CConfigData::GetInstance();
	pConfig->SetServer(ip, p, net_type);
}

void __stdcall _Init0825()
{
}

void __stdcall PackPacket(unsigned char *argu,unsigned int _len, unsigned char **msg,unsigned int *size)
{
	TransmitParameters::CallArgus mCallArgus;
	mCallArgus.ParseFromArray(argu, _len);

	unsigned short _type = mCallArgus.pack_argu().topackargu().type();
	switch (_type)
	{
		case Type0825:
		{
			CConfigData *pConfig=CConfigData::GetInstance();
			CLoginReq _login_packet;   //数据包类型
			_login_packet.SetPacketType(Type0825);
			_login_packet.pConfig=pConfig;
			_login_packet.PackData(); 
			short len = _login_packet.pack.size();
			if (pConfig->net_type==NET_TCP)
				_login_packet.pack.insert(0, htons(len));


			TransmitParameters::Pack *pPack = new TransmitParameters::Pack();
			pPack->set_type(Type0825);
			pPack->set_msg(_login_packet.pack.contents(), _login_packet.pack.size());

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(true);
			pPackArgus->set_allocated_pack_data(pPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);
			if (strPackData.size() > *size)
			{
				//传入的空间过小
			}
			*size = strPackData.size();
			memcpy(*msg, strPackData.c_str(), strPackData.size());

		}break;
		case Type0836:
		{
			CConfigData *pConfig = CConfigData::GetInstance();
			CTeaCrypt::initkey(pConfig->key0836, TEA_KEY_LEN);
			CLoginReq _login_packet;   //数据包类型
			_login_packet.SetPacketType(Type0836);
			_login_packet.pConfig = pConfig;
			_login_packet.PackData();
			short len = _login_packet.pack.size();
			if (pConfig->net_type == NET_TCP)
				_login_packet.pack.insert(0, htons(len));

			TransmitParameters::Pack *pPack = new TransmitParameters::Pack();
			pPack->set_type(Type0836);
			pPack->set_msg(_login_packet.pack.contents(), _login_packet.pack.size());

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(true);
			pPackArgus->set_allocated_pack_data(pPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *size)
			{
				//传入的空间过小
			}
			*size = strPackData.size();
			memcpy(*msg, strPackData.c_str(), strPackData.size());
		}break;
		case 0x0828:
		{
			CConfigData *pConfig = CConfigData::GetInstance();
			CLoginReq _login_packet;   //数据包类型
			_login_packet.SetPacketType(Type0828);
			_login_packet.pConfig = pConfig;
			_login_packet.PackData();
			short len = _login_packet.pack.size();
			if (pConfig->net_type == NET_TCP)
				_login_packet.pack.insert(0, htons(len));

			TransmitParameters::Pack *pPack = new TransmitParameters::Pack();
			pPack->set_type(Type0828);
			pPack->set_msg(_login_packet.pack.contents(), _login_packet.pack.size());

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(true);
			pPackArgus->set_allocated_pack_data(pPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *size)
			{
				//传入的空间过小
			}
			*size = strPackData.size();
			memcpy(*msg, strPackData.c_str(), strPackData.size());
		}break;
		default:
		{
			CConfigData *pConfig = CConfigData::GetInstance();
				
			CCommReq _packet;   //数据包类型
			_packet.SetPacketType(_type);
			_packet.pConfig = pConfig;
			if (mCallArgus.pack_argu().has_topackargu())
				_packet.ptoPackArgus = &mCallArgus.pack_argu().topackargu();
			_packet.PackData();
			short len = _packet.pack.size();
			if (pConfig->net_type == NET_TCP)
				_packet.pack.insert(0, htons(len));

			TransmitParameters::Pack *pPack = new TransmitParameters::Pack();
			pPack->set_type(_type);
			pPack->set_msg(_packet.pack.contents(), _packet.pack.size());

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(true);
			pPackArgus->set_allocated_pack_data(pPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *size)
			{
				//传入的空间过小
			}
			*size = strPackData.size();
			memcpy(*msg, strPackData.c_str(), strPackData.size());
		}break;
	}
}

bool __stdcall unPackPacket(unsigned char *data, unsigned int size, unsigned char **notifymsg, unsigned int *notifysize)
{
	CConfigData *pConfig = CConfigData::GetInstance();
	CCommonUnPack *packet = new CCommonUnPack();
	ByteBuffer b;
	b.append(data, size);
	packet->Wrapping(b);
	packet->pConfig = pConfig;
	packet->UnPackData();
	if (packet->Analysis() != 0)
	{
		TransmitParameters::CallArgus mCallArgus;
		mCallArgus.set_iscallsucess(false);
		std::string strPackData;
		mCallArgus.SerializeToString(&strPackData);
		if (strPackData.size() > *notifysize)
		{
			//传入的空间过小
		}
		*notifysize = strPackData.size();
		memcpy(*notifymsg, strPackData.c_str(), strPackData.size());

		return false;
	}
	packet->pack.rpos(0);
	switch (packet->GetPackType())
	{
		case Type0825:
		{
			TransmitParameters::unPack *punPack = new TransmitParameters::unPack();
			punPack->set_type(Type0825);
			punPack->set_isturnip(pConfig->isTurnIp);
			punPack->set_serverip(pConfig->ServerIp);

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(false);
			pPackArgus->set_allocated_unpack_data(punPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *notifysize)
			{
				//传入的空间过小
			}
			*notifysize = strPackData.size();
			memcpy(*notifymsg, strPackData.c_str(), strPackData.size());

		}break;
		case Type0836:
		{
			TransmitParameters::unPack *punPack = new TransmitParameters::unPack();
			punPack->set_type(Type0836);
			TransmitParameters::LoginResult *pLoginResult = new TransmitParameters::LoginResult();
			switch (pConfig->LoginVerifyCode)
			{
				case RESULT_NORMAL:
				{
					std::string *str = new std::string();
					*str = "RESULT_NORMAL";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(true);
				}break;
				case RESULT_ABNORMAL:
				{
					std::string *str = new std::string();
					*str = "RESULT_ABNORMAL";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case PWD_ERROR:
				{
					std::string *str = new std::string();
					*str = "PWD_ERROR";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case NEED_LOGINVERIFY:
				{
					std::string *str = new std::string();
					*str = "NEED_LOGINVERIFY";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case NEED_LOGINVERIFYAGAIN:
				{
					std::string *str = new std::string();
					*str = "NEED_LOGINVERIFYAGAIN";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case NEED_CHECKCODE:
				{
					std::string *str = new std::string();
					*str = "NEED_CHECKCODE";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case NEED_DEVICE_UNLOCKED:
				{
					std::string *str = new std::string();
					*str = "NEED_DEVICE_UNLOCKED";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);

				}break;
				case ID_ALREADY_RECOVERY:
				{
					std::string *str = new std::string();
					*str = "ID_ALREADY_RECOVERY";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);

				}break;
				case NEED_REINPUTPWD:
				{
					std::string *str = new std::string();
					*str = "NEED_REINPUTPWD";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);

				}break;
				case LOGIN_FAILED:
				{
					std::string *str = new std::string();
					*str = "LOGIN_FAILED";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case ID_PWD_ERROR:
				{
					std::string *str = new std::string();
					*str = "ID_PWD_ERROR";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
				case RESULT_UNKNOW:
				default:
				{
					std::string *str = new std::string();
					*str = "RESULT_UNKNOW";
					pLoginResult->set_allocated_notifymsg(str);
					punPack->set_is0836suc(false);
				}break;
			}

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(false);
			pPackArgus->set_allocated_unpack_data(punPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);
			mCallArgus.set_allocated_loginresult(pLoginResult);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *notifysize)
			{
				//传入的空间过小
			}
			*notifysize = strPackData.size();
			memcpy(*notifymsg, strPackData.c_str(), strPackData.size());
		}break;
		case 0x0828:
		{
			TransmitParameters::unPack *punPack = new TransmitParameters::unPack();
			punPack->set_type(Type0828);
			TransmitParameters::LoginResult *pLoginResult = new TransmitParameters::LoginResult();
			switch (pConfig->LoginVerifyCode)
			{
			case RESULT_NORMAL:
			{
				std::string *str = new std::string();
				*str = "RESULT_NORMAL";
				pLoginResult->set_allocated_notifymsg(str);
				punPack->set_is0828suc(true);
			}break;
			case LOGIN_FAILED:
			{
				std::string *str = new std::string();
				*str = "LOGIN_FAILED";
				pLoginResult->set_allocated_notifymsg(str);
				punPack->set_is0828suc(false);
			}break;
			case RESULT_UNKNOW:
			default:
			{
				std::string *str = new std::string();
				*str = "RESULT_UNKNOW";
				pLoginResult->set_allocated_notifymsg(str);
				punPack->set_is0836suc(false);
			}break;
			}

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(false);
			pPackArgus->set_allocated_unpack_data(punPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);
			mCallArgus.set_allocated_loginresult(pLoginResult);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *notifysize)
			{
				//传入的空间过小
			}
			*notifysize = strPackData.size();
			memcpy(*notifymsg, strPackData.c_str(), strPackData.size());
		}break;
		case Type00EC:
		{
			TransmitParameters::unPack *punPack = new TransmitParameters::unPack();
			punPack->set_type(Type00EC);

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(false);
			pPackArgus->set_allocated_unpack_data(punPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *notifysize)
			{
				//传入的空间过小
			}
			*notifysize = strPackData.size();
			memcpy(*notifymsg, strPackData.c_str(), strPackData.size());

		}break;
		default:
		{
			TransmitParameters::unPack *punPack = new TransmitParameters::unPack();
			punPack->set_type(packet->GetPackType());
			CCommHeadResp *pHead=static_cast<CCommHeadResp*>(packet->pHead);
			punPack->set_seq(pHead->Hda.serial);
			punPack->set_data(packet->pack.contents(), packet->pack.size());

			TransmitParameters::PackArgus *pPackArgus = new TransmitParameters::PackArgus();
			pPackArgus->set_ispack(false);
			pPackArgus->set_allocated_unpack_data(punPack);

			TransmitParameters::CallArgus mCallArgus;
			mCallArgus.set_iscallsucess(true);
			mCallArgus.set_allocated_pack_argu(pPackArgus);

			std::string strPackData;
			mCallArgus.SerializeToString(&strPackData);

			if (strPackData.size() > *notifysize)
			{
				//传入的空间过小
			}
			*notifysize = strPackData.size();
			memcpy(*notifymsg, strPackData.c_str(), strPackData.size());
		}
	}
	delete packet;
	packet = NULL;
	return true;
}