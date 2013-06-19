#if !defined(AFX_LLKHOME_H__94041AC9_077F_465A_B374_292BE75D5DBE__INCLUDED_)
#define AFX_LLKHOME_H__94041AC9_077F_465A_B374_292BE75D5DBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LLKHome.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLLKHome dialog

class CLLKHome : public CDialog
{
// Construction
public:
	CLLKHome(CWnd* pParent = NULL);   // standard constructor
	void GetTab(POINT p);
	void ChangeTable(int tn,boolean isOn);
	void ChangeHead(int tabNum,int chaNum,boolean isIn);
	LRESULT OnChangeTable(WPARAM w, LPARAM l);
	LRESULT OnUserInfoAll(WPARAM w, LPARAM l);
	LRESULT OnExitGame(WPARAM w, LPARAM l);
	LRESULT OnGameStart(WPARAM w, LPARAM l);
	LRESULT GetTableState(WPARAM w, LPARAM l);
	LRESULT Onlooker(WPARAM w, LPARAM l);
	int m_uid;
	CString m_nick;
	CString m_sex;
	int  m_score;
// Dialog Data
	//{{AFX_DATA(CLLKHome)
	enum { IDD = IDD_GAMEHOME };
	int chaNum;
	int tabNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKHome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap m_bmpBgHome;
	CBitmap m_bmpTable;
	CBitmap m_bmpTableOn;
	CBitmap m_bmpTableOff;
	CBitmap m_bmpFace1;
	CBitmap m_bmpFace0;
	CBitmap m_bmpDown;

	CDC		m_dcMem;
	CDC		m_dcBuf;

	BITMAP	m_infoBmpBgHome;
	BITMAP  m_infoBmpTable;
	BITMAP	m_infoBmpTableOn;
	BITMAP  m_infoBmpTableOff;
	BITMAP  m_infoBmpFace1;
	BITMAP  m_infoBmpFace0;
	BITMAP  m_infoBmpDown;

	int		sitState[15][6];//座位信息
	int		tableState[15];//桌子状态信息

	// Generated message map functions
	//{{AFX_MSG(CLLKHome)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKHOME_H__94041AC9_077F_465A_B374_292BE75D5DBE__INCLUDED_)
