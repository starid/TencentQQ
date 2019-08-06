#include "StdAfx.h"
#include<WinSock.h>
#include "ConfigData.h"
#include <stdlib.h>
#include<string.h>

#pragma comment(lib,"Ws2_32.lib")


CConfigData::CConfigData(void)
{
	clear();
}


CConfigData::~CConfigData(void)
{
}

void CConfigData::restart()
{
	//对所有数据清0
	clear();
}
