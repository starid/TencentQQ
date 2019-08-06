#pragma once
#include "dbghelp.h"
#pragma comment(lib, "dbghelp.lib")

void CreateMiniDump(EXCEPTION_POINTERS*,LPCSTR);
BOOL CALLBACK MiniDumpCallback(PVOID,const PMINIDUMP_CALLBACK_INPUT,PMINIDUMP_CALLBACK_OUTPUT);
BOOL IsDataSectionNeeded(const WCHAR* pModuleName);