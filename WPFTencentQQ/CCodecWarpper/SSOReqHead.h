#pragma once
#include<string>
#include"../UtilLib/ByteBuffer.h"
class CSSOReqHead
{
public:
	CSSOReqHead(void);
	virtual ~CSSOReqHead(void);
public:
	void init(int,int,int,char,std::string &,std::string &,char const*,int,std::string &,
		std::string &,std::string &,std::string &,std::string &,int);
	int	Length();
	int Length_ver9();
	void deSerialize(ByteBuffer&,int&);
	void serialize(std::string&);
	void serialize_ver8(std::string&);
	void serialize_ver9(std::string&);
public:
	std::string readString(ByteBuffer&);
public:
	int m_Seq;
	int	m_RetCode;
	std::string	a;
	std::string	b;
	std::string	c;
	int m_Flag;
};

