#include"MyLog.h"

//日志对象
LOG gStatusLog;			//过程日志
LOG gDataLog;			//数据日志

void StatusLogText(const char *text)
{
#ifdef MYLOGOUT
	gStatusLog.StatusOut(text);
#endif
}

void DataLogText(const char *text)
{
#ifdef MYLOGOUT
	gDataLog.StatusOut(text);
#endif
}

void DataLogBytes(const char *tip,const unsigned char *bytes,const unsigned int n)
{
#ifdef MYLOGOUT
	gDataLog.DataOut(tip,bytes,n);
#endif
}