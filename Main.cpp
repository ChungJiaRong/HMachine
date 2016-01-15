// Main.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Main.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"

// CMain 對話方塊
IMPLEMENT_DYNAMIC(CMain, CPropertyPage)

CMain::CMain()
	: CPropertyPage(IDD_MAIN)
{
	m_MainListWKCount = 0;
	m_MainWorkData.SetSize(201);//設定陣列大小201筆
	for (int i = 0; i < sizeof(m_MainWorkData); i++)//清空所有陣列 
	{
		m_MainWorkData[i].Empty();
	}
}
CMain::~CMain()
{
}
void CMain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTMAINWORK, m_ListCtrlWork);
}

BEGIN_MESSAGE_MAP(CMain, CPropertyPage)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNMAINGOORIGIN, &CMain::OnBnClickedBtnmaingoorigin)
	ON_BN_CLICKED(IDC_BTNMAINTIMEOUT, &CMain::OnBnClickedBtnmaintimeout)
	ON_BN_CLICKED(IDC_BTNMAINSTOP, &CMain::OnBnClickedBtnmainstop)
	ON_BN_CLICKED(IDC_BTNMAINSTART, &CMain::OnBnClickedBtnmainstart)
	ON_WM_PAINT()
	ON_MESSAGE(WM_WORKLIST, OnListRefresh)
END_MESSAGE_MAP()

// CMain 訊息處理常式
BOOL CMain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// TODO:  在此加入額外的初始化
	CHeaderCtrl *pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlWork.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlWork.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlWork.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 38, -1);
	m_ListCtrlWork.InsertColumn(1, _T("起始點"), LVCFMT_CENTER, 118, -1);
	m_ListCtrlWork.InsertColumn(2, _T("結束點"), LVCFMT_CENTER, 118, -1);
	m_ListCtrlWork.InsertColumn(3, _T("動作"), LVCFMT_CENTER, 38, -1);
