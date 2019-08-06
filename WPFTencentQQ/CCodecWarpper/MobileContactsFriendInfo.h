#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"
#include"../JceProtocol/JCEByteArray.h"
#include"PacketType.h"

//Ô­ÐÍSecurityAccountServer/MobileContactsFriendInfo
class CMobileContactsFriendInfo:public JCE::CJceStruct
{
public:
	CMobileContactsFriendInfo(void);
	~CMobileContactsFriendInfo(void);
public:
	JCE::JCEString QQ;
	JCE::JCELong  bindingDate;
	JCE::JCELong	isRecommend;
	JCE::JCEString contactsInfoEncrypt;
	JCE::JCEByteArray MobileNoMask;
	JCE::JCELong originBinder;
	JCE::JCEInt accountAbi;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructMobileContactsFriendInfo;};
};

