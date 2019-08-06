#include "StdAfx.h"
#include"HelpFunc.h"
#include<stdlib.h>
#include"Dump.h"
#include<math.h>
#include<shlobj.h>  
#include"CpuId.h"
#include"LOG.h"
#include <iphlpapi.h>
#include"..\CipherLib\Md5.h"
#include"..\CipherLib\TeaCrypt.h"
#include"err_code.h"

#ifdef _DEBUG
#pragma comment(lib,"../LibD/CipherLib.lib")
#else
#pragma comment(lib,"../Lib/CipherLib.lib")
#endif


#pragma comment(lib,"Iphlpapi.lib")

HANDLE g_DumpThread;
LONG WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	//写共享内存
	HANDLE hMapFile=CreateFileMapping( (HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,1024,"Surreal");
	if(hMapFile)
	{
		LPWSTR lpMapAddr=(LPWSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0);
		memcpy_s(lpMapAddr,1024,(LPWSTR)pExceptionInfo,sizeof(EXCEPTION_POINTERS));
		FlushViewOfFile(lpMapAddr,0);
		OutputDebugString("共享内存写入完毕");
	}else
	{
		return EXCEPTION_EXECUTE_HANDLER;
		OutputDebugString("共享内存写入失败");
	}


	ResumeThread(g_DumpThread);
	WaitForSingleObject(g_DumpThread,INFINITE);
	return EXCEPTION_EXECUTE_HANDLER;  // 程序停止运行

}

DWORD WINAPI ThreadProc( LPVOID lpParam )
{
	EXCEPTION_POINTERS ExceptionInfo;
	HANDLE hMapFile=OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE,"Surreal");

	if(hMapFile)
	{
		LPWSTR lpMapAddr = (LPWSTR)MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0); 
		memcpy_s(&ExceptionInfo,sizeof(EXCEPTION_POINTERS),lpMapAddr,sizeof(EXCEPTION_POINTERS));
		FlushViewOfFile(lpMapAddr,0);  
		UnmapViewOfFile(lpMapAddr);
		CloseHandle(hMapFile);
		OutputDebugString("共享内存读取成功");
	}else
	{
		OutputDebugString("共享内存读取失败");
		return FALSE;
	}
	OutputDebugString("开始生成转储文件");

	CreateMiniDump(&ExceptionInfo,"Exception.dmp");
	MessageBox(NULL,"程序发生崩溃","警告",MB_OK|MB_ICONERROR);
	exit(ExceptionInfo.ExceptionRecord->ExceptionCode);
	return TRUE;
}

int WINAPI WideCharToBytes( LPWSTR szWStr, LPSTR lpBStr, int nBStrLen )
{
//宽字节转多字节
    int nBytes = 0;

    nBytes=WideCharToMultiByte( CP_ACP, 0, szWStr, -1, lpBStr, nBStrLen, NULL, NULL);
    nBStrLen = nBytes;

return nBStrLen;
} 

bool GetMachineGuid(unsigned char *dst,unsigned int *dstlen)
{
	HKEY bKey =HKEY_LOCAL_MACHINE,hKey=0;
	char SubKey[]="SOFTWARE\\Microsoft\\Cryptography";
	char key[]="MachineGuid";
	unsigned int retVal=RegOpenKeyEx(bKey,SubKey,0,KEY_READ|KEY_WOW64_64KEY,&hKey);
	if (retVal != ERROR_SUCCESS)
		return false;
	unsigned int type=REG_SZ;
	retVal=RegQueryValueEx(hKey,key,NULL,(LPDWORD)&type,(LPBYTE)dst,(LPDWORD)dstlen); 
	if (retVal != ERROR_SUCCESS)
	{
		RegCloseKey(bKey);
		return false;
	}
	RegCloseKey(bKey);
	return true;
}