#ifdef ALL_STAR
    if (!MO_Open())
    {
        MessageBox(_T("啟動失敗"));
    }
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此加入您的訊息處理常式程式碼
					   // 不要呼叫圖片訊息的 CPropertyPage::OnPaint()
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
	if (pView->m_MainDataUP) {
		pView->m_MainDataUP = FALSE;
		m_ListCtrlWork.DeleteAllItems();//清除工作點列表
		CFile File;
		CString StrBuff;
		if (File.Open(_T("Inprocess.txt"), CFile::modeRead )) {//打開檔案
			CArchive ar(&File, CArchive::load);//讀取入檔案
			ar >> m_MainPosData1 >> m_MainPosData2 >> m_MainListWKCount;
			for (int i = 0; i < m_MainListWKCount * 2 + 1; i++) {
				ar >> m_MainWorkData[i];
			}
			File.Close();
		}
		for (int i = 0; i < m_MainListWKCount; i++) {//刷新工作列表
			(i + 1>9) ? StrBuff.Format(_T("0%d"), i + 1) : StrBuff.Format(_T("00%d"), i + 1);
			m_ListCtrlWork.InsertItem(i,StrBuff);
			if (i == 0)
			{
				m_ListCtrlWork.SetItemText(i, 1, m_MainWorkData[0]);
			}
			else
			{
				m_ListCtrlWork.SetItemText(i, 1, m_MainWorkData[i * 2 - 1]);
			}
			m_ListCtrlWork.SetItemText(i, 2, m_MainWorkData[i * 2 + 1]);
			m_ListCtrlWork.SetItemText(i, 3, m_MainWorkData[i * 2 + 2]);
		}
		StrBuff.Format(_T("共%d個工作點"), m_MainListWKCount);
		pMain->m_StatusBar.SetPaneText(3, StrBuff);//設定狀態列文字
		pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(0));//工作燈亮
	}
}
void CMain::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	CWnd *pWnd;
	/*pWnd = GetDlgItem(IDC_BTNMAINSTART);
	ChangeSize(pWnd, cx, cy);*/
	for (int i = 1000; i < 1018;i++)
	{
		pWnd = GetDlgItem(i);
		ChangeSize(pWnd, cx, cy);
	}
	pWnd = GetDlgItem(IDC_MOVEDRAW);
	ChangeSize(pWnd, cx, cy);
	GetClientRect(&m_InitRect); 
}
/*改變控件大小*/
void CMain::ChangeSize(CWnd* pWnd, int cx, int cy)
{
	if (pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建   
	{
		CRect Rect;   //获取控件变化前的大小    
		pWnd->GetWindowRect(&Rect);
		ScreenToClient(&Rect);//将控件大小转换为在对话框中的区域坐标 
		//控件隨著視窗變大而變大-缺點位置會改變
		Rect.left = Rect.left*cx / m_InitRect.Width();//调整控件大小  
		Rect.right = Rect.right*cx / m_InitRect.Width();
		Rect.top = Rect.top*cy / m_InitRect.Height();
		Rect.bottom = Rect.bottom*cy / m_InitRect.Height();
		pWnd->MoveWindow(Rect);//设置控件大小
	}
}
/*開始*/
void CMain::OnBnClickedBtnmainstart()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
	m_ListCtrlWork.EnableWindow(FALSE);//關閉工作列表
	pMain->m_ProgressCtrl.SetRange(0, m_MainListWKCount);//設置進度條%數
	pMain->m_ProgressCtrl.SetPos(0);//進度條歸零
    pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(2));//工作燈運作中
    WorkPoint *pData = new WorkPoint;
    pData->hwnd = m_hWnd;
    pData->WorkCount = m_MainListWKCount;
    pData->Work = new CStringArray;
    pData->Work->Copy(m_MainWorkData);
    if (g_pThreadRun == NULL) {
        g_pThreadRun = AfxBeginThread(Run, (LPVOID)pData);
    }
    else {
        MessageBox(_T("運作中"));
    }
}
/*回原點*/
void CMain::OnBnClickedBtnmaingoorigin()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//MessageBox(_T("此功能尚未完成"));
#ifdef ALL_STAR1
    CRect src;
    CWnd *twnd = GetDlgItem(IDC_PICMAINREALTIME);
    twnd->GetClientRect(&src);

    MappAllocDefault(M_DEFAULT, &MilApplication, &MilSystem, &MilDisplay, &MilDigitizer, &MilImage);
    MdigGrabContinuous(MilDigitizer, MilImage);

    MdispControl(MilDisplay, M_OVERLAY, M_ENABLE);
    MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
    MdispInquire(MilDisplay, M_OVERLAY_ID, &MilOverlayImage);

    MgraColor(M_DEFAULT, M_COLOR_RED);
    MgraLine(M_DEFAULT, MilOverlayImage, 320 - src.Width() / 2, 240, 320 + src.Width() / 2, 240);
    MgraLine(M_DEFAULT, MilOverlayImage, 320, 240 + src.Height() / 2, 320, 240 - src.Height() / 2);
    MgraColor(M_DEFAULT, M_COLOR_RED);
    MdispSelectWindow(MilDisplay, MilImage, GetDlgItem(IDC_PICMAINREALTIME)->GetSafeHwnd());
    MdispPan(MilDisplay, 320 - src.Width() / 2, 240 - src.Height() / 2);
#endif // ALL_STAR 
}
/*暫停*/
void CMain::OnBnClickedBtnmaintimeout()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//MessageBox(_T("此功能尚未完成"));
    CString StrBuff;
    GetDlgItem(IDC_BTNMAINTIMEOUT)->GetWindowText(StrBuff);
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
    if (StrBuff == _T("暫停"))
    {
        if (g_pThreadRun == NULL) {
            MessageBox(_T("目前尚未運行"));
        }
        else { 
            pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(3));//工作燈暫停中
            g_pThreadRun->SuspendThread();//暫停線程
            GetDlgItem(IDC_BTNMAINTIMEOUT)->SetWindowText(_T("重新啟動"));
        }
    }
    else
    {
        g_pThreadRun->ResumeThread();//啟動線程
        GetDlgItem(IDC_BTNMAINTIMEOUT)->SetWindowText(_T("暫停"));
        pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(2));//工作燈暫停中
    }
}
/*停止*/
void CMain::OnBnClickedBtnmainstop()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//MessageBox(_T("此功能尚未完成"));
#ifdef ALL_STAR1
    MdigHalt(MilDigitizer);
    MappFreeDefault(MilApplication, MilSystem, MilDisplay, MilDigitizer, MilImage);
