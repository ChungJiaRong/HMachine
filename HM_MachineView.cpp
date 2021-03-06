
// HM_MachineView.cpp : CHM_MachineView 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "HM_Machine.h"
#endif

#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "History.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHM_MachineView
IMPLEMENT_DYNCREATE(CHM_MachineView, CView)
BEGIN_MESSAGE_MAP(CHM_MachineView, CView)
	/*分頁*/
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, &CHM_MachineView::OnTabSelChange)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TABCTRL, &CHM_MachineView::OnTabSelChanging)
	/*生成*/
	ON_WM_CREATE()
	ON_WM_SIZE()
    /*工具列按鈕*/
	ON_COMMAND(IDC_BTNACCOUNT, &CHM_MachineView::OnBtnaccount)
	ON_COMMAND(IDC_BTNINPROCESS, &CHM_MachineView::OnBtninprocess)
    ON_COMMAND(IDC_BTNOBJMENAGEMENT, &CHM_MachineView::OnBtnobjmenagement)
    ON_COMMAND(IDC_BTNHISTORY, &CHM_MachineView::OnBtnhistory)
END_MESSAGE_MAP()
// CHM_MachineView 建構/解構
CHM_MachineView::CHM_MachineView()
    : m_MainDataUP(TRUE)
{
	// TODO: 在此加入建構程式碼
	m_TabCtrl = NULL;//初始化分頁變數
}

CHM_MachineView::~CHM_MachineView()
{      
	/*結束後刪除分頁*/
	if (m_TabCtrl)
		delete m_TabCtrl;
	int num = m_DlgArray.GetSize();
	for (int i = 0; i < num; i++)
	{
		if (m_DlgArray[i])
			delete m_DlgArray[i];
	}
}

BOOL CHM_MachineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}
// CHM_MachineView 描繪
void CHM_MachineView::OnDraw(CDC* /*pDC*/)
{
	CHM_MachineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此加入原生資料的描繪程式碼
}

// CHM_MachineView 診斷
#ifdef _DEBUG
void CHM_MachineView::AssertValid() const
{
	CView::AssertValid();
}

void CHM_MachineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHM_MachineDoc* CHM_MachineView::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHM_MachineDoc)));
	return (CHM_MachineDoc*)m_pDocument;
}
#endif //_DEBUG

