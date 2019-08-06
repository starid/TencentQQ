// MyIOCP.cpp: implementation of the MyIOCP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyIOCP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyIOCP* MyIOCP::pInstance = NULL;

MyIOCP::MyIOCP()
{
	m_bFlood=FALSE;
	m_sSendText="";
	m_iNumberOfMsg=0;
}

MyIOCP::~MyIOCP()
{
	if (NULL != pInstance)
	{
		delete pInstance;
		pInstance = NULL;
	}
}

MyIOCP* MyIOCP::Instantialize()
{
	if (pInstance == NULL)
	{   //double check
		Lock lock;           //用lock实现线程安全，用资源管理类，实现异常安全
		//使用资源管理类，在抛出异常的时候，资源管理类对象会被析构，析构总是发生的无论是因为异常抛出还是语句块结束。
		if (pInstance == NULL)
		{
			pInstance = new MyIOCP();
		}
	}
	return pInstance;
}


//NotifyCode=0x0001
void MyIOCP::NotifyReceivedPackage(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext)
{
//	BYTE PackageType=pOverlapBuff->GetPackageType();
//	switch (PackageType)
//	{
//	case Job_SendText2Client :
//		Packagetext(pOverlapBuff,nSize,pContext);
//		break;
//	case Job_SendFileInfo :
//		PackageFileTransfer(pOverlapBuff,nSize,pContext);
//		break;	
//	case Job_StartFileTransfer: 
//		PackageStartFileTransfer(pOverlapBuff,nSize,pContext);
//		break;
//	case Job_AbortFileTransfer:
//#ifdef TRANSFERFILEFUNCTIONALITY
//		DisableSendFile(pContext->m_Socket);
//#endif
//		break;
//	};
	static_cast<MainCallBack>(pContext->mCall)(pContext->m_Socket, 0x0001, pOverlapBuff->GetBuffer(), pOverlapBuff->GetUsed());

}

/*
 * This functions defines what should be done when A job from the work queue is arrived. 
 * (not used). 
 *
 */
void MyIOCP::ProcessJob(JobItem *pJob,IOCPS* pServer)
{

	switch (pJob->m_command)
	{
	case Job_SendText2Client :
		
		break;
	} 

}


void MyIOCP::AppendLog(CString msg)
{
	TRACE("%s\r\n",msg);
	int nLen = msg.GetLength();
	char *pBuffer = new char[nLen+1]; 
	strcpy(pBuffer,(const char*)msg);
	pBuffer[nLen]='\0';
	BOOL bRet=::PostMessage(m_hWnd, WM_LOGG_APPEND, 0, (LPARAM) pBuffer);
}


//NotifyCode=0x0000
void MyIOCP::NotifyNewConnection(ClientContext *pContext)
{
	unsigned int *pBuffer= new unsigned int;
	if(pBuffer)
		*pBuffer = pContext->m_Socket;
	pContext->mCall = mMainCallBack;
	static_cast<MainCallBack>(pContext->mCall)(pContext->m_Socket, 0x0000, (unsigned char *)pBuffer, sizeof(unsigned int));
	//::PostMessage(m_hWnd, WM_NEW_CONNECTION, 0, (LPARAM) pBuffer);
}

//NotifyCode=0x0002
void MyIOCP::NotifyDisconnectedClient(ClientContext *pContext)
{
	unsigned int *pBuffer= new unsigned int;
	if(pBuffer)
		*pBuffer=pContext->m_Socket;
	static_cast<MainCallBack>(pContext->mCall)(pContext->m_Socket, 0x0002, (unsigned char *)pBuffer, sizeof(unsigned int));
	//::PostMessage(m_hWnd, WM_CLIENTDISCONNECTED, 0, (LPARAM) pBuffer);	
}


void MyIOCP::NotifyNewClientContext(ClientContext *pContext)
{
	pContext->m_iNumberOfReceivedMsg=0;
	pContext->m_bUpdate=FALSE;
}

