#pragma once

enum RESULT
{
	RESULT_SUCCESS=0xFF00,
	ERR_COMMON,						//一般性错误

	ERR_NORESPOND,					//远程服务器没有反应
	ERR_NETINIT,					//网络初始化失败
	ERR_GETHOSTBYNAME,				//dns转换错误
	ERR_LOGIN_FAILED,				//登陆失败
	ERR_LOGIN_PASSWORD,				//密码错误
	ERR_LOGIN_CHECK,				//验证码
	ERR_SEND_FAILED,				//数据发送失败
	ERR_CONNECT_FAILED,				//tcp链接服务器失败
	ERR_NOENOUGHBUF,				//malloc分配失败
	ERR_CHECK_PACKET,				//数据包检查出错
	ERR_ANALYSIS_PACKET,			//数据包分析出错
	ERR_OPEN_REG,					//注册表操作失败
	ERR_ADJUSTPRIVILEGES_FAILED,	//权限提升失败
	ERR_PROCESS_FAILED,				//隐藏函数获取失败
	ERR_ENCRYPT_FAILED,				//数据加密失败
	ERR_CREATEGUID_FAILED,			//CoCreateGuid创建guid失败
	ERR_GENERATE_COMPUTERID_FAILED,	//computer id生成失败
	ERR_INSTRUCT_INVALID,
	ERR_ECDH_ERROR,					//ECDH失败
	ERR_GETSID_FAILED,				//获取sid错误
	ERR_IOCP,						//iocp相关错误
	ERR_PACKET_ABANDON,				//丢弃数据包

};
