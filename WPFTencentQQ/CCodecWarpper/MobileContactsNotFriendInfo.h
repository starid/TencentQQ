#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEBoolean.h"
#include"PacketType.h"

//Ô­ÐÍSecurityAccountServer/MobileContactsNotFriendInfo
class CMobileContactsNotFriendInfo:public JCE::CJceStruct
{
public:
	CMobileContactsNotFriendInfo(void);
	~CMobileContactsNotFriendInfo(void);
public:
	JCE::JCELong bindingDate;
	JCE::JCELong isRecommend;
	JCE::JCEString nickname;
	JCE::JCEString contactsInfoEncrypt;
	JCE::JCEByteArray MobileNoMask;
	JCE::JCELong originBinder;
	JCE::JCEInt accountAbi;
	JCE::JCEInt conType;
	JCE::JCEChar detalStatusFlag;
	JCE::JCEInt iTermType;
	JCE::JCEInt eNetworkType;
	JCE::JCEString strTermDesc;
	JCE::JCELong uAbiFlag;
	JCE::JCEByteArray personalSign;
	JCE::JCEBoolean isUpdateSign;
	JCE::JCELong richTime;
	JCE::JCEBoolean isNew;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructMobileContactsNotFriendInfo;};
};

