#pragma once
#include<string>
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_FUNC_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_FUNC_API __declspec(dllimport)
#endif


#define GUID_LEN 64
#define MODMULT(a,b,c,m,s,q) q=s/a;s=b*(s-a*q)-c*q;if(s<0) s+=m;

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
extern LPFN_ISWOW64PROCESS fnIsWow64Process;
extern unsigned int arCrc32Table[256];
extern bool isCrcTableInit;
extern const char str_SSOConfig[];
extern const char str_txssogbcf[];
extern const char str_OSRoot[];
extern const char str_SSOPhysicalDrive0[];
extern const char encode16_table[];
extern const unsigned char decrypt_file_data[];


/*****************************未导出函数声明********************************/
bool EnableSpecificPrivilege(char * Name);
bool AdjustPrivileges();
unsigned int IsCurrentWow64();
void GenerateCrc32Table();
bool GetCpuId(unsigned char *dst,unsigned int dstlen);
bool Encode16(unsigned char *,unsigned int,unsigned char*,unsigned int);
bool DecryptBuf(unsigned char *buf,DWORD size,unsigned char b);
bool DecryptDb(unsigned char *buf,DWORD len,unsigned char *dst);
unsigned char * CaculteTGT(unsigned char *s,unsigned char *d);
/*****************************未导出函数声明********************************/



/*****************************导出函数声明********************************/
extern DIPPEREXPORTS_FUNC_API HANDLE g_DumpThread;
LONG _stdcall GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);
DWORD _stdcall ThreadProc( LPVOID lpParam );
int _stdcall WideCharToBytes( LPWSTR szWStr, LPSTR lpBStr, int  nBStrLen );
bool GetMachineGuid(unsigned char *dst,unsigned int *dstlen);
bool GetGenerateG(unsigned char *);
bool GetGenerateEx(unsigned char *dst,unsigned int dstlen);
unsigned int CalculatebufCrc(const char *pbtBuffer, unsigned int dwSize);
bool GetSSOConfigSid(unsigned char *dst,unsigned int dstlen);
void _get_host_name(unsigned char *,unsigned int *len);
unsigned char *memstr(unsigned char *dst,unsigned int dstlen,unsigned char *src,unsigned int srclen);
void CaculteGuid(unsigned char *guid,unsigned int glen,unsigned char *dst,unsigned int dlen);
void GetTGTGT(unsigned char *p1,unsigned char *p2,unsigned char *p3,unsigned char *dst);
bool GenerateGuid(unsigned char *dst,unsigned int dstlen);
unsigned char CalcRound(unsigned char b,unsigned char *s1,unsigned char *s2);
//转换函数
unsigned int Utf8ToMultiByte(const char *src,unsigned char srclen,unsigned char **dst);         //0 fail
unsigned int MultiByteToUtf8(const char *src,unsigned char srclen,unsigned char **dst);         //0 fail
unsigned int StrToHex(unsigned char *s,unsigned int slen,OUT unsigned char *d);
unsigned int HexToStr(unsigned char *s,unsigned int slen,OUT unsigned char *d);
/*****************************导出函数声明********************************/