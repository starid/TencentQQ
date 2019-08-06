#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CCommonUnPack_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CCommonUnPack_API __declspec(dllimport)
#endif

#include "iunpackdata.h"
#include"ConfigData.h"

class DIPPEREXPORTS_CCommonUnPack_API CCommonUnPack :
	public CIUnPackData
{
public:
	CCommonUnPack(void);
	~CCommonUnPack(void);
private:
	unsigned int UnPackHead();
	unsigned int UnPackBody();
public:
	unsigned int UnPackData();
	unsigned int Analysis();
	unsigned int DispatchCmd(void *pModel=NULL);
	unsigned int _check_packet();
	void SetPacketType(const unsigned short);
	std::string ReadString();
	void TLV_Decode(unsigned int n);
	void Deflate(unsigned int mFlag,ByteBuffer &);
public:
	CConfigData *pConfig;
};