// CHM_MachineView 訊息處理常式
int CHM_MachineView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此加入特別建立的程式碼
    m_TabCtrl = new CTabCtrl;//分配記憶體給分頁
    if (m_TabCtrl->Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,CRect(0, 0, 0, 0), this, IDC_TABCTRL) == FALSE)
    {
        return -1;
    }
	return 0;
}
void CHM_MachineView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: 在此加入您的訊息處理常式程式碼
	m_TabCtrl->MoveWindow(0, 0, cx, cy);//改變分頁控件大小
}                                        
/*創建分頁-頁面增加*/
void CHM_MachineView::CreatePages()
{
    CDialog* dlg;
    dlg = new CMain;
    m_DlgArray.Add(dlg);
    dlg->Create(IDD_MAIN, m_TabCtrl);
    m_TabCtrl->InsertItem(0, _T("主頁面"));
    if (((CHM_MachineApp*)AfxGetApp())->Post == _T("工程師"))
    {
        dlg = new CCompiler;
        m_DlgArray.Add(dlg);
        dlg->Create(IDD_COMPILER, m_TabCtrl);
        m_TabCtrl->InsertItem(1, _T("編輯頁面"));
        dlg = new CParameter;
        m_DlgArray.Add(dlg);
        dlg->Create(IDD_PARAMETER, m_TabCtrl);
        m_TabCtrl->InsertItem(2, _T("參數設定"));
        dlg = new CIOState;
        m_DlgArray.Add(dlg);
        dlg->Create(IDD_IOSTATE, m_TabCtrl);
        m_TabCtrl->InsertItem(3, _T("I/O狀態"));
    } 
    OnTabSelChange(NULL, NULL);
    Invalidate();      
}
/*分頁改變*/
void CHM_MachineView::OnTabSelChanging(NMHDR* pnmhdr, LRESULT* pResult)
{
	int sel_index = m_TabCtrl->GetCurSel();//獲取當前選擇分頁的索引
	m_DlgArray[sel_index]->ShowWindow(SW_HIDE);//隱藏分頁
	*pResult = FALSE;
}
/*改變後顯示分頁*/
void CHM_MachineView::OnTabSelChange(NMHDR* pnmhdr, LRESULT* pResult)
{
	CRect TabClientR;
	m_TabCtrl->GetClientRect(&TabClientR);
	int sel_index = m_TabCtrl->GetCurSel();
	m_DlgArray[sel_index]->SetWindowPos(
		NULL,
		TabClientR.left+1, TabClientR.top+25, TabClientR.right-1, TabClientR.bottom-25,
		 SWP_SHOWWINDOW);
	m_DlgArray[sel_index]->SetFocus();
}
/*切換使用者*/
void CHM_MachineView::OnBtnaccount()
{
#ifdef MOVE
    MO_Close();
#endif // MOVE
#ifdef VI
    VI_FreeApp();
#endif //VI
    int nCount = m_DlgArray.GetSize();//獲取分頁數
    for (int i = 0; i < nCount; i++) {//釋放分頁記憶體
        delete m_DlgArray.GetAt(i);
    }
    m_DlgArray.RemoveAll();//清除分頁
    m_TabCtrl->DeleteAllItems();//清除分頁控件項目
    m_MainDataUP = TRUE;//主頁面資料更新開啟
    GetDocument()->DeleteContents();//清除檔案陣列
    ((CHM_MachineApp*)AfxGetApp())->LoginApp();//切換使用者介面 

}
/*載入加工程序*/
void CHM_MachineView::OnBtninprocess()
{   
}
/*RECIPE管理*/
void CHM_MachineView::OnBtnobjmenagement()
{
   
}
/*歷史訊息*/
void CHM_MachineView::OnBtnhistory()
{
    if (((CHM_MachineApp*)AfxGetApp())->Post == _T("工程師"))
    {
        ((CHM_MachineApp*)AfxGetApp())->HistoryFile.Close();
        CHistory HistoryDlg;
        if (HistoryDlg.DoModal()) {
            if ((((CHM_MachineApp*)AfxGetApp())->HistoryFile.Open(GetModulePath()+_T("History.txt"), CFile::modeCreate | CFile::modeNoTruncate
                | CFile::modeWrite | CFile::typeUnicode | CFile::shareDenyNone)) == 0)
            {
                AfxMessageBox(_T("History開啟失敗"));
            }
            else
            {
                ((CHM_MachineApp*)AfxGetApp())->HistoryFile.SeekToEnd();
            }
        }
        
    }
    else
    {
        MessageBox(_T("此功能無法使用"));
    }
}
/*快捷鍵*/
BOOL CHM_MachineView::HandleKeyDownMsg(MSG* pMsg)
{
    if (pMsg->wParam == VK_F1 && GetKeyState(VK_CONTROL) < 0)
    {
        BOOL    shift_down = GetKeyState(VK_SHIFT) < 0;
        int		old_sel = m_TabCtrl->GetCurSel();		//目前的標籤
        int		num = m_TabCtrl->GetItemCount();  //目前的控制項
        int		new_sel = shift_down ? (old_sel + (num - 1)) % num : (old_sel + 1) % num;   //如果shift鍵down 為左邊，反之右邊

        RECT    r_tab;
        m_TabCtrl->GetItemRect(new_sel, &r_tab);
        m_TabCtrl->SendMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(r_tab.left, r_tab.top));
        return TRUE;
    }
}

BOOL CHM_MachineView::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        CView* view = ((CFrameWnd *)AfxGetMainWnd())->GetActiveView();
        HandleKeyDownMsg(pMsg);
    }
    return CView::PreTranslateMessage(pMsg);
}
