// stdafx.cpp : 只包括标准包含文件的源文件
// Packet.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

#ifdef _DEBUG
#pragma comment(lib,"../LibD/JceProtocol.lib")
#pragma comment(lib,"../LibD/CipherLib.lib")
#pragma comment(lib,"../LibD/UtilLib.lib")
#pragma comment(lib,"json_vc71_libmtd.lib")
#pragma comment(lib,"libprotobuf.lib")
#pragma comment(lib,"libprotobuf-lite.lib")
#pragma comment(lib,"libprotoc.lib")
#else
#pragma comment(lib,"../Lib/JceProtocol.lib")
#pragma comment(lib,"../Lib/CipherLib.lib")
#pragma comment(lib,"../Lib/UtilLib.lib")
#pragma comment(lib,"json_vc71_libmt.lib")
#pragma comment(lib,"libprotobuf.lib")
#pragma comment(lib,"libprotobuf-lite.lib")
#pragma comment(lib,"libprotoc.lib")
#endif