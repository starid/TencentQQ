#include "StdAfx.h"
#include "StreamIn.h"
#include "PacketType.h"
#include "EventLog.h"
#include "LogInfo.h"
#include"InfoB.h"
#include"InfoC.h"
#include"InfoF.h"
#include"MobileContactsFriendInfo.h"
#include"MobileContactsNotFriendInfo.h"
#include"RespEncounterInfo.h"

CStreamIn::CStreamIn(void)
{
}


CStreamIn::~CStreamIn(void)
{
}

JCE::IObject *CStreamIn::ObjectAlloc(unsigned int mType)
{
	JCE::IObject *object=NULL;
	switch(mType)
	{
	case StructEventLog:
		object=new CEventLog();
		break;
	case StructLogInfo:
		object=new LogInfo();
		break;
	case StructInfoC:
		object=new InfoC();
		break;
	case StructInfoB:
		object=new InfoB();
		break;
	case StructInfoF:
		object=new InfoF();
		break;
	case StructMobileContactsNotFriendInfo:
		object=new CMobileContactsNotFriendInfo();
		break;
	case StructMobileContactsFriendInfo:
		object=new CMobileContactsFriendInfo();
		break;
	case StructRespEncounterInfo:
		object=new CRespEncounterInfo();
		break;
	default:
		object=CJceInputStream::ObjectAlloc(mType);
		break;
	}
	return object;
}