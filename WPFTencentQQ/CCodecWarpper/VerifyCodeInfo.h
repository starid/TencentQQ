#include<string>
#include"../UtilLib/ByteBuffer.h"

//class VerifyCodeInfo
//{
//public:
//	int appSeq;
//	int ssoSeq;	//getRequestSsoSeq
//	int svrSeqNo;
//	std::string uin;
//	std::string verifyNote;
//	ByteBuffer	verifyimage;
//	std::string	verifyurl;
//	std::string	vpicSid;
//	int wupSeq;		//getRequestId
//};

typedef struct
{
	bool		isNeedCode;
	ByteBuffer sBuf_TLV104;
	ByteBuffer sBuf_TLV105;
	ByteBuffer verifyimage;
	std::string	sIndetifyCode;
}VerifyCodeInfo;