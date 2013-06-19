// LLKGame.cpp : implementation file
//

#include "stdafx.h"
#include "LLKCLI.h"
#include "LLKGame.h"
#include "windows.h" 
#include "Scorelist.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
//在按钮里（或其他地方等）加上下边语句，即可播放
//PlaySound("c:\\test.wav", NULL, SND_FILENAME | SND_ASYNC);


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LEFT_POS 100				//方块的左上点的坐标
#define TOP_POS  220

#define TIMEBAR_LEFT 80				//时间条的左上点的坐标
#define TIMEBAR_TOP 574

#define TIMEBAR_WIDTH 332			//时间条的宽和高
#define TIMEBAR_HIGHT 13

#define TIMEBAR_BG_W 61//630			//时间条背景色的位置
#define TIMEBAR_BG_H 542//295

/////////////////////////////////////////////////////////////////////////////
// CLLKGame dialog
boolean isPlay=false;

CLLKGame::CLLKGame(CWnd* pParent /*=NULL*/)
	: CDialog(CLLKGame::IDD, pParent){
	//{{AFX_DATA_INIT(CLLKGame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	preX=-1;preY=-1;nowX=-1;nowY=-1;
	c1.x=c1.y=c2.x=c2.y=0;
	seconds=0;
	gameOn=true;
	for(int i=0;i<14;i++){
		for(int j=0;j<10;j++){
			llk_map[i][j]=0;
		}
	}
	number=96;
	link_times=0;
	max_count=1;
	x=30;
	isPlay=false;
	memset(userNick,0,6*100*sizeof(char));
}


void CLLKGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLLKGame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLLKGame, CDialog)
	//{{AFX_MSG_MAP(CLLKGame)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(NET_REC_MAP,OnGetRecMap)
	ON_MESSAGE(NET_GAME_OVER,OnGameOver)
	ON_MESSAGE(NET_BOX_CLEAR,OnBoxClear)
	ON_MESSAGE(NET_REDO_MAP,OnRedoMap)
	ON_MESSAGE(NET_RANK_LIST,GetRankList)
	ON_MESSAGE(NET_LOOKER_REC_MAP,GetLookerRecMap)
	ON_MESSAGE(NET_LOOKER_EXIT,OnLookerExit)
	
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLLKGame message handlers
BOOL CLLKGame::OnInitDialog() {
	CDialog::OnInitDialog();

	//请求随机矩阵
	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);	
	pApp->m_pSockThd->gameMsg=m_hWnd;
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	if (!isLooked){
		buf.Format("11 %d",m_uid);
	}
	else{
		buf.Format("19 %d %d",lookerUid,tabNum);
	}
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));

	m_bmpTmpBg.LoadBitmap(IDB_GAME_BG);
	m_bmpBoom.LoadBitmap(IDB_GAME_BOOM);
	m_bmpBg.LoadBitmap(IDB_GAME_BG);
	m_bmpBox.LoadBitmap(IDB_GAME_BOX);
	m_bmpLight.LoadBitmap(IDB_GAME_LIGHT);
	m_bmpTool.LoadBitmap(IDB_GAME_TOOL);

	m_bmpBoom.GetBitmap(&m_infoBoom);
	m_bmpBg.GetBitmap(&m_infoBmpBg);
	m_bmpBox.GetBitmap(&m_infoBox);
	m_bmpLight.GetBitmap(&m_infoLight);
	m_bmpTool.GetBitmap(&m_infoBmpTool);

	CDC *pDC = GetDC();

	m_dcMem.CreateCompatibleDC(pDC);
	m_dcBuf.CreateCompatibleDC(pDC);
	m_dcMem.SelectObject(&m_bmpBg);
	m_dcBuf.SelectObject(&m_bmpBox);

	RECT rc;
	GetWindowRect(&rc);//得到窗口信息
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);//菜单高度
	MoveWindow(rc.left,rc.top,m_infoBmpBg.bmWidth,m_infoBmpBg.bmHeight+cyCaption);//调整窗口大小
	ReleaseDC(pDC);

	//道具
	cn=5;
	Tool(cn);
	//初始化方块数
	SetDlgItemInt(IDC_NUMBER,number);
	//游戏开始声音
	PlaySound(".\\res\\start.wav", NULL, SND_FILENAME | SND_ASYNC);

	m_brush.CreateSolidBrush(RGB(55,77,118));
	if(!isLooked){
		SetTimer(1,50,NULL);//计时器
		SetTimer(2,100,NULL);
	}
	return TRUE;
}

void CLLKGame::OnPaint() {
	CPaintDC dc(this); // device context for painting
	//画背景
	dc.BitBlt(0,0,m_infoBmpBg.bmWidth,m_infoBmpBg.bmHeight,&m_dcMem,0,0,SRCCOPY);

	// Do not call CDialog::OnPaint() for painting messages
}

