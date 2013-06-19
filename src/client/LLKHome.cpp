// LLKHome.cpp : implementation file
//

#include "stdafx.h"
#include "LLKCLI.h"
#include "LLKHome.h"
#include "LLKGame.h"
#include "LLKBgReady.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LEFT_POS		16				//桌子的左上点的坐标
#define TOP_POS			36

#define TABLE_WIDTH		140				//桌子的长和宽
#define TABLE_HIGHT		152

#define HEAD_WIDTH		30				//头像的长和宽
#define HEAD_HIGHT		30


/////////////////////////////////////////////////////////////////////////////
// CLLKHome dialog
char nick[15][6][100];

CLLKHome::CLLKHome(CWnd* pParent /*=NULL*/)
	: CDialog(CLLKHome::IDD, pParent){
	//{{AFX_DATA_INIT(CLLKHome)
	//}}AFX_DATA_INIT
	tabNum=0;
	chaNum=0;
	memset(sitState,0,15*6*sizeof(int));
	memset(tableState,0,15*sizeof(int));
}


void CLLKHome::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLLKHome)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLLKHome, CDialog)
	//{{AFX_MSG_MAP(CLLKHome)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_MESSAGE(NET_INTABEL,OnChangeTable)
	ON_MESSAGE(NET_USERINFO_ALL,OnUserInfoAll)
	ON_MESSAGE(NET_GAME_EXIT,OnExitGame)
	ON_MESSAGE(NET_CHANGE_TABLE,OnGameStart)
	ON_MESSAGE(NET_TABLE_STATE,GetTableState)
	ON_MESSAGE(NET_ONLOOKER,Onlooker)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLLKHome message handlers

BOOL CLLKHome::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);	
	pApp->m_pSockThd->homeMsg=m_hWnd;
	
	m_bmpBgHome.LoadBitmap(IDB_HOME);
	m_bmpTable.LoadBitmap(IDB_HOME_TABLE);
	m_bmpTableOn.LoadBitmap(IDB_HOME_TABLE_ON);
	m_bmpTableOff.LoadBitmap(IDB_HOME_TABLE_OFF);
	m_bmpFace1.LoadBitmap(IDB_HOME_FACE1);
	m_bmpFace0.LoadBitmap(IDB_HOME_FACE0);
	m_bmpDown.LoadBitmap(IDB_HOME_DOWN);


	m_bmpBgHome.GetBitmap(&m_infoBmpBgHome);
	m_bmpTable.GetBitmap(&m_infoBmpTable);
	m_bmpTableOff.GetBitmap(&m_infoBmpTableOff);
	m_bmpTableOn.GetBitmap(&m_infoBmpTableOn);
	m_bmpFace1.GetBitmap(&m_infoBmpFace1);
	m_bmpFace0.GetBitmap(&m_infoBmpFace0);
	m_bmpDown.GetBitmap(&m_infoBmpDown);


	CDC *pDC = GetDC();
	
	m_dcMem.CreateCompatibleDC(pDC);
	m_dcBuf.CreateCompatibleDC(pDC);

	m_dcMem.SelectObject(&m_bmpBgHome);
	m_dcBuf.SelectObject(&m_bmpTable);

	RECT rc;
	GetWindowRect(&rc);//得到窗口信息
	
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);//菜单高度
	
	MoveWindow(rc.left,rc.top,m_infoBmpBgHome.bmWidth,m_infoBmpBgHome.bmHeight+cyCaption);//调整窗口大小
	
	ReleaseDC(pDC);

	//显示Table
	for (int i=0;i<15;i++){
		m_dcMem.BitBlt(LEFT_POS+(m_infoBmpTable.bmWidth+LEFT_POS)*(i%5),TOP_POS+(m_infoBmpTable.bmHeight+TOP_POS)*(i/5),m_infoBmpTable.bmWidth,m_infoBmpTable.bmHeight,
				&m_dcBuf,0,0,SRCCOPY);

	}

	//请求用户信息
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	buf.Format("8 %d",m_uid);
	
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));

	buf.Format("16 %d",m_uid);
	sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/************************************************************************/
