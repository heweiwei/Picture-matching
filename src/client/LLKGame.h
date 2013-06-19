#include <windows.h>
#if !defined(AFX_LLKGAME_H__45A6D0CC_ABFB_4727_A39A_16EDDE8AFBB2__INCLUDED_)
#define AFX_LLKGAME_H__45A6D0CC_ABFB_4727_A39A_16EDDE8AFBB2__INCLUDED_

#define MAXX 14		//行数
#define MAXY 10		//列数

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LLKGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLLKGame dialog

class CLLKGame : public CDialog
{
// Construction
public:
	CLLKGame(CWnd* pParent = NULL);   // standard constructor

	static BOOL		FindLine(int map[][MAXY], POINT p1, POINT p2);
	BOOL			Find(int map[MAXX][MAXY], POINT p1, POINT p2);
	static BOOL		FindTwoCorner(int map[][MAXY], POINT p1, POINT p2, POINT  *cross1, POINT *cross2);
	static BOOL		FindCorner(int map[][MAXY], POINT p1, POINT p2, POINT *cross1);
	void			PrintCorner(int x,int y,int t,int type);
	void            MiniMap();
	void            Batter();
	void			PrintPath();
	void			Tool(int cn);
	LRESULT			OnGetRecMap(WPARAM w, LPARAM l);
	void			SendGameOverMsg(boolean isFail);
	LRESULT			OnGameOver(WPARAM w, LPARAM l);
	void			SendBoxMsg(int x1,int y1,int x2,int y2);
	LRESULT			OnBoxClear(WPARAM w, LPARAM l);
	LRESULT			OnRedoMap(WPARAM w, LPARAM l);
	void			SendRedoMapMsg();
	LRESULT			GetRankList(WPARAM w, LPARAM l);
	LRESULT			GetLookerRecMap(WPARAM w, LPARAM l);
	LRESULT			OnLookerExit(WPARAM w, LPARAM l);

	void			GameWin();
	void			GameFail();
	int				m_uid;
	int				number;//方块剩余个数
	int				cn;
	int				tabNum,chaNum;
	MapInfo			userMap[6];
	boolean			isLooked;//是否旁观
	int				lookerUid;
	POINT			c1,c2;//拐点
	char			userNick[6][100];
	int             max_count;//连击最大记录
	int             link_times;//当前连击数
	int             x;

// Dialog Data
	//{{AFX_DATA(CLLKGame)
	enum { IDD = IDD_LLK_GAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLLKGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CBitmap m_bmpBg;
	CBitmap m_bmpTmpBg;
	CBitmap m_bmpBoom;
	CBitmap m_bmpBox;
	CBitmap m_bmpLight;
	CBrush	m_brush;
	CBitmap m_bmpTool;

	CDC		m_dcMem;
	CDC		m_dcBuf; 
	

	BITMAP	m_infoBmpBg;
	BITMAP  m_infoBox;
	BITMAP  m_infoBoom;
	BITMAP  m_infoLight;
	BITMAP  m_infoBmpTool;
	

	int preX,preY,nowX,nowY;//前一个及后一个选中点
	int llk_map[14][10];
	

	int		seconds;//时间
	boolean gameOn;
	boolean isWin;
	// Generated message map functions
	//{{AFX_MSG(CLLKGame)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LLKGAME_H__45A6D0CC_ABFB_4727_A39A_16EDDE8AFBB2__INCLUDED_)
