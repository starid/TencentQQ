#include "StdAfx.h"
#include "LBSService.h"
#include <WinSock.h>
#include"../MobileQQ/protocol_type.h"
#include"Packet.h"
#include"StreamIn.h"
#include"StreamOut.h"
#include"UniPacket.h"
#include"SummaryCardReqHead.h"
#include"addcontacts\search.pb.h"
#include"profilecard\comm.pb.h"
#include"addcontacts\Location.pb.h"
#include"NeighborCommReqHeader.h"


LBSService::LBSService(void)
{
}


LBSService::~LBSService(void)
{
}

ByteBuffer LBSService::Encode(unsigned int type,void *data)
{
	CTXCommPack p1;
	EncodeHead(p1,type,data);
	CTXCommPack p2;
	EncodeBody(p2,type,data);

	mPack.AddByteBuffer(p1.buffer);
	p1.GetBufferOut();
	mPack.AddByteBuffer(p2.buffer);
	p2.GetBufferOut();

	return mPack.buffer;
}

void LBSService::EncodeHead(CTXCommPack &p,unsigned int type,void *data)
{
	std::string strValue;
	switch(type)
	{
	case SummaryCard_ReqSearch:
		{
			strValue=STR_SummaryCard_ReqSearch;
		}break;
	case EncounterSvc_ReqGetEncounter:
		{
			strValue=STR_EncounterSvc_ReqGetEncounter;
		}break;
	}
	p.AddDWord(htonl(0x4+strValue.size()));
	p.AddBuf(strValue.c_str(),strValue.size());
	p.AddDWord(htonl(0x4+pConfig->unknow1.size()));
	p.AddBuf(pConfig->unknow1.c_str(),pConfig->unknow1.size());
	p.AddLenDWord();
}

void LBSService::EncodeBody(CTXCommPack &p,unsigned int type,void *data)
{

	JCE::JCEString strKey1;
	JCE::JCEString strKey2;
	std::string sServantName;
	std::string sFuncName;
	JCE::CJceStruct* pBody=NULL;
	JCE::CJceStruct* pHead=NULL;
	switch(type)
	{
	case SummaryCard_ReqSearch:
		{
			strKey1.value("ReqSearch");
			strKey2.value("ReqHead");
			pBody=static_cast<JCE::CJceStruct*>(data);
			sServantName="SummaryCardServantObj";
			sFuncName="ReqSearch";
			pHead=new CSummaryCardReqHead();
			static_cast<CSummaryCardReqHead*>(pHead)->iVersion.value(2);
		}break;
	case EncounterSvc_ReqGetEncounter:
		{
			strKey1.value("ReqGetEncounterV2");
			strKey2.value("ReqHeader");
			pBody=static_cast<JCE::CJceStruct*>(data);
			sServantName="EncounterObj";
			sFuncName="CMD_GET_ENCOUNTERV2";
			pHead=new CNeighborCommReqHeader();
			static_cast<CNeighborCommReqHeader*>(pHead)->shVersion.value(2);
			static_cast<CNeighborCommReqHeader*>(pHead)->lMID.value(pConfig->qq_id);
			static_cast<CNeighborCommReqHeader*>(pHead)->iAppID.value(CONST_FIXAPPID);
			static_cast<CNeighborCommReqHeader*>(pHead)->eBusiType.value(0);
			static_cast<CNeighborCommReqHeader*>(pHead)->eMqqSysType.value(2);
			static_cast<CNeighborCommReqHeader*>(pHead)->uClientIp.value(0);
			static_cast<CNeighborCommReqHeader*>(pHead)->uClientPort.value(0);
		}break;
	}
	//添加UniPacket
	CStreamOut mStream1;
	//封装body
	mStream1.write(pBody,0);
	JCE::JCEByteArray *p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	JCE::JCEMap	Map1;
	Map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&strKey1,p2));
	mStream1.clearbs();
	
	//封装ReqHead
	mStream1.write(pHead,0);
	delete pHead;
	pHead=NULL;
	p2=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p2->value(mStream1.getByteBuffer());
	Map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&strKey2,p2));
	mStream1.clearbs();
	mStream1.write(&Map1,0);

	//封装UniPacket
	std::map<std::string,std::string> a;			//空map
	UniPacket mUniPacket(3,0,0,CONST_dwRequestId,sServantName,sFuncName,mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	p.AddDWord(htonl(0x4+mStream1.getByteBuffer().size()));
	p.AddBuf((char*)mStream1.getByteBuffer().contents(),mStream1.getByteBuffer().size());
}

void LBSService::DecodeBody(const ByteBuffer &bt,unsigned int type,JCE::CJceStruct* pRetPack)
{
	JCE::JCEString *mKey1=new JCE::JCEString();
	JCE::JCEString *mKey2=new JCE::JCEString();
	switch(type)
	{
	case SummaryCard_ReqSearch:
		{
			mKey1->value("RespSearch");
			mKey2->value("SummaryCard.RespSearch");
		}break;
	case EncounterSvc_ReqGetEncounter:
		{
			mKey1->value("RespGetEncounterV2");
			mKey2->value("EncounterSvc.RespGetEncounterV2");
		}break;
	}
	UniPacket mUniPacket;
	mUniPacket.decode((char*)bt.contents(),bt.size());
	if(mUniPacket._package.sBuffer.value().size()!=0)
	{
		JCE::JCEMap mMap;
		CStreamIn mStreamIn;
		mStreamIn.wrap((unsigned char*)mUniPacket._package.sBuffer.value().contents(),
			mUniPacket._package.sBuffer.value().size());
		mStreamIn.read(&mMap,0,true);
		JCE::JCEMap *pMap=static_cast<JCE::JCEMap *>(mMap._value[mKey1]);
		if(pMap==NULL)
		{
			return;
		}
		JCE::JCEByteArray *pList=static_cast<JCE::JCEByteArray *>(pMap->_value[mKey2]);
		if(pList==NULL)
		{
			return;
		}
		mStreamIn.clearbs();
		mStreamIn.wrap((unsigned char*)pList->value().contents(),pList->value().size());
		mStreamIn.read(pRetPack,0,true);
		delete mKey1;
		delete mKey2;
	}
}