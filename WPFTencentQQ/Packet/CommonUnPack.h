#pragma once

#include "iunpackdata.h"
#include"..\Packet\ConfigData.h"

class CCommonUnPack :
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
	unsigned int Analysis(void *pModel=NULL);
	unsigned int _check_packet();
	void SetPacketType(const unsigned short);
public:
	CConfigData *pConfig;
};

