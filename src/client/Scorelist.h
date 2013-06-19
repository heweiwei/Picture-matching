#if !defined(AFX_SCORELIST_H__B8C9A565_2FC5_4B57_9240_9FE2CDE8326F__INCLUDED_)
#define AFX_SCORELIST_H__B8C9A565_2FC5_4B57_9240_9FE2CDE8326F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Scorelist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Scorelist dialog

class Scorelist : public CDialog
{
// Construction
public:
	Scorelist(CWnd* pParent = NULL);   // standard constructor
	int		sorce[6];
	int		total[6];
	char	username[6][100];
	int		uid[6];
	MapInfo	userMap[6];
// Dialog Data
	//{{AFX_DATA(Scorelist)
	enum { IDD = IDD_SCORE_LIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Scorelist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap m_bmpScoreList;
	CBitmapButton CloseButton;
	
	CDC		m_dcMem;
	CDC		m_dcBuf;
	
	BITMAP	m_infoBmpScoreList;

	// Generated message map functions
	//{{AFX_MSG(Scorelist)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORELIST_H__B8C9A565_2FC5_4B57_9240_9FE2CDE8326F__INCLUDED_)
