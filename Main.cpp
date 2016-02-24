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
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNMAINGOORIGIN, &CMain::OnBnClickedBtnmaingoorigin)
	ON_BN_CLICKED(IDC_BTNMAINTIMEOUT, &CMain::OnBnClickedBtnmaintimeout)
	ON_BN_CLICKED(IDC_BTNMAINSTOP, &CMain::OnBnClickedBtnmainstop)
	ON_BN_CLICKED(IDC_BTNMAINSTART, &CMain::OnBnClickedBtnmainstart)
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
	SetTimer(1, 100, NULL);
    /*開即時影像*/
#ifdef VI
	VI_ModelDefine(GetDlgItem(IDC_PICMAINALIGNMENT));
#endif //VI
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
		if (File.Open(GetModulePath()+_T("Inprocess.txt"), CFile::modeRead )) {//打開檔案
			CArchive ar(&File, CArchive::load);//讀取入檔案
			ar >> m_MainPosData1 >> m_MainPosData2 >> m_MainListWKCount >>m_MainZDataDown >> m_MainZDataUp;
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
    /*切換即時影像*/
#ifdef VI
	VI_ChangeWindow(GetDlgItem(IDC_PICMAINALIGNMENT));
#endif //VI
}
void CMain::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	// TODO: 在此加入您的訊息處理常式程式碼
	CWnd *pWnd;
	for (int i = IDC_LISTMAINWORK; i <= IDC_MOVEDRAW;i++)
	{
		pWnd = GetDlgItem(i);
		ChangeSize(pWnd, cx, cy);
	}
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
	WorkPoint *pData = new WorkPoint;
	pData->hwnd = m_hWnd;
	pData->WorkCount = m_MainListWKCount;
	pData->Work = new CStringArray;
	pData->Work->Copy(m_MainWorkData);
	pData->StandPos1 = m_MainPosData1;
	pData->StandPos2 = m_MainPosData2;
    pData->m_ZDataDown = m_MainZDataDown;
    pData->m_ZDataUp = m_MainZDataUp;
	if (!g_pThreadRun) {
		g_pThreadRun = AfxBeginThread(Run, (LPVOID)pData);
	}
	else {
		MessageBox(_T("運作中"));
	}
    WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("開始"));
}
/*回原點*/
void CMain::OnBnClickedBtnmaingoorigin()
{
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
#ifdef MOVE
	MO_MoveToHome(pParameter->OSpeed, pParameter->OLSpeed,7,0);
#endif //MOVE
    WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("原點復歸"));
}
/*暫停*/
void CMain::OnBnClickedBtnmaintimeout()
{
	CString StrBuff;
	GetDlgItem(IDC_BTNMAINTIMEOUT)->GetWindowText(StrBuff);
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
	if (StrBuff == _T("暫停"))
	{
		if (!g_pThreadRun) 
		{
			MessageBox(_T("目前尚未運行"));
		}
		else 
		{   
			g_pThreadRun->SuspendThread();//暫停線程
			GetDlgItem(IDC_BTNMAINTIMEOUT)->SetWindowText(_T("重新啟動"));
			pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(3));//工作燈暫停中
            WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("暫停"));
		}
	}
	else
	{
		g_pThreadRun->ResumeThread();//啟動線程
		GetDlgItem(IDC_BTNMAINTIMEOUT)->SetWindowText(_T("暫停"));
		pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(2));//工作燈暫停中
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("重新啟動"));
	}
    
}
/*停止*/
void CMain::OnBnClickedBtnmainstop()
{
#ifdef MOVE
	MO_STOP();
#endif //MOVE
	if (g_pThreadRun)
	{
		g_ThreadClose = TRUE;
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("停止"));
	}   
}
/*座標字串分割轉換*/
LONG CMain::CStringToXY(CString Data, int Choose) {
	int iLength = Data.Find(_T('，'));
	if(!Choose)
	{
		return _ttol(Data.Left(iLength));
	}
	else
	{
		return _ttol(Data.Right(Data.GetLength()-iLength-1));//從右讀回來Data.GetLength()-iLength-1多個字元
	}
}
/*運行*/
UINT CMain::Run(LPVOID pParam) {
	HWND hwnd = ((WorkPoint*)pParam)->hwnd;
	CStringArray* Work = ((WorkPoint*)pParam)->Work;
    int WorkCount = ((WorkPoint*)pParam)->WorkCount;

	LONG PointX = 0, PointY = 0 , PointZ = 0;
    double OffSetX, OffSetY, Angle;

	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
#ifdef VI
    void *Model1 = malloc(2 * sizeof(void*));
    void *Model2 = malloc(2 * sizeof(void*));
    VI_Load(_T("D:"), _T("Model1"), Model1);
    VI_Load(_T("D:"), _T("Model2"), Model2);
    void *PicTemp1 = malloc(2 * sizeof(void*));
    VI_Getpicture(PicTemp1);
    void *PicTemp2 = malloc(2 * sizeof(void*));
    VI_Getpicture(PicTemp2);
    VI_FindModel(PicTemp1, PicTemp2, Model1, Model2, OffSetX, OffSetY, Angle);
    CString a;
    a.Format(_T("%f,%f,%f"), OffSetX, OffSetY, Angle);
    AfxMessageBox(a);
#endif // VI 
	if (WorkCount > 0)
	{ 
		for (int i = 0; i <= WorkCount; i++)
		{
			PointX = CStringToXY(i ? Work->GetAt(i * 2 - 1) : Work->GetAt(i), 0);
			PointY = CStringToXY(i ? Work->GetAt(i * 2 - 1) : Work->GetAt(i), 1);
            ModifyWork(PointX, PointY, OffSetX, OffSetY, Angle);
            if (i <= 1)
            {
                ::PostMessage(hwnd, WM_WORKLIST, 0, 0);
            }    
#ifdef MOVE
			MO_Do2DLineMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
			while (MO_ReadIsDriving(7)) {
				Sleep(1);//軸卡限制
			}
			if (g_ThreadClose)
			{
				g_ThreadClose = FALSE;
				g_pThreadRun = NULL;
				::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
				return 0;
			}
			if (i == 0)
			{
				/*對位點1動作*/
				PointX = CStringToXY(((WorkPoint*)pParam)->StandPos1, 0);
				PointY = CStringToXY(((WorkPoint*)pParam)->StandPos1, 1);
				MO_Do2DLineMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
				while (MO_ReadIsDriving(7)) {
					Sleep(1);//軸卡限制
				}
				if (g_ThreadClose) 
				{
					g_ThreadClose = FALSE;
					g_pThreadRun = NULL;
					::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
					return 0;
				}
#ifdef VI
                void *PicTemp1 = malloc(2 * sizeof(void*));
                VI_Getpicture(PicTemp1);
#endif //VI
                /*對位點2動作*/
				PointX = CStringToXY(((WorkPoint*)pParam)->StandPos2, 0);
				PointY = CStringToXY(((WorkPoint*)pParam)->StandPos2, 1);
				MO_Do2DLineMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
				while (MO_ReadIsDriving(7)) {
					Sleep(1);//軸卡限制
				}
				if (g_ThreadClose)
				{
					g_ThreadClose = FALSE;
					g_pThreadRun = NULL;
					::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
					return 0;
				}
#ifdef VI
                void *PicTemp2 = malloc(2 * sizeof(void*));
                VI_Getpicture(PicTemp2);
                VI_FindModel(PicTemp1, PicTemp2,Model1,Model2,OffSetX, OffSetY, Angle);
#endif // VI       
			}
            else
            {
                /*Z軸點膠動作*/
                /*Down*/
                PointZ = _ttol(((WorkPoint*)pParam)->m_ZDataDown);
                MO_DoZLineMove(PointZ - MO_ReadLogicPosition(2), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
                while (MO_ReadIsDriving(7)) {
                    Sleep(1);//軸卡限制
                }
                if (g_ThreadClose)
                {
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }
                /*Up*/
                PointZ = _ttol(((WorkPoint*)pParam)->m_ZDataUp);
                MO_DoZLineMove(PointZ - MO_ReadLogicPosition(2), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
                while (MO_ReadIsDriving(7)) {
                    Sleep(1);//軸卡限制
                }
                if (g_ThreadClose)
                {
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }
                ::PostMessage(hwnd, WM_WORKLIST, 0, i);
            }
#endif //MOVE

		}  
	}
	g_pThreadRun = NULL;
	return 0;
}
/*列表刷新*/
LRESULT CMain::OnListRefresh(WPARAM wParam, LPARAM lParam)
{
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
    if (lParam == 0)
    {
        m_ListCtrlWork.EnableWindow(FALSE);//關閉工作列表
        pMain->m_ProgressCtrl.SetRange(0, m_MainListWKCount);//設置進度條%數
        pMain->m_ProgressCtrl.SetPos(0);//進度條歸零
        pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(2));//工作燈運作中
        m_ListCtrlWork.SetItemState(lParam, LVIS_SELECTED, LVIS_SELECTED);//將工作點設為高亮
        m_ListCtrlWork.SetSelectionMark(lParam);//改變選中索引
        m_ListCtrlWork.EnsureVisible(lParam, FALSE);//使List中一項可見(如滾動條向下滾)
        pMain->m_ProgressCtrl.SetPos(lParam);//設置進度條進度
    } 
	else if (lParam == m_MainListWKCount) 
	{
		pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(0));//工作燈閒置中
		m_ListCtrlWork.EnableWindow(TRUE);//開啟工作列表
		pMain->m_ProgressCtrl.SetPos(0);
	}
	else
	{
		m_ListCtrlWork.SetItemState(lParam, LVIS_SELECTED, LVIS_SELECTED);//將工作點設為高亮
		m_ListCtrlWork.SetSelectionMark(lParam);//改變選中索引
		m_ListCtrlWork.EnsureVisible(lParam, FALSE);//使List中一項可見(如滾動條向下滾)
		pMain->m_ProgressCtrl.SetPos(lParam);//設置進度條進度
	}
	return LRESULT();
}
/*刷新XYZ座標*/
void CMain::OnTimer(UINT_PTR nIDEvent)
{
#ifdef MOVE
	SetDlgItemInt(IDC_STAMAINX2, MO_ReadLogicPosition(0));
	SetDlgItemInt(IDC_STAMAINY2, MO_ReadLogicPosition(1));
	SetDlgItemInt(IDC_STAMAINZ2, MO_ReadLogicPosition(2));
#endif //MOVE
	CPropertyPage::OnTimer(nIDEvent);
}
/*修正工作點*/
void CMain::ModifyWork(LONG &PointX, LONG &PointY, double OffSetX, double OffSetY, double Angle) {
    double OldPointX = PointX;
    double OldPointY = PointY;
    PointX = (OldPointX * cos(Angle * M_PI / 180)) - (OldPointY * sin(Angle * M_PI / 180)) + OffSetX + 0.5;//加0.5四捨五入
    PointY = (OldPointX * sin(Angle * M_PI / 180)) + (OldPointY * sin(Angle * M_PI / 180)) + OffSetY + 0.5;
}


