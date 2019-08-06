#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CNetHttp_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CNetHttp_API __declspec(dllimport)
#endif

#include<string>
#include"../UtilLib/ByteBuffer.h"


enum HTTP_TYPE
{
	TYPE_POST,
	TYPE_GET
};

class DIPPEREXPORTS_CNetHttp_API CNetHttp
{
public:
	CNetHttp(void);
	~CNetHttp(void);

public:
	bool CoInitialize();
	void UnInitialize();
	bool perform(HTTP_TYPE,std::string,unsigned int,ByteBuffer*);
};

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p);
