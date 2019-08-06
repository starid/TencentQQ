#pragma once
#include"../JceProtocol/JceInputStream.h"
#include"../JceProtocol/JceOutputStream.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCEByteArray.h"
#include"../JceProtocol/JCEListArray.h"

//Ô­ÐÍfriendlist/CGetTroopListReqV2.Class
class CGetTroopListReqV2: public JCE::CJceStruct
{
public:
	CGetTroopListReqV2(void);
	virtual ~CGetTroopListReqV2(void);
public:
	JCE::JCELong	uin;
	JCE::JCEChar	bGetMSFMsgFlag;
	JCE::JCEByteArray	vecCookies;
	JCE::JCEListArray	vecGroupInfo;
	JCE::JCEChar	bGroupFlagExt;
	JCE::JCEInt		shVersion;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