void CLLKGame::OnLButtonDown(UINT nFlags, CPoint point) {

	//游戏开始
	if(gameOn && !isLooked){
		//如果前一点存在，将其置为非选中
		if (preX!=-1){
			m_dcBuf.SelectObject(&m_bmpBox);
			m_dcMem.BitBlt(LEFT_POS+preX*m_infoBox.bmWidth/3,TOP_POS+preY*m_infoBox.bmHeight/16,
				m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,0,m_infoBox.bmHeight/16*(llk_map[preX+1][preY+1]-1),SRCCOPY);
		}
		//得到当前点合法坐标
		if((point.x-LEFT_POS)>0&&(point.y-TOP_POS)>0){
			nowX=(point.x-LEFT_POS)/(m_infoBox.bmWidth/3);
			nowY=(point.y-TOP_POS)/(m_infoBox.bmHeight/16);
			if (nowX>=0 && nowX<12 && nowY>=0 && nowY<8){//坐标合法
				
			}else{
				nowX=-1;nowY=-1;
			}
		}
		else{
			nowX=-1;nowY=-1;
		}
		//存在前一点和后一点
		if(preX!=-1 && nowX!=-1 && llk_map[nowX+1][nowY+1]!=0 && llk_map[preX+1][preY+1]!=0){
			boolean isReach;
			if(preX==nowX&&preY==nowY){
				isReach=false;
			}
			else{
				POINT p1,p2;
				p1.x=nowX+1;p1.y=nowY+1;
				p2.x=preX+1;p2.y=preY+1;
				isReach=CLLKGame::Find(llk_map,p2,p1);
				TRACE("c1,c2=%d %d %d %d",CLLKGame::c1.x,CLLKGame::c1.y,CLLKGame::c2.x,CLLKGame::c2.y);
			} 
			//可达并且选中的两个图标相同
			if(isReach && llk_map[preX+1][preY+1]==llk_map[nowX+1][nowY+1] && llk_map[preX+1][preY+1]!=0){
				PrintPath();
				llk_map[nowX+1][nowY+1]=0;
				llk_map[preX+1][preY+1]=0;
				SendBoxMsg(preX+1,preY+1,nowX+1,nowY+1);
				preX=-1;preY=-1;
			}
			else{
				preX=nowX;preY=nowY;
				m_dcBuf.SelectObject(&m_bmpBox);
				m_dcMem.BitBlt(LEFT_POS+preX*m_infoBox.bmWidth/3,TOP_POS+preY*m_infoBox.bmHeight/16,
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
					&m_dcBuf,m_infoBox.bmWidth/3,m_infoBox.bmHeight/16*(llk_map[nowX+1][nowY+1]-1),SRCCOPY);
			}
			nowX=-1;nowX=-1;
		}
		//前一点不存在，后一点存在
		else if(preX==-1 && nowX!=-1 && llk_map[nowX+1][nowY+1]!=0){
			preX=nowX;
			preY=nowY;
			m_dcBuf.SelectObject(&m_bmpBox);
			m_dcMem.BitBlt(LEFT_POS+preX*m_infoBox.bmWidth/3,TOP_POS+preY*m_infoBox.bmHeight/16,
				m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,m_infoBox.bmWidth/3,m_infoBox.bmHeight/16*(llk_map[nowX+1][nowY+1]-1),SRCCOPY);
		}
		Invalidate(FALSE);
	}
	//重排
	if(!isPlay && !isLooked){
		if (point.x>=619&&point.x<=619+m_infoBmpTool.bmWidth/6&&point.y>=190&&point.y<=190+m_infoBmpTool.bmHeight){
			if (cn>0){
				SendRedoMapMsg();
			}
		}
	}
	c1.x=c1.y=c2.x=c2.y=0;

	CDialog::OnLButtonDown(nFlags, point);
}
/************************************************************************/
/* 发送重排请求                                                         */
/************************************************************************/
void CLLKGame::SendRedoMapMsg(){
	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);	
	pApp->m_pSockThd->gameMsg=m_hWnd;
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	buf.Format("14 %d",m_uid);
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
}
/************************************************************************/
/* 发送消除方块消息                                                     */
/************************************************************************/
void CLLKGame::SendBoxMsg(int x1,int y1,int x2,int y2){
	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);	
	pApp->m_pSockThd->gameMsg=m_hWnd;
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	buf.Format("13 %d %d %d %d %d",m_uid,x1,y1,x2,y2);
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
}
/************************************************************************/
/* 响应计时器                                                           */
/************************************************************************/
void CLLKGame::OnTimer(UINT nIDEvent) {
	if(nIDEvent==1){
		int width = TIMEBAR_WIDTH/120;
		m_dcBuf.SelectObject(&m_bmpTmpBg);
		m_dcMem.BitBlt(TIMEBAR_LEFT+TIMEBAR_WIDTH-width*(seconds+1),TIMEBAR_TOP+1,width,TIMEBAR_HIGHT-2,&m_dcBuf,TIMEBAR_BG_W,TIMEBAR_BG_H,SRCCOPY);
		RECT rc;
		rc.left=TIMEBAR_LEFT;
		rc.top=TIMEBAR_TOP;
		rc.right=TIMEBAR_LEFT+TIMEBAR_WIDTH;
		rc.bottom=TIMEBAR_TOP+TIMEBAR_HIGHT;
		InvalidateRect(&rc,false);
		UpdateWindow();
		seconds++;
		if(seconds==166){
			KillTimer(1);
			SendGameOverMsg(true);
		}
		if(number==0){
			KillTimer(1);
			SendGameOverMsg(false);
		}
	}
	if (nIDEvent==2)//连击计时器
	{
		x--;
	}
	CDialog::OnTimer(nIDEvent);
}
/************************************************************************/
/* 发送游戏结束消息                                                     */
/************************************************************************/
void CLLKGame::SendGameOverMsg(boolean isFail){

	CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
	pApp->m_pSockThd->SetHwnd(m_hWnd);	
	pApp->m_pSockThd->gameMsg=m_hWnd;
	sockaddr_in remotAddr;
	remotAddr.sin_family = AF_INET;
	remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
	remotAddr.sin_port = htons(pApp->port);
	CString buf;
	if(isFail){
		buf.Format("12 fail %d",m_uid);
	}
	else {
		buf.Format("12 win %d",m_uid);
	}
	CSocket *pSock = pApp->m_pSockThd->GetSock();
	sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
}
/************************************************************************/
/* 消除棋子并画出闪电路径                                               */
/************************************************************************/
void CLLKGame::PrintPath(){
	//生成路径的绝对的坐标
	int path[4][2]={0},index=0;
	path[0][0]=preX+2;path[0][1]=preY+2;index++;
	if(c1.x!=0 || c1.y!=0){
		path[index][0]=c1.x+1;path[index][1]=c1.y+1;
		index++;
	}
	if(c2.x !=0 || c2.y!=0){
		path[index][0]=c2.x+1;path[index][1]=c2.y+1;
		index++;
	}
	path[index][0]=nowX+2;path[index][1]=nowY+2;index++;
	//======================
	for (int t=0;t<11;t++){
		//=====爆炸效果=====
		if(t<10){
			m_dcBuf.SelectObject(&m_bmpBoom);
			m_dcMem.BitBlt(LEFT_POS+nowX*(m_infoBox.bmWidth/3),TOP_POS+nowY*(m_infoBox.bmHeight/16),m_infoBox.bmWidth/3,
				m_infoBox.bmHeight/16,&m_dcBuf,t*(m_infoBoom.bmWidth/10),0,SRCCOPY);
			m_dcMem.BitBlt(LEFT_POS+preX*(m_infoBox.bmWidth/3),TOP_POS+preY*(m_infoBox.bmHeight/16),m_infoBox.bmWidth/3,
			m_infoBox.bmHeight/16, &m_dcBuf,t*(m_infoBoom.bmWidth/10),0,SRCCOPY);
		}
		//=====闪电效果=====
		//绘制路径
		int dir[2][2]={0};
		for(int i=1;i<index;i++){
			//===============纵向================
			if(path[i-1][0]==path[i][0]){
				dir[1][0]=0;
				if((path[i-1][1]-path[i][1])>0){
					dir[1][1]=-1;//向上(0,-1)
					//==========绘制拐点===============
					if(dir[0][0]!=0 || dir[0][1]!=0){
						if(dir[0][0]==-1 && dir[0][1]==0){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,2);//绘制左下角
						}
						else if(dir[0][0]==1 && dir[0][1]==0){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,3);//绘制右下角
						}
					}
				}
				else{
					dir[1][1]=1;//向下(0,1)
					if(dir[0][0]!=0 || dir[0][1]!=0){
						if(dir[0][0]==1 && dir[0][1]==0){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,4);//绘制右上角
						}
						else if(dir[0][0]==-1 && dir[0][1]==0){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,1);//绘制左上角
						}
					}
				}
				int tmpX=path[i-1][0],tmpY=path[i-1][1];
				while(true){
					tmpY=tmpY+dir[1][1];
					if(tmpY==path[i][1]){//到达拐点
						dir[0][0]=dir[1][0];
						dir[0][1]=dir[1][1];
						dir[1][0]=0;
						dir[1][1]=0;
						break;
					}
					else{
						PrintCorner(tmpX-2,tmpY-2,t,6);//绘制纵向路径
					}
				}
			}
			//===================横向======================
			else if(path[i-1][1]==path[i][1]){
				dir[1][1]=0;
				if((path[i-1][0]-path[i][0])>0){
					dir[1][0]=-1;//向左(-1,0)
					if(dir[0][0]!=0 || dir[0][1]!=0){
						if(dir[0][0]==0 && dir[0][1]==-1){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,4);//绘制右上角
						}
						else if(dir[0][0]==0 && dir[0][1]==1){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,3);//绘制右下角
						}
					}
				}
				else{
					dir[1][0]=1;//向右(1,0)
					if(dir[0][0]!=0 || dir[0][1]!=0){//绘制拐点
						if(dir[0][0]==0 && dir[0][1]==-1){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,1);//绘制左上角
						}
						else if(dir[0][0]==0 && dir[0][1]==1){
							PrintCorner(path[i-1][0]-2,path[i-1][1]-2,t,2);//绘制左下角
						}
					}
				}
				int tmpX=path[i-1][0];
				int tmpY=path[i-1][1];
				while(true){
					tmpX=tmpX+dir[1][0];
					if(tmpX==path[i][0] && tmpY==path[i][1]){//到达拐点
						dir[0][0]=dir[1][0];
						dir[0][1]=dir[1][1];
						dir[1][0]=0;
						dir[1][1]=0;
						break;
					}
					else{//TODO绘制横向路径
						PrintCorner(tmpX-2,tmpY-2,t,5);
					}
				}
			}
		}
		Invalidate(FALSE);
		UpdateWindow();
		Sleep(20);
	}
	PlaySound(".\\res\\elec.wav", NULL, SND_FILENAME | SND_ASYNC);
	
	//消去的两个图标，绘制背景色
	m_dcBuf.SelectObject(&m_bmpTmpBg);
	m_dcMem.BitBlt(LEFT_POS+nowX*(m_infoBox.bmWidth/3),TOP_POS+nowY*(m_infoBox.bmHeight/16),m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
		&m_dcBuf,LEFT_POS+nowX*(m_infoBox.bmWidth/3),TOP_POS+nowY*(m_infoBox.bmHeight/16),SRCCOPY);
	m_dcMem.BitBlt(LEFT_POS+preX*(m_infoBox.bmWidth/3),TOP_POS+preY*(m_infoBox.bmHeight/16),m_infoBox.bmWidth/3,m_infoBox.bmHeight/16, 
		&m_dcBuf,LEFT_POS+preX*(m_infoBox.bmWidth/3),TOP_POS+preY*(m_infoBox.bmHeight/16),SRCCOPY);

	Invalidate(false);

	//还原拐点
	c1.x=c1.y=c2.x=c2.y=0;
	//计算剩余方块数
	number=number-2;
	SetDlgItemInt(IDC_NUMBER,number);

	if (x>=0)
	{
		link_times++;
		if (link_times>max_count)
		{
			max_count=link_times;	
		}
	}
	else if(x<0)
	{
		link_times=1;
		x=30;
	}
	Batter();

	m_dcBuf.SelectObject(&m_bmpTmpBg);
	m_dcMem.BitBlt(TIMEBAR_LEFT,TIMEBAR_TOP+1,TIMEBAR_WIDTH,TIMEBAR_HIGHT-2,&m_dcBuf,TIMEBAR_LEFT,TIMEBAR_TOP,SRCCOPY);
	RECT rc;
	rc.left=TIMEBAR_LEFT;
	rc.top=TIMEBAR_TOP;
	rc.right=TIMEBAR_LEFT+TIMEBAR_WIDTH;
	rc.bottom=TIMEBAR_TOP+TIMEBAR_HIGHT;
	InvalidateRect(&rc,false);
	
	UpdateWindow();
	seconds=0;
}
/************************************************************************/
/* 绘制闪电                                                             */
/************************************************************************/
void CLLKGame::PrintCorner(int x,int y,int t,int type){
		int a,b,c;//标记替换闪电
		if(t%2==0){
			a=0;
			b=m_infoLight.bmWidth/6*2;
			c=m_infoLight.bmWidth/6;
		}
		else{
			a=m_infoLight.bmWidth/6*3;
			b=m_infoLight.bmWidth/6*5;
			c=m_infoLight.bmWidth/6*4;
		}

		if(t!=10){
			if(type==1){//TODO 绘制左上角
				m_dcBuf.SelectObject(&m_bmpLight);
				m_dcMem.BitBlt(LEFT_POS+x*(m_infoBox.bmWidth/3),TOP_POS+y*(m_infoBox.bmHeight/16),
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,&m_dcBuf,a,0,SRCCOPY);
			}
			else if(type==2){//TODO 绘制左下角
				m_dcBuf.SelectObject(&m_bmpLight);
				m_dcMem.BitBlt(LEFT_POS+(x)*(m_infoBox.bmWidth/3),TOP_POS+(y)*(m_infoBox.bmHeight/16),
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,a,m_infoLight.bmHeight/3*2,SRCCOPY);
			}
			else if(type==3){//TODO 绘制右下角
				m_dcBuf.SelectObject(&m_bmpLight);
				m_dcMem.BitBlt(LEFT_POS+(x)*(m_infoBox.bmWidth/3),TOP_POS+(y)*(m_infoBox.bmHeight/16),
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,b,m_infoLight.bmHeight/3*2,SRCCOPY);
			}
			else if(type==4){//TODO 绘制右上角
				m_dcBuf.SelectObject(&m_bmpLight);
				m_dcMem.BitBlt(LEFT_POS+(x)*(m_infoBox.bmWidth/3),TOP_POS+(y)*(m_infoBox.bmHeight/16),
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,b,0,SRCCOPY);
			}
			else if(type==5){//TODO绘制横向路径
				m_dcBuf.SelectObject(&m_bmpLight);
				m_dcMem.BitBlt(LEFT_POS+(x)*(m_infoBox.bmWidth/3),TOP_POS+(y)*(m_infoBox.bmHeight/16),
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,c,0,SRCCOPY);
			}
			else if(type==6){//TODO绘制纵向路径
				m_dcBuf.SelectObject(&m_bmpLight);
				m_dcMem.BitBlt(LEFT_POS+(x)*(m_infoBox.bmWidth/3),TOP_POS+(y)*(m_infoBox.bmHeight/16),
					m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,a,m_infoLight.bmHeight/3,SRCCOPY);
			}
		}
		else{
			m_dcBuf.SelectObject(&m_bmpTmpBg);
			m_dcMem.BitBlt(LEFT_POS+x*(m_infoBox.bmWidth/3),TOP_POS+y*(m_infoBox.bmHeight/16),
				m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,LEFT_POS+x*(m_infoBox.bmWidth/3),TOP_POS+y*(m_infoBox.bmHeight/16),SRCCOPY);
			}

}
/************************************************************************/
/* 查找路径                                                             */
/************************************************************************/
BOOL CLLKGame::Find(int map[][MAXY], 
					 POINT p1, POINT p2){
	CString str;
	if(FindLine(map, p1, p2)){
		return TRUE;
	}
	if(FindCorner(map, p1, p2, &c1)){
		return TRUE;
	}
	if(FindTwoCorner(map, p1, p2, &c1, &c2)){
		return TRUE;
	}
	return FALSE;
}

