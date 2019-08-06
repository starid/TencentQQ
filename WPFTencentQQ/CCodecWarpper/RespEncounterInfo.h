#pragma once
#include"PacketType.h"
#include"../JceProtocol/JceStruct.h"
#include"../JceProtocol/JCELong.h"
#include"../JceProtocol/JCEShort.h"
#include"../JceProtocol/JCEChar.h"
#include"VipBaseInfo.h"
#include"RishState.h"

class CRespEncounterInfo:public JCE::CJceStruct
{
public:
	CRespEncounterInfo(void);
	virtual ~CRespEncounterInfo(void);
public:
	JCE::JCELong lEctID;
	JCE::JCEInt iDistance;
	JCE::JCEInt lTime;
	JCE::JCEString strDescription;
	JCE::JCEShort wFace;
	JCE::JCEChar cSex;
	JCE::JCEChar cAge;
	JCE::JCEString strNick;
	JCE::JCEChar cGroupId;
	JCE::JCEString strPYFaceUrl;
	JCE::JCEString strSchoolName;
	JCE::JCEString strCompanyName;
	JCE::JCEString strPYName;
	JCE::JCEInt nFaceNum;
	JCE::JCEString strCertification;
	JCE::JCEShort shIntroType;
	JCE::JCEByteArray vIntroContent;
	JCE::JCEByteArray vFaceID;
	JCE::JCEInt eMerchantType;
	JCE::JCEInt eUserIdentityType;
	JCE::JCEInt iVoteIncrement;
	JCE::JCEChar bIsSingle;
	JCE::JCEInt iLat;
	JCE::JCEInt iLon;
	JCE::JCEInt iRank;
	JCE::JCELong lTotalVisitorsNum;
	JCE::JCEChar cSpecialFlag;
	CVipBaseInfo vipBaseInfo;
	CRishState richState;
	JCE::JCEByteArray sig;
	JCE::JCEString enc_id;
	JCE::JCEString uid;
	JCE::JCEChar is_trav;
	JCE::JCEChar constellation;
	JCE::JCEInt profession_id;
	JCE::JCEByteArray vDateInfo;
	JCE::JCEChar marriage;
	JCE::JCELong tiny_id;
	JCE::JCEInt common_face_timestamp;
	JCE::JCEInt stranger_face_timestamp;
	JCE::JCEChar authFlag;
	JCE::JCEInt iVoteNum;
	JCE::JCEChar god_flag;
	JCE::JCEInt charm;
	JCE::JCEInt charm_level;
	JCE::JCEChar watch_color;
	JCE::JCEChar charm_shown;
	JCE::JCEByteArray vInterestInfo;
public:
	void readFrom(CJceInputStream& paramd);
	void writeTo(CJceOutputStream& paramd);
public:
	unsigned int type(){return StructRespEncounterInfo;};
};

