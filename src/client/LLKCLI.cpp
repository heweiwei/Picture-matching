// LLKCLI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LLKCLI.h"
#include "LLKCLIDlg.h"
#include "LLKHome.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIApp

BEGIN_MESSAGE_MAP(CLLKCLIApp, CWinApp)
	//{{AFX_MSG_MAP(CLLKCLIApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIApp construction

CLLKCLIApp::CLLKCLIApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLLKCLIApp object

CLLKCLIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIApp initialization

BOOL CLLKCLIApp::InitInstance()
{

	AfxSocketInit();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	GetPrivateProfileStringA("SERVER_INFO","IP","127.0.0.1",ip,sizeof(ip),"./set.ini");
	char strPort[5];
	GetPrivateProfileStringA("SERVER_INFO","PORT","5601",strPort,sizeof(strPort),"./set.ini");
	port = atoi(strPort);
	m_pSockThd = new CSockThd;
	m_pSockThd->CreateThread();

	CLLKCLIDlg login;
	int nResponse = login.DoModal();

	if(nResponse == IDCANCEL)
		return FALSE;

	CLLKHome home;
	home.m_uid=userInfo.id;
	home.m_nick=userInfo.nick;
	home.m_score=userInfo.type;
	if(userInfo.sex==0){
		home.m_sex="Å®";
	}
	else{
		home.m_sex="ÄÐ";
	}
	m_pMainWnd = &home;
	home.DoModal();

	return FALSE;
}