/* 变更桌面                                                             */
/************************************************************************/
void CLLKHome::ChangeTable(int tn,boolean isOn){
	int tab_left=LEFT_POS+(TABLE_WIDTH+LEFT_POS)*((tn-1)%5)+HEAD_WIDTH;
	int tab_top=TOP_POS+(TABLE_HIGHT+TOP_POS)*((tn-1)/5)+HEAD_HIGHT;
	if (isOn){
		m_dcBuf.SelectObject(&m_bmpTableOn);
		m_dcMem.BitBlt(tab_left+3,tab_top+10,76,70,&m_dcBuf,0,0,SRCCOPY);
	}
	else{
		m_dcBuf.SelectObject(&m_bmpTableOff);
		m_dcMem.BitBlt(tab_left+2,tab_top+9,78,73,&m_dcBuf,0,0,SRCCOPY);
	}
	
	Invalidate(false);
	UpdateWindow();

}
/************************************************************************/
/* 变更头像                                                             */
/************************************************************************/
void CLLKHome::ChangeHead(int tabNum,int chaNum,boolean isIn){

	int x,y;
	int tab_left=LEFT_POS+(TABLE_WIDTH+LEFT_POS)*((tabNum-1)%5);
	int tab_top=TOP_POS+(TABLE_HIGHT+TOP_POS)*((tabNum-1)/5);

	if (chaNum==1){
		x=tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2;
		y=tab_top;
	}
	else if (chaNum==2){
		x=(tab_left+TABLE_WIDTH-HEAD_WIDTH);
		y=(tab_top+HEAD_HIGHT);		
	}
	else if (chaNum==3){
		x=(tab_left+TABLE_WIDTH-HEAD_WIDTH);
		y=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2);
	}
	else if (chaNum==4){
		x=(tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2);
		y=(tab_top+TABLE_HIGHT-HEAD_HIGHT);
	}
	else if (chaNum==5){
		x=(tab_left);
		y=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2);
	}
	else if (chaNum==6){
		x=(tab_left);
		y=(tab_top+HEAD_HIGHT);
	}

	if (isIn){
		m_dcBuf.SelectObject(&m_bmpFace1);
		m_dcMem.BitBlt(x,y,m_infoBmpFace1.bmWidth,m_infoBmpFace1.bmHeight,&m_dcBuf,0,0,SRCCOPY);
	}
	else{
		m_dcBuf.SelectObject(&m_bmpFace0);
		m_dcMem.BitBlt(x,y,m_infoBmpFace0.bmWidth,m_infoBmpFace0.bmHeight,&m_dcBuf,0,0,SRCCOPY);
	
	}
	Invalidate(false);
	UpdateWindow();
	
}
/************************************************************************/
/* 根据坐标判断在几号桌第几个座位                                       */
/************************************************************************/
void CLLKHome::GetTab(POINT p){
	//判断在几号桌
	for(int i=0;i<15;i++){
		int tab_left=LEFT_POS+(TABLE_WIDTH+LEFT_POS)*(i%5);
		int tab_top=TOP_POS+(TABLE_HIGHT+TOP_POS)*(i/5);
		if(p.x>=tab_left && p.x<=(tab_left+TABLE_WIDTH) && p.y>=tab_top && p.y<(tab_top+TABLE_HIGHT)){
			tabNum=i+1;
			//判断在第几个座位
			if(p.x>=(tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2)
				&& p.x<=(tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2+HEAD_WIDTH)
				&& p.y>=tab_top
				&& p.y<=(tab_top+HEAD_HIGHT)){//#1
				chaNum=1;
				break;
			}
			else if(p.x>=(tab_left+TABLE_WIDTH-HEAD_WIDTH)
				&& p.x<=(tab_left+TABLE_WIDTH-HEAD_WIDTH+HEAD_WIDTH)
				&& p.y>=(tab_top+HEAD_HIGHT)
				&& p.y<=(tab_top+HEAD_HIGHT+HEAD_HIGHT)){//#2
				chaNum=2;
				break;
			}
			else if(p.x>=(tab_left+TABLE_WIDTH-HEAD_WIDTH)
				&& p.x<=(tab_left+TABLE_WIDTH-HEAD_WIDTH+HEAD_WIDTH)
				&& p.y>=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2)
				&& p.y<=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2+HEAD_HIGHT)){//#3
				chaNum=3;
				break;
			}
			else if(p.x>=(tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2)
				&& p.x<=(tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2+HEAD_WIDTH)
				&& p.y>=(tab_top+TABLE_HIGHT-HEAD_HIGHT)
				&& p.y<=(tab_top+TABLE_HIGHT-HEAD_HIGHT+HEAD_HIGHT)){//#4
				chaNum=4;

				break;
			}
			else if(p.x>=(tab_left)
				&& p.x<=(tab_left+HEAD_WIDTH)
				&& p.y>=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2)
				&& p.y<=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2+HEAD_HIGHT)){//#5
				chaNum=5;
				break;
			}
			else if(p.x>=(tab_left)
				&& p.x<=(tab_left+HEAD_WIDTH)
				&& p.y>=(tab_top+HEAD_HIGHT)
				&& p.y<=(tab_top+HEAD_HIGHT+HEAD_HIGHT)){//#6
				chaNum=6;
				break;
			}
		}
	}
	if(chaNum==0){
		tabNum=0;
	}
}
int lastTab,lastCha;//为了在按钮中记录DOWN的座位信息在UP的时候还原
/************************************************************************/
/* 鼠标左键响应事件                                                     */
/************************************************************************/
void CLLKHome::OnLButtonDown(UINT nFlags, CPoint point) {


	tabNum=chaNum=0;
	GetTab(point);
	int x,y;
	int tab_left=LEFT_POS+(TABLE_WIDTH+LEFT_POS)*((tabNum-1)%5);
	int tab_top=TOP_POS+(TABLE_HIGHT+TOP_POS)*((tabNum-1)/5);
	if(tabNum!=0){
		if (chaNum==1){
			x=tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2;
			y=tab_top;
		}
		else if (chaNum==2){
			x=(tab_left+TABLE_WIDTH-HEAD_WIDTH);
			y=(tab_top+HEAD_HIGHT);		
		}
		else if (chaNum==3){
			x=(tab_left+TABLE_WIDTH-HEAD_WIDTH);
			y=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2);
		}
		else if (chaNum==4){
			x=(tab_left+TABLE_WIDTH/2-HEAD_WIDTH/2);
			y=(tab_top+TABLE_HIGHT-HEAD_HIGHT);
		}
		else if (chaNum==5){
			x=(tab_left);
			y=(tab_top+TABLE_HIGHT-HEAD_HIGHT*2);
		}
		else if (chaNum==6){
			x=(tab_left);
			y=(tab_top+HEAD_HIGHT);
		}
		m_dcBuf.SelectObject(&m_bmpDown);
		m_dcMem.BitBlt(x,y,m_infoBmpFace1.bmWidth,m_infoBmpFace1.bmHeight,&m_dcBuf,0,0,SRCCOPY);
		Invalidate(false);
		lastCha=chaNum;
		lastTab=tabNum;
	}

	CDialog::OnLButtonDown(nFlags, point);
}
void CLLKHome::OnLButtonUp(UINT nFlags, CPoint point) {
	tabNum=chaNum=0;
	GetTab(point);
	if(tabNum!=0){
		if(tableState[tabNum-1]==1){//游戏已开始
			if(sitState[tabNum-1][chaNum-1]!=0){
				//座位有人，发送旁观信息
				ChangeHead(lastTab,lastCha,true);
				CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
				sockaddr_in remotAddr;
				remotAddr.sin_family = AF_INET;
				remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
				remotAddr.sin_port = htons(pApp->port);
				CString buf;
				buf.Format("18 onlooker %d %d %d",chaNum,tabNum,m_uid);
				CSocket *pSock = pApp->m_pSockThd->GetSock();
				sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
			}
			else{
				ChangeHead(lastTab,lastCha,false);
				MessageBox("该桌已经开始游戏，请选择其他桌子。或者点击人物进行旁观");
			}
		}
		else if(lastCha==chaNum&&lastTab==tabNum){//游戏未开始，发送进入座位信息
			CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
			sockaddr_in remotAddr;
			remotAddr.sin_family = AF_INET;
			remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
			remotAddr.sin_port = htons(pApp->port);
			CString buf;
			buf.Format("4 in %d %d %d",chaNum,tabNum,m_uid);
			
			CSocket *pSock = pApp->m_pSockThd->GetSock();
			int res;
			res = sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
		}
	}
	if (sitState[lastTab-1][lastCha-1]!=0)
	{
		ChangeHead(lastTab,lastCha,true);
	}
	else
		ChangeHead(lastTab,lastCha,false);

	CDialog::OnLButtonUp(nFlags, point);
}

