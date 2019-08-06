#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CAddressBookItem_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CAddressBookItem_API __declspec(dllimport)
#endif

#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍSecurityAccountServer/AddressBookItem
class DIPPEREXPORTS_CAddressBookItem_API CAddressBookItem:public JCE::CJceStruct
{
public:
	CAddressBookItem(void);
	~CAddressBookItem(void);
public:
	JCE::JCEString mobileNo;
	JCE::JCEString name;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

