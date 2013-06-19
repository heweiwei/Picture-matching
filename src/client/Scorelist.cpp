// Scorelist.cpp : implementation file
//

#include "stdafx.h"
#include "LLKCLI.h"
#include "Scorelist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Scorelist dialog


Scorelist::Scorelist(CWnd* pParent /*=NULL*/)
	: CDialog(Scorelist::IDD, pParent)
{
	//{{AFX_DATA_INIT(Scorelist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Scorelist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Scorelist)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Scorelist, CDialog)
	//{{AFX_MSG_MAP(Scorelist)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////


BOOL Scorelist::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bmpScoreList.LoadBitmap(IDB_GAME_SCORE_LIST);
	
	m_bmpScoreList.GetBitmap(&m_infoBmpScoreList);

	CloseButton.LoadBitmaps(IDB_GAME_CLOSE,IDB_GAME_CLOSE_DOWN,0,0);
	CloseButton.SubclassDlgItem(IDC_CANCEL,this);
	CloseButton.SizeToContent();

	
	
	CDC *pDC = GetDC();
	
	m_dcMem.CreateCompatibleDC(pDC);
	m_dcBuf.CreateCompatibleDC(pDC);
	
	m_dcMem.SelectObject(&m_bmpScoreList);
	m_dcBuf.SelectObject(&m_bmpScoreList);
	
	RECT rc;
	GetWindowRect(&rc);//得到窗口信息
	
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);//菜单高度
	
	MoveWindow(rc.left,rc.top,m_infoBmpScoreList.bmWidth,m_infoBmpScoreList.bmHeight+cyCaption);//调整窗口大小
	
	ReleaseDC(pDC);


	int y=60;
	int x=25;
	int num=0;
	CFont font;
	font.CreatePointFont(120,"Monotype Corsiva",&m_dcMem);
	
	m_dcMem.SelectObject(&font);
	
	m_dcMem.SetBkMode(TRANSPARENT);

	for (int i=0;i<6;i++)
	{
		if (sorce[i]!=-1)
		{
			num=i+1;
			char c[10];
			m_dcMem.SetTextColor(RGB(0,0,255));//设置字体颜色
			itoa(num,c,10);

			m_dcMem.TextOut(x+10,y,c);//NUM
			
			for(int j=0;j<6;j++){
				if(userMap[j].type==uid[i]){
					m_dcMem.TextOut(x+170,y,username[j]);//USERNAME
					break;
				}   
			}
			CString strTotal;
			strTotal.Format("%d(+%d)",total[i]-sorce[i],sorce[i]);
			m_dcMem.TextOut(x+300,y,strTotal);//SCORE;

			CString level;
			if(total[i]<100){
				level.Format("独眼龙");	
			}
			else if(total[i]<500){
				level.Format("近视眼");
			}
			else if(total[i]<1000){
				level.Format("三只眼");
			}
			else{
				level.Format("火眼金睛");
			}
			m_dcMem.TextOut(x+450,y,level);//LEVEL;

			y=y+25;
		}

	}

	Invalidate(false);
	//还原字体，使用完还原是好习惯= =
	CFont font1;
	font1.CreatePointFont(110,"system",&m_dcMem);
	m_dcMem.SelectObject(&font1);
	m_dcMem.SetTextColor(RGB(0,0,0));
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Scorelist::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.BitBlt(0,0,m_infoBmpScoreList.bmWidth,m_infoBmpScoreList.bmHeight,&m_dcMem,0,0,SRCCOPY);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void Scorelist::OnCancel() 
{
	EndDialog(IDCANCEL);
	// TODO: Add your control notification handler code here
	
}