bool AdjustPrivileges()
{
		//Adjust Privileges
	if(
	EnableSpecificPrivilege(SE_BACKUP_NAME)&&
	EnableSpecificPrivilege(SE_CHANGE_NOTIFY_NAME)&&
	EnableSpecificPrivilege(SE_CREATE_PAGEFILE_NAME)&&
	EnableSpecificPrivilege(SE_DEBUG_NAME)&&
	EnableSpecificPrivilege(SE_INC_BASE_PRIORITY_NAME)&&
	EnableSpecificPrivilege(SE_INCREASE_QUOTA_NAME)&&
	EnableSpecificPrivilege(SE_LOAD_DRIVER_NAME)&&
	EnableSpecificPrivilege(SE_PROF_SINGLE_PROCESS_NAME)&&
	EnableSpecificPrivilege(SE_RESTORE_NAME)&&
	EnableSpecificPrivilege(SE_SECURITY_NAME)&&
	EnableSpecificPrivilege(SE_SHUTDOWN_NAME)&&
	EnableSpecificPrivilege(SE_SYSTEM_ENVIRONMENT_NAME)&&
	EnableSpecificPrivilege(SE_SYSTEMTIME_NAME)&&
	EnableSpecificPrivilege(SE_TAKE_OWNERSHIP_NAME))
	{
		MessageBox(NULL,TEXT("权限提升成功"),TEXT("提示"),MB_OK);
		return TRUE;
	}else
	{
		MessageBox(NULL,TEXT("权限提升失败"),TEXT("提示"),MB_OK);
		return FALSE;
	}
}

bool EnableSpecificPrivilege(char * Name)				//分配相应的特权
{
	BOOL bResult = FALSE;
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES TokenPrivileges;

	if( OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,&hToken) == 0 )
	{
		return FALSE;
	}

	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	bResult = LookupPrivilegeValue(NULL,Name,&TokenPrivileges.Privileges[0].Luid);

	if( !bResult )
	{
		CloseHandle(hToken);
		return FALSE;
	}

	bResult = AdjustTokenPrivileges(hToken,FALSE,&TokenPrivileges,sizeof(TOKEN_PRIVILEGES),NULL,NULL);

	if(GetLastError() != ERROR_SUCCESS || !bResult)
	{
		CloseHandle(hToken);
		return FALSE;
	}

	CloseHandle(hToken);
	return TRUE;
}

LPFN_ISWOW64PROCESS fnIsWow64Process;
bool IsCurrentWow64(BOOL *bIsWow64)
{
    *bIsWow64 = FALSE;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),bIsWow64))
        {
            // handle error
			return false;
        }
    }
    return true;
}

const char str_txssogbcf[]="SSOConfig\\GlobleDB\\_SID_0\\_UIN_0\\txssogbcf.db";
//const char str_txssogbcf[]="SSOConfig\\AppDB\\_TSA_QQ\\_SID_1\\_UIN_0\\txssoappcf.db";
bool GetGenerateG(unsigned char *dst)
{
	//HWND hwnd=GetDesktopWindow();
	//char szPath[MAX_PATH]={0};
	//SHGetSpecialFolderPath(hwnd,szPath,CSIDL_APPDATA,TRUE);
	//完了+"\Tencent\TXSSO\SSOConfig\"（死的）
	//构成"C:\Documents and Settings\Administrator\Application Data\Tencent\TXSSO\SSOConfig\"
	//"GlobleDB\_SID_%lu\_UIN_%lu\txssogbcf.db"(死的)
	//构成“C:\Documents and Settings\Administrator\Application Data\Tencent\TXSSO\SSOConfig\GlobleDB\_SID_0\_UIN_0\txssogbcf.db”

	//串“_TSSOM:GlobleDB/_SID_0/_UIN_0/txssogbcf.db”
//串“C:\Documents and Settings\Administrator\Application Data\Tencent\TXSSO\SSOConfig\GlobleDB\_SID_0\_UIN_0\txssogbcf.db”
	//串“OSRoot:C:\Documents and Settings\Administrator\Application Data\Tencent\TXSSO\SSOConfig\GlobleDB\_SID_0\_UIN_0\txssogbcf.db”（OSRoot:固定）


	//OSRoot:C:\Users\Administrator\AppData\Roaming\Tencent\TXSSO\SSOConfig\GlobleDB\_SID_0\_UIN_0\txssogbcf.db

	//strcat(szPath,str_SSOConfig);
	//strcat(szPath,str_txssogbcf);

	//memcpy(szPath+strlen(str_OSRoot),szPath,strlen(szPath));
	//memcpy(szPath,str_OSRoot,strlen(str_OSRoot));

	char szPath[MAX_PATH]={0};
	::GetModuleFileName(NULL,szPath,MAX_PATH);
	*(strrchr(szPath,'\\')+1)=0x00;
	strcat_s(szPath,MAX_PATH,str_txssogbcf);

	HANDLE hFile=CreateFile(szPath,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);
	DWORD readsize=0;
	if(!ReadFile(hFile,dst,0x20,&readsize,NULL))
	{
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);
	return true;
}

