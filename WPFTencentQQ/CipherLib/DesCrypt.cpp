#include "StdAfx.h"
#include "DesCrypt.h"
#include<Windows.h>
#include<openssl\des.h>


#ifdef _DEBUG
#pragma comment(lib,"ssleay32MDd.lib")
#pragma comment(lib,"libeay32MDd.lib")
#else
#pragma comment(lib,"ssleay32MD.lib")
#pragma comment(lib,"libeay32MD.lib")
#endif


DES_key_schedule	sched1;
DES_cblock			ivec;
EncMode				mode;

CDesCrypt::CDesCrypt(EncMode m)
{
	mode=m;
}


CDesCrypt::~CDesCrypt(void)
{
}

void CDesCrypt::SetKey(unsigned char *sid,unsigned int len)
{
	DES_cblock block;
	memcpy(block,sid,0x8);
	DES_set_key((const_DES_cblock*)block,&sched1);
}

void CDesCrypt::SetIv(unsigned char *iv,unsigned int len)
{
	memcpy(ivec, iv, len);  
}

void CDesCrypt::Encrypt(unsigned char *src,unsigned int slen,unsigned char *dst)
{
	switch(mode)
	{
	case MODE_ECB:
		{
			for(unsigned int i=0;i<slen/8u;i++)
			{
				DES_encrypt1((unsigned long*)(src+i*8),&sched1,DES_ENCRYPT);
			}
		}break;
	case MODE_CBC:
		{
		}break;
	}
}

void CDesCrypt::Decrypt(unsigned char *src,unsigned int slen,unsigned char *dst)
{
	switch(mode)
	{
	case MODE_ECB:
		{
			for(unsigned int i=0;i<slen/8u;i++)
			{
				DES_encrypt1((unsigned long*)(src+i*8),&sched1,DES_DECRYPT);
			}
		}break;
	case MODE_CBC:
		{
			DES_ncbc_encrypt(src,dst,slen,&sched1,&ivec, 
              DES_DECRYPT);
		}break;
	}		
}