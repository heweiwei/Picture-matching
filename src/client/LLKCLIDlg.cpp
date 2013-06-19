// LLKCLIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LLKCLI.h"
#include "LLKCLIDlg.h"
#include "LLKReg.h"
#include "LLKHome.h"
#include "LLKChangePwd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIDlg dialog

CLLKCLIDlg::CLLKCLIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLLKCLIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLLKCLIDlg)
	m_user = _T("");
	m_pwd = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKCLIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLLKCLIDlg)
	DDX_Control(pDX, IDC_GIF_ANIMATION, m_Animation);
	DDX_Text(pDX, IDC_USER, m_user);
	DDV_MaxChars(pDX, m_user, 6);
	DDX_Text(pDX, IDC_PWD, m_pwd);
	DDV_MaxChars(pDX, m_pwd, 6);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLLKCLIDlg, CDialog)
	//{{AFX_MSG_MAP(CLLKCLIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(IDC_OUT, OnOut)
	ON_BN_CLICKED(IDC_ChangePwd,OnChangePwd)
	ON_BN_CLICKED(IDC_EXPAND,OnExpand)
	ON_MESSAGE(NET_LOGIN,OnLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLLKCLIDlg message handlers

BOOL CLLKCLIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);	

	LoginButton.LoadBitmaps(IDB_GAME_LOGIN_BUTTON,IDB_GAME_LOGIN_DOWN,0,0);
	LoginButton.SubclassDlgItem(IDC_BTN_TEST,this);
	LoginButton.SizeToContent();
	AddUserButton.LoadBitmaps(IDB_GAME_ADDUSER,IDB_GAME_ADDUSER_DOWN,0,0);
	AddUserButton.SubclassDlgItem(IDC_OUT,this);
	AddUserButton.SizeToContent();
	ChangePwdButton.LoadBitmaps(IDB_GAME_CHANGEPWD,IDB_GAME_CHANGEPWD_DOWN,0,0);
	ChangePwdButton.SubclassDlgItem(IDC_ChangePwd,this);
	ChangePwdButton.SizeToContent();
	ExpandButton.LoadBitmaps(IDB_GAME_EXPAND,IDB_GAME_EXPANG_DOWN,0,0);
	ExpandButton.SubclassDlgItem(IDC_EXPAND,this);
	ExpandButton.SizeToContent();

	m_Animation.LoadAnimatedGif("./res/1.gif");//加载动画
	m_Animation.Play();//显示动画

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLLKCLIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLLKCLIDlg::OnPaint() 
{
	if (IsIconic()){
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); 
		// dc.TextOut(10,10,"Hello World");
		CDialog::OnPaint();
	}	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLLKCLIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLLKCLIDlg::OnBtnTest() 
{
	CDC *pDC = GetDC(); 

	CBitmap bmpBgHome;

	bmpBgHome.LoadBitmap(IDB_GAME_HOME);

	CDC dcMem;

	dcMem.CreateCompatibleDC(pDC);
	dcMem.SelectObject(&bmpBgHome);

	ReleaseDC(pDC);

	UpdateData();
	if(m_user=="" || m_pwd==""){
		MessageBox("请输入正确的用户名密码");
		return;
	}
	//发送用户名密码
	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	buf.Format("1 %s %s",m_user,m_pwd);

	CSocket *pSock = pApp->m_pSockThd->GetSock();
	int res;
	res = sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));

	m_Animation.Stop();//停止动画

}

void CLLKCLIDlg::OnOut(){
//	if(IDYES==(MessageBox("是否注册新账号","提示",MB_YESNO)))
	//	CDialog::OnCancel();
//	{

		CLLKReg adduser;
		adduser.DoModal();
		CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
		pApp->m_pSockThd->SetHwnd(m_hWnd);

//	}
}
LRESULT CLLKCLIDlg::OnLogin(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type,sex,uid,score;
	char nick[6]="",result[7]="";
	sscanf(data,"%d %s",&type,result);
	if(strcmp(result,"success")==0){
		sscanf(data,"%d %s %d %s %d %d",&type,result,&uid,nick,&sex,&score);
		CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
		pApp->userInfo.id=uid;
		pApp->userInfo.nick.Format("%s",nick);
		pApp->userInfo.sex=sex;
		pApp->userInfo.type=score;//分数
		CDialog::OnOK();
	}
	else if(strcmp(result,"fail")==0){
		MessageBox("用户名密码错误");
	}
	else if(strcmp(result,"hasLogin")==0){
		MessageBox("此用户已登陆");
	}

	delete[] data;
	return 0;
}

void CLLKCLIDlg::OnChangePwd()
{
	CLLKChangePwd changepwd;
	changepwd.DoModal();
	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);
}

void CLLKCLIDlg::OnExpand()
{
	MessageBox("test");
}

BOOL CLLKCLIDlg::PreTranslateMessage(MSG *pMsg)//将enter键屏蔽
{
    if(pMsg->message == WM_KEYDOWN)
        if(int(pMsg->wParam) == VK_RETURN)
			return TRUE;
		return CDialog::PreTranslateMessage(pMsg);
}