const char str_SSOPhysicalDrive0[]="\\\\.\\PhysicalDrive0";
bool GetGenerateEx(unsigned char *dst,unsigned int dstlen)
{
	//对应代码0x3431FFD1,0x3403683D

	DWORD ret=GetTickCount();

	HANDLE hFile=CreateFile(str_SSOPhysicalDrive0,0,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	
	STORAGE_PROPERTY_QUERY query;
    DWORD cbBytesReturned=0;
    PSTORAGE_DEVICE_DESCRIPTOR pDescript;
    
    memset(&query, 0, sizeof(query));

	query.PropertyId = StorageDeviceProperty;
    query.QueryType = PropertyStandardQuery;

	unsigned char buffer[0x400]={0};
	ret=DeviceIoControl(hFile,IOCTL_STORAGE_QUERY_PROPERTY,&query,sizeof(query),buffer,sizeof(buffer),&cbBytesReturned,NULL);//第二个参数为0x2D1400
	if(!ret)
	{
		CloseHandle(hFile);
		return false;
	}
	pDescript=(PSTORAGE_DEVICE_DESCRIPTOR)buffer;

	//先取出硬盘productid以及长度
	unsigned int length1=strlen((const char *)(buffer+pDescript->ProductIdOffset)); //productid长度
	memcpy(buffer,buffer+pDescript->ProductIdOffset,length1);
	memset(buffer+length1,0,sizeof(buffer)-length1);
	//取出CPU型号以及长度
	GetCpuId(buffer+length1,sizeof(buffer)-length1);
	unsigned int length2=strlen((const char *)(buffer+length1)); //cpu型号长度

	//取出网卡信息并编码
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulOutBufLen);
	DWORD dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	// 第一次调用GetAdapterInfo获取ulOutBufLen大小
	if (dwRetVal == ERROR_BUFFER_OVERFLOW)
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
		dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	}
	if (dwRetVal == NO_ERROR)
	{
		pAdapter = pAdapterInfo;
		while(pAdapter)
		{
			//取第一块物理地址非0的网卡地址
			 //pAdapter->Address[0];
			 //pAdapter->Address[1];
			 //pAdapter->Address[2];
			 //pAdapter->Address[3];
			 //pAdapter->Address[4];
			 //pAdapter->Address[5];
			 //int test=pAdapter->Address[0]| pAdapter->Address[1]| pAdapter->Address[3]|pAdapter->Address[4]| pAdapter->Address[5];
			unsigned char buf[0x10]={0};
			Encode16(pAdapter->Address,sizeof(pAdapter->Address),buf,sizeof(buf));                  //有时网卡地址取的不是这一个

			memcpy(buffer+length1+length2,buf,sizeof(buf));
			break;

			pAdapter = pAdapter->Next;
		}
		free(pAdapterInfo);
		pAdapterInfo=NULL;
	}
	else
	{
		CloseHandle(hFile);
		return false;
	}
	CMd5 md5; 
	md5.GetMd5(dst,dstlen,buffer,strlen((const char *)buffer));
	CloseHandle(hFile);
	return true;
}

unsigned int arCrc32Table[256]={0};
bool isCrcTableInit=false;
void GenerateCrc32Table()  
{  
	//memset(arCrc32Table,0,sizeof(arCrc32Table)); 
	for(int i = 0; i < 256; i++)  
    {  
      unsigned int dwTempCrc = i;  
       for (int j = 0; j < 8; j++)  
       {  
           dwTempCrc = (dwTempCrc & 1) ? (dwTempCrc >> 1) ^ 0xEDB88320 : dwTempCrc >> 1;  
        }  
        arCrc32Table[i] = dwTempCrc;  
    }  
}  

unsigned int CalculatebufCrc(const char *pbtBuffer, unsigned int dwSize)  
{  
	if(!isCrcTableInit)
	{
		GenerateCrc32Table();
		isCrcTableInit=true;
	}
    const char * pbtTempBuffer = pbtBuffer;  
    unsigned int dwTempCrc = 0xFFFFFFFF;  
    while (dwSize--)  
    {  
        dwTempCrc = ((dwTempCrc >> 8) & 0x00FFFFFF) ^ arCrc32Table[(dwTempCrc ^ (*pbtTempBuffer)) & 0xFF];  
        pbtTempBuffer++;  
    }  
    return dwTempCrc ^ 0xFFFFFFFF;  
}

