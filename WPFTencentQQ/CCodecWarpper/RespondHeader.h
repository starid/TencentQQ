#pragma once
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCEInt.h"
#include"../JceProtocol/JCEString.h"

//原型SecurityAccountServer/RespondHeader
class CRespondHeader:public JCE::CJceStruct
{
public:
	CRespondHeader(void);
	virtual ~CRespondHeader(void);
public:
	JCE::JCEString account;
	JCE::JCEInt cmd;
	JCE::JCEString ksid;
	JCE::JCEInt requestID;
	JCE::JCEInt result;		//value=(0:bindOK=true,hadBind=false)(107:bindOK=false,hadBind=true)(105:bind_state=false)(106:uin="")(104:返回码不正确)
	//217手机号码不正确。219或者216请求频率太高，请稍后再试。224所属地区运营商暂未支持开通服务。223绑定失败，请稍后再试。
	//其他：请求失败，请稍候重试。（com.tencent.mobileqq.phonecontact/ContactBindObserver定义）
	JCE::JCEInt svrSeqNo;
	JCE::JCEString tips;
	JCE::JCEInt ver;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
};

