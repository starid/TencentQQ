#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CResponeUploadAddressBookV2_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CResponeUploadAddressBookV2_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEListArray.h"

//Ô­ÐÍÎªSecurityAccountServer/ResponeUploadAddressBookV2
class DIPPEREXPORTS_CResponeUploadAddressBookV2_API CResponeUploadAddressBookV2:public JCE::CJceStruct
{
public:
	CResponeUploadAddressBookV2(void);
	~CResponeUploadAddressBookV2(void);
public:
	JCE::JCELong nextFlag;
	JCE::JCEByteArray sessionSid;
	JCE::JCEListArray BindFriendContacts;
	JCE::JCEListArray BindNotFriendContacts;
	JCE::JCELong MaxsignTimeStamp;
	JCE::JCELong timeStamp;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

