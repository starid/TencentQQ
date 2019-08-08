// stdafx.cpp : 只包括标准包含文件的源文件
// SkinUI.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"




//库文件
#ifdef _DEBUG
#pragma comment (lib,"../LibD/SkinUI_ScrollBar.lib")
#pragma comment (lib,"Detours.lib")
#else
#pragma comment (lib,"../Lib/SkinUI_ScrollBar.lib")
#pragma comment (lib,"Detours.lib")
#endif
#pragma comment(lib,"Gdiplus.lib")