bool GetCpuId(unsigned char *dst,unsigned int dstlen)
{
	CCpuId puid;
	if(!puid.isSupport())
	{
		//计算机不支持cpuid指令
		return false;
	}

	puid.getCpuName(dst,dstlen);

	return true;
}

const char encode16_table[]="0123456789ABCDEF";
bool Encode16(unsigned char *src,unsigned int srclen,unsigned char*dst,unsigned int dstlen)
{
	//34036729(encode16)
	char *p=(char *)encode16_table;
	for(int i=0;i<srclen;i++)
	{
		unsigned char c1=src[i];
		*(dst+i*2)=*(p+(c1>>0x4));
		*(dst+i*2+0x1)=*(p+(c1&0x0F));
	}
	return true;
}

const char str_txssoappcf[]="SSOConfig\\AppDB\\_TSA_QQ\\_SID_1\\_UIN_0\\txssoappcf.db";
//原始字符串"AppDB\_TSA_%s\_SID_%lu\_UIN_%lu\txssoappcf.db"其中参数可能和应用程序相关
const unsigned char decrypt_file_data[]=
{
0xE9,0x29,0xCE,0x76,0xE1,0x45,0x11,0x7E,0x33,0x51,0xE9,0x60,0xE3,0x61,0x54,0x2C,0xDA,0x0B,0xEC,0x7B,0x37,0x5E,0x81,0x44,0x12,0x3C,0x48,0x20,0x58,0x74,0xBE,0x11,
0xB8,0x59,0x75,0x1A,0xB1,0x62,0x59,0x2D,0x39,0x5B,0x40,0x00,0xA5,0x3C,0xB7,0x1E,0xB0,0x25,0x67,0x70,0xD2,0x7B,0x8E,0x37,0x4E,0x48,0x63,0x70,0x97,0x36,0x54,0x00,
0xFF,0x06,0x85,0x5C,0xD3,0x1F,0xF8,0x48,0x4A,0x78,0x44,0x1E,0xF0,0x33,0xCF,0x31,0x79,0x3A,0xD6,0x1C,0x21,0x37,0xD1,0x40,0xFB,0x03,0xFD,0x1B,0xE7,0x68,0x05,0x57,
0x06,0x13,0x24,0x7D,0xDA,0x10,0x3A,0x1A,0x81,0x40,0xAA,0x16,0xA6,0x48,0xF8,0x26,0x20,0x3A,0x7E,0x15,0x54,0x27,0xB6,0x1E,0xD1,0x27,0xEC,0x1C,0xCB,0x31,0x4E,0x66,
};
const wchar_t strSidFild[]=L"SSO_Config_App_bufSID"; 
bool GetSSOConfigSid(unsigned char *dst,unsigned int dstlen)
{

	//unsigned char byte[]={0x23,0x97,0x13,0x6B,0xFA,0x28,0x08,0xD0,0x94,0x28,0x9B,0x23,0xA1,0xE9,0xC9};
	//*dst=(unsigned char *)malloc(0x10);
	//memcpy(*dst,byte,0x10);

	//return RESULT_SUCCESS;


	char szPath[MAX_PATH]={0};
	::GetModuleFileName(NULL,szPath,MAX_PATH);
	*(strrchr(szPath,'\\')+1)=0x00;
	strcat_s(szPath,MAX_PATH,str_txssoappcf);

	HANDLE hFile=CreateFile(szPath,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		return false;
	}
	DWORD size=0;
	size=GetFileSize(hFile,NULL);
	SetFilePointer(hFile,0,NULL,FILE_BEGIN);

	//申请文件大小的buffer
	unsigned char *buf=(unsigned char *)malloc(size);
	if(buf==NULL) return false;
	
	DWORD readsize=0;
	if(!ReadFile(hFile,buf,size,&readsize,NULL))
	{
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);
	DecryptDb(buf,size,dst);
	free(buf);
	buf=NULL;
	return true;
}
bool DecryptBuf(unsigned char *buf,DWORD size,unsigned char b)
{
	for(int i=0;i<size;i++)
	{
		buf[i]=~buf[i];
		buf[i]^=b;
	}
	return true;
}

