#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_LOG_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_LOG_API __declspec(dllimport)
#endif

#include<string>
#include<Windows.h>

class DIPPEREXPORTS_LOG_API LOG
{
public:
	LOG(void);
	~LOG(void);
public:
   void	Init(const char *pOutputFilename);
   void	StatusOut(const char* fmt, ...);
   void DataOut(const char *,const unsigned char *,const unsigned int);
   void	Enable(bool bEnable);
   void     PrintTime(bool b) {m_bPrintTime = b;};
   void     PrintAppName(bool b) {m_bPrintAppName = b;};
   void     SetAppName(const char *pName) {m_csAppName = pName;};
private:
	enum {TBUF_SIZE = 3000};
	char	m_tBuf[TBUF_SIZE];
	std::string  m_csAppName;
	std::string	m_csFileName;
	CRITICAL_SECTION  m_crit;
	bool	m_bEnable;
	bool     m_bPrintTime;
	bool     m_bPrintAppName;
	std::string GetBaseDir(const std::string & path);
	std::string GetBaseName(const std::string & path);
};

