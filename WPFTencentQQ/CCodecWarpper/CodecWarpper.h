#pragma once
#include"../UtilLib/ByteBuffer.h"
#include "SSOData.h"
class CCodecWarpper
{
public:
	CCodecWarpper(void);
	virtual ~CCodecWarpper(void);
public:
	void CreatePhSigLcIdCheckPacket(std::string &,int,
		std::vector<std::string,std::allocator<std::string>> &,char const*);
	void FixAppid(void);
	void ParseOtherResp(ByteBuffer&);
	void ParsePhSigCheck(ByteBuffer&);
	void ParseRecvData(ByteBuffer &);
	void encodeRequest();
	void getFileStoreKey(/*_JNIEnv **/);
	void getMaxPackageSize(void);
	void getParseFailReturnCode(int,int,int);
	void getParseSuccReturnCode(int);
	void getVersionCode(void);
	void init(/*_JNIEnv *,_jobject *,_jobject *,uchar*/);
	void onConnClose(void);
	void onReceData(ByteBuffer &);
	void parseData(/*_JNIEnv *,_jobject *,_jbyteArray **/);
	void removeAccountKey(/*_JNIEnv *,_jstring **/);
	void setAccountKey(/*_JNIEnv *,_jstring *,_jbyteArray *,_jbyteArray *,_jbyteArray *,_jbyteArray *,_jbyteArray *,_jbyteArray *,_jbyteArray *,_jbyteArray *,_jstring **/);
	void setKsid(/*_JNIEnv *,_jclass *,_jbyteArray **/);
	void setMaxPackageSize(int);
	void setUseSimpleHead(/*_JNIEnv *,_jstring *,uchar*/);
private:
	CSSOData mSSOData;
public://Ìí¼ÓµÄº¯Êý
	std::string readString(ByteBuffer &mBuffer);
};

