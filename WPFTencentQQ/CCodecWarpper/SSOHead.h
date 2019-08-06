#pragma once
#include<string>
#include"../UtilLib/ByteBuffer.h"
class CSSOHead
{
public:
	CSSOHead(void);
	virtual ~CSSOHead(void);
public:
	void init(char,std::string&);
	void serialize(std::string&,int);
	/*
	*数据包数据（偏移4字节）
	*数据包长度-4
	*位置存储空间（数据初始化为0）,应该为输出剩余数据长度
	*/
	void deSerialize(ByteBuffer&,int&);
	void serialize_ver8(std::string&);
	void serialize_ver9(std::string&,int);
public:
	std::string readString(ByteBuffer &mBuffer);
public:
	int	m_Version;
	int m_Flag;
	std::string	strQQ;
	char	a;
	char	b;
};

