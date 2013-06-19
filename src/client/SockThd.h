#if !defined(AFX_SOCKTHD_H__C87296C7_B1AE_45EC_A410_62EE7533864F__INCLUDED_)
#define AFX_SOCKTHD_H__C87296C7_B1AE_45EC_A410_62EE7533864F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SockThd.h : header file
//
#include <list>
using namespace std;

struct MapInfo{
	int type;
	int val;
	int recMap[14][10];
};
struct TableState{
	int type;
	int tableOn[15];
};
struct UserInfo{
	int id;
	CString nick;
	CString password;
	int sex;
	sockaddr_in address;
	int tabNum;
	int chaNum;
	int isReady;
	int	type;
};
struct RankListMsg{
	int type;
	int uid[6];
	int rankNum[6];
	int score[6];
};
#define NET_LOGIN			WM_USER+1//登陆消息ID
#define NET_REG				WM_USER+2//注册消息ID
#define NET_CHANGEPWD		WM_USER+3 //修改密码消息ID
#define NET_INTABEL			WM_USER+4 //进入桌面消息ID
#define NET_OUTTABLE		WM_USER+5//退出桌面消息ID
#define NET_READY			WM_USER+6//游戏准备消息ID
#define NET_USERINFO_READY	WM_USER+7 //游戏准备时，用户信息
#define NET_USERINFO_ALL	WM_USER+8//大厅用户信息消息
#define NET_GAME_START		WM_USER+9//游戏开始消息
#define NET_GAME_EXIT		WM_USER+10//退出游戏消息
#define NET_REC_MAP			WM_USER+11//得到随机矩阵消息
#define NET_GAME_OVER		WM_USER+12//游戏结束消息
#define NET_BOX_CLEAR		WM_USER+13//方块消除消息
#define NET_REDO_MAP		WM_USER+14//重排矩阵消息
#define NET_CHANGE_TABLE	WM_USER+15//游戏开始修改桌面
#define NET_TABLE_STATE		WM_USER+16//桌面状态
#define NET_RANK_LIST		WM_USER+17//游戏排行
#define NET_ONLOOKER		WM_USER+18//旁观者消息
#define NET_LOOKER_REC_MAP  WM_USER+19//旁观随机矩阵信息
#define NET_LOOKER_EXIT		WM_USER+20//旁观者退出消息
#define NET_TALKMSG         WM_USER+21//聊天消息
/////////////////////////////////////////////////////////////////////////////
// CSockThd thread

class CSockThd : public CWinThread
{
	DECLARE_DYNCREATE(CSockThd)
public:
	CSockThd();           // protected constructor used by dynamic creation

// Attributes
public:
	HWND	homeMsg;
	HWND	readyMsg;
	HWND	gameMsg;
// Operations
public:

	CSocket* GetSock(){
		return &m_sock;
	}

	void SetHwnd(HWND hWnd){
		m_hWndMsg = hWnd;
	}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockThd)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSockThd();

	CSocket m_sock; //udp 套接字，负责传输数据

	HWND	m_hWndMsg; 
	
	// Generated message map functions
	//{{AFX_MSG(CSockThd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKTHD_H__C87296C7_B1AE_45EC_A410_62EE7533864F__INCLUDED_)
