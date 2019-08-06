#include "StdAfx.h"
#include "ReportT1.h"
#include"../MobileQQ/protocol_type.h"
#include<json\json.h>

//¾²Ì¬
unsigned int CReportT1::serialVersionUID=1;

CReportT1::CReportT1(void)
{

}

CReportT1::CReportT1(std::string str1,std::string str2,std::string str3,std::string str4,std::string str5,CConfigData *p)
{
	pConfig=p;
	_os=2;
	_bver=CONST_V;
	_os_v.append((char*)pConfig->mHardware.DEFAULT_OS_VERSION.c_str(),pConfig->mHardware.DEFAULT_OS_VERSION.size());
	_disp_name=CONST_DISP_NAME;
	_btime=CONST_BUILD_TIME;
	_app_v=CONST_APK_V;
	_ksid=str1;
	_sub_app=str2;
	email=str3;
	start=str4;
	oper=str5;
	
}


CReportT1::~CReportT1(void)
{
}

std::string CReportT1::toJasonObj()
{
	Json::Value mRoot;
	std::string str;
	str.append(SIG_HASH);
	mRoot["app_sig"]=Json::Value(str);
	str.clear();
	str.append((char*)CONST_APP_N,sizeof(CONST_APP_N));
	mRoot["app_n"]=Json::Value(str.c_str());
	mRoot["os"]=Json::Value(_os);
	mRoot["bver"]=Json::Value(_bver);
	mRoot["os_v"]=Json::Value(_os_v);
	mRoot["disp_name"]=Json::Value(_disp_name);
	mRoot["btime"]=Json::Value(_btime);
	str.clear();
	str.append(pConfig->mHardware.DEFAULT_BRAND.c_str(),pConfig->mHardware.DEFAULT_BRAND.size());
	mRoot["device"]=Json::Value(str.c_str());
	mRoot["app_v"]=Json::Value(_app_v);
	mRoot["ksid"]=Json::Value(_ksid);
	Json::Value subValue;
	subValue["sub_app"]=Json::Value(_sub_app);
	subValue["app"]=Json::Value(16);
	subValue["rst1"]=Json::Value(0);
	subValue["rst2"]=Json::Value(0);
	subValue["applist"]=Json::Value("");
	subValue["email"]=Json::Value(email);
	subValue["start"]=Json::Value(start);
	subValue["oper"]=Json::Value(oper);
	subValue["uin"]=Json::Value(email);
	subValue["used"]=Json::Value(400);
	subValue["type"]=Json::Value("login");

	Json::Value subsubValue;
	subsubValue["wap"]=Json::Value(3);
	subsubValue["port"]=Json::Value(0);
	subsubValue["sub"]=Json::Value(0x9);
	subsubValue["conn"]=Json::Value(0);
	subsubValue["host"]=Json::Value("");
	subsubValue["rlen"]=Json::Value("1073");
	subsubValue["net"]=Json::Value("0");
	subsubValue["used"]=Json::Value("140");
	subsubValue["ip"]=Json::Value("");
	subsubValue["slen"]=Json::Value("724");
	subsubValue["cmd"]=Json::Value("0x810");
	subsubValue["str"]=Json::Value("");
	subsubValue["rst2"]=Json::Value("0");
	subsubValue["try"]=Json::Value("0");
	subValue["log"].append(subsubValue);
	mRoot["lst"].append(subValue);
	mRoot["sdk_v"]=Json::Value("5");

	Json::FastWriter mWriter;
	return mWriter.write(mRoot);
}