bool DecryptDb(unsigned char *buf,DWORD size,unsigned char *dst)
{
	//初次解密
	for(unsigned int i=0;i<size;i++)
	{
		unsigned int offset=i&0x3F;
		buf[i]^=decrypt_file_data[offset*2];
	}
	//第二次解密
	//首次
	for(int offset=0;offset<size;)
	{
		if(buf[offset]!=0x54)
		{
			return false;
		}
		offset++;
		if(buf[offset]!=0x44)
		{
			return false;
		}
		offset+=0x3;
		int num=buf[offset];
		offset+=0x3;
		int tmp=buf[offset];
		offset+=0x2;
		if(tmp+0x4>size)
		{
			break;
		}
		DecryptBuf(buf+offset,tmp,tmp);
		if(memcmp(buf+offset,strSidFild,sizeof(strSidFild)-2)==0)
		{
			offset+=tmp;
			tmp=buf[offset];
			offset+=0x4;
			DecryptBuf(buf+offset,tmp,tmp);
			//*dst=(unsigned char *)malloc(0x10);
	/*		if(*dst==NULL)
				return ERR_NOENOUGHBUF;*/
			memcpy(dst,buf+offset,0x10);
			return true;
		}
		offset+=tmp;
		offset+=0x4;
	}


	return true;
}


void _get_host_name(unsigned char *dst,unsigned int *len)
{
	//dst QQ系统设置0x104空间大小
	GetComputerName((LPSTR)dst,(LPDWORD)len);
}

unsigned char *memstr(unsigned char *dst,unsigned int dstlen,unsigned char *src,unsigned int srclen)
{
	unsigned char *p=NULL;
	if(dstlen<srclen) return NULL;
	for(unsigned int i=0;i<dstlen;i++)
	{
		unsigned char *s=(dst+i);
		for(unsigned int k=0;k<srclen;k++)
		{
			if(*(s+k)!=*(src+k))
			{
				break;
			}
			if(k==srclen-1) return s;
		}
		if(dstlen-i<srclen) return NULL;
	}
	return NULL;
}

bool GenerateGuid(unsigned char *dst,unsigned int dstlen)
{

	GUID guid;
	CoInitialize(NULL); 
	if(S_OK != CoCreateGuid(&guid))
	{
		return false;
	}
	CoUninitialize();
	memcpy(dst,&guid,sizeof(GUID));
	return true;
}

//用于计算GUID
#define STR_GUID "FGDEBC@A-JKHI-NOLM-PQRS-TUVWXYZ[\\]^_";
void CaculteGuid(unsigned char *guid,unsigned int glen,unsigned char *dst,unsigned int dlen)
{
	unsigned char _tmp_buf[0x20]={0};
	unsigned char *p=(unsigned char *)STR_GUID;
	unsigned char *s=guid;
	unsigned char *j=_tmp_buf;
	do
	{
		unsigned short n=0;

		if(*p>=0x40)
		{
			unsigned int n=*s;
			n|=0x20;
			if(n<0x61)
			{
				n-=0x30;
				*(j+*p-0x40)=n;
			}else
			{
				n-=0x57;
				*(j+*p-0x40)=n;
			}
		}
		p++;
		s++;
	}while(*p!=0x00);
	//进行合并处理
	for(int i=0;i<sizeof(_tmp_buf);i+=2)
	{
		unsigned char m=_tmp_buf[i];
		m<<=0x4;
		unsigned char n=_tmp_buf[i+1];
		m|=n;
		dst[i/2]=m;
	}
}

