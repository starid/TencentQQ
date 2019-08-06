#include "StdAfx.h"
#include "TXCommPack.h"
#include<stdlib.h>
#include<WinSock.h>
#include<ObjBase.h>
#include "../UtilLib/err_code.h"
#include<shlobj.h>   
#include<Windows.h>
#include<WinIoCtl.h>

#pragma   comment(lib,"shell32.lib") 


CTXCommPack::CTXCommPack(void)
{
}

CTXCommPack::CTXCommPack(size_t size)
{
}

CTXCommPack::~CTXCommPack(void)
{
}

void CTXCommPack::AddByte(const char b)
{
	buffer.append(b);
}

void CTXCommPack::AddDWord(const int data)
{
	buffer.append<uint32>(data);
}

void CTXCommPack::AddWord(const short data)
{
	buffer.append<uint16>(data);
}

void CTXCommPack::AddBuf(const char *buf,const int buflen)
{
	buffer.append(buf,buflen);
}

void CTXCommPack::AddBufLenWord()
{
	unsigned short len=buffer.size();
	//应该前置插入
	buffer.insert<uint16>(0,htons(len));

}

//插入前置特征码
void CTXCommPack::AddFieldCode(short value)
{
	buffer.insert<uint16>(0,value);
}

void CTXCommPack::GetBufferOut()
{
	buffer.clear();
}

//void CTXCommPack::AddHostName()
//{
//	unsigned char dst[MAX_COMPUTERNAME_LENGTH + 1]={0};
//	unsigned int dstlen=sizeof(dst);
//	_get_host_name(dst,&dstlen);
//	AddBuf((char*)dst,dstlen);
//}
//
//void CTXCommPack::CaculteGuid(unsigned char *guid,unsigned int glen,unsigned char *dst,unsigned int dlen)
//{
//	unsigned char _tmp_buf[0x20]={0};
//	unsigned char *p=(unsigned char *)STR_GUID;
//	unsigned char *s=guid;
//	unsigned char *j=_tmp_buf;
//	do
//	{
//		unsigned short n=0;
//
//		if(*p>=0x40)
//		{
//			unsigned int n=*s;
//			n|=0x20;
//			if(n<0x61)
//			{
//				n-=0x30;
//				*(j+*p-0x40)=n;
//			}else
//			{
//				n-=0x57;
//				*(j+*p-0x40)=n;
//			}
//		}
//		p++;
//		s++;
//	}while(*p!=0x00);
//	//进行合并处理
//	for(int i=0;i<sizeof(_tmp_buf);i+=2)
//	{
//		unsigned char m=_tmp_buf[i];
//		m<<=0x4;
//		unsigned char n=_tmp_buf[i+1];
//		m|=n;
//		dst[i/2]=m;
//	}
//}

//void CTXCommPack::GetCaculteGuid(unsigned char *dst,unsigned int dstlen)
//{
//	unsigned char buffer[GUID_LEN] = { 0 };
//	unsigned int _guid_len=GUID_LEN;
//	GetMachineGuid(buffer,&_guid_len);
//
//	CaculteGuid(buffer,_guid_len,dst,sizeof(dst));
//	//unsigned char guid[]="7f362792-391d-472d-947d-217b1ce0e0e7";
//	//CaculteGuid(guid,_guid_len,dst,dstlen);
//}

//void CTXCommPack::AddCaculteGuid()
//{
//	unsigned char dst[0x10]={0};
//	GetCaculteGuid(dst,sizeof(dst));
//	AddBuf((char*)dst,sizeof(dst));
//}

//unsigned int CTXCommPack::AddNewGuid()
//{
//	GUID guid;
//	//CoInitialize(NULL); 
//	if(S_OK != CoCreateGuid(&guid))
//	{
//		return ERR_CREATEGUID_FAILED;
//	}
//	//CoUninitialize(); 
//	AddBuf((char *)&guid,sizeof(GUID));
//	return RESULT_SUCCESS;
//}

//void CTXCommPack::AddPwdMd5(unsigned char *s,unsigned int slen)
//{
//	unsigned char _dst_md5[0x10]={0};
//	GetMd5(_dst_md5,sizeof(_dst_md5),s,slen,0xB);
//	AddBuf((char*)_dst_md5,sizeof(_dst_md5));
//}

//void CTXCommPack::AddVague(unsigned char *s,unsigned int slen)
//{
//	AddBuf((char*)s,slen);
//}

