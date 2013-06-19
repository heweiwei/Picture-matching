// LLKCLIDlg.h : header file
//

#if !defined(AFX_LLKCLIDLG_H__0D5983C2_3E7E_4DE7_BFD6_533836A8E9BD__INCLUDED_)
#define AFX_LLKCLIDLG_H__0D5983C2_3E7E_4DE7_BFD6_533836A8E9BD__INCLUDED_
#include "GifAnimation.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIDlg dialog

class CLLKCLIDlg : public CDialog
{
// Construction
public:
	CLLKCLIDlg(CWnd* pParent = NULL);	// standard constructor
	CBitmapButton LoginButton;
	CBitmapButton AddUserButton;
	CBitmapButton ChangePwdButton;
	CBitmapButton ExpandButton;
	BOOL PreTranslateMessage(MSG *pMsg);

// Dialog Data
	//{{AFX_DATA(CLLKCLIDlg)
	enum { IDD = IDD_LLKCLI_LOGIN };
	CGifAnimation m_Animation;
	CString	m_user;
	CString	m_pwd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKCLIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLLKCLIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnTest();
	afx_msg void OnOut();
	afx_msg void OnChangePwd();
	afx_msg void OnExpand();
	//}}AFX_MSG

	LRESULT OnLogin(WPARAM w, LPARAM l);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKCLIDLG_H__0D5983C2_3E7E_4DE7_BFD6_533836A8E9BD__INCLUDED_)
