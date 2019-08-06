// NetLib.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include"NetLib.h"
#include <stdlib.h>
#include <process.h>
#include"MyIOCP.h"


MyIOCP *pIocp = MyIOCP::Instantialize();

bool	__stdcall StartTheSystem(
	int		m_iPortNr,
	int		m_iMaxNumberOfConnections,
	int		m_iNrOfIOWorkers,
	int		m_iNrOfLogicalWorkers,
	int		m_iMaxNrOfFreeBuff,
	int		m_iMaxNrOfFreeContext,
	bool	m_iSendInOrder,
	bool	m_bReadInOrder,
	int		m_iNrOfPendlingReads)
{
	if(pIocp->IsStarted())
		EndTheSystem();
	pIocp->m_StatusLock.Lock();
	pIocp->mMainCallBack=0;
	pIocp->m_StatusLock.Unlock();
	if(!pIocp->Start(m_iPortNr,
		m_iMaxNumberOfConnections,
		m_iNrOfIOWorkers,
		m_iNrOfLogicalWorkers,
		m_iMaxNrOfFreeBuff,
		m_iMaxNrOfFreeContext,
		m_iSendInOrder,
		m_bReadInOrder,
		m_iNrOfPendlingReads))
	{
		return false;
	}
	return true;
}

void __stdcall ChangeNotifyWnd(const HWND mHnd, unsigned int mMsg)
{
	//pIocp->m_hWnd=mHnd;
	//pIocp->m_Msg=mMsg;
}

bool __stdcall	EndTheSystem()
{
	if(pIocp!=NULL)
	{
		delete pIocp;
		pIocp=NULL;
	}
	return true;
}

bool __stdcall OnConnectA(MainCallBack _render, char *mIp, const short mPort, const unsigned int _type)
{
	if (!pIocp->IsStarted())
	{
		return false;
	}
	pIocp->mMainCallBack = _render;
	if(pIocp==NULL||!pIocp->Connect(mIp,mPort,_type))
	{
		return false;
	}
	return true;
}

void __stdcall OnDisconnect(unsigned int ClientID)
{
	pIocp->DisconnectClient(ClientID);
}

void __stdcall SendPacket(unsigned int ClientID, unsigned char *buffer,unsigned int size)
{
	ByteBuffer message;
	message.append(buffer, size);
	pIocp->BuildPackageAndSend(ClientID, &message);
}