void GetTGTGT(unsigned char *p1,unsigned char *p2,unsigned char *p3,unsigned char *tgtgt)
{
	unsigned char *dst=NULL;
	unsigned int dlen=0;
	unsigned char *a=p1;
	unsigned char *b=p2;
	unsigned char *c=NULL;       //堆内存需要释放
	unsigned char *d=p3;
	CTeaCrypt mTea;
	mTea.InitTeaOne();
	if(a==NULL||b==NULL||d==NULL)
	{
		return;
	}
	c=CaculteTGT(b,a);
	if(c==NULL)
		return;
	dst=(unsigned char *)malloc(0x40);
	memset(dst,0,0x40);
	memcpy(dst,a,0x10);
	memcpy(dst+0x10,b,0x10);
	memcpy(dst+0x20,c,0x10);
	memcpy(dst+0x30,d,0x10);
	unsigned char md5[0x10]={0};
	CMd5 m_md5;
	m_md5.GetMd5(md5,sizeof(md5),dst,0x40);
	free(dst);dst=NULL;
	unsigned char md5_10[0x10]={0};  //求十次MD5
	m_md5.GetMd5(md5_10,sizeof(md5_10),md5,0x10);      //本处应该求十次MD5
	unsigned int bytes=0;
	unsigned char buf_1[0x10]={0};       //用10次MD5对MD5加密
	mTea.encrypt_tea((unsigned long*)md5,(unsigned long*)md5_10,(unsigned long *)buf_1);
	mTea.encrypt_tea((unsigned long*)(md5+0x8),(unsigned long*)md5_10,(unsigned long *)(buf_1+0x8));
	unsigned char buf_2[0x10]={0};      //用A对MD5加密
	mTea.encrypt_tea((unsigned long*)md5,(unsigned long*)b,(unsigned long *)buf_2);
	mTea.encrypt_tea((unsigned long*)(md5+0x8),(unsigned long*)b,(unsigned long *)(buf_2+0x8));
	for(int i=1;i<0x10;i++)
	{
		buf_1[i]^=buf_2[i];         //保留buf_1第一字节
	}
	memset(buf_2,0,sizeof(buf_2));       //用C对MD5加密
	mTea.encrypt_tea((unsigned long*)md5,(unsigned long*)c,(unsigned long *)buf_2);
	mTea.encrypt_tea((unsigned long*)(md5+0x8),(unsigned long*)c,(unsigned long *)(buf_2+0x8));
	for(int i=2;i<0x10;i++)
	{
		buf_1[i]^=buf_2[i];         //保留buf_1前两个字节
	}
	memset(buf_2,0,sizeof(buf_2));       //用D对MD5加密
	mTea.encrypt_tea((unsigned long*)md5,(unsigned long*)d,(unsigned long *)buf_2);
	mTea.encrypt_tea((unsigned long*)(md5+0x8),(unsigned long*)d,(unsigned long *)(buf_2+0x8));
	for(int i=3;i<0x10;i++)
	{
		buf_1[i]^=buf_2[i];         //保留buf_1前三个字节
	}

	//对buf_1取MD5并计算CRC值到末尾构成0x14字节数据
	memset(md5,0,sizeof(md5));
	m_md5.GetMd5(md5,sizeof(md5),buf_1,sizeof(buf_1));
	//计算crc
	unsigned int crc_ret=CalculatebufCrc((char*)md5,sizeof(md5));

	memcpy(tgtgt,md5,sizeof(md5));
	memcpy(tgtgt+0x10,&crc_ret,sizeof(crc_ret));
	free(c);c=NULL;
}

unsigned char * CaculteTGT(unsigned char *s,unsigned char *d)
{
	unsigned char buf1[0x100]={0};
	for(int i=0;i<0x10;i++)
	{
		memcpy(buf1+i*0x10,s,0x10);
	}
	unsigned char buf2[0x100]={0};
	for(int i=0;i<0x100;i++)
	{
		buf2[i]=i;
	}
	int a=0;             //118数据
	int b=0;              //238数据
	unsigned char tmp=0;			//231
	for(int i=0;i<0x100;i++)
	{
		a=buf2[i];
		a+=b;
		int data=buf1[i];      //
		a+=data;
		a&=0x800000FF;
		if(a<0)
		{
			a--;
			a|=0xFFFFFF00;
			a++;
		}
		b=a;
		unsigned char tmp=buf2[a];       //231临时值
		a=b;
		buf2[a]=buf2[i];
		a=i;
		buf2[a]=tmp;
	}
	//第二次运算
	a=0;b=0;tmp=0;


	unsigned char *dst=NULL;
	dst=(unsigned char *)malloc(0x10);
	if(dst==NULL)
		return NULL;
	for(int i=0;i<0x10;i++)
	{
		if(i==0)
		{
			a=1;
		}else
		{
			a=i+1;
		}
		a&=0x800000FF;
		if(a<0)
		{
			a--;
			a|=0xFFFFFF00;
			a++;
		}
		a=buf2[a];
		a+=b;
		a&=0x800000FF;
		if(a<0)
		{
			a--;
			a|=0xFFFFFF00;
			a++;
		}
		b=a;
		unsigned char tmp=buf2[a];           //231临时值
		a=b;
		buf2[a]=buf2[i+1];
		a=i+1;
		buf2[a]=tmp;
		a=buf2[a];
		int ecx=b;
		ecx=buf2[ecx];
		a+=ecx;
		a&=0x800000FF;
		if(a<0)
		{
			a--;
			a|=0xFFFFFF00;
			a++;
		}
		a=buf2[a];
		a^=*(d+i);

		dst[i]=a;                  //测试通过
	}
	return dst;
}

