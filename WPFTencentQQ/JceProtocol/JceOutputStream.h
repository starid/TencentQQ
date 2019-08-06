#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_CJceOutputStream_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_CJceOutputStream_API __declspec(dllimport)
#endif

#include"../UtilLib/ByteBuffer.h"
#include"JCEIObject.h"
#include"JCEByteArray.h"
#include"JCEListArray.h"
#include"JCEMap.h"

class DIPPEREXPORTS_CJceOutputStream_API CJceOutputStream
{
public:
	CJceOutputStream(void);
	CJceOutputStream(ByteBuffer paramByteBuffer);
	virtual ~CJceOutputStream(void);
private:
	ByteBuffer bs;
protected:
	std::string sServerEncoding /*= "GBK"*/;
public:
	ByteBuffer getByteBuffer();
	void clearbs(){bs.clear();};
	void setServerEncoding(std::string paramString);
private:
	void writeHead(char,int);
	void writeBool(bool,int);
	void writeChar(char,int);			//tag=0
	void writeShort(short,int);			//tag=1
	void writeInt(int,int);				//tag=2
	void writeLong(__int64,int);			//java中long	//tag=3
	void writeFloat(float, int);			//tag=4
	void writeDouble(double, int);		//tag=5
	void writeString(std::string,int);			//tag=6
	void writeStruct(JCE::IObject *paramJceStruct, int paramInt);	//tag=10
	//tag=12字段为空
	void writeByteArray(JCE::JCEByteArray&,int);	//tag=13
	void writeList(JCE::JCEListArray&,unsigned int,int);	//tag=9(list<int>,list<float>,list<double>,list<string>,list<CJceStruct>)
	void writeMap(JCE::JCEMap&,unsigned int,int);	//tag=8
public:
	virtual JCE::IObject *ObjectAlloc(unsigned int);	//基本数据类型内存的分配
	void write(JCE::IObject*,int);		//基本类型

};