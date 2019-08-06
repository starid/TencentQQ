#pragma once
#pragma pack(1)       //强制1字节对齐(保证所见即所得)
#include<vector>
#include<string>

/**************************0134好友以及分组数据包*******************************************/
struct PacketRet0134_FriendsFolder
{
	unsigned int	dwUin;
	unsigned char	cUinType;
	unsigned char	cUinFlags1;
	unsigned char	cUinFlags2;
	unsigned char	cUinFlags3;
	unsigned char	cUinFlags4;
	unsigned short	arrFolderIDList;
	unsigned short	arrFolderIndex;		//当arrFolderIDList==0，无此字段
};

struct PacketRet0134
{
	unsigned char	cResult;
	unsigned short	wFriendNum;
	unsigned int	dwNewFriendListSeq;
	unsigned int	dwNewTime;
	unsigned int	dwRefreshTime;
	unsigned char	cOver;
	unsigned short	wIndex;
	unsigned short	arstUin;
	std::vector<PacketRet0134_FriendsFolder> FriendsFolderList;
};
/**************************0134好友以及分组数据包*******************************************/

/**************************0001好友状态数据包*******************************************/
struct PacketRet0027_Friend
{
	unsigned int	dwUin;
	unsigned char	cType;
	unsigned int	dwIp;
	unsigned short	wPort;
	unsigned short	wStatus;
	unsigned short	wProtocol;
	unsigned char	cMode;
	unsigned int	dwClientType;
	unsigned char	cStatusFlag;
	unsigned char	cMicroMsgStatus;
	unsigned char	cNetType;
	unsigned char	cAudioDevFlag;
	unsigned char	cNetWorkStatusExFlag;
	unsigned char	buffReserved[0x6];
	unsigned int	dwUinLevel;
	unsigned short	wRsSeq;
	unsigned short	cRsRefresh;
	unsigned short	wStatusSeq;
	unsigned short	wReserve;
};

struct PacketRet0027
{
	unsigned char	cResult;
	std::vector<PacketRet0027_Friend> FriendsList;
};
/**************************0001好友状态数据包*******************************************/

/**************************0001分组信息数据包**********************************************/
struct PacketRet0001_FriendsFolder
{
	unsigned short	wLen;
	unsigned char	cFolderSvrIndex;
	unsigned char	cGroupSeq;
	unsigned char	cFolderLen;
	std::string		strFolderName;	//分组标识符
};
struct PacketRet0001
{
	unsigned char	cSubCmd;
	unsigned char	cResult;
	unsigned char	cVer;
	unsigned char	cTotal;
	unsigned int	dwSeq;
	unsigned char	cTotalPageNum;
	unsigned char	cPageNum;
	unsigned char	cFolderNum;          //分组数
	std::vector<PacketRet0001_FriendsFolder> FriendsFolderList;
};
/**************************0001分组数据包**********************************************/