extern unsigned char GENERATEG_SERIE[]={
	0xE9,0x29,0xCE,0x76,0xE1,0x45,0x11,0x7E,0x33,0x51,0xE9,0x60,0xE3,0x61,0x54,0x2C,0xDA,0x0B,0xEC,0x7B,0x37,0x5E,0x81,0x44,0x12,0x3C,0x48,0x20,0x58,0x74,0xBE,0x11,
	0xB8,0x59,0x75,0x1A,0xB1,0x62,0x59,0x2D,0x39,0x5B,0x40,0x00,0xA5,0x3C,0xB7,0x1E,0xB0,0x25,0x67,0x70,0xD2,0x7B,0x8E,0x37,0x4E,0x48,0x63,0x70,0x97,0x36,0x54,0x00,
	0xFF,0x06,0x85,0x5C,0xD3,0x1F,0xF8,0x48,0x4A,0x78,0x44,0x1E,0xF0,0x33,0xCF,0x31,0x79,0x3A,0xD6,0x1C,0x21,0x37,0xD1,0x40,0xFB,0x03,0xFD,0x1B,0xE7,0x68,0x05,0x57,
	0x06,0x13,0x24,0x7D,0xDA,0x10,0x3A,0x1A,0x81,0x40,0xAA,0x16,0xA6,0x48,0xF8,0x26,0x20,0x3A,0x7E,0x15,0x54,0x27,0xB6,0x1E,0xD1,0x27,0xEC,0x1C,0xCB,0x31,0x4E,0x66,
};

//void CTXCommPack::AddComputerIdGenerateG(unsigned char *src,unsigned int srclen)
//{
//	unsigned char dst[0x20]={0};
//	memcpy(dst,src,srclen);
//
//	for(int i=0;i<sizeof(dst);i++)
//	{
//		unsigned int c=i&0x3F;
//		dst[i]^=GENERATEG_SERIE[c*2];
//	}
//	//只取前十字节，并计算CRC32值
//	unsigned int crc32=CalculatebufCrc(dst,0x10);
//	AddDWord(htonl(crc32));
//	AddBuf((char*)dst,0x10);
//}
/*
*此函数应为生成硬件特征码
*/
//void CTXCommPack::AddComputerIdGenerateEx()
//{
//	unsigned char src[0x10]={0};
//	GetGenerateEx(src,sizeof(src));
//	unsigned int crc32=CalculatebufCrc(src,0x10);
//	AddDWord(htonl(crc32));
//	AddBuf((char*)src,sizeof(src));
//}

//void CTXCommPack::AddTGTGT(unsigned char *p1,unsigned char *p2,unsigned char *p3)
//{
//	unsigned char *d=NULL;
//	unsigned int ret=GetTGTGT(&d,p1,p2,p3);
//	if(ret!=RESULT_SUCCESS)
//	{
//		return;
//	}
//	this->AddBuf((char*)d,0x14);
//	free(d);
//	d=NULL;
//}

