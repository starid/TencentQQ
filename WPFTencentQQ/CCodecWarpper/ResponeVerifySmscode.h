#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CResponeVerifySmscode_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CResponeVerifySmscode_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEString.h"

//‘≠–ÕŒ¥’“µΩ
class DIPPEREXPORTS_CResponeVerifySmscode_API CResponeVerifySmscode:public JCE::CJceStruct
{
public:
	CResponeVerifySmscode(void);
	~CResponeVerifySmscode(void);
public:
	JCE::JCEByteArray sessionSid;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

