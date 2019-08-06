#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CMD5_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CMD5_API __declspec(dllimport)
#endif

class DIPPEREXPORTS_CMD5_API CMd5
{
public:
	CMd5(void);
	~CMd5(void);
public:
	void GetMd5(unsigned char *szMd5,size_t len,unsigned char *szData,size_t size);
};

