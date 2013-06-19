#if !defined(AFX_LLKBGREADY_H__45B799E6_44CB_4C13_A37B_2DDD32A8DEE3__INCLUDED_)
#define AFX_LLKBGREADY_H__45B799E6_44CB_4C13_A37B_2DDD32A8DEE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LLKBgReady.h : header file
//
#include <map>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CLLKBgReady dialog

class CLLKBgReady : public CDialog
{
// Construction
public:
	CLLKBgReady(CWnd* pParent = NULL);   // standard constructor
	void ChangeReadyHead(int cn,boolean isMan,boolean isReady,boolean isIn);
	void Tool(int cn);
	void ShowName(int chaNum,CString nick);
	BOOL PreTranslateMessage(MSG *pMsg);
	void SendMsg();

	LRESULT OnChangeTable(WPARAM w, LPARAM l);
	LRESULT OnChangeReady(WPARAM w, LPARAM l);
	LRESULT OnUserInfoReady(WPARAM w, LPARAM l);
	LRESULT OnGameStart(WPARAM w, LPARAM l);
	LRESULT RecvMsg(WPARAM w, LPARAM l);

	map<int,UserInfo> userList;
 	int		c_uid;
 	CString c_nick;
 	CString c_sex;
	int		c_score;
	bool	isReady;
	int		userIds[6];
	CBitmapButton StartButton;
	CBitmapButton TestButton;
	//
// Dialog Data
	//{{AFX_DATA(CLLKBgReady)
	enum { IDD = IDD_READYBG };
	CEdit	m_RCDCon;
	int chaNum;
	int tabNum;
	CString	m_Record;
	CString	m_MyEnter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKBgReady)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap m_bmpBgReady;
	CBitmap m_bmpBgReady3;
	CBitmap m_bmpReadyPlayer;
	CBitmap m_bmpTool;
	CBitmap m_bmpBgReady2;
	CBitmap m_bmpBgTmp;
	CBitmapButton CloseButton;

	CDC		m_dcMem;
	CDC		m_dcBuf;
	CDC     m_dcBuf1;
	CDC     m_dcBuf2;
	
	BITMAP  m_infoBmpBgReady;
	BITMAP  m_infoBmpReadyPlayer;
	BITMAP  m_infoBmpTool;
	BITMAP  m_infoBmpBgReady2;


	// Generated message map functions
	//{{AFX_MSG(CLLKBgReady)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTest();
	afx_msg void OnCancel();
	afx_msg void OnReady();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKBGREADY_H__45B799E6_44CB_4C13_A37B_2DDD32A8DEE3__INCLUDED_)
