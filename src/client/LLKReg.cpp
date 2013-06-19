// LLKReg.cpp : implementation file
//

#include "stdafx.h"
#include "LLKCLI.h"
#include "LLKReg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLLKReg dialog


CLLKReg::CLLKReg(CWnd* pParent /*=NULL*/)
	: CDialog(CLLKReg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLLKReg)
	m_sex = -1;
	m_user = _T("");
	m_pwd = _T("");
	m_repwd = _T("");
	//}}AFX_DATA_INIT
}


void CLLKReg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLLKReg)
	DDX_Radio(pDX, IDC_RADIO_MALE, m_sex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_user);
	DDV_MaxChars(pDX, m_user, 6);
	DDX_Text(pDX, IDC_EDIT_PWD, m_pwd);
	DDV_MaxChars(pDX, m_pwd, 6);
	DDX_Text(pDX, IDC_EDIT_REPWD, m_repwd);
	DDV_MaxChars(pDX, m_repwd, 6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLLKReg, CDialog)
	//{{AFX_MSG_MAP(CLLKReg)
	ON_BN_CLICKED(IDC_RADIO_MALE, OnRadioMale)
	ON_MESSAGE(NET_REG,OnReg)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLLKReg message handlers

void CLLKReg::OnRadioMale() 
{
	// TODO: Add your control notification handler code here
	
	
}

void CLLKReg::OnOK() {

	UpdateData();
	if (m_user=="")
	{
		MessageBox("用户名不能为空！");
		return;
	}
	else if(m_user.Find(' ')!=-1){
		MessageBox("用户名中不得有空格！");
		return;
	}
	else if (m_pwd=="")
	{
		MessageBox("密码不能为空！");
		return;
	}
	else if (m_pwd!=m_repwd)
	{
		MessageBox("两次输入密码不一致！");
		return;
	}
	else if (m_sex==-1)
	{
		MessageBox("请选择性别！");
		return;
	}

	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	buf.Format("2 %s %s %d",m_user,m_pwd,m_sex);
	
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	int res;
	res = sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));

//	CDialog::OnOK();
}

BOOL CLLKReg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bmpAdduserBg.LoadBitmap(IDB_ADDUSER_BG);
	m_bmpAdduserBg.GetBitmap(&m_infoBmpAdduserBg);
	CDC *pDC = GetDC();
	
	m_dcMem.CreateCompatibleDC(pDC);
	m_dcBuf.CreateCompatibleDC(pDC);
	
	m_dcMem.SelectObject(&m_bmpAdduserBg);
	
	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CLLKReg::OnReg(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type,id;
	char action[10];
	sscanf(data,"%d %s",&type,action);
	if(strcmp(action,"success")==0){
		sscanf(data,"%d %s %d",&type,action,&id);
		CString str;
		str.Format("注册成功，你的ID是%d,请牢记",id);
		MessageBox(str);
		CDialog::OnOK();
	}	
	else{
		MessageBox("注册失败");
	}
	delete[] data;

	CDialog::OnOK();

	return 0;
}

HBRUSH CLLKReg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_NAME)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  
	} 
	if(pWnd->GetDlgCtrlID()==IDC_PWD)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  
	} 
	if(pWnd->GetDlgCtrlID()==IDC_PWD2)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  
	} 
	if(pWnd->GetDlgCtrlID()==IDC_SEX)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  
	} 
	if(pWnd->GetDlgCtrlID()==IDC_RADIO_MALE)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  
	} 
	if(pWnd->GetDlgCtrlID()==IDC_RADIO_FEMALE)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  
	} 
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CLLKReg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.BitBlt(0,0,m_infoBmpAdduserBg.bmWidth,m_infoBmpAdduserBg.bmHeight,&m_dcMem,0,0,SRCCOPY);
	
	// Do not call CDialog::OnPaint() for painting messages
}
