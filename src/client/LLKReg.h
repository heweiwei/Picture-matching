#if !defined(AFX_LLKREG_H__440019EC_DA66_4D72_8298_12898363CB89__INCLUDED_)
#define AFX_LLKREG_H__440019EC_DA66_4D72_8298_12898363CB89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LLKReg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLLKReg dialog

class CLLKReg : public CDialog
{
// Construction
public:
	CLLKReg(CWnd* pParent = NULL);   // standard constructor
	LRESULT OnReg(WPARAM w, LPARAM l);
// Dialog Data
	//{{AFX_DATA(CLLKReg)
	enum { IDD = IDD_ADDUSER };
	int		m_sex;
	CString	m_user;
	CString	m_pwd;
	CString	m_repwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKReg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap m_bmpAdduserBg;
	
	CDC		m_dcMem;
	CDC		m_dcBuf;
	
	BITMAP	m_infoBmpAdduserBg;

	// Generated message map functions
	//{{AFX_MSG(CLLKReg)
	afx_msg void OnRadioMale();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKREG_H__440019EC_DA66_4D72_8298_12898363CB89__INCLUDED_)
