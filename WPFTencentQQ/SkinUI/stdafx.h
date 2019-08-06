#pragma once

//////////////////////////////////////////////////////////////////////////////////

//MFC 文件
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>

//其他文件
#include "../SkinUI_ScrollBar/detours.h"
#include "../SkinUI_ScrollBar/SkinUI_ScrollBar.h"

//库文件
#ifdef _DEBUG
#pragma comment (lib,"../LibD/SkinUI_ScrollBar.lib")
#pragma comment (lib,"../LibD/Detours.lib")
#else
#pragma comment (lib,"../Lib/SkinUI_ScrollBar.lib")
#pragma comment (lib,"../Lib/Detours.lib")
#endif
#pragma comment(lib,"Gdiplus.lib")
