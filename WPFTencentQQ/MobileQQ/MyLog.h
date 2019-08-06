#include"../UtilLib/LOG.h"
#define MYLOGOUT			//是否打印日志



extern LOG gStatusLog;			//过程日志
extern LOG gDataLog;			//数据日志

void StatusLogText(const char*);
void DataLogText(const char*);
void DataLogBytes(const char*,const unsigned char*,const unsigned int);