#endif // ALL_STAR
}
/*座標字串分割*/
CString CMain::CStringToXY(CString Data, int Choose) {
	int iLength = Data.Find(_T('，'));
	if(!Choose)
	{
		return Data.Left(iLength);
	}
	else
	{
		return Data.Right(Data.GetLength()-iLength-1);//從右讀回來Data.GetLength()-iLength-1多個字元
	}
}
/*運行*/
UINT CMain::Run(LPVOID pParam) {
    HWND hwnd = ((WorkPoint*)pParam)->hwnd;
    CStringArray* Work = ((WorkPoint*)pParam)->Work;
    LONG PointX = 0, PointY = 0;
    LONG OldPointX = 0, OldPointY = 0;
    if (((WorkPoint*)pParam)->WorkCount > 0)
    { 
        for (int i = 0; i <= ((WorkPoint*)pParam)->WorkCount; i++)
        {
#ifdef ALL_STAR
            OldPointX = MO_ReadPosition(1, NULL);
            OldPointY = MO_ReadPosition(2, NULL);
#endif
            PointX = _ttol(CStringToXY(i ? Work->GetAt(i * 2 - 1) : Work->GetAt(i), 0));
            PointY = _ttol(CStringToXY(i ? Work->GetAt(i * 2 - 1) : Work->GetAt(i), 1));
#ifdef ALL_STAR
            MO_Do2DLineMove(PointX - OldPointX, PointY - OldPointY, 100000, 10, 30000);
#endif
            /*CString S;
            S.Format(_T("%d,%d,%d"),i, PointX, PointY);
            AfxMessageBox(S);*/
            ::PostMessage(hwnd, WM_WORKLIST, 0, i);
#ifdef ALL_STAR
            while (MO_IsDriving(7));
#endif
            Sleep(500);
        }  
    }
    g_pThreadRun = NULL;
    return 0;
}
/*列表刷新*/
LRESULT CMain::OnListRefresh(WPARAM wParam, LPARAM lParam)
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
    LONG PointX = 0, PointY = 0;
    if (lParam == m_MainListWKCount) 
    {
       /* CDC *dc = GetDlgItem(IDC_MOVEDRAW)->GetDC();
        PointX = _ttol(CStringToXY(lParam ? m_MainWorkData[lParam * 2 - 1] : m_MainWorkData[lParam], 0));
        PointY = _ttol(CStringToXY(lParam ? m_MainWorkData[lParam * 2 - 1] : m_MainWorkData[lParam], 1));
        dc->LineTo(PointX, PointY);
        */
        pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(0));//工作燈閒置中
        m_ListCtrlWork.EnableWindow(TRUE);//開啟工作列表
        pMain->m_ProgressCtrl.SetPos(0);
    }
    else
    {
        /*CDC *dc = GetDlgItem(IDC_MOVEDRAW)->GetDC();
        PointX = _ttol(CStringToXY(lParam ? m_MainWorkData[lParam * 2 - 1] : m_MainWorkData[lParam], 0));
        PointY = _ttol(CStringToXY(lParam ? m_MainWorkData[lParam * 2 - 1] : m_MainWorkData[lParam], 1));
        dc->LineTo(PointX, PointY);
        */
        m_ListCtrlWork.SetItemState(lParam, LVIS_SELECTED, LVIS_SELECTED);//將工作點設為高亮
        m_ListCtrlWork.SetSelectionMark(lParam);//改變選中索引
        m_ListCtrlWork.EnsureVisible(lParam, FALSE);//使List中一項可見(如滾動條向下滾)
        pMain->m_ProgressCtrl.SetPos(lParam+1);//設置進度條進度
    }
	return LRESULT();
}