void CLLKHome::OnPaint() {
	CPaintDC dc(this);

	dc.BitBlt(0,0,m_infoBmpBgHome.bmWidth,m_infoBmpBgHome.bmHeight,&m_dcMem,0,0,SRCCOPY);
	dc.SetBkColor(RGB(82,113,156));
	CString info;
	info.Format("ID:%d  昵称:%s  性别:%s",m_uid,m_nick,m_sex);
	SetWindowText(info);
}

LRESULT CLLKHome::OnChangeTable(WPARAM w, LPARAM l){
	char *data = (char*)w;
	TRACE("home msg=%s\n",data);
	int type;
	char action[10];
	sscanf(data,"%d %s",&type,action);
	if(strcmp(action,"success")==0){//进入座位
		CLLKBgReady ReadyBg;//将需要的值赋给BgReady界面
		ReadyBg.chaNum=chaNum;
		ReadyBg.tabNum=tabNum;
		ReadyBg.c_uid=m_uid;
		ReadyBg.c_sex=m_sex;
		ReadyBg.c_nick=m_nick;
		ReadyBg.c_score=m_score;

		ReadyBg.DoModal();
		CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
		pApp->m_pSockThd->SetHwnd(m_hWnd);
	}
	else if(strcmp(action,"fail")==0){//已有人
		ChangeHead(lastTab,lastCha,true);
	 	MessageBox("该位置已经有人坐");
	}
	else if(strcmp(action,"userin")==0){//其他用户进入
		int tmpTabNum,tmpChaNum,tmpUid;
		char nickname[100];
		sscanf(data,"%d %s %d %d %d %s",&type,action,&tmpChaNum,&tmpTabNum,&tmpUid,nickname);
		strcpy(nick[tmpTabNum-1][tmpChaNum-1],nickname);
		sitState[tmpTabNum-1][tmpChaNum-1]=tmpUid;
		ChangeHead(tmpTabNum,tmpChaNum,true);
	}
	else if(strcmp(action,"userout")==0){//其他用户退出
		int tmpTabNum,tmpChaNum,tmpUid;
		char nickname[100];
		sscanf(data,"%d %s %d %d %d %s",&type,action,&tmpChaNum,&tmpTabNum,&tmpUid,nickname);
		strcpy(nick[tmpTabNum-1][tmpChaNum-1],nickname);
		sitState[tmpTabNum-1][tmpChaNum-1]=0;	
		ChangeHead(tmpTabNum,tmpChaNum,false);
	}
 	delete[] data;
	return 0;
}