// Text in a Package is arrived. 
void MyIOCP::Packagetext(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext)
{
	CString txt="";
	BYTE type;
	if(pOverlapBuff->GetPackageInfo(type,txt))
	{
		// to be sure that pcontext Suddenly does not dissapear by disconnection... 
		m_ContextMapLock.Lock();
		pContext->m_ContextLock.Lock();
		pContext->m_sReceived=txt;
		// Update that we have data
		pContext->m_iNumberOfReceivedMsg++;
		pContext->m_bUpdate=TRUE;
		pContext->m_ContextLock.Unlock();
		m_ContextMapLock.Unlock();

		// Update Statistics. 
		m_StatusLock.Lock();
		m_iNumberOfMsg++;
		m_StatusLock.Unlock();
		// Send back the message if we are echoing. 
		// Send Flood if needed. 
		BOOL bRet=FALSE;
		if(m_bFlood)
			bRet=BuildPackageAndSend(pContext,m_sSendText);
		

	}
}



/*
 * This function is called when the remote connection, whant to send a file.  
 *
 */  
void MyIOCP::PackageFileTransfer(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext)
{
#ifdef TRANSFERFILEFUNCTIONALITY
	
	CString sFileName="";
	UINT	iMaxFileSize=0;
	BYTE dummy=0;
	if(pOverlapBuff->GetPackageInfo(dummy,iMaxFileSize,sFileName))
	{
		// Get The Current Path name and application name.
		CString sFilePath="";		
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		CString strTemp;
		GetModuleFileName(NULL,strTemp.GetBuffer(MAX_PATH),MAX_PATH);
		strTemp.ReleaseBuffer();
		_splitpath( strTemp, drive, dir, fname, ext );
		sFilePath=drive; //Drive
		sFilePath+=dir; //dir
		sFilePath+=sFileName; //name.. 
		TRACE("Incoming File >%s.\r\n",sFilePath);
		// Perpare for Receive
	
		if(PrepareReceiveFile(pContext->m_Socket,sFilePath,iMaxFileSize))
		{
			// Send start file transfer.. 
			CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
			if(pOverlapBuff)
			{
				if(pOverlapBuff->CreatePackage(Job_StartFileTransfer))
			     ASend(pContext,pOverlapBuff);

			}
		}else
		{
		   // Abort Transfer. 
			CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
			if(pOverlapBuff)
			{
				if(pOverlapBuff->CreatePackage(Job_AbortFileTransfer))
			     ASend(pContext,pOverlapBuff);

			}
		}
		
		// to be sure that pcontext Suddenly does not dissapear.. 
		m_ContextMapLock.Lock();
		pContext->m_ContextLock.Lock();
		pContext->m_sReceived=sFilePath;
		// Update that we have data
		pContext->m_iNumberOfReceivedMsg++;
		pContext->m_ContextLock.Unlock();
		m_ContextMapLock.Unlock();

		// Update Statistics. 
		m_StatusLock.Lock();
		m_iNumberOfMsg++;
		m_StatusLock.Unlock();
	}
#endif
}

// The remote Connections whant to start the transfer. 
void MyIOCP::PackageStartFileTransfer(CIOCPBuffer *pOverlapBuff,int nSize,ClientContext *pContext)
{
	#ifdef TRANSFERFILEFUNCTIONALITY
	StartSendFile(pContext->m_Socket);
	#endif 
}

BOOL MyIOCP::BuildPackageAndSend(int ClientID, CString sText)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(ClientID);

	if (pContext == NULL)
		return FALSE;
	bRet=BuildPackageAndSend(pContext,sText);
	m_ContextMapLock.Unlock();
	return bRet;
}


