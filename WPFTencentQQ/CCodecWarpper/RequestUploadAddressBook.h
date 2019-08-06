#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEListArray.h"

//Ô­ÐÍSecurityAccountServer/RequestUploadAddressBook
class CRequestUploadAddressBook:public JCE::CJceStruct
{
public:
	CRequestUploadAddressBook(void);
	~CRequestUploadAddressBook(void);
public:
	JCE::JCELong nextFlag;
	JCE::JCEString MobileUniqueNo;
	JCE::JCEByteArray sessionSid;
	JCE::JCEListArray AddressBookList;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

