#pragma once
#pragma pack(1)
#include<array>
class Protocol
{
private:
	Protocol();
	virtual ~Protocol();
	static Protocol *m_pInstance;
public:
	static Protocol * GetInstance()
	{
		if (m_pInstance == NULL)  //判断是否第一次调用
		{
			m_pInstance = new Protocol();
			m_pInstance->LoadProtocol_3727("");
		}
		return m_pInstance;
	}
public:
	bool LoadProtocol_360D(std::string strFile);
	bool LoadProtocol_371B(std::string strFile);
	bool LoadProtocol_3727(std::string strFile);
public:
	unsigned short wSSOVersion;
	unsigned short wClientVersion;
	unsigned short wMainVersion;	//cMainVer cSubVer
	unsigned int	dwPubNo;
	unsigned short wDHVersion;
	unsigned int	dwQDVersion;
	unsigned short wQdCsSubNo;
	unsigned char	cQdCsSubNo;
	unsigned char	cQdSubFixed;
	unsigned char	cOsType;
	unsigned char	bIsWOW64;
	unsigned int	dwDrvVersionInfoHight;
	unsigned int	dwDrvVersionInfoLow;
	std::array<BYTE, 0x10> DEFAULT_QQEXE_MD5;//QQ.exe文件MD5
	std::array<BYTE, 8> bufVersion_TSSafeEdit;//文件版本（2015 5.6.1）
	std::array<BYTE, 8> bufVersion_QScanEngine;//文件版本（2.4.0.0）
	std::array<BYTE, 0x31> ECDH_PUBLIC_KEY;
	std::array<BYTE, 0x19> ST_KEY;
	std::array<BYTE, 0x10> ECDH_KEY;
	std::array<BYTE, 0x10> QD_KEY;
	std::string STR_COMPUTER_ID;
	std::array<BYTE, 0x10> DEFAULT_GUID;//SSOCommon的CComputerIDGenerator::GenerateEx
	std::array<BYTE, 0x10> DEFAULT_GUID2;//标记为GUID2,算法未知
	std::array<BYTE, 0x10> DEFAULT_VAGUE;
	std::array<BYTE, 0x10> COMPUTER_GENERATEG_ID;//AddComputerIdGenerateG算法生成(SSOCommon的CComputerIDGenerator::Generate)
	std::array<BYTE, 0x10> DEFAULT_SID;//GetSSOConfigSid函数生成
	std::array<BYTE, 0x4> DEFAULT_LAN_IP;
};

