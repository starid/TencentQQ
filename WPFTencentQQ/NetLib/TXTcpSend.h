#pragma once
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

	

SOCKET tcp_socket();
unsigned int tcp_create(const unsigned int h,const unsigned int p);
unsigned int tcp_net_send(const SOCKET sockClient,const LPWSABUF lpBuffer,const DWORD dwBufferCount,const LPDWORD lpNumberOfBytesSent,const DWORD dwFlags,const LPWSAOVERLAPPED pOlap);
unsigned int tcp_net_recv(const SOCKET sockClient,LPWSABUF lpBuffer,const DWORD dwBufferCount,LPDWORD lpNumberOfBytesRecv,DWORD *dwFlags,LPWSAOVERLAPPED pOlap);