unsigned char CalcRound(unsigned char byte_0,unsigned char *s1,unsigned char *s2)
{
	byte_0 = byte_0 % 0x100;
	for(int i=0;i<0x88;i++)
	{
		byte_0=byte_0^s2[i];
	}
	for(int i=0;i<0x10;i++)
	{
		byte_0=byte_0^s1[i];
	}
    byte_0 = byte_0 % 0x100;
    return byte_0;

		//byte RC = byte_0;
		//for (int i = 0; i < 0x88; i++) {
		//	RC ^= s2[i];
		//}
		//byte RCC = 0x00;
		//for (int i = 0; i < 4; i++) {
		//	RCC = s1[i * 4];
		//	RCC ^= s1[(i * 4) + 1];
		//	RCC ^= s1[(i * 4) + 3];
		//	RCC ^= s1[(i * 4) + 2];
		//	RC ^= RCC;
		//}
		//return RC;
}

unsigned int Utf8ToMultiByte(const char *src,unsigned char srclen,unsigned char **dst)         //0 fail
{
	int nLen = MultiByteToWideChar(CP_UTF8, 0, (LPTSTR)src, srclen, NULL, 0);  
	WCHAR* lpszW = new WCHAR[nLen];  
	int nRtn = MultiByteToWideChar(CP_UTF8, 0, (LPTSTR)src, srclen, lpszW, nLen);  
	int MBLen = WideCharToMultiByte(CP_ACP, 0, lpszW, nLen, NULL, 0, NULL, NULL);
	*dst=(unsigned char*)malloc(MBLen);
	if(*dst==NULL) return 0;
	nRtn = WideCharToMultiByte(CP_ACP, 0, lpszW, nLen, (LPTSTR)(*dst), MBLen, NULL, NULL);
	delete lpszW;
	lpszW=NULL;
	return MBLen;
}

unsigned int MultiByteToUtf8(const char *src,unsigned char srclen,unsigned char **dst)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0, (LPTSTR)src, srclen, NULL, 0);  
	WCHAR* lpszW = new WCHAR[nLen];  
	int nRtn = MultiByteToWideChar(CP_ACP, 0, (LPTSTR)src, srclen, lpszW, nLen);  
	int MBLen = WideCharToMultiByte(CP_UTF8, 0, lpszW, nLen, NULL, 0, NULL, NULL);
	*dst=(unsigned char*)malloc(MBLen);
	if(*dst==NULL) return 0;
	nRtn = WideCharToMultiByte(CP_UTF8, 0, lpszW, nLen, (LPTSTR)(*dst), MBLen, NULL, NULL);
	delete lpszW;
	lpszW=NULL;
	return MBLen;
}

unsigned int StrToHex(unsigned char *s,unsigned int slen,OUT unsigned char *d)
{
	int j=0;
	for(int i=0;i<slen;i+=2,j++)
	{
		char a=*(s+i);
		char b=*(s+i+1);
		if(a>='0'&&a<='9')
		{
			a-='0';
		}else if(a>='A'&&a<='F')
		{
			a-=0x37;
		}
		else
		{
			a-=0x57;
		}
		if(b>='0'&&b<='9')
		{
			b-='0';
		}else if(b>='A'&&b<='F')
		{
			b-=0x37;
		}else
		{
			b-=0x57;
		}
		*(d+j)=a*0x10+b;
	}
	return RESULT_SUCCESS;
}

unsigned int HexToStr(unsigned char *s,unsigned int slen,OUT unsigned char *d)
{
	unsigned int j=0;
	for(unsigned int i=0;i<slen;i++,j+=2)
	{
		unsigned char l=*(s+i)&0xF;
		unsigned char h=*(s+i)>>0x4;
		if(l>=0&&l<=9)
		{
			l+='0';
		}else if(l>=0xA&&l<=0xF)
		{
			l+=0x57;
		}
		if(h>=0&&h<=9)
		{
			h+='0';
		}else if(h>=0xA&&h<=0xF)
		{
			h+=0x57;
		}
		*(d+j)=h;
		*(d+j+1)=l;
	}
	return RESULT_SUCCESS;
}