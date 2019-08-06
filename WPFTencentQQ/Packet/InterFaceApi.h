

//必须由被调用者C#函数在使用完数据后（退出函数时）自己清空堆栈，所以必须使用__stdcall方式
typedef  void(__stdcall *MainCallBack)(unsigned char*, unsigned int);

//导出函数
void __stdcall PackPacket(unsigned char *argu, unsigned int _len, unsigned char **msg, unsigned int *size);
bool __stdcall unPackPacket(unsigned char *data, unsigned int size, unsigned char **notifymsg, unsigned int *notifysize);


void __stdcall _InitId(unsigned int);
void __stdcall _InitPassword(unsigned char *password, unsigned int size);
void __stdcall _InitServer(unsigned int,unsigned int,unsigned int);

void __stdcall _Init0825();