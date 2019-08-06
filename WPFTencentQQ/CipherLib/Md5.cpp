#include "StdAfx.h"
#include "Md5.h"
#include <openssl\md5.h>


CMd5::CMd5(void)
{
}


CMd5::~CMd5(void)
{
}

void CMd5::GetMd5(unsigned char *szMd5,size_t len,unsigned char *szData,size_t size)
{
	if(len<0x10) return;
	MD5_CTX c;
	MD5_Init(&c);
	MD5_Update(&c, szData, size);  
	MD5_Final(szMd5,&c);
}
