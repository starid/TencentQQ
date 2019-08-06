#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEChar.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//Ô­ÐÍcom.tencent.msf.service.protocol.push.SvcRespRegister
class CSvcRespRegister:public JCE::CJceStruct
{
public:
	CSvcRespRegister(void);
	virtual ~CSvcRespRegister(void);
public:
	JCE::JCEChar bCrashFlag;
	JCE::JCEChar bLargeSeqUpdate;
	JCE::JCEChar bLogQQ;
	JCE::JCEChar bNeedKik;
	JCE::JCEChar bUpdateFlag;
	JCE::JCEChar cReplyCode;
	JCE::JCEInt iClientPort;
	JCE::JCEInt iHelloInterval; //Ä¬ÈÏ300
	JCE::JCELong iLargeSeq;
	JCE::JCELong lBid;
	JCE::JCELong lServerTime;
	JCE::JCELong lUin;
	JCE::JCEString strClientIP;
	JCE::JCEString strResult;
	JCE::JCELong timeStamp;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

