#include "StdAfx.h"
#include "TXUdpSend.h"


SOCKET udp_socket()
{
 return WSASocket(AF_INET, SOCK_DGRAM,IPPROTO_UDP,NULL,0,WSA_FLAG_OVERLAPPED);
}

SOCKET udp_create(const unsigned int h,const unsigned int p)
{  
	//创建套接字   
	SOCKET sockClient = WSASocket(AF_INET, SOCK_DGRAM,IPPROTO_UDP,NULL,0,WSA_FLAG_OVERLAPPED);  
	 if(INVALID_SOCKET == sockClient) 
	 {  
		WSACleanup();//释放套接字资源   
		return INVALID_SOCKET;
	 } 
	 //设置允许非阻塞模式
	 //ULONG ul = 1;
	 //ioctlsocket(sockClient, FIONBIO, &ul);

	//set Recv   and  Send time   out 
	 //int   TimeOut = 3000;   //设置发送超时6秒 
	 //if(setsockopt(sockClient,SOL_SOCKET,SO_SNDTIMEO,(char   *)&TimeOut,sizeof(TimeOut))==SOCKET_ERROR) 
	 //{ 
	 // return ERR_NETINIT;
	 //} 
 
	 //TimeOut = 3000;//设置接收超时6秒 
	 //if(setsockopt(sockClient,SOL_SOCKET,SO_RCVTIMEO,(char   *)&TimeOut,sizeof(TimeOut))==SOCKET_ERROR) 
	 //{ 
	 // return ERR_NETINIT;
	 //} 

	 SOCKADDR_IN    servAddr;    //服务器地址
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family =AF_INET;  
	servAddr.sin_addr.s_addr = h;
	servAddr.sin_port = htons(p); 
	int nServAddlen = sizeof(servAddr);

	//首先对UDP进行connect绑定目的地址和端口，保证首先投递的WSARecvFrom能够正常返回数据
	int nRet=WSAConnect(sockClient,(const sockaddr *)&servAddr,nServAddlen,NULL,NULL,NULL,NULL);

	 if (nRet == SOCKET_ERROR &&
		WSAGetLastError() != WSAEWOULDBLOCK)
	{
		closesocket(sockClient);
		return INVALID_SOCKET;
	}

	 return sockClient;
}

unsigned int udp_net_send(const SOCKET sockClient,const LPWSABUF lpBuffer,const DWORD dwBufferCount,const LPDWORD lpNumberOfBytesSent,const DWORD dwFlags,const LPWSAOVERLAPPED pOlap)
{
	return WSASendTo(sockClient,lpBuffer,dwBufferCount,lpNumberOfBytesSent,dwFlags,NULL,0,pOlap,NULL);
}

unsigned int udp_net_recv(const SOCKET sockClient,LPWSABUF lpBuffer,const DWORD dwBufferCount,LPDWORD lpNumberOfBytesRecv,DWORD *dwFlags,LPWSAOVERLAPPED pOlap)
{
	unsigned int nRetVal=WSARecvFrom(sockClient, 
	lpBuffer, 
	1, 
	lpNumberOfBytesRecv, 
	dwFlags,
	NULL,
	0,
	pOlap, 
	NULL); 
	return nRetVal;
}