LRESULT CLLKHome::OnUserInfoAll(WPARAM w, LPARAM l){
	char *data = (char*)w;
	UserInfo tmpUser;
	char nickname[100];
	sscanf(data,"%d %d %s %d %d %d %d",&tmpUser.type,&tmpUser.id,nickname,&tmpUser.sex,&(tmpUser.tabNum),&(tmpUser.chaNum),&tmpUser.isReady);
	strcpy(nick[tmpUser.tabNum-1][tmpUser.chaNum-1],nickname);
	TRACE("nickname=%s\n",nick[tmpUser.tabNum-1][tmpUser.chaNum-1]);
	sitState[tmpUser.tabNum-1][tmpUser.chaNum-1]=tmpUser.id;
	ChangeHead(tmpUser.tabNum,tmpUser.chaNum,true);
	delete[] data;
	return 0;
}

LRESULT CLLKHome::OnExitGame(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type;
	char action[10];
	sscanf(data,"%d %s",&type,action);
	if (strcmp(action,"exit")==0){
		EndDialog(IDCANCEL);
	}
	delete[] data;
	return 0;
}
void CLLKHome::OnClose() {

	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	buf.Format("10 %d",m_uid);
	
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	int res = sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
}
LRESULT CLLKHome::OnGameStart(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type,tmpTabNum;
	char action[10];
	sscanf(data,"%d %s %d",&type,action,&tmpTabNum);
	if(strcmp(action,"start")==0){
		tableState[tmpTabNum-1]=1;
		ChangeTable(tmpTabNum,true);
	}
	else if(strcmp(action,"finish")==0){
		tableState[tmpTabNum-1]=0;
		ChangeTable(tmpTabNum,false);
	}
	return 0;
}
LRESULT CLLKHome::GetTableState(WPARAM w, LPARAM l){
	TableState *tmp = (TableState*)w;
	for (int i=0;i<15;i++){
		if(tmp->tableOn[i]==1){
			tableState[i]=1;
			ChangeTable(i+1,true);
		}
	}
	return 0;
}
/************************************************************************/
/* 旁观者                                                               */
/************************************************************************/
LRESULT CLLKHome::Onlooker(WPARAM w, LPARAM l){
	char *data = (char*)w;
	char action[10];
	int type,lookedUid,tmpTabNum;
	sscanf(data,"%d %s %d %d",&type,action,&lookedUid,&tmpTabNum);
	if(strcmp(action,"success")==0){
		CLLKGame game;
		for(int i=0;i<6;i++){
			game.userMap[i].type=sitState[tmpTabNum-1][i];
			TRACE("onlooker=%s\n",nick[tmpTabNum-1][i]);
			strcpy(game.userNick[i],nick[tmpTabNum-1][i]);
		}
		game.tabNum=tmpTabNum;
		game.chaNum=chaNum;
		game.m_uid=lookedUid;
		game.isLooked=true;
		game.lookerUid=m_uid;
		game.DoModal();
		CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
		pApp->m_pSockThd->SetHwnd(m_hWnd);
	}

	return 0;
}