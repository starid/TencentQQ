#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CECDH_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CECDH_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define ptkey_len	0x19
#define key_len		0x18


class DIPPEREXPORTS_CECDH_API CEcdh
{
public:
	CEcdh(void);
	~CEcdh(void);
private:
	unsigned int nid;    //Õ÷‘≤≤Œ ˝
public:
	void ecdh_init();
	bool ecdh_generate_publicKey(BYTE *,unsigned int len);
public:
	unsigned char stKey[ptkey_len];
	unsigned char key[key_len];
};