//unsigned int CTXCommPack::GetTGTGT(unsigned char **dst,unsigned char *p1,unsigned char *p2,unsigned char *p3)
//{
//	*dst=NULL;
//	unsigned int dlen=0;
//	unsigned char *a=p1;
//	unsigned char *b=p2;
//	unsigned char *c=NULL;       //堆内存需要释放
//	unsigned char *d=p3;
//	if(a==NULL||b==NULL||d==NULL)
//	{
//		return ERR_COMMON;
//	}
//	c=CaculteTGT(b,a);
//	if(c==NULL)
//		return ERR_NOENOUGHBUF;
//	*dst=(unsigned char *)malloc(0x40);
//	memset(*dst,0,0x40);
//	memcpy(*dst,a,0x10);
//	memcpy(*dst+0x10,b,0x10);
//	memcpy(*dst+0x20,c,0x10);
//	memcpy(*dst+0x30,d,0x10);
//	unsigned char md5[0x10]={0};
//	GetMd5(md5,sizeof(md5),*dst,0x40,0x1);
//	free(*dst);*dst=NULL;
//	unsigned char md5_10[0x10]={0};  //求十次MD5
//	GetMd5(md5_10,sizeof(md5_10),md5,0x10,0xA);
//	unsigned int bytes=0;
//	unsigned char buf_1[0x10]={0};       //用10次MD5对MD5加密
//	CTeaCrypt::encrypt_tea_16((unsigned long*)md5,(unsigned long*)md5_10,(unsigned long *)buf_1);
//	CTeaCrypt::encrypt_tea_16((unsigned long*)(md5+0x8),(unsigned long*)md5_10,(unsigned long *)(buf_1+0x8));
//	unsigned char buf_2[0x10]={0};      //用A对MD5加密
//	CTeaCrypt::encrypt_tea_16((unsigned long*)md5,(unsigned long*)b,(unsigned long *)buf_2);
//	CTeaCrypt::encrypt_tea_16((unsigned long*)(md5+0x8),(unsigned long*)b,(unsigned long *)(buf_2+0x8));
//	for(int i=1;i<0x10;i++)
//	{
//		buf_1[i]^=buf_2[i];         //保留buf_1第一字节
//	}
//	memset(buf_2,0,sizeof(buf_2));       //用C对MD5加密
//	CTeaCrypt::encrypt_tea_16((unsigned long*)md5,(unsigned long*)c,(unsigned long *)buf_2);
//	CTeaCrypt::encrypt_tea_16((unsigned long*)(md5+0x8),(unsigned long*)c,(unsigned long *)(buf_2+0x8));
//	for(int i=2;i<0x10;i++)
//	{
//		buf_1[i]^=buf_2[i];         //保留buf_1前两个字节
//	}
//	memset(buf_2,0,sizeof(buf_2));       //用D对MD5加密
//	CTeaCrypt::encrypt_tea_16((unsigned long*)md5,(unsigned long*)d,(unsigned long *)buf_2);
//	CTeaCrypt::encrypt_tea_16((unsigned long*)(md5+0x8),(unsigned long*)d,(unsigned long *)(buf_2+0x8));
//	for(int i=3;i<0x10;i++)
//	{
//		buf_1[i]^=buf_2[i];         //保留buf_1前三个字节
//	}
//
//	//对buf_1取MD5并计算CRC值到末尾构成0x14字节数据
//	memset(md5,0,sizeof(md5));
//	GetMd5(md5,sizeof(md5),buf_1,sizeof(buf_1),0x1);
//	//计算crc
//	unsigned crc_ret=CalculatebufCrc(md5,sizeof(md5));
//
//	*dst=(unsigned char *)malloc(0x14);
//	memcpy(*dst,md5,sizeof(md5));
//	memcpy(*dst+0x10,&crc_ret,sizeof(crc_ret));
//	free(c);c=NULL;
//	return RESULT_SUCCESS;
//}

//unsigned char * CTXCommPack::CaculteTGT(unsigned char *s,unsigned char *d)
//{
//	unsigned char buf1[0x100]={0};
//	for(int i=0;i<0x10;i++)
//	{
//		memcpy(buf1+i*0x10,s,0x10);
//	}
//	unsigned char buf2[0x100]={0};
//	for(int i=0;i<0x100;i++)
//	{
//		buf2[i]=i;
//	}
//	int a=0;             //118数据
//	int b=0;              //238数据
//	unsigned char tmp=0;			//231
//	for(int i=0;i<0x100;i++)
//	{
//		a=buf2[i];
//		a+=b;
//		int data=buf1[i];      //
//		a+=data;
//		a&=0x800000FF;
//		if(a<0)
//		{
//			a--;
//			a|=0xFFFFFF00;
//			a++;
//		}
//		b=a;
//		unsigned char tmp=buf2[a];       //231临时值
//		a=b;
//		buf2[a]=buf2[i];
//		a=i;
//		buf2[a]=tmp;
//	}
//	//第二次运算
//	a=0;b=0;tmp=0;
//
//
//	unsigned char *dst=NULL;
//	dst=(unsigned char *)malloc(0x10);
//	if(dst==NULL)
//		return NULL;
//	for(int i=0;i<0x10;i++)
//	{
//		if(i==0)
//		{
//			a=1;
//		}else
//		{
//			a=i+1;
//		}
//		a&=0x800000FF;
//		if(a<0)
//		{
//			a--;
//			a|=0xFFFFFF00;
//			a++;
//		}
//		a=buf2[a];
//		a+=b;
//		a&=0x800000FF;
//		if(a<0)
//		{
//			a--;
//			a|=0xFFFFFF00;
//			a++;
//		}
//		b=a;
//		unsigned char tmp=buf2[a];           //231临时值
//		a=b;
//		buf2[a]=buf2[i+1];
//		a=i+1;
//		buf2[a]=tmp;
//		a=buf2[a];
//		int ecx=b;
//		ecx=buf2[ecx];
//		a+=ecx;
//		a&=0x800000FF;
//		if(a<0)
//		{
//			a--;
//			a|=0xFFFFFF00;
//			a++;
//		}
//		a=buf2[a];
//		a^=*(d+i);
//
//		dst[i]=a;                  //测试通过
//	}
//	return dst;
//}