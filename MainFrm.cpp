
// MainFrm.cpp : CMainFrame 類別的實作
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CSkinFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CSkinFrameWnd)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_PAINT()
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, TBToolTips)
END_MESSAGE_MAP()

//狀態列指示器
static UINT indicators[] = {
	STA_WORKLED,
	ID_SEPARATOR,
	STA_ALLTIMER,
	STA_WORKCOUNT,
	STA_PROCESS,
	STA_SYSTIMER,
};

// CMainFrame 建構/解構

CMainFrame::CMainFrame()
{
	// TODO: 在此加入成員初始化程式碼
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的
	//cs.style = WS_OVERLAPPEDWINDOW;
	//cs.style = WS_CAPTION;
	cs.style &= ~WS_SYSMENU;//關閉系統菜單
	cs.style &= ~WS_SIZEBOX;//關閉可自由改變大小
	cs.style &= ~WS_MAXIMIZEBOX;//關閉最大化標示
	return TRUE;
}

// CMainFrame 診斷

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 訊息處理常式

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSkinFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此加入特別建立的程式碼
	if (NULL != GetMenu())
	{
		DelAllMenu(GetMenu()->GetSafeHmenu());
	}
	CreateToolBar();//創建工具欄
	CreateStatusBar();//窗見狀態列
	SetTimer(1, 1000, NULL);//時間刷新
	return 0;
}
void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此加入您的訊息處理常式程式碼
					   // 不要呼叫圖片訊息的 CFrameWnd::OnPaint()
	CRect rect;
	m_StatusBar.GetItemRect(4, &rect);//獲得欄位矩形大小
	rect.bottom = rect.bottom - 1;
	if (!m_ProgressCtrl.m_hWnd)
	{
		m_ProgressCtrl.Create(WS_CHILD | WS_VISIBLE, rect, &m_StatusBar, IDC_PROGRESS);//創建進度條
	}
	else
	{
		m_ProgressCtrl.MoveWindow(rect);
	}
	//m_ProgressCtrl.StepIt();
}
void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CSkinFrameWnd::OnShowWindow(bShow, nStatus);
	// TODO: 在此加入您的訊息處理常式程式碼
	//SetWindowPos(this, 8, 8, 1024, 768, SWP_NOMOVE);//改變窗口大小
	MoveWindow(0, 0, 1024, 768);//防止工具列跑掉
	CenterWindow();//顯示在螢幕中間
}
/*狀態列時鐘*/
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (nIDEvent == 1) {
		/*系統執行時間更新*/
		CClientDC dc(this);
		CString str;
		long t = GetTickCount();
		str.Format(_T("系統已執行%2d時%2d分%2d秒"),
			t / 3600000,
			t % 3600000 / 60000,
			t % 3600000 % 60000 / 1000);
		CSize sz = dc.GetTextExtent(str);  //獲取文本寬度
		m_StatusBar.SetPaneText(2, str);//顯示狀態列時間文字
		/*時鐘更新*/
		m_SysTime = CTime::GetCurrentTime();
		str = m_SysTime.Format("%Y/%m/%d %H:%M:%S");//時間格式化
		m_StatusBar.SetPaneText(5, str);//顯示狀態列時間文字
	}
	//m_StatusBar.GetStatusBarCtrl().SetIcon(0, AfxGetApp()->LoadIcon(IDI_WORKGLED));
	CSkinFrameWnd::OnTimer(nIDEvent);
}
/*刪除菜單*/
void CMainFrame::DelAllMenu(HMENU hMenu)
{
	int Menucount = GetMenuItemCount(hMenu);
	for (int i = Menucount - 1; i > -1; i--) {
		::DeleteMenu(hMenu, i, MF_BYPOSITION);
	}
}
/*創建ToolBar*/
void CMainFrame::CreateToolBar()
{
	m_TBImageList.Create(48, 48, ILC_COLOR32 | ILC_MASK, 1, 1);//創建圖標列表
	for (int i = IDI_ACCOUNT; i <= IDI_HISTORY; i++)
	{
		m_TBImageList.Add(AfxGetApp()->LoadIcon(i));
	}
	UINT nArray[4];//創建按鈕陣列
	for (int i = 0; i < 4; i++)
	{
		nArray[i] = IDC_BTNACCOUNT + i;
	}
	m_ToolBar.CreateEx(this);
	m_ToolBar.EnableToolTips();//激活信息提示功能
	m_ToolBar.SetButtons(nArray, 4);//設置按鈕到工具欄上
	m_ToolBar.SetSizes(CSize(60, 56), CSize(48, 48));//設置工具欄一個按鈕空間大小
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_TBImageList);//設置按鈕圖片
	//m_TBImageList.Detach();//釋放img對象													
}
/*創建StatusBar*/
void CMainFrame::CreateStatusBar()
{
	m_StatusBar.CreateEx(this, SBARS_TOOLTIPS);
	m_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));//加入指示器ID
	m_StatusBar.SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL | SBPS_STRETCH, 1);//設置每一格寬度
	m_StatusBar.SetPaneInfo(2, STA_ALLTIMER, SBPS_NORMAL, 140);
	m_StatusBar.SetPaneInfo(3, STA_WORKCOUNT, SBPS_NORMAL, 80);
	m_StatusBar.SetPaneInfo(4, STA_PROCESS, SBPS_NORMAL, 80);
	m_StatusBar.SetPaneInfo(5, STA_SYSTIMER, SBPS_NORMAL, 120);
	m_StatusBar.GetStatusBarCtrl().SetMinHeight(20);//設置高度
	m_SBImageList.Create(16, 16, ILC_COLOR32, 1, 1);//建立图像控制
	for (int i = IDI_WORKGLED; i <= IDI_WORKTLED; i++)//增加ICon
	{
		m_SBImageList.Add(AfxGetApp()->LoadIcon(i));
	}
	//m_SBImageList.Detach();//釋放img對象
	//m_StatusBar.GetStatusBarCtrl().SetIcon(0, m_SBImageList.ExtractIcon(0));//設置圖標在狀態欄上  
}
/*ToolBar提示*/
BOOL CMainFrame::TBToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID = pNMHDR->idFrom; //獲取工具欄ID
    UINT nIndex = m_ToolBar.CommandToIndex(nID); //獲取工具欄ID的索引號
    CString str;
    switch (nIndex)
    {
    case 0:
        str = TT_BTNACCOUNT;
        break;
    case 1:
        str = TT_BTNINPROCESS;
        break;
    case 2:
        str = TT_BTNOBJMENAGEMENT;
        break;
    case 3:
        str = TT_BTNHISTORY;
        break;
    default:
        break;
    }
    pTTT->lpszText = str.AllocSysString();
    pTTT->hinst = AfxGetResourceHandle();
    return 0;
}