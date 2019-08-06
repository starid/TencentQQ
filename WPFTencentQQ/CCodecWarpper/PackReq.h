#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CPackReq_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CPackReq_API __declspec(dllimport)
#endif

#include "IPackData.h"
#include"TXCommPack.h"

//登陆数据包定义
#define MAX_PACKET_SIZE 2049


class DIPPEREXPORTS_CPackReq_API CPackReq:
	public CIPackData
{
public:
	CPackReq(void);
	~CPackReq(void);
private:
	unsigned int PackHead(CTXCommPack*,void *data=0);
	unsigned int PackBody(CTXCommPack*,void *data=0);
public:
	unsigned int PackData(void *data=0);
	void	Merge(const ByteBuffer &a);
};

