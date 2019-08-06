#pragma once
#ifdef _USRDLL
#define DIPPER_EXPORTS 1
#else
#undef  DIPPER_EXPORTS
#endif

#ifdef DIPPER_EXPORTS
#define DIPPEREXPORTS_FolderList_API __declspec(dllexport)
#else
#define DIPPEREXPORTS_FolderList_API __declspec(dllimport)
#endif


#include"PacketRet.h"


struct Friend
{
	//参考PacketRet0027_Friend字段
	unsigned int	dwUin;
	unsigned short	wStatus;
};

//定义朋友位置结构体
struct FriendPos
{
	unsigned int	mClusterIndex;	//std::vector<FriendFolder> mList;目录序号
	unsigned int	mFriendIndex;	//std::vector<Friend> Friends;朋友列表序号
};

struct ClusterFolder
{
	unsigned short	wClusterIndex;
	std::string		strClusterName;		//分组名
	std::vector<Friend> Friends;		//好友列表
};

struct GroupFolder
{
	unsigned int dwClusterId;
	unsigned int dwExternalClusterId;
	std::string				strFolderName;		//群名
	std::vector<Friend> mMembers;		//成员列表
};

#define	FriendsFolderIterator	std::vector<FriendFolder>::iterator

class DIPPEREXPORTS_FolderList_API FolderList
{
public:
	FolderList(){Clear();};
	~FolderList(){Clear();};
public:
	void InsertFolder(const PacketRet0134&);	//插入目录（分组或者群）
	void InsertCluster(const PacketRet0001&);	//插入分组信息
	void InitFriendsStatus(const PacketRet0027&);
	void Clear(){mList1.clear();mList2.clear();};
private:
	bool IsExistCluster(const unsigned short,unsigned int&);
	bool IsExistFriend(const unsigned int,FriendPos&);
public:
	std::vector<ClusterFolder> mList1;
	std::vector<GroupFolder> mList2;
};