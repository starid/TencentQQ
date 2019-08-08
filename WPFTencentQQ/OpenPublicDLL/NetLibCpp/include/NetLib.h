#pragma once
#include<WinSock2.h>


//必须由被调用者C#函数在使用完数据后（退出函数时）自己清空堆栈，所以必须使用__stdcall方式
typedef  void(__stdcall *MainCallBack)(unsigned int,unsigned int,unsigned char*,unsigned int);

bool __stdcall	StartTheSystem(
	const int		m_iPortNr,
	const int		m_iMaxNumberOfConnections,
	const int		m_iNrOfIOWorkers,
	const int		m_iNrOfLogicalWorkers,
	const int		m_iMaxNrOfFreeBuff,
	const int		m_iMaxNrOfFreeContext,
	const bool	m_iSendInOrder,
	const bool	m_bReadInOrder,
	const int		m_iNrOfPendlingReads);

bool __stdcall	EndTheSystem();

//_type=0(TCP),_type=1(UDP)
bool __stdcall	OnConnectA(const MainCallBack _render, const unsigned char* mIp, const unsigned int mPort, const unsigned int _type);

void __stdcall OnDisconnect(const unsigned int);

void __stdcall SendPacket(const unsigned int ClientID, const unsigned char *buffer, const unsigned int size);

void __stdcall ChangeNotifyWnd(const HWND mHnd, const unsigned int);

