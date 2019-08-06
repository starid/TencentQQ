#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEListArray.h"

//Ô­ÐÍSecurityAccountServer/RequestUpdateAddressBook
class CRequestUpdateAddressBook:public JCE::CJceStruct
{
public:
	CRequestUpdateAddressBook(void);
	~CRequestUpdateAddressBook(void);
public:
	JCE::JCELong nextFlag;
	JCE::JCEString MobileUniqueNo;
	JCE::JCEByteArray sessionSid;
	JCE::JCEListArray AddressBookAddList;
	JCE::JCEListArray AddressBookDelList;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

