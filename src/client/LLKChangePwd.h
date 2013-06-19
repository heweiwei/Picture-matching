#if !defined(AFX_LLKCHANGEPWD_H__BBD4F3AB_592F_48BD_9C03_1B3DC277211F__INCLUDED_)
#define AFX_LLKCHANGEPWD_H__BBD4F3AB_592F_48BD_9C03_1B3DC277211F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LLKChangePwd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLLKChangePwd dialog

class CLLKChangePwd : public CDialog
{
// Construction
public:
	CLLKChangePwd(CWnd* pParent = NULL);   // standard constructor
	LRESULT OnChangePwd(WPARAM w, LPARAM l);
// Dialog Data
	//{{AFX_DATA(CLLKChangePwd)
	enum { IDD = IDD_CHANGEPWD };
	CString	m_pwd;
	CString	m_repwd;
	CString	m_repwd2;
	CString	m_user;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKChangePwd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap m_bmpChangePwdBg;
	
	CDC		m_dcMem;
	CDC		m_dcBuf;
	
	BITMAP	m_infoBmpChangePwdBg;

	// Generated message map functions
	//{{AFX_MSG(CLLKChangePwd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKCHANGEPWD_H__BBD4F3AB_592F_48BD_9C03_1B3DC277211F__INCLUDED_)
