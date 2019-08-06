#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CResponeBindMobile_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CResponeBindMobile_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍÎªSecurityAccountServer/ResponeBindMobile
class DIPPEREXPORTS_CResponeBindMobile_API CResponeBindMobile:public JCE::CJceStruct
{
public:
	CResponeBindMobile(void);
	virtual ~CResponeBindMobile(void);
public:
	JCE::JCEString alreadyBindedUin;
	JCE::JCEByteArray sessionSid;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};