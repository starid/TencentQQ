//此处用于定义全局的宏定义
#pragma once
#include"stdafx.h"
#include"..\UtilLib\Ini.h"
#include"..\UtilLib\HelpFunc.h"
#include"..\NetLib\NetLib.h"
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