#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CHardware_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CHardware_API __declspec(dllimport)
#endif

#include<string>
class DIPPEREXPORTS_CHardware_API CHardware
{
public:
	CHardware(void);
	virtual ~CHardware(void);
public:
	std::string DEFAULT_DEVICE_ID_UNIQUENO;
	std::string DEFAULT_IMEI;
	std::string DEFAULT_WIFI_MAC;
	std::string DEFAULT_DEVICE_ID;
	std::string DEFAULT_IMSI;
	std::string DEFAULT_OS_TYPE;
	std::string DEFAULT_OS_VERSION;
	unsigned int DEFAULT_OS_INT_VERSION;
	unsigned short DEFALUT_NETWORK_INT_TYPE;
	std::string DEFAULT_SIM_OPERATOR_NAME;
	std::string DEFAULT_APN;
	std::string DEFAULT_BRAND;
	std::string DEFAULT_ANDROID_ID;
	std::string DEFAULT_BSSID;
	std::string DEFAULT_SSID;
};

