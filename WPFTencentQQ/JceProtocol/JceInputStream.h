#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CJceInputStream_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CJceInputStream_API __declspec(dllimport)
#endif

#include"../UtilLib/ByteBuffer.h"
#include"HeadData.h"
#include"JCEIObject.h"
#include"JCEByteArray.h"
#include"JCEMap.h"
#include "JCEListArray.h"
#include "JCEInt.h"
#include<string>
#include<list>
#include<map>

class DIPPEREXPORTS_CJceInputStream_API CJceInputStream
{
protected:
	CJceInputStream(void);
	CJceInputStream(ByteBuffer paramByteBuffer);
	CJceInputStream(JCE::JCEByteArray paramArrayOfByte);
	CJceInputStream(JCE::JCEByteArray paramArrayOfByte,int paramInt);
public:
	virtual ~CJceInputStream(void);
private:
	ByteBuffer bs;
protected:
	std::string sServerEncoding /*= "GBK"*/;
public:
	void clearbs(){bs.clear();};
	void skip(int paramInt);
	void skipField();
	void skipField(char paramByte);
	bool skipToTag(int paramInt);
	void skipToStructEnd();
	ByteBuffer getBs();
	void setServerEncoding(std::string paramString);
	void wrap(unsigned char* paramArrayOfByte,unsigned int cnt);
private:
	bool readBool(int,bool);
	char readChar(int,bool);			//tag=0
	short readShort(int,bool);			//tag=1
	int readInt(int,bool);				//tag=2
	__int64 readLong(int,bool); //java中long	//tag=3
	float readFloat(int paramInt, bool paramBoolean);	//tag=4
	double readDouble(int paramInt, bool paramBoolean);	//tag=5
	std::string readString(int,bool);			//tag=6
	void readStruct(JCE::IObject *paramJceStruct, int paramInt, bool paramBoolean);	//tag=10
	//tag=12字段为空
	void readByteArray(JCE::JCEByteArray&,int,bool);	//tag=13
	void readList(JCE::JCEListArray&,int,bool);	//tag=9(list<int>,list<float>,list<double>,list<string>,list<CJceStruct>)
	void readMap(JCE::JCEMap&,int,bool);	//tag=8
private:
	int peakHead(CHeadData &paramHeadData);
	void readHead(CHeadData &paramHeadData);
	int readHead(CHeadData &paramHeadData, ByteBuffer &paramByteBuffer);
	unsigned int peakType();
public:
	virtual JCE::IObject *ObjectAlloc(unsigned int);	//基本数据类型内存的分配
	void read(JCE::IObject*,int,bool);		//基本类型
};