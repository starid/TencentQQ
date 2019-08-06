#include"GlobeVar.h"

namespace GlobeVar
{
	CRespondQueryQQBindingStat mRespondQueryQQBindingStat;
	void Error_Check(unsigned int mode)
	{
		switch(mode)
		{
		case RESULT_SUCCESS:
			{
			}break;
		case ERR_LOGIN_FAILED:
			{
				AfxMessageBox("登陆失败,请重新登陆");
			}break;
		case ERR_LOGIN_PASSWORD:
			{
				AfxMessageBox("密码错误,请重新输入");
			}break;
		default:
			{
				char buf[0x20]={0};
				sprintf(buf,"%0x04",mode);
				MessageBox(NULL,buf,"error",MB_OK);
				exit(-1);
			}break;
		}
	}
};