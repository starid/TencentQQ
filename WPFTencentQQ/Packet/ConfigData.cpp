#include "StdAfx.h"
#include<WinSock.h>
#include "ConfigData.h"
#include <stdlib.h>
#include<string.h>
#include"Protocol.h"

#pragma comment(lib,"Ws2_32.lib")


CConfigData *CConfigData::m_pInstance = NULL;

CConfigData::CConfigData(void)
{
	Init();
	CTeaCrypt::initkey(key0825, TEA_KEY_LEN);
	CTeaCrypt::initkey(key0836, TEA_KEY_LEN);
	//CEcdh mEcdh;
	//mEcdh.ecdh_init();
	//mEcdh.ecdh_generate_publicKey(Protocol::GetInstance()->ECDH_PUBLIC_KEY.data(), Protocol::GetInstance()->ECDH_PUBLIC_KEY.size());
	//memcpy(stKey, mEcdh.stKey, sizeof(mEcdh.stKey));
	//memcpy(ecdh_key, mEcdh.key, sizeof(mEcdh.key));

	char st[0x19] = { 0x03, 0x29, 0x6d, 0x50, 0x36, 0x61, 0x54, 0x24, 0xdb, 0x76, 0x4c, 0x5c, 0xc9, 0xc4, 0xa6, 0x43, 0x5c, 0xba, 0x37, 0xa9, 0x92, 0x22, 0xfa, 0xbf, 0x86 };
	char k[0x18] = { 0x48, 0xa7, 0xae, 0xa4, 0xc2, 0xbe, 0x82, 0xce, 0xe2, 0x19, 0xf9, 0x52, 0xb3, 0xb3, 0x8c, 0xb9, 0x8e, 0x66, 0xba, 0x89, 0x86, 0xc3, 0xa0, 0x8a };
	memcpy(stKey, st, sizeof(st));
	memcpy(ecdh_key, k, sizeof(k));

}


CConfigData::~CConfigData(void)
{
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CConfigData::restart()
{
	//对所有数据清0
	Init();
}