BOOL CLLKGame::FindCorner(int map[][MAXY], POINT p1, POINT p2, POINT *cross1){
	int maxx, maxy, minx, miny;
	POINT tempPoint = {0};
	
	//测试矩形格子
	maxx = (p1.x>p2.x)?p1.x:p2.x;
	maxy = (p1.y>p2.y)?p1.y:p2.y;
	minx = (p1.x<p2.x)?p1.x:p2.x;
	miny = (p1.y<p2.y)?p1.y:p2.y;
	
	if(map[minx][maxy] == 0)
	{
		tempPoint.x = minx;
		tempPoint.y = maxy;
		if((FindLine(map, p1, tempPoint)) 
			&& (FindLine(map, tempPoint, p2)))
		{
			cross1->x = tempPoint.x;
			cross1->y = tempPoint.y;
			return TRUE;
		}
	}
	
	if(map[maxx][miny] == 0)
	{
		tempPoint.x = maxx;
		tempPoint.y = miny;
		if((FindLine(map, p1, tempPoint)) 
			&& (FindLine(map, tempPoint, p2)))
		{
			cross1->x = tempPoint.x;
			cross1->y = tempPoint.y;
			return TRUE;
		}
	}
	
	if(map[minx][miny] == 0)
	{
		tempPoint.x = minx;
		tempPoint.y = miny;
		if((FindLine(map, p1, tempPoint)) 
			&& (FindLine(map, tempPoint, p2)))
		{
			cross1->x = tempPoint.x;
			cross1->y = tempPoint.y;
			return TRUE;
		}
	}
	
	if(map[maxx][maxy] == 0)
	{
		tempPoint.x = maxx;
		tempPoint.y = maxy;
		if((FindLine(map, p1, tempPoint)) 
			&& (FindLine(map, tempPoint, p2)))
		{
			cross1->x = tempPoint.x;
			cross1->y = tempPoint.y;
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CLLKGame::FindTwoCorner(int map[][MAXY], POINT p1, POINT p2, POINT *cross1, POINT *cross2){
	int i;
	POINT tempPoint1 = {0};
	POINT tempPoint2 = {0};
	//横向
	for(i=0; i<MAXY; i++)
	{
		if(i == p1.y)
			continue;
		tempPoint1.x = p1.x;
		tempPoint1.y = i;
		if((map[tempPoint1.x][tempPoint1.y]==0) 
			|| (map[tempPoint1.x][tempPoint1.y]==-1))
		{
			if(FindLine(map, tempPoint1, p1))
			{
				tempPoint2.x = p2.x;
				tempPoint2.y = i;
				if((map[tempPoint2.x][tempPoint2.y]==0) 
					|| (map[tempPoint2.x][tempPoint2.y]==-1))
				{
					if(FindLine(map, tempPoint2, p2))
					{	//判断两个转折点是否连通
						if(FindLine(map, tempPoint1, tempPoint2))
						{
							cross1->x = p1.x;
							cross1->y = i;
							cross2->x = p2.x;
							cross2->y = i;
							return TRUE;
						}	
					}
				}
			}
		}
	}
	//纵向
	for(i=0; i<MAXX; i++)
	{
		if(i == p1.x)
			continue;
		tempPoint1.x = i;
		tempPoint1.y = p1.y;
		if((map[tempPoint1.x][tempPoint1.y]==0) 
			|| (map[tempPoint1.x][tempPoint1.y]==-1))
		{
			if(FindLine(map, tempPoint1, p1))
			{
				tempPoint2.x = i;
				tempPoint2.y = p2.y;
				if((map[tempPoint2.x][tempPoint2.y]==0) 
					|| (map[tempPoint2.x][tempPoint2.y]==-1))
				{
					if(FindLine(map, tempPoint2, p2))
					{//判断两个转折点是否连通
						if(FindLine(map, tempPoint1, tempPoint2))
						{
							cross1->x = i;
							cross1->y = p1.y;
							cross2->x = i;
							cross2->y = p2.y;
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CLLKGame::FindLine(int map[][MAXY], POINT p1, POINT p2){
	int max, min;
	int i;
	
	if(p1.x == p2.x){
		max = (p1.y>p2.y)?p1.y:p2.y;
		min = (p1.y<p2.y)?p1.y:p2.y;
		if(max == min+1){
			return TRUE;//相邻的两个格子
		}
		for(i=min+1; i<max; i++){
			if((map[p1.x][i]!=0) && (map[p1.x][i]!=-1)){
				return FALSE;
			}
		}
		return TRUE;
	}
	
	if(p1.y == p2.y){
		max = (p1.x>p2.x)?p1.x:p2.x;
		min = (p1.x<p2.x)?p1.x:p2.x;
		if(max == min+1){
			return TRUE;//相邻的两个格子
		}
		for(i=min+1; i<max; i++){
			if((map[i][p1.y]!=0) && (map[i][p1.y]!=-1)){
				return FALSE;
			}
		}
		return TRUE;
	}
	
	return FALSE;
}

 HBRUSH CLLKGame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
 {
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID()==IDC_NUMBER)
	{
	//	pDC->SetTextColor(RGB(255,0,0));
	//	pDC->SetBkColor(RGB(255,255,255));//设置文本背景色
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		hbr = (HBRUSH)m_brush;
	} 
 	return hbr;
 }
/************************************************************************/
/* 画重排工具栏                                                         */
/************************************************************************/
 void CLLKGame::Tool(int cn)
 {
	 //int x,y;
	 int x=619,y=190;
	 m_dcBuf.SelectObject(&m_bmpTool);
	 if (cn==1)
	 {
		 m_dcMem.BitBlt(x,y,m_infoBmpTool.bmWidth/6,m_infoBmpTool.bmHeight,&m_dcBuf,m_infoBmpTool.bmWidth/6,0,SRCCOPY);
	 }
	 else if (cn==2)
	 {
		 m_dcMem.BitBlt(x,y,m_infoBmpTool.bmWidth/6,m_infoBmpTool.bmHeight,&m_dcBuf,m_infoBmpTool.bmWidth/3,0,SRCCOPY);
	 }
	 else if (cn==3)
	 {
		 m_dcMem.BitBlt(x,y,m_infoBmpTool.bmWidth/6,m_infoBmpTool.bmHeight,&m_dcBuf,m_infoBmpTool.bmWidth/2,0,SRCCOPY);
	 }
	 else if (cn==4)
	 {
		 m_dcMem.BitBlt(x,y,m_infoBmpTool.bmWidth/6,m_infoBmpTool.bmHeight,&m_dcBuf,m_infoBmpTool.bmWidth/6*4,0,SRCCOPY);
	 }
	 else if (cn==5)
	 {
		 m_dcMem.BitBlt(x,y,m_infoBmpTool.bmWidth/6,m_infoBmpTool.bmHeight,&m_dcBuf,m_infoBmpTool.bmWidth/6*5,0,SRCCOPY);
	 }	
	 else if (cn==0)
	 {
		 m_dcMem.BitBlt(x,y,m_infoBmpTool.bmWidth/6,m_infoBmpTool.bmHeight,&m_dcBuf,0,0,SRCCOPY);
	 }
	 
	 Invalidate(false);
	 UpdateWindow();
 }
 /************************************************************************/
 /* 得到随机矩阵信息                                                     */
 /************************************************************************/
 LRESULT CLLKGame::OnGetRecMap(WPARAM w, LPARAM l){
	 MapInfo *mapInfo = (MapInfo*)w;

	 for (int i=0;i<14;i++){
		 for(int j=0;j<10;j++){
			llk_map[i][j]=mapInfo->recMap[i][j];
		 }
	 }
	//复制矩阵，每个用户初始矩阵都是相同的
	 int index=1;
	 for(int k=0;k<6;k++){
		 userMap[k].val=0;
		 if(userMap[k].type!=0){
			 for (int i=0;i<14;i++){
				 for(int j=0;j<10;j++){
					 userMap[k].recMap[i][j]=mapInfo->recMap[i][j];
				 }
			}
			 if ((k+1)!=chaNum){
				 MiniMap();
			 }
		 }
		 if(index!=chaNum){
			 index++;
		 }
	 }

	 m_dcBuf.SelectObject(&m_bmpBox);
	 for(i=1;i<=12;i++){
		 for( int j=1;j<=8;j++){
			 m_dcMem.BitBlt(LEFT_POS+(i-1)*m_infoBox.bmWidth/3,TOP_POS+(j-1)*m_infoBox.bmHeight/16,m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				 &m_dcBuf,0,m_infoBox.bmHeight/16*(llk_map[i][j]-1),SRCCOPY);
		 }
	 }
	 return 0;
}
/************************************************************************/
/* 响应游戏结束消息                                                     */
/************************************************************************/
LRESULT CLLKGame::OnGameOver(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type,uid;
	char action[1024];
	sscanf(data,"%d %s %d",&type,action,&uid);

	if (strcmp(action,"win")==0){
		if (uid==m_uid){//本用户成功
			isWin=true;
			gameOn=false;
			for(int i=0;i<6;i++){
				if(userMap[i].type!=0 && (i+1)!=chaNum){
					userMap[i].val=-1;
				}
			}
			MiniMap();
			if(!isPlay){
				GameWin();
			}
		}
		else{//其他用户成功
			isWin=false;
			gameOn=false;
			for(int i=0;i<6;i++){
				if(userMap[i].type!=0 && userMap[i].type!=uid){
					userMap[i].val=-1;
				}
			}
			MiniMap();
			if(!isPlay){
				GameFail();
			}
		}
	}
	else if(strcmp(action,"fail")==0){
		if(uid==m_uid){//本用户失败
			isWin=false;
			userMap[chaNum-1].val=-1;
			MiniMap();
			if(!isPlay){
				GameFail();
			}
		}
		else{//其他用户失败
			for(int i=0;i<6;i++){
				if(userMap[i].type==uid){
					userMap[i].val=-1;
				}
			}
			MiniMap();
		}
	}
	else if (strcmp(action,"exit")==0){//有用户退出消息
		MessageBox("有用户退出");
	}
	delete[] data;
	return 0;
}
/************************************************************************/
/* 胜利                                                                 */
/************************************************************************/
void CLLKGame::GameWin(){
	isPlay=true;
	KillTimer(1);
	PlaySound(".\\res\\zhangsheng.wav", NULL, SND_FILENAME | SND_ASYNC);
	//MessageBox("恭喜，你赢了",NULL,MB_OK);
	if (isLooked){
		CDialog::OnClose();
	}
}
/************************************************************************/
/* 失败                                                                 */
/************************************************************************/
void CLLKGame::GameFail(){
	isPlay=true;
	KillTimer(1);
	//显示方块
	for( int i=1;i<=12;i++){
		for( int j=1;j<=8;j++){
			m_dcBuf.SelectObject(&m_bmpBox);
			m_dcMem.BitBlt(LEFT_POS+(i-1)*m_infoBox.bmWidth/3,TOP_POS+(j-1)*m_infoBox.bmHeight/16,
				m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
				&m_dcBuf,m_infoBox.bmWidth/3*2,m_infoBox.bmHeight/16*(llk_map[i][j]-1),SRCCOPY);
		}
	}
	Invalidate(false);
	UpdateWindow();
	PlaySound(".\\res\\end.wav", NULL, SND_FILENAME | SND_ASYNC);
	//MessageBox("你输了");
	if (isLooked){
		CDialog::OnClose();
	}
}

/************************************************************************/
/* 方块消除消息                                                         */
/************************************************************************/
LRESULT CLLKGame::OnBoxClear(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type,tmpChaNum,x1,y1,x2,y2;
	sscanf(data,"%d %d %d %d %d %d",&type,&tmpChaNum,&x1,&y1,&x2,&y2);
	userMap[tmpChaNum-1].recMap[x1][y1]=0;
	userMap[tmpChaNum-1].recMap[x2][y2]=0;
	if(tmpChaNum!=chaNum){
		MiniMap();
	}
	if(isLooked && tmpChaNum==chaNum){//旁观者画棋盘
		preX=x1-1;
		preY=y1-1;
		nowX=x2-1;
		nowY=y2-1;
		POINT p1,p2;
		p1.x=nowX+1;p1.y=nowY+1;
		p2.x=preX+1;p2.y=preY+1;
		boolean isReach=CLLKGame::Find(llk_map,p2,p1);
		TRACE("c1,c2=%d %d %d %d",CLLKGame::c1.x,CLLKGame::c1.y,CLLKGame::c2.x,CLLKGame::c2.y);

		PrintPath();
		llk_map[nowX+1][nowY+1]=0;
		llk_map[preX+1][preY+1]=0;
		c1.x=c1.y=c2.x=c2.y=0;
		Invalidate(false);
	}
	return 0;
}
/************************************************************************/
/*重排消息                                                              */
/************************************************************************/
LRESULT CLLKGame::OnRedoMap(WPARAM w, LPARAM l){
	MapInfo *mapInfo = (MapInfo*)w;
	int val=mapInfo->val;//chaNum
	for (int i=0;i<14;i++){
		for(int j=0;j<10;j++){
			userMap[val-1].recMap[i][j]=mapInfo->recMap[i][j];
		}
	}
	if (chaNum==val){
		for (int i=0;i<14;i++){
			for(int j=0;j<10;j++){
				llk_map[i][j]=mapInfo->recMap[i][j];
			}
		}
		cn--;
		Tool(cn);

		m_dcBuf.SelectObject(&m_bmpBox);
		for(i=1;i<=12;i++){
		 	for(int j=1;j<=8;j++){
		 		m_dcMem.BitBlt(LEFT_POS+(i-1)*m_infoBox.bmWidth/3,TOP_POS+(j-1)*m_infoBox.bmHeight/16,m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
		 			&m_dcBuf,0,m_infoBox.bmHeight/16*(llk_map[i][j]-1),SRCCOPY);	
		 	}
		}
	}
	else{
		MiniMap();
	}
	Invalidate(false);
	UpdateWindow();
	return 0;
}
/************************************************************************/
/*绘制缩略图                                                            */
/************************************************************************/
void CLLKGame::MiniMap(){

	int x=14,y=36;
	int z=119;
	int MiniWidth=108;
	int MiniHigh=96;

	int XOrigin=77;
	int YOrigin=184;

	int Mapwidth=462;
	int MapHigh=380;

	for (int n=1;n<=6;n++){
		if (n!=chaNum && userMap[n-1].type!=0){

			CDC     m_dcMap;
			CDC *pDC = GetDC();
			CBitmap m_bmpMap;
			BITMAP  m_infoBmpMap;

			m_bmpMap.LoadBitmap(IDB_GAME_BG);
			m_bmpMap.GetBitmap(&m_infoBmpMap);

			m_dcMap.CreateCompatibleDC(pDC);

			m_dcMap.SelectObject(&m_bmpMap);
			m_dcBuf.SelectObject(&m_bmpBox);

			if (userMap[n-1].val==-1){
				for( int i=1;i<=12;i++){
					for( int j=1;j<=8;j++){
						m_dcMap.BitBlt(LEFT_POS+(i-1)*m_infoBox.bmWidth/3,TOP_POS+(j-1)*m_infoBox.bmHeight/16,
							m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
							&m_dcBuf,m_infoBox.bmWidth/3*2,m_infoBox.bmHeight/16*(userMap[n-1].recMap[i][j]-1),SRCCOPY);
					}
				}
			}
			else{
				for(int i=1;i<=12;i++){
					for( int j=1;j<=8;j++){
						m_dcMap.BitBlt(LEFT_POS+(i-1)*m_infoBox.bmWidth/3,TOP_POS+(j-1)*m_infoBox.bmHeight/16,
							m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
							&m_dcBuf,0,m_infoBox.bmHeight/16*(userMap[n-1].recMap[i][j]-1),SRCCOPY);
					}	
				}
			}

			m_dcMem.SetStretchBltMode(HALFTONE);
			m_dcMem.StretchBlt(x,y,MiniWidth,MiniHigh,&m_dcMap,XOrigin,YOrigin,Mapwidth,MapHigh,SRCCOPY);
			m_dcBuf.SelectObject(&m_bmpTmpBg);
			m_dcMem.BitBlt(x,y+MiniHigh,MiniWidth,30,&m_dcBuf,x,y+MiniHigh,SRCCOPY);

			CFont font;
			font.CreatePointFont(120,"宋体",&m_dcMem);
			m_dcMem.SelectObject(&font);
			m_dcMem.SetTextColor(RGB(255,0,255));

			char c[10];
			itoa(userMap[n-1].type,c,10);
			m_dcMem.SetBkMode(TRANSPARENT);
			m_dcMem.TextOut(x+MiniWidth/2-15,y+MiniHigh+10,userNick[n-1]);
		}
		if(n!=chaNum){
			x=x+z;
		}
	}
	CRect rec;
	rec.left=14;
	rec.right=x+z;
	rec.bottom=y+MiniHigh+30;
	rec.top=y;
	InvalidateRect(rec,false);
	UpdateWindow();
}

void CLLKGame::OnClose(){
	if(isLooked){
		CLLKCLIApp* pApp = (CLLKCLIApp*)AfxGetApp();
		pApp->m_pSockThd->SetHwnd(m_hWnd);	
		pApp->m_pSockThd->gameMsg=m_hWnd;
		sockaddr_in remotAddr;
		remotAddr.sin_family = AF_INET;
		remotAddr.sin_addr.S_un.S_addr = inet_addr(pApp->ip);
		remotAddr.sin_port = htons(pApp->port);
		CString buf;
		buf.Format("20 lookout %d %d",lookerUid,m_uid);
		CSocket *pSock = pApp->m_pSockThd->GetSock();
		sendto(pSock->m_hSocket,buf.GetBuffer(buf.GetLength()),buf.GetLength(),0,(SOCKADDR*)&remotAddr,sizeof(SOCKADDR));
	}
	else{
		if(gameOn){
			MessageBox("游戏进行时，无法退出");
		}
		else{
			CDialog::OnClose();
		}
	}
}
/************************************************************************/
/* 得到游戏排行消息                                                     */
/************************************************************************/
LRESULT CLLKGame::GetRankList(WPARAM w, LPARAM l){
	RankListMsg *rankListMsg= (RankListMsg*)w;

	Scorelist showlist;//显示成绩列表

	for (int i=0;i<6;i++)//将变量传进列表窗体
	{
		strcpy(showlist.username[i],userNick[i]);
		showlist.sorce[i]=rankListMsg->rankNum[i];
		showlist.uid[i]=rankListMsg->uid[i];
		showlist.userMap[i].type=userMap[i].type;
		showlist.total[i]=rankListMsg->score[i];
	}

	
	showlist.DoModal();
	

	return 0;
}
/************************************************************************/
/* 旁观者获得随机矩阵                                                   */
/************************************************************************/
LRESULT CLLKGame::GetLookerRecMap(WPARAM w, LPARAM l){
	MapInfo *mapInfo = (MapInfo*)w;
	if(m_uid==mapInfo->val){//本地的map
		for (int i=0;i<14;i++){
			for(int j=0;j<10;j++){
				llk_map[i][j]=mapInfo->recMap[i][j];
			}
		}
		m_dcBuf.SelectObject(&m_bmpBox);
		for(i=1;i<=12;i++){
			for( int j=1;j<=8;j++){
				m_dcMem.BitBlt(LEFT_POS+(i-1)*m_infoBox.bmWidth/3,TOP_POS+(j-1)*m_infoBox.bmHeight/16,m_infoBox.bmWidth/3,m_infoBox.bmHeight/16,
					&m_dcBuf,0,m_infoBox.bmHeight/16*(llk_map[i][j]-1),SRCCOPY);
			}
		}
	}
	for (int k=0;k<6;k++){
		if(userMap[k].type==mapInfo->val){
			for (int i=0;i<14;i++){
				for(int j=0;j<10;j++){
					userMap[k].recMap[i][j]=mapInfo->recMap[i][j];
				}
			}
			break;
		}
	}
	MiniMap();
	return 0;
}
/************************************************************************/
/* 旁观者退出消息                                                       */
/************************************************************************/
LRESULT CLLKGame::OnLookerExit(WPARAM w, LPARAM l){
	char *data = (char*)w;
	int type;
	char action[10];
	sscanf(data,"%d %s",&type,action);
	if(strcmp(action,"success")==0){
		EndDialog(IDCANCEL);
	}
	return 0;
}
/************************************************************************/
/* 游戏连击                                                             */
/************************************************************************/
void CLLKGame::Batter(){

	for (int i=4;i>0;i--)
	{
		CRect rec;
		rec.left=500;
		rec.right=600;
		rec.bottom=400;
		rec.top=300;
		m_dcBuf.SelectObject(&m_bmpTmpBg);
		m_dcMem.BitBlt(500,300,100,200,&m_dcBuf,500,300,SRCCOPY);
		InvalidateRect(rec,false);
		CString tmp;
		tmp.Format("连击数  %d/%d",link_times,max_count);
		
		CFont font;
		//CBitmap *oldMem=m_dcMem.SelectObject(&m_bmpBg);
		font.CreatePointFont(120,"Comic Sans MS",&m_dcMem);
		m_dcMem.SelectObject(&font);
		
		m_dcMem.SetTextColor(RGB(255, 0, 255));
		m_dcMem.SetBkMode(TRANSPARENT);
		m_dcMem.TextOut(500,280+20*i,tmp);
		
		UpdateWindow();
		//m_dcMem.SelectObject(oldMem);

		Sleep(100);		
	}
		//还原字体，使用完还原是好习惯= =
		CFont font1;
		font1.CreatePointFont(110,"system",&m_dcMem);
		m_dcMem.SelectObject(&font1);
		m_dcMem.SetTextColor(RGB(0,0,0));
}
