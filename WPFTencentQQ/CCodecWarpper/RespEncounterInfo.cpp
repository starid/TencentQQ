#include "StdAfx.h"
#include "RespEncounterInfo.h"


CRespEncounterInfo::CRespEncounterInfo(void)
{
}


CRespEncounterInfo::~CRespEncounterInfo(void)
{
}


void CRespEncounterInfo::readFrom(CJceInputStream& paramd)
{
	paramd.read(&lEctID,0,true);
	paramd.read(&iDistance,1,true);
	paramd.read(&lTime,2,true);
	paramd.read(&strDescription,3,true);
	paramd.read(&wFace,4,true);
	paramd.read(&cSex,5,true);
	paramd.read(&cAge,6,true);
	paramd.read(&strNick,7,true);
	paramd.read(&cGroupId,8,false);
	paramd.read(&strPYFaceUrl,9,false);
	paramd.read(&strSchoolName,10,false);
	paramd.read(&strCompanyName,11,false);
	paramd.read(&strPYName,12,false);
	paramd.read(&nFaceNum,13,false);
	paramd.read(&strCertification,14,false);
	paramd.read(&shIntroType,15,false);
	paramd.read(&vIntroContent,16,false);
	paramd.read(&vFaceID,17,false);
	paramd.read(&eMerchantType,18,false);
	paramd.read(&eUserIdentityType,19,false);
	paramd.read(&iVoteIncrement,20,false);
	paramd.read(&bIsSingle,21,false);
	paramd.read(&iLat,22,false);
	paramd.read(&iLon,23,false);
	paramd.read(&iRank,24,false);
	paramd.read(&lTotalVisitorsNum,25,false);
	paramd.read(&cSpecialFlag,26,false);
	paramd.read(&vipBaseInfo,27,false);
	paramd.read(&richState,28,false);
	paramd.read(&sig,29,false);
	paramd.read(&enc_id,30,false);
	paramd.read(&uid,31,false);
	paramd.read(&is_trav,32,false);
	paramd.read(&constellation,33,false);
	paramd.read(&profession_id,34,false);
	paramd.read(&vDateInfo,35,false);
	paramd.read(&marriage,36,false);
	paramd.read(&tiny_id,37,false);
	paramd.read(&common_face_timestamp,38,false);
	paramd.read(&stranger_face_timestamp,39,false);
	paramd.read(&authFlag,40,false);
	paramd.read(&iVoteNum,41,false);
	paramd.read(&god_flag,42,false);
	paramd.read(&charm,43,false);
	paramd.read(&charm_level,44,false);
	paramd.read(&watch_color,45,false);
	paramd.read(&charm_shown,46,false);
	paramd.read(&vInterestInfo,47,false);
}
void CRespEncounterInfo::writeTo(CJceOutputStream& paramJceOutputStream)
{
}