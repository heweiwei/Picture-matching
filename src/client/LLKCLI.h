// LLKCLI.h : main header file for the LLKCLI application
//

#if !defined(AFX_LLKCLI_H__5C6EAE22_1B68_4201_BC86_F6B36B823D93__INCLUDED_)
#define AFX_LLKCLI_H__5C6EAE22_1B68_4201_BC86_F6B36B823D93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "SockThd.h"

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIApp:
// See LLKCLI.cpp for the implementation of this class
//
class CLLKCLIApp : public CWinApp
{
public:
	CLLKCLIApp();

	CSockThd *m_pSockThd;
	UserInfo userInfo;
	char ip[20];
	int port;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKCLIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLLKCLIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKCLI_H__5C6EAE22_1B68_4201_BC86_F6B36B823D93__INCLUDED_)