// Build the a text message message and send it.. 
BOOL MyIOCP::BuildPackageAndSend(ClientContext *pContext, CString sText)
{
		CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
		if(pOverlapBuff)
		{
			if(pOverlapBuff->CreatePackage(Job_SendText2Client,sText))
			return ASend(pContext,pOverlapBuff);
			else
			{
				AppendLog("CreatePackage(0,sText) Failed in BuildPackageAndSend");
				ReleaseBuffer(pOverlapBuff);
				return FALSE;
			}
		
		}else
		{
			CString msg;
			msg.Format("Could not allocate memory ASend: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
		DisconnectClient(pContext->m_Socket);
			return FALSE;
		}
	return FALSE;	
}

BOOL MyIOCP::BuildFilePackageAndSend(int ClientID,CString sFile)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(ClientID);
	if (pContext == NULL)
		return FALSE;
	bRet=BuildFilePackageAndSend(pContext,sFile);
	m_ContextMapLock.Unlock();
	return bRet;
}

BOOL MyIOCP::BuildPackageAndSendToAll(CString sText)
{
    	CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
		if(pOverlapBuff)
		{
			if(pOverlapBuff->CreatePackage(0,sText))
			return ASendToAll(pOverlapBuff);
			else
			{
				AppendLog("CreatePackage(0,sText) Failed in BuildPackageAndSendToAll");
				ReleaseBuffer(pOverlapBuff);
				return FALSE;
			}
		
		}else
		{
			CString msg;
			msg.Format("Could not allocate memory ASend: %s",ErrorCode2Text(WSAGetLastError()));
			AppendLog(msg);
			return FALSE;
		}
	return FALSE;	
}

/*
 * Perpares for file transfer and sends a package containing information about the file. 
 *
 */
BOOL MyIOCP::BuildFilePackageAndSend(ClientContext *pContext,CString sFile)
{
	#ifdef TRANSFERFILEFUNCTIONALITY
	return PrepareSendFile(pContext->m_Socket,(LPCTSTR)sFile);
	#else
	return FALSE;
	#endif
}

BOOL MyIOCP::BuildStartFileTransferPackageAndSend(int ClientID)
{
	BOOL bRet=FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(ClientID);
	if (pContext == NULL)
		return FALSE;
	bRet= BuildStartFileTransferPackageAndSend(pContext);
	m_ContextMapLock.Unlock();
	return bRet;
}


/*
 * Send a "Start the file transfer package" to the remote connection. 
 *
 *
 */
BOOL MyIOCP::BuildStartFileTransferPackageAndSend(ClientContext *pContext)
{
	CIOCPBuffer *pOverlapBuff=AllocateBuffer(IOWrite);
	if(pOverlapBuff)
	{
		if(pOverlapBuff->CreatePackage(Job_StartFileTransfer))
		return ASend(pContext,pOverlapBuff);
		
	}else
	{
		CString msg;
		msg.Format("Could not allocate memory ASend: %s",ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		DisconnectClient(pContext->m_Socket);
		return FALSE;
	}
	return TRUE;	
}



BOOL MyIOCP::BuildPackageAndSend(int ClientID, ByteBuffer *sText)
{
	BOOL bRet = FALSE;
	m_ContextMapLock.Lock();
	ClientContext* pContext = FindClient(ClientID);

	if (pContext == NULL)
		return FALSE;
	bRet = BuildPackageAndSend(pContext, sText);
	m_ContextMapLock.Unlock();
	return bRet;
}

BOOL MyIOCP::BuildPackageAndSend(ClientContext *pContext, ByteBuffer *sText)
{
	CIOCPBuffer *pOverlapBuff = AllocateBuffer(IOWrite);
	if (pOverlapBuff)
	{
		if (pOverlapBuff->CreatePackage(Job_SendText2Client, *sText))
			return ASend(pContext, pOverlapBuff);
		else
		{
			AppendLog("CreatePackage(0,sText) Failed in BuildPackageAndSend");
			ReleaseBuffer(pOverlapBuff);
			return FALSE;
		}

	}
	else
	{
		CString msg;
		msg.Format("Could not allocate memory ASend: %s", ErrorCode2Text(WSAGetLastError()));
		AppendLog(msg);
		DisconnectClient(pContext->m_Socket);
		return FALSE;
	}
	return FALSE;
}