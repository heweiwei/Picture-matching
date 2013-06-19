// SockThd.cpp : implementation file
//

#include "stdafx.h"
//#include "SockDemo.h"
#include "SockThd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSockThd

IMPLEMENT_DYNCREATE(CSockThd, CWinThread)

CSockThd::CSockThd(){
}

CSockThd::~CSockThd(){
}

BOOL CSockThd::InitInstance()
{
	m_sock.Create(0,SOCK_DGRAM);

	return TRUE;
}

int CSockThd::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSockThd, CWinThread)
	//{{AFX_MSG_MAP(CSockThd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSockThd message handlers

int CSockThd::Run() {
	char data[1024] = {0};
	sockaddr_in remoteAddr; //对方的地址
	int len = sizeof(sockaddr_in);
	int recvLen = 0;

	while(1){
		recvLen = m_sock.ReceiveFrom(data,sizeof(data),(SOCKADDR*)&remoteAddr,&len);
		TRACE("socket data=%s\n",data);
		if(recvLen > 0){
			int type=0;
			if(recvLen==sizeof(MapInfo)){//随机矩阵信息
				MapInfo *mapInfo = new MapInfo;
				memcpy(mapInfo,data,sizeof(MapInfo));
				if(mapInfo->type==11){
					PostMessage(gameMsg,NET_REC_MAP,(WPARAM)mapInfo,0);
				}
				else if(mapInfo->type==14){
					PostMessage(gameMsg,NET_REDO_MAP,(WPARAM)mapInfo,0);
				}
				else if(mapInfo->type==19){//旁观的随机矩阵
					PostMessage(gameMsg,NET_LOOKER_REC_MAP,(WPARAM)mapInfo,0);
				}
			}
			else if(recvLen==sizeof(TableState)){
				TableState *tableState = new TableState;
				memcpy(tableState,data,sizeof(TableState));
				if(tableState->type==16){
					PostMessage(homeMsg,NET_TABLE_STATE,(WPARAM)tableState,0);
				}
			}
			else if(recvLen==sizeof(RankListMsg)){
				RankListMsg *rankListMsg = new RankListMsg;
				memcpy(rankListMsg,data,sizeof(RankListMsg));
				if(rankListMsg->type==12){
					PostMessage(gameMsg,NET_RANK_LIST,(WPARAM)rankListMsg,0);
				}
			}
			else{
				sscanf(data,"%d",&type);
			}
			
			if(type==1){//登陆消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(m_hWndMsg,NET_LOGIN,(WPARAM)buf,0);
			}
			else if(type==2){//注册消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(m_hWndMsg,NET_REG,(WPARAM)buf,0);
			}
			else if(type==3){//修改密码消息
				char *msg = new char[recvLen];
				sscanf(data,"%d %s",&type,msg);
				PostMessage(m_hWndMsg,NET_CHANGEPWD,(WPARAM)msg,0);
			}
			else if (type==4){//进入房间消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(homeMsg,NET_INTABEL,(WPARAM)buf,0);
			}
			else if (type==5){//退出房间消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(readyMsg,NET_OUTTABLE,(WPARAM)buf,0);
			}
			else if (type==6){//游戏准备消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(readyMsg,NET_READY,(WPARAM)buf,0);
			}
			else if(type==7){//房间用户消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(readyMsg,NET_USERINFO_READY,(WPARAM)buf,0);
			}
			else if(type==8){//大厅所有用户消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(homeMsg,NET_USERINFO_ALL,(WPARAM)buf,0);
			}
			else if(type==9){//游戏开始消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(readyMsg,NET_GAME_START,(WPARAM)buf,0);
			}	
			else if (type==10){//退出游戏消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(homeMsg,NET_GAME_EXIT,(WPARAM)buf,0);
			}
			else if(type==12){//游戏结束消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(gameMsg,NET_GAME_OVER,(WPARAM)buf,0);
			}
			else if(type==13){//消除方块消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(gameMsg,NET_BOX_CLEAR,(WPARAM)buf,0);
			}
			else if(type==15){//home界面游戏开始消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(homeMsg,NET_CHANGE_TABLE,(WPARAM)buf,0);
			}
			else if(type==16){
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(homeMsg,NET_TABLE_STATE,(WPARAM)buf,0);
			}
			else if(type==18){
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(homeMsg,NET_ONLOOKER,(WPARAM)buf,0);
			}
			else if(type==20){//旁观者退出消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(gameMsg,NET_LOOKER_EXIT,(WPARAM)buf,0);
			}
			else if(type==21){//聊天消息
				char *buf = new char[recvLen];
				memcpy(buf,data,recvLen);
				PostMessage(readyMsg,NET_TALKMSG,(WPARAM)buf,0);
			}
		}
		else{
			break;
		}
	}
	return 0;
}
