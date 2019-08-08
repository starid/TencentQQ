#include "StdAfx.h"
#include "ClassFactory.h"
#include"addcontacts\search.pb.h"
#include"profilecard\comm.pb.h"
#include"../MobileQQ/protocol_type.h"
#include<WinSock2.h>
#include"SOSO_Cell.h"
#include"SOSO_Wifi.h"
#include"ReqGetNearbyPubAcctInfo.h"
#include"StreamOut.h"
#include<json\json.h>
#include"UniPacket.h"


CClassFactory::CClassFactory(void)
{
}


CClassFactory::~CClassFactory(void)
{
}

void CClassFactory::SetCSummaryCardReqSearch(CSummaryCardReqSearch &mSummaryCardReqSearch,std::string strKeyWord,std::string strCountryCode)
{
	mSummaryCardReqSearch.strKeyword.value(strKeyWord);
	mSummaryCardReqSearch.strCountryCode.value(strCountryCode);
	mSummaryCardReqSearch.shVersion.value(3);
	//添加PB部分
	SummaryCardBusiEntry::comm mComm;
	mComm.set_ver(1);
	mComm.set_seq(-1);
	mComm.set_service(80000000);
	mComm.set_platform(2);
	mComm.set_qqver(CONST_QQ_VER);
	mComm.set_build(CONST_QQ_BUILD);
	std::string strcomm=mComm.SerializeAsString();
	AccountSearchPb::search mSearch;
	mSearch.set_start(0);
	mSearch.set_keyword(strKeyWord);
	AccountSearchPb::Location *pLocation=mSearch.mutable_msg_user_location();
	pLocation->set_double_longitude(0.0);//108.940175
	pLocation->set_double_latitude(0.0);//34.341568
	std::string strsearch=mSearch.SerializeAsString();
	JCE::JCEByteArray *p=new JCE::JCEByteArray();
	ByteBuffer bt;
	bt.append(char(0x28));
	bt.append(htonl(strcomm.size()));
	bt.append(htonl(strsearch.size()));
	bt.append(strcomm.c_str(),strcomm.size());
	bt.append(strsearch.c_str(),strsearch.size());
	bt.append(char(0x29));
	p->value(bt);
	mSummaryCardReqSearch.vvReqServices._value.push_back(p);
}

