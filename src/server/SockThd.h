#if !defined(AFX_SOCKTHD_H__C87296C7_B1AE_45EC_A410_62EE7533864F__INCLUDED_)
#define AFX_SOCKTHD_H__C87296C7_B1AE_45EC_A410_62EE7533864F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SockThd.h : header file
#include <map>
#include <list>
using namespace std;

struct TableState{
	int type;
	int tableOn[15];
};

struct RankListMsg{
	int type;
	int uid[6];
	int rankNum[6];
	int score[6];
};
/************************************************************************/
/* 矩阵信息                                                             */
/************************************************************************/
struct MapInfo{
	int type;
	int val;
	int recMap[14][10];
};
/************************************************************************/
/* 用户信息                                                             */
/************************************************************************/
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
	int isFail;
	MapInfo mapInfo;
	list<int> onlookers;
};

/////////////////////////////////////////////////////////////////////////////
// CSockThd thread

class CSockThd : public CWinThread
{
	DECLARE_DYNCREATE(CSockThd)
public:
	CSockThd();           // protected constructor used by dynamic creation

// Attributes
public:
	UserInfo	GetUserById(int uid);
	int			AddUser(UserInfo ui);
	int			ChangePassword(int uid,CString password,CString repassword);
	int         GetTableMsg(int chaNum,int tabNum);
	int         GetReadyMsg(int chaNum);
	void		SendMsgToClients(char *data);
	void		SendMsgToClients(int tabNum,char *data);
	void		SendSameTableUserInfo(UserInfo ui);
	void		SendAllUserInfo(UserInfo ui);
	void		SendGameStartMsg(int tabNum,int uid);
	void		SendGameOverMsg(int uid,int isFail);
	void		DealBoxClearMsg(int uid,int x1,int y1,int x2,int y2);
	void		RedoMap(int (&recMap)[14][10]);
	void		DealRedoMapRequest(int uid);
	int			GetRecNum(int (&recMap)[14][10]);
	int			ChangeScore(int uid,int score);
	RankListMsg	GetRankList(int tabNum);
 	map<int,UserInfo>	clients;		//客户端列表

	TableState	tableState;
	
// Operations
public:

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
	void		GeneralRec(int (&randMap)[14][10]);
	void		CopyMap(int (&src)[14][10],int (&trg)[14][10]);

	CSocket m_sock; //udp 套接字，负责传输数据
	int		tmpRecMap[12][8];
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
