#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CRequestBindMobile_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CRequestBindMobile_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//原型SecurityAccountServer/RequestBindMobile
class DIPPEREXPORTS_CRequestBindMobile_API CRequestBindMobile:public JCE::CJceStruct
{
public:
	CRequestBindMobile(void);
	virtual ~CRequestBindMobile(void);
public:
	JCE::JCEString mobileNo;
	JCE::JCEString nationCode;
	JCE::JCELong originBinder;
	JCE::JCEInt	type;//作用未知
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};


typedef struct _BindInfo
{
	std::string strMobileNo;
 	std::string strNationCode;
	std::string strBindUin;
}BindInfo;

typedef struct _BindMobile
{
	std::vector<BindInfo> mBindInfos;
	unsigned int dwCurSel;
}BindMobile;