void CClassFactory::SetCReqGetEncounterV2(CReqGetEncounterV2 &mReqGetEncounterV2)
{
	//填充stUserInfo
	mReqGetEncounterV2.stUserInfo.stGps.iLat.value(0);
	mReqGetEncounterV2.stUserInfo.stGps.iLon.value(0);
	mReqGetEncounterV2.stUserInfo.stGps.iAlt.value(-1);
	mReqGetEncounterV2.stUserInfo.stGps.eType.value(0);
	mReqGetEncounterV2.stUserInfo.strAuthName.value("B1_QQ_Neighbor_android");
	mReqGetEncounterV2.stUserInfo.strAuthPassword.value("NzVK_qGE");
	mReqGetEncounterV2.stUserInfo.eLocalInfo.value(2);//LocalInfoType_SOSO=2
	//CSOSO_Wifi *pSOSO_Wifi=new CSOSO_Wifi();
	mReqGetEncounterV2.stUserInfo.vSOSOMac._value.clear();//SOSO_Wifi数据
	CSOSO_Cell *pSOSO_Cell=new CSOSO_Cell();
	pSOSO_Cell->shMcc.value(0x01CC);//460代表中国
	pSOSO_Cell->shMnc.value(0x1);//1代表中国联通，0代表中国移动等等
	pSOSO_Cell->iLac.value(0xbb11);
	pSOSO_Cell->iCellId.value(0x0c11402f);
	pSOSO_Cell->shRssi.value(-1);
	mReqGetEncounterV2.stUserInfo.vSOSOCells._value.push_back(pSOSO_Cell);
	//填充stUserData
	mReqGetEncounterV2.stUserData.lTime.value(0);
	mReqGetEncounterV2.stUserData.iLat.value(900000000);
	mReqGetEncounterV2.stUserData.iLon.value(900000000);
	mReqGetEncounterV2.stUserData.lOriginGrid.value(0);
	mReqGetEncounterV2.stUserData.lNextGrid.value(0);
	mReqGetEncounterV2.stUserData.strProvince.ref_value().clear();
	mReqGetEncounterV2.stUserData.strCookie.ref_value().clear();
	mReqGetEncounterV2.eNewListType.value(0);
	mReqGetEncounterV2.iListSize.value(-1);
	mReqGetEncounterV2.vTagsID._value.clear();
	mReqGetEncounterV2.strA2.ref_value().append(char(0));
	mReqGetEncounterV2.bTraversing.value(0);
	mReqGetEncounterV2.iRadius.value(2000);	//默认2000
	mReqGetEncounterV2.iMaxSearchNum.value(-1);
	mReqGetEncounterV2.iSimpleSort.value(0);
	mReqGetEncounterV2.nearbyGroupReq.ref_value().clear();
	//封装CReqGetNearbyPubAcctInfo
	CReqGetNearbyPubAcctInfo mReqGetNearbyPubAcctInfo;
	mReqGetNearbyPubAcctInfo.shVersion.value(2);
	mReqGetNearbyPubAcctInfo.vContext.ref_value().clear();
	mReqGetNearbyPubAcctInfo.iCount.value(2);
	mReqGetNearbyPubAcctInfo.stLBSInfo.stGps.iLat.value(0);
	mReqGetNearbyPubAcctInfo.stLBSInfo.stGps.iLon.value(0);
	mReqGetNearbyPubAcctInfo.stLBSInfo.stGps.iAlt.value(-1);
	mReqGetNearbyPubAcctInfo.stLBSInfo.stGps.eType.value(0);
	mReqGetNearbyPubAcctInfo.stLBSInfo.vWifis._value.clear();
	pSOSO_Cell=new CSOSO_Cell();
	pSOSO_Cell->shMcc.value(0x01CC);//460代表中国
	pSOSO_Cell->shMnc.value(0x1);//1代表中国联通，0代表中国移动等等
	pSOSO_Cell->iLac.value(0xbb11);
	pSOSO_Cell->iCellId.value(0x0c11402f);
	pSOSO_Cell->shRssi.value(-1);
	mReqGetNearbyPubAcctInfo.stLBSInfo.vCells._value.push_back(pSOSO_Cell);
	mReqGetNearbyPubAcctInfo.stLBSInfo.stAttr.strImei.value("357747058988888");
	mReqGetNearbyPubAcctInfo.stLBSInfo.stAttr.strImsi.value("310260419859463");
	mReqGetNearbyPubAcctInfo.stLBSInfo.stAttr.strPhonenum.ref_value().clear();
	CStreamOut mStream1;
	mStream1.write(&mReqGetNearbyPubAcctInfo,0);
	JCE::JCEByteArray *p1=static_cast<JCE::JCEByteArray *>(mStream1.ObjectAlloc(JCETypeJCEByteArray));
	p1->value(mStream1.getByteBuffer());
	JCE::JCEMap	Map1;
	JCE::JCEString strKey;
	strKey.value("nearby_pubacct");
	Map1._value.insert(std::pair<JCE::JCEString*,JCE::IObject*>(&strKey,p1));
	mStream1.clearbs();
	mStream1.write(&Map1,0);
	//封装UniPacket
	std::map<std::string,std::string> a;			//空map
	UniPacket mUniPacket(3,0,0,1,"PubAccountSvc.nearby_pubacct","nearby_pubacct",mStream1.getByteBuffer(),0,a,a);
	mStream1.clearbs();
	mUniPacket.encode(mStream1);
	
	mReqGetEncounterV2.nearbyPublicAcctReq.ref_value()=mStream1.getByteBuffer();
	mReqGetEncounterV2.random_trav_dis_level.value(0);
	mReqGetEncounterV2.encrypt_proto.value(1);
	mReqGetEncounterV2.constellation.value(0);
	mReqGetEncounterV2.age_lower.value(0);
	mReqGetEncounterV2.age_up.value(0);
	mReqGetEncounterV2.time_interval.value(480);
	mReqGetEncounterV2.profession_id.value(0);
	mReqGetEncounterV2.home_province.value(0);
	mReqGetEncounterV2.home_city.value(0);
	mReqGetEncounterV2.use_tinyid.value(1);
	mReqGetEncounterV2.home_country.value(0);
	mReqGetEncounterV2.support_entrace_type.value(-1);//0x0f
	mReqGetEncounterV2.appoint_params.value();//cmd0x5fb$ReqInfo 
	mReqGetEncounterV2.use_watch.value(0);
	mReqGetEncounterV2.watch_color.value(0);
	mReqGetEncounterV2.interest_id.value(0);
	//extra json数据
	Json::Value mRoot;
	mRoot["posw"]=Json::Value(216);
	mRoot["conn"]=Json::Value(1);
	mRoot["posh"]=Json::Value(150);
	mRoot["c_osver"]=Json::Value("2.3.4");
	mRoot["dtype"]=Json::Value(1);
	mRoot["carrier"]=Json::Value(0);
	mRoot["lng"]=Json::Value(0);
	mRoot["c_os"]=Json::Value("android");
	mRoot["muid"]=Json::Value("BC1D0E533916E80CB5AC4006873E50A2");//MD5(getDeviceId())
	mRoot["lat"]=Json::Value(0);
	Json::FastWriter mWriter;
	mReqGetEncounterV2.ad_extra.value(mWriter.write(mRoot));

	mReqGetEncounterV2.ad_ctrl.value(1);
}