#pragma once
#pragma pack(1)
//#ifdef _USRDLL
//#define DIPPER_EXPORTS 1
//#else
//#undef  DIPPER_EXPORTS
//#endif
//
//#ifdef DIPPER_EXPORTS
//#define DIPPEREXPORTS_CONFIG_API __declspec(dllexport)
//#else
//#define DIPPEREXPORTS_CONFIG_API __declspec(dllimport)
//#endif


#include"..\CipherLib\TeaCrypt.h"
#include"..\CipherLib\Ecdh.h"
#include"Packet.h"
#include"../UtilLib/ByteBuffer.h"

#define SIZE_ACCOUNT	0x20
#define SIZE_PWD		0x11	//保证以0结尾数据
#define SIZE_URL		0xFF
#define SIZE_IP			0x20
#define SIZE_TOKEN		0x38
#define SIZE_VERIFY		0x78
#define SIZE_NAME		0x37	//QQ昵称不超过24个字母或者12个汉字
#define SIZE_CODE		0x4		//验证码长度


enum NetType
{
	NET_TCP=0,
	NET_UDP=1
};


class CConfigData
{
private:
	CConfigData(void);
	~CConfigData(void);
	static CConfigData *m_pInstance;
public:
	static CConfigData * GetInstance()
	{
		if (m_pInstance == NULL)  //判断是否第一次调用  
			m_pInstance = new CConfigData();
		return m_pInstance;
	}

public:
	void restart();
private:
	void Init()
	{
		qq_id=0;
		memset(qq_pwd,0,sizeof(qq_pwd));
		memset(pwd_key,0,sizeof(pwd_key));
		mCodePngData.clear();
		memset(IndetifyCode,0,sizeof(IndetifyCode));
		isNeedCode=false;
		memset(host,0,sizeof(host));
		ServerIp=0;
		port=0;
		memset(key0825,0,sizeof(key0825));
		memset(key0836,0,sizeof(key0836));
		memset(key0104,0,sizeof(key0104));
		memset(key00BA,0,sizeof(key00BA));
		memset(token25ret,0,sizeof(token25ret));
		memset(token36ret,0,sizeof(token36ret));
		memset(verify36ret,0,sizeof(verify36ret));
		memset(key0836ret1,0,sizeof(key0836ret1));
		memset(key0836ret2,0,sizeof(key0836ret2));
		memset(data0036ret28,0,sizeof(data0036ret28));
		memset(tokenBAret,0,sizeof(tokenBAret));
		ClientIp=0;
		ServerTime=0;
		memset(UserName,0,sizeof(UserName));
		isTurnIp=false;
		net_type=NET_UDP;
		LoginVerifyCode=RESULT_NORMAL;
		memset(stKey,0,sizeof(stKey));
		memset(ecdh_key,0,sizeof(ecdh_key));
		memset(vague_key,0,sizeof(vague_key));
		memset(login_verify,0,sizeof(login_verify));
		memset(_random_10,0,sizeof(_random_10));
		memset(_random_38,0,sizeof(_random_38));
		memset(SessionKey,0,sizeof(SessionKey));
		memset(ClientKey,0,sizeof(ClientKey));
		mStatus=BeOffine;
		m_iCurrentClientID=0;
	};
public:
	unsigned int qq_id;
	unsigned char qq_pwd[SIZE_PWD];
	unsigned char pwd_key[TEA_KEY_LEN];
	ByteBuffer mCodePngData;
	unsigned char IndetifyCode[SIZE_CODE];				//验证码数据
	bool	isNeedCode;
	char host[SIZE_URL];                //hostname地址
	unsigned int ServerIp;              //ip整形地址
	unsigned int port;
	unsigned char key0825[TEA_KEY_LEN];
	unsigned char key0836[TEA_KEY_LEN];
	unsigned char key0104[TEA_KEY_LEN];
	unsigned char key00BA[TEA_KEY_LEN];
	//返回数据
	unsigned char token25ret[SIZE_TOKEN];             //0825数据包返回token
	unsigned char token36ret[SIZE_TOKEN];			//0836数据包返回token
	unsigned char verify36ret[SIZE_VERIFY];             //0836数据包返回0x78验证数据
	unsigned char key0836ret1[TEA_KEY_LEN];
	unsigned char key0836ret2[TEA_KEY_LEN];
	unsigned char data0036ret28[0x28];
	unsigned char tokenBAret[SIZE_TOKEN];
	unsigned int ClientIp;
	unsigned int ServerTime;
	unsigned char UserName[SIZE_NAME];         //第一字节存储长度
	bool isTurnIp;
	NetType net_type;
	unsigned int LoginVerifyCode;
public:
	unsigned char stKey[ptkey_len];      //0x19字节数据
	unsigned char ecdh_key[key_len];           //加密和解密均使用前十个字节数据（0836数据包）
public:
	unsigned char vague_key[TEA_KEY_LEN];
	unsigned char login_verify[TEA_KEY_LEN];
	unsigned char _random_10[0x10];            //MD5
	unsigned char _random_38[0x10];            //MD5
public:                        //登陆成功之后的key
	unsigned char SessionKey[TEA_KEY_LEN];
	unsigned char ClientKey[TEA_KEY_LEN*2];
public:
	UinStatus mStatus;        //登陆账号状态信息
	int m_iCurrentClientID;		//客户端socket
public:
	void SetID(unsigned int id){ qq_id = id; };
	void SetPassword(unsigned char *password, unsigned int len)
	{
		memcpy(qq_pwd, password, len);
	}
	void SetServer(unsigned int ip, unsigned int p,unsigned int m)
	{ 
		ServerIp = ip;
		port = p;
		if (m == 0)
			net_type = NET_TCP;
		else if (m==1)
			net_type = NET_UDP;
	};
};
