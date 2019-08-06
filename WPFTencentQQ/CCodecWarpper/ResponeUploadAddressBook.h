#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CResponeUploadAddressBook_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CResponeUploadAddressBook_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEListArray.h"

//Ô­ÐÍÎªSecurityAccountServer/ResponeUploadAddressBook
class DIPPEREXPORTS_CResponeUploadAddressBook_API CResponeUploadAddressBook:public JCE::CJceStruct
{
public:
	CResponeUploadAddressBook(void);
	~CResponeUploadAddressBook(void);
public:
	JCE::JCELong nextFlag;
	JCE::JCEByteArray sessionSid;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

