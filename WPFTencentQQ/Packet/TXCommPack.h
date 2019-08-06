#pragma once
#include"../UtilLib/ByteBuffer.h"

#define BUFFER_SIZE	0x200
#pragma pack(1)
class CTXCommPack
{
public:
	CTXCommPack(void);
	CTXCommPack(size_t);
	virtual ~CTXCommPack(void);
public:
	//其中第二个参数为保留参数，设置为1
	void AddByte(const char);
	void AddWord(const short);
	void AddDWord(const int);
	void AddBuf(const char *,const int);
	void AddBufLenWord();
	void AddFieldCode(short);
	//void AddHostName();
	//void GetCaculteGuid(unsigned char *,unsigned int);
	//void AddCaculteGuid();
	//unsigned int AddNewGuid();
	//void AddPwdMd5(unsigned char *,unsigned int);
	//void AddVague(unsigned char *,unsigned int);
	//void AddComputerIdGenerateG(unsigned char *,unsigned int);
	//void AddComputerIdGenerateEx();
	//void AddTGTGT(unsigned char*,unsigned char *,unsigned char *);
	void GetBufferOut();
public:
	//void CaculteGuid(unsigned char *,unsigned int,unsigned char *,unsigned int);
	//unsigned int GetTGTGT(unsigned char **,unsigned char *,unsigned char *,unsigned char *);
	//unsigned char * CaculteTGT(unsigned char *,unsigned char *);
public:
	ByteBuffer buffer;
};





extern unsigned char GENERATEG_SERIE[];
