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
#pragma comment(lib,"jsoncpp.lib")
#pragma comment(lib,"/debug/libprotobufd.lib")
#pragma comment(lib,"/debug/libprotobuf-lited.lib")
#pragma comment(lib,"/debug/libprotocd.lib")
#else
#pragma comment(lib,"../Lib/JceProtocol.lib")
#pragma comment(lib,"../Lib/CipherLib.lib")
#pragma comment(lib,"../Lib/UtilLib.lib")
#pragma comment(lib,"jsoncpp.lib")
#pragma comment(lib,"/release/libprotobuf.lib")
#pragma comment(lib,"/release/libprotobuf-lite.lib")
#pragma comment(lib,"/release/libprotoc.lib")
#endif