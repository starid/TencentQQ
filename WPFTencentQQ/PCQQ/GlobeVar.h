//此处用于定义全局的宏定义
#pragma once
#include"stdafx.h"
#include"..\UtilLib\SimpleIni.h"
#include"..\UtilLib\HelpFunc.h"
#include<NetLib.h>
#include"..\SkinUI\SkinUI.h"

#ifdef _DEBUG
#pragma comment(lib,"../LibD/NetLib.lib")
#pragma comment(lib,"../LibD/UtilLib.lib")
#pragma comment(lib,"../LibD/Packet.lib")
#pragma comment(lib,"../LibD/SkinUI.lib")
#else
#pragma comment(lib,"../Lib/NetLib.lib")
#pragma comment(lib,"../Lib/UtilLib.lib")
#pragma comment(lib,"../Lib/Packet.lib")
#pragma comment(lib,"../Lib/SkinUI.lib")
#endif


namespace GlobeVar
{
	void Error_Check(unsigned int mode);
	void __stdcall MainCallBackHandle(unsigned int, unsigned int, unsigned char*, unsigned int);
};