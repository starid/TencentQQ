#include "StdAfx.h"
#include "LOG.h"
#include<stdio.h>
#include<time.h>
#include "Shlwapi.h"
#pragma comment(lib,"Shlwapi.lib") /*需要加上此行才可以正确link，VC6.0*/


LOG::LOG(void)
{
	m_bEnable = FALSE;
	m_bPrintTime = FALSE;
	m_csFileName = "";
	m_csAppName = "";
   // we'll make sure only one call uses the critical stuff at a time
   InitializeCriticalSection(&m_crit);
}

LOG::~LOG(void)
{
	DeleteCriticalSection(&m_crit);
}

void LOG::DataOut(const char*tip,const unsigned char *bytes,const unsigned int n)
{	
	 EnterCriticalSection(&m_crit);
	char buffer[0x100]={0};
	std::string strResult;

	DWORD nNumberOfBytesToWrite=0; 
	std::string strLine;
	std::string strcLine;
	for(int i=0;i<n;i++)
	{
		memset(buffer,0,sizeof(buffer));
		nNumberOfBytesToWrite=wsprintf(buffer,"%02X ",*(bytes+i));
		strLine.append(buffer,nNumberOfBytesToWrite);
		if(*(bytes+i)==0xd||*(bytes+i)==0xa||*(bytes+i)==0x9||*(bytes+i)==0x1a||
			*(bytes+i)==0x1b)
		{
			strcLine.push_back(0x2e);
		}else
		{
			strcLine.push_back(*(bytes+i));
		}
		if((i+1)%0x10==0&&(i+1)!=n)
		{
			memset(buffer,0,sizeof(buffer));
			nNumberOfBytesToWrite=wsprintf(buffer,"\r\n");
			strLine.append(strcLine.c_str(),strcLine.size());
			strcLine.clear();
			strLine.append(buffer,nNumberOfBytesToWrite);
			strResult.append(strLine);
			strLine.clear();
		}
	}
	if(strcLine.size()!=0)
		strLine.append(strcLine);
	if(strLine.size()!=0)
		strResult.append(strLine);
  
   FILE *fp = fopen(m_csFileName.c_str(), "a");
	if (fp)
	{
      if (m_bPrintAppName)
      {
		  fprintf(fp,"%s : ", m_csAppName.c_str());
      }

      if (m_bPrintTime)
      {
		  SYSTEMTIME st;
		  GetLocalTime(&st);
		  fprintf(fp," %d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
      }
	  fprintf(fp," %s\r\n",tip);
	  fwrite(strResult.c_str(),strResult.size(),1,fp);
	  //fprintf(fp, " %s\n", strResult.c_str());
	  fprintf(fp,"\r\n",tip);
      fclose(fp);
	}

   LeaveCriticalSection(&m_crit);

}



/////////////////////////////////////////////////////////////////////////////

void LOG::Init(const char *pOutputFilename)
{
	m_bEnable = TRUE;
	char buf[MAX_PATH+1];
	DWORD res = GetModuleFileName(NULL, buf, MAX_PATH);
	std::string appDir = GetBaseDir(buf);
   m_csAppName = GetBaseName(buf);
   m_csFileName+=appDir;
   m_csFileName+="\\";
   m_csFileName+="AppLog";
   //创建目录
   CreateDirectory(m_csFileName.c_str(),NULL);
   m_csFileName+="\\";
   m_csFileName+=pOutputFilename;
   // overwrite the old file!
   remove(m_csFileName.c_str());

}

/////////////////////////////////////////////////////////////////////////////

void LOG::Enable(bool bEnable)
{
	m_bEnable = bEnable;
}

/////////////////////////////////////////////////////////////////////////////

void LOG::StatusOut(const char* fmt, ...)
{
	if (m_csFileName.length()==0)
		return;

	if (!m_bEnable)
		return;

	//if (!AfxIsValidString(fmt, -1))
	//	return FALSE;

   EnterCriticalSection(&m_crit);

   // parse that string format
   try
   {
	   va_list argptr;
	   va_start(argptr, fmt);
	   _vsnprintf(m_tBuf, TBUF_SIZE, fmt, argptr);
	   va_end(argptr);
   }
   catch (...)
   {
      m_tBuf[0] = 0;
   }

   // output 
   FILE *fp = fopen(m_csFileName.c_str(), "a");
	if (fp)
	{
      if (m_bPrintAppName)
      {
		  fprintf(fp,"%s : ", m_csAppName.c_str());
      }

      if (m_bPrintTime)
      {
		  SYSTEMTIME st;
		  GetLocalTime(&st);
		  fprintf(fp," %d-%02d-%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
      }

      fprintf(fp, " %s\n", m_tBuf);
      fclose(fp);
	}

   LeaveCriticalSection(&m_crit);

}

/////////////////////////////////////////////////////////////////////////////

std::string	LOG::GetBaseName(const std::string &path)
{
	std::string out = path;

	int iSlashPos = path.find_last_of('\\');
	if (iSlashPos !=-1) 
	{
		out = out.substr(iSlashPos+1,out.length());
	}

   int iDotPos = out.find_last_of('.');
   if (iDotPos>0)
   {
	   out = out.substr(0,iDotPos);
   }
   return out;
}

/////////////////////////////////////////////////////////////////////////////

std::string LOG::GetBaseDir(const std::string & path)
{
	std::string out = "";
	int iSlashPos = path.find_last_of('\\');
	if (iSlashPos !=-1) 
	{
		out = path.substr(0,iSlashPos);
	} 
	return out;
}