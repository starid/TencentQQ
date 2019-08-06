#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_ResponeQueryQQMobileContactsV3_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_ResponeQueryQQMobileContactsV3_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEListArray.h"

//Ô­ÐÍÎªSecurityAccountServer/ResponeQueryQQMobileContactsV3
class DIPPEREXPORTS_ResponeQueryQQMobileContactsV3_API CResponeQueryQQMobileContactsV3:public JCE::CJceStruct
{
public:
	CResponeQueryQQMobileContactsV3(void);
	~CResponeQueryQQMobileContactsV3(void);
public:
	JCE::JCELong nextFlag;
	JCE::JCELong timeStamp;
	JCE::JCEByteArray sessionSid;
	JCE::JCEInt queryFlag;
	JCE::JCEListArray BindFriendContacts;
	JCE::JCEListArray BindNotFriendContacts;
	JCE::JCEString nationCode;
	JCE::JCEString mobileNo;
	JCE::JCEString MobileUniqueNo;
	JCE::JCELong isRecommend;
	JCE::JCELong originBinder;
	JCE::JCELong bindingTime;
	JCE::JCELong lastUsedFlag;
	JCE::JCEInt type;
	JCE::JCELong ConfigVersion;
	JCE::JCELong PopWindowsCount;
	JCE::JCELong PopWindowsTime;
	JCE::JCELong PopCloseCount;
	JCE::JCELong ForcePopSwitch;
	JCE::JCELong nextQueryTimeInterval;
	JCE::JCELong MaxsignTimeStamp;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

