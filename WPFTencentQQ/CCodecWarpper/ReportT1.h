#pragma once
#include<string>
#include"ConfigData.h"
class CReportT1
{
private:
	CReportT1(void);
public:
	CReportT1(std::string str1,std::string str2,std::string str3,std::string str4,
		std::string str5,CConfigData *p);
	virtual ~CReportT1(void);
private:
	unsigned static int serialVersionUID;
	std::string _app_n;
	std::string _app_sig;
	std::string _app_v;
	std::string _btime;
	std::string _bver;
	std::string _disp_name;
	std::string _ksid;
	std::string _sub_app;
	int			_os;
	std::string _os_v;
	std::string _sdk_v;
	std::string email;
	std::string start;
	std::string oper;
public:
	std::string	toJasonObj();
	CConfigData *pConfig;
};

