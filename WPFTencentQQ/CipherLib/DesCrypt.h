#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CDESCRYPT_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CDESCRYPT_API __declspec(dllimport)
#endif

enum EncMode
{
	MODE_ECB,
	MODE_CBC,
	MODE_CFB
};

class DIPPEREXPORTS_CDESCRYPT_API CDesCrypt
{
public:
	CDesCrypt(EncMode);
	~CDesCrypt(void);
public:
	void SetKey(unsigned char *sid,unsigned int len);
	void SetIv(unsigned char *iv,unsigned int len);
	void Encrypt(unsigned char *,unsigned int,unsigned char*);
	void Decrypt(unsigned char *,unsigned int,unsigned char*);
};

