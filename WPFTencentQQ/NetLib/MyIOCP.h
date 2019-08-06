// MyIOCP.h: interface for the MyIOCP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYIOCP_H__4093193A_D0A0_4E6A_82FA_65B17A1FEB71__INCLUDED_)
#define AFX_MYIOCP_H__4093193A_D0A0_4E6A_82FA_65B17A1FEB71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IOCPS.h"
#include"NetLib.h"

#define WM_NEW_CONNECTION	WM_APP + 0x1001
#define WM_LOGG_APPEND	WM_NEW_CONNECTION+1
#define WM_CLIENTDISCONNECTED WM_NEW_CONNECTION+2


class Lock
{
private:
	CCriticalSection m_cs;
public:
	Lock()
	{
		m_cs.Lock();
	}
	~Lock()
	{
		m_cs.Unlock();
	}
};

class MyIOCP : public IOCPS  
{
private:
	MyIOCP();
	//MyIOCP(const MyIOCP&);
	//MyIOCP& operator = (const MyIOCP &);
public:
	static MyIOCP *Instantialize();
	static MyIOCP *pInstance;
	static CCriticalSection cs;
public:
	MainCallBack mMainCallBack;
	CCriticalSection m_StatusLock;
	volatile BOOL m_bFlood;
	CString m_sSendText;
	HWND m_hWnd;


	virtual ~MyIOCP();

	virtual void NotifyNewClientContext(ClientContext *pContext);
	// A client have Disconnected. 
	virtual void NotifyDisconnectedClient(ClientContext *pContext);
	
    virtual void NotifyNewConnection(ClientContext *pcontext);

	// A Package have arrived. 
	virtual void NotifyReceivedPackage(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	
	// Called to do some work. 
	virtual inline void ProcessJob(JobItem *pJob,IOCPS* pServer);

	virtual void AppendLog(CString msg);
	int m_iNumberOfMsg;


	// Text in a Package is arrived. 
	void Packagetext(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	// A File transfer info package is arrived
	void PackageFileTransfer(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	// A start transfering package is arrived. 
	void PackageStartFileTransfer(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext);
	// Build the a text message message and send it.. 
	BOOL BuildPackageAndSend(ClientContext *pContext,CString sText);
	BOOL BuildPackageAndSend(int ClientID,CString sText);
	BOOL BuildPackageAndSendToAll(CString sText);


	// Builds a Package containing info about a filetranser and send it to the Remote Computer
	BOOL BuildFilePackageAndSend(ClientContext *pContext,CString sFile);
	BOOL BuildFilePackageAndSend(int ClientID,CString sFile);

	// Build StartFilsTransfer 
	BOOL BuildStartFileTransferPackageAndSend(ClientContext *pContext);
	BOOL BuildStartFileTransferPackageAndSend(int ClientID);

public:
	//add by wzh
	BOOL BuildPackageAndSend(int ClientID, ByteBuffer *sText);
	BOOL BuildPackageAndSend(ClientContext *pContext, ByteBuffer *sText);
};

#endif // !defined(AFX_MYIOCP_H__4093193A_D0A0_4E6A_82FA_65B17A1FEB71__INCLUDED_)
