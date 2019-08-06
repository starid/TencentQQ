#pragma once

#define WM_RECEIVED_MSG		WM_USER+100		//netlib模块发来消息
#define WM_TRANSMIT_MSG		WM_USER+101

#define WM_LOGINSUCCESSED	WM_USER+104
#define WM_TRAY_NOTIFICATION	WM_USER+105


//sCmd命令定义
enum
{
	ACTION_SEND_MSG,
	ACTION_QUERY_USERDATA,
};	

//统一消息类型码(wParam)
struct ActionCommand
{
	unsigned short	sCmd;		//消息类型
	unsigned short	sSubCmd;	//列表位置
};
