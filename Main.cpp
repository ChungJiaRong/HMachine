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
	m_MainWorkCount = 0;
    m_Znone = FALSE;
    m_Single = FALSE;
}
CMain::~CMain()
{
}
void CMain::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LISTMAINWORK, m_ListCtrlWork);
    DDX_Check(pDX, IDC_CHKMAINZNONE, m_Znone);
    DDX_Check(pDX, IDC_CHKMAINSINGLE, m_Single);
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
	ON_MESSAGE(WM_ERRORXY, OnXYRefresh)
    ON_MESSAGE(WM_SINGLE, OnSetText)
END_MESSAGE_MAP()
// CMain 訊息處理常式
BOOL CMain::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// TODO:  在此加入額外的初始化
	CHeaderCtrl *pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlWork.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlWork.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlWork.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 36, -1);
	m_ListCtrlWork.InsertColumn(1, _T("起始點"), LVCFMT_CENTER, 108, -1);
	m_ListCtrlWork.InsertColumn(2, _T("結束點"), LVCFMT_CENTER, 158, -1);
	m_ListCtrlWork.InsertColumn(3, _T("動作"), LVCFMT_CENTER, 36, -1);
	m_ListCtrlWork.InsertColumn(4, _T("運動方式"), LVCFMT_CENTER, 90, -1);
	/*工具提示*/
    m_tooltip.Create(this, TTS_ALWAYSTIP);  //  TTS_BALLOON | TTS_NOFADE | TTS_CLOSE
    m_tooltip.Activate(TRUE);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNMAINSTART), TT_BTNMAINSTART);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNMAINGOORIGIN), TT_BTNMAINGOORIGIN);
    m_tooltip.SetDelayTime(TTDT_INITIAL, 1000);
    m_tooltip.SetDelayTime(TTDT_AUTOPOP, 10000);
    m_fasttooltip.Create(this, TTS_ALWAYSTIP);  //  TTS_BALLOON | TTS_NOFADE | TTS_CLOSE
    m_fasttooltip.Activate(TRUE);
    m_fasttooltip.AddTool(GetDlgItem(IDC_BTNMAINTIMEOUT), TT_BTNMAINTIMEOUT);
    m_fasttooltip.AddTool(GetDlgItem(IDC_BTNMAINSTOP), TT_BTNMAINSTOP);
    m_fasttooltip.SetDelayTime(TTDT_INITIAL, 100);
    m_fasttooltip.SetDelayTime(TTDT_AUTOPOP, 10000);
    m_fasttooltip.SetTitle(TTI_INFO, _T("提示"));
	/*刷新XYZ值*/
	SetTimer(1, 10, NULL);
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
        m_MainWorkData.clear();//清空向量陣列
		CFile File;
		CString StrBuff;
		if (File.Open(GetModulePath()+_T("Inprocess.txt"), CFile::modeRead )) {//打開檔案
			CArchive ar(&File, CArchive::load);//讀取入檔案
			ar >> m_MainPosData1 >> m_MainPosData2 >> m_MainPickUp >> m_MainGlueTime >> m_MainWorkCount;
			for (int i = 0; i < m_MainWorkCount * 3; i++) {
				ar >> StrBuff;
                m_MainWorkData.push_back(StrBuff);
			}
			File.Close();
		}
		for (int i = 1; i < m_MainWorkCount; i++) {//刷新工作列表
			(i>9) ? StrBuff.Format(_T("0%d"), i) : StrBuff.Format(_T("00%d"), i);
			m_ListCtrlWork.InsertItem(i-1,StrBuff);
			m_ListCtrlWork.SetItemText(i-1, 1, m_MainWorkData.at((i-1) * 3));
			m_ListCtrlWork.SetItemText(i-1, 2, m_MainWorkData.at(i * 3));
			m_ListCtrlWork.SetItemText(i-1, 3, m_MainWorkData.at(i * 3 + 1));
			m_ListCtrlWork.SetItemText(i-1, 4, m_MainWorkData.at(i * 3 + 2));
		}
		StrBuff.Format(_T("共%d個工作點"), m_MainWorkCount);
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
	if (!g_pThreadRun) {
        WorkPoint *pData = new WorkPoint;
        pData->hwnd = m_hWnd;
        pData->WorkCount = m_MainWorkCount;
        pData->Work = new  std::vector<CString>;
        pData->Work->assign(m_MainWorkData.begin(), m_MainWorkData.end());
        pData->GlueTime = m_MainGlueTime;
        pData->PickUp = m_MainPickUp;
        pData->StandPos1 = m_MainPosData1;
        pData->StandPos2 = m_MainPosData2;
		g_pThreadRun = AfxBeginThread(Run, (LPVOID)pData);
	}
	else {
		MessageBox(_T("加工運作中"));
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
    CWait Waitdialog;
    if (Waitdialog.DoModal())
    {
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("原點復歸"));
    }
}
/*暫停*/
void CMain::OnBnClickedBtnmaintimeout()
{
	CString StrBuff;
	GetDlgItemText(IDC_BTNMAINTIMEOUT, StrBuff);
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
			SetDlgItemText(IDC_BTNMAINTIMEOUT, _T("重新啟動"));
			pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(3));//工作燈暫停中
			WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("暫停"));
		}
	}
	else
	{
		g_pThreadRun->ResumeThread();//啟動線程
		SetDlgItemText(IDC_BTNMAINTIMEOUT, _T("暫停"));
		pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(2));//工作燈暫停中
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("重新啟動"));
	}
	
}
/*停止*/
void CMain::OnBnClickedBtnmainstop()
{
	if (g_pThreadRun)//判斷是否有在運作
	{
        CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
        if (SuspendThread(g_pThreadRun) != GetLastError())
        {
            SetDlgItemText(IDC_BTNMAINTIMEOUT, _T("暫停"));
            g_pThreadRun->ResumeThread();//啟動線程
        }
        #ifdef MOVE
            MO_STOP();
            MO_StopGumming();
        #endif //MOVE
        g_ThreadClose = TRUE;
        pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(0));//工作燈閒置中
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件加工"), _T("停止"));
	}   
}
/*座標字串分割轉換*/
LONG CMain::CStringToXYZ(CString Data, int Choose) {
	int iLength = Data.Find(_T('，'));
	int iLength2 = Data.Right(Data.GetLength() - iLength - 1).Find(_T('，'));
	if (Choose == 0)
	{
		return _ttol(Data.Left(iLength));
	}
	else if (Choose == 1)
	{
		return _ttol(Data.Right(Data.GetLength() - iLength - 1).Left(iLength2));
	}
	else
	{
		return _ttol(Data.Right(Data.GetLength() - iLength - 1).Right((Data.Right(Data.GetLength() - iLength - 1)).GetLength() - iLength2 - 1));//從右讀回來Data.GetLength()-iLength-1多個字元
	}
}
/*運行*/
UINT CMain::Run(LPVOID pParam) {
	HWND hwnd = ((WorkPoint*)pParam)->hwnd;
    std::vector<CString>* Work = ((WorkPoint*)pParam)-> Work;
	int WorkCount = ((WorkPoint*)pParam)->WorkCount;
	LONG PickUp = _ttol(((WorkPoint*)pParam)->PickUp);

	LONG PointX = 0, PointY = 0, PointZ = 0;
	double OffSetX = 0, OffSetY = 0, Angle = 0 ,Angle1 = 0 , Angle2 = 0;

	CString Buff;

	CMainFrame *pMainFrm = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMainFrm->GetActiveView();
	CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
    CMain* pMain = (CMain*)pView->m_DlgArray.GetAt(0);
	::PostMessage(hwnd, WM_WORKLIST, 0, 0);//初始工作列表
    /*載入Model 1和2*/
    #ifdef VI
		void *Model1 = malloc(2 * sizeof(void*));
		void *Model2 = malloc(2 * sizeof(void*));
		VI_Load(GetModulePath(), _T("Model1"), Model1);
		VI_Load(GetModulePath(), _T("Model2"), Model2);
    #endif // VI 
    #ifdef MOVE
	if (WorkCount > 0)
	{ 
		for (int i = 0; i < WorkCount; i++)
		{
            /*工作點字串轉整數*/
			PointX = CStringToXYZ(Work->at(i * 3), 0);
			PointY = CStringToXYZ(Work->at(i * 3), 1);
			PointZ = CStringToXYZ(Work->at(i * 3), 2);
			/*待命點不修正*/
			if (i != 0)
			{
				Correct(PointX, PointY, CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 0), CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 2), OffSetX, OffSetY, Angle); 
			}  
			if (Work->at(i * 3 + 1) == _T("無") || Work->at(i * 3 + 1) == _T("點膠"))
			{
                /*要做移動時先將Z軸上升至最高點*/
                MO_DoZLineMove(PickUp - MO_ReadLogicPosition(2), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
                while (MO_ReadIsDriving(7)) {
                    Sleep(1);//軸卡限制
                }
                if (g_ThreadClose)
                {
                    if (i == 0)
                    {
                        VI_FreeModel(Model1);
                        VI_FreeModel(Model2);
                    }
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }
                if (pMain->m_Single)
                {
                    ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                    Sleep(1);
                    ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                    Sleep(1);
                }
                if (g_ThreadClose)
                {
                    if (i == 0)
                    {
                        VI_FreeModel(Model1);
                        VI_FreeModel(Model2);
                    }
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }

				if (Work->at(i * 3 + 2) == _T("直線"))
				{
					MO_Do2DLineMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
				}
				else
				{
					/*注意:圓速度  圓初速度固定1000 or pParameter->WSpeed.Init/10*/
					LONG RoundCX, RoundCY;
					RoundCX = CStringToXYZ(Work->at(i * 3 + 2).Right(Work->at(i * 3 + 2).GetLength() - Work->at(i * 3 + 2).Find(_T('，')) - 1), 0);
					RoundCY = CStringToXYZ(Work->at(i * 3 + 2).Right(Work->at(i * 3 + 2).GetLength() - Work->at(i * 3 + 2).Find(_T('，')) - 1), 1);
                    Correct(RoundCX, RoundCY, CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 0), CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 2), OffSetX, OffSetY, Angle);//修正圓心
					MO_Do2DArcMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1),
						RoundCX - MO_ReadLogicPosition(0),
						RoundCY - MO_ReadLogicPosition(1),
						pParameter->WSpeed.End, pParameter->WSpeed.Init, CStringToXYZ(Work->at(i * 3 + 2).Right(Work->at(i * 3 + 2).GetLength() - Work->at(i * 3 + 2).Find(_T('，')) - 1), 2));
				}
				while (MO_ReadIsDriving(7)) {
					Sleep(1);//軸卡限制
				}
                if (g_ThreadClose)
                {
                    if (i == 0)
                    {
                        VI_FreeModel(Model1);
                        VI_FreeModel(Model2);
                    }
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }
                if (pMain->m_Single )
                {
                    ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                    Sleep(1);
                    ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                    Sleep(1);
                }
                if (g_ThreadClose)
                {
                    if (i == 0)
                    {
                        VI_FreeModel(Model1);
                        VI_FreeModel(Model2);
                    }
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }

				Buff.Format(_T("%d"), i);
				WriteLogFile(((CHM_MachineApp*)AfxGetApp())->LogFile, _T("Move"), Buff);
				/*點膠動作*/
				if (Work->at(i * 3 + 1) == _T("點膠"))
				{
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
                    if (pMain->m_Single)
                    {
                        ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                        Sleep(1);
                        ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                        Sleep(1);
                    }
                    if (g_ThreadClose)
                    {
                        g_ThreadClose = FALSE;
                        g_pThreadRun = NULL;
                        ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                        return 0;
                    }

                    if (!pMain->m_Znone)//不出膠
                    {
                        MO_GummingSet(_ttol(((WorkPoint*)pParam)->GlueTime), GummingTimeOutThread);//出膠
                        while (MO_ReadGumming())
                        {
                            Sleep(1);
                        }
                        Sleep(pParameter->Glue.EndWaitTime);       
                    }

                    if (g_ThreadClose)
                    {
                        g_ThreadClose = FALSE;
                        g_pThreadRun = NULL;
                        ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                        return 0;
                    }
                    if (pMain->m_Single)
                    {
                        ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                        Sleep(1);
                        ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                        Sleep(1);
                    }
                    if (g_ThreadClose)
                    {
                        g_ThreadClose = FALSE;
                        g_pThreadRun = NULL;
                        ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                        return 0;
                    }
                    
                    /*Z軸回最高點*/
                    MO_DoZLineMove(PickUp - MO_ReadLogicPosition(2), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
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
                    if (pMain->m_Single)
                    {
                        ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                        Sleep(1);
                        ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                        Sleep(1);
                    }
                    if (g_ThreadClose)
                    {
                        g_ThreadClose = FALSE;
                        g_pThreadRun = NULL;
                        ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                        return 0;
                    }
                   
					Buff.Format(_T("%d,X:%d,Y:%d,Z:%d"), i, PointX, PointY, PointZ);
					WriteLogFile(((CHM_MachineApp*)AfxGetApp())->LogFile, _T("spot"), Buff);
				}
			}
			else    //塗膠動作
			{
				/*Z軸下降*/
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
                if (pMain->m_Single)
                {
                    ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                    Sleep(1);
                    ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                    Sleep(1);
                }
                if (g_ThreadClose)
                {
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }

                if (!pMain->m_Znone)//不出膠
                {
                    MO_GummingSet(0, GummingTimeOutThread);//出膠
                    Sleep(pParameter->Glue.BeginWaitTime);
                }
				/*移動*/
				if (Work->at(i * 3 + 2) == _T("直線"))
				{
					MO_Do2DLineMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
				}
				else
				{
					/*注意:圓速度*/
					LONG RoundCX, RoundCY;
					RoundCX = CStringToXYZ(Work->at(i * 3 + 2).Right(Work->at(i * 3 + 2).GetLength() - Work->at(i * 3 + 2).Find(_T('，')) - 1), 0);
					RoundCY = CStringToXYZ(Work->at(i * 3 + 2).Right(Work->at(i * 3 + 2).GetLength() - Work->at(i * 3 + 2).Find(_T('，')) - 1), 1);
                    Correct(RoundCX, RoundCY, CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 0), CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 2), OffSetX, OffSetY, Angle);
					MO_Do2DArcMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1),
						RoundCX - MO_ReadLogicPosition(0),
						RoundCY - MO_ReadLogicPosition(1),
						pParameter->WSpeed.End, pParameter->WSpeed.Init, CStringToXYZ(Work->at(i * 3 + 2).Right(Work->at(i * 3 + 2).GetLength() - Work->at(i * 3 + 2).Find(_T('，')) - 1), 2));
				}

				while (MO_ReadIsDriving(7)) {
					Sleep(1);//軸卡限制
				}
                if (!pMain->m_Znone)//不出膠 
                {
                    MO_FinishGumming();//關閉出膠
                    Sleep(pParameter->Glue.EndWaitTime);//斷膠後等待時間
                }

                if (g_ThreadClose)
                {
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }
                if (pMain->m_Single)
                {
                    ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                    Sleep(1);
                    ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                    Sleep(1);
                }
                if (g_ThreadClose)
                {
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }

				Buff.Format(_T("%d,X:%d,Y:%d,Z:%d"), i, PointX, PointY, PointZ);
				WriteLogFile(((CHM_MachineApp*)AfxGetApp())->LogFile, _T("Apply"), Buff);
			}
			/*對位動作*/
			if (i == 0)
			{
				/*對位點1*/
				PointX = CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 0);
				PointY = CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 2);
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
                if (pMain->m_Single)
                {
                    ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                    Sleep(1);
                    ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                    Sleep(1);
                }
                if (g_ThreadClose)
                {
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }

				Buff.Format(_T("%d,X:%d,Y:%d"), i,PointX,PointY);
				WriteLogFile(((CHM_MachineApp*)AfxGetApp())->LogFile, _T("stand1"), Buff);
                #ifdef VI
				void *PicTemp1 = malloc(2 * sizeof(void*));
				VI_Getpicture(PicTemp1);
                #endif // VI
				/*對位點2*/
				PointX = CStringToXYZ(((WorkPoint*)pParam)->StandPos2, 0);
				PointY = CStringToXYZ(((WorkPoint*)pParam)->StandPos2, 2);
				MO_Do2DLineMove(PointX - MO_ReadLogicPosition(0), PointY - MO_ReadLogicPosition(1), pParameter->WSpeed.End, pParameter->WSpeed.Add, pParameter->WSpeed.Init);
				
                while (MO_ReadIsDriving(7)) {
					Sleep(1);//軸卡限制
				}
                if (g_ThreadClose)
                {
                    VI_FreeModel(Model1);
                    VI_FreeModel(Model2);
                    VI_FreePic(PicTemp1);
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }
                if (pMain->m_Single)
                {
                    ::PostMessage(hwnd, WM_SINGLE, 0, 0);
                    Sleep(1);
                    ::PostMessage(hwnd, WM_COMMAND, IDC_BTNMAINTIMEOUT, 0);
                    Sleep(1);
                }
                if (g_ThreadClose)
                {
                    VI_FreeModel(Model1);
                    VI_FreeModel(Model2);
                    VI_FreePic(PicTemp1);
                    g_ThreadClose = FALSE;
                    g_pThreadRun = NULL;
                    ::PostMessage(hwnd, WM_WORKLIST, 0, WorkCount);
                    return 0;
                }

				Buff.Format(_T("%d,X:%d,Y:%d"), i, PointX, PointY);
				WriteLogFile(((CHM_MachineApp*)AfxGetApp())->LogFile, _T("stand2"), Buff);
                
                #ifdef VI
				void *PicTemp2 = malloc(2 * sizeof(void*));
				VI_Getpicture(PicTemp2);
				VI_FindModel(PicTemp1,PicTemp2,Model1,Model2, CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 0), CStringToXYZ(((WorkPoint*)pParam)->StandPos1, 2),
					CStringToXYZ(((WorkPoint*)pParam)->StandPos2, 0), CStringToXYZ(((WorkPoint*)pParam)->StandPos2, 2), OffSetX, OffSetY, Angle);        
				VI_FreeModel(Model1);
				VI_FreeModel(Model2);
				VI_FreePic(PicTemp1);
				VI_FreePic(PicTemp2);

				XYError *buff = new XYError;
				buff->Angle = Angle;
				buff->X = OffSetX;
				buff->Y = OffSetY;
				::PostMessage(hwnd, WM_ERRORXY, 0, (LPARAM)buff);
                #endif // VI
			} 
			::PostMessage(hwnd, WM_WORKLIST, 0, i + 1);
		}  
	}
    #endif // MOVE
    g_pThreadRun = NULL;
	return 0;
}
DWORD CMain::GummingTimeOutThread(LPVOID)
{
#ifdef MOVE
	MO_FinishGumming();
#endif // MOVE  
	return 0;
}
/*列表刷新*/
LRESULT CMain::OnListRefresh(WPARAM wParam, LPARAM lParam)
{
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取View已建立的指針
	if (lParam == 0)
	{
		m_ListCtrlWork.EnableWindow(FALSE);//關閉工作列表
		pMain->m_ProgressCtrl.SetRange(0, m_MainWorkCount - 2);//設置進度條%數
		pMain->m_ProgressCtrl.SetPos(0);//進度條歸零
		pMain->m_StatusBar.GetStatusBarCtrl().SetIcon(0, pMain->m_SBImageList.ExtractIcon(2));//工作燈運作中
		m_ListCtrlWork.SetItemState(lParam, LVIS_SELECTED, LVIS_SELECTED);//將工作點設為高亮
		m_ListCtrlWork.SetSelectionMark(lParam);//改變選中索引
		m_ListCtrlWork.EnsureVisible(lParam, FALSE);//使List中一項可見(如滾動條向下滾)
		pMain->m_ProgressCtrl.SetPos(lParam);//設置進度條進度
	} 
	else if (lParam >= m_MainWorkCount - 1)
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
LRESULT CMain::OnXYRefresh(WPARAM wParam, LPARAM lParam)
{
	CString StrBuff;
	StrBuff.Format(_T("%f"), ((XYError*)lParam)->X);
	SetDlgItemText(IDC_STAMAINXER2, StrBuff);
	StrBuff.Format(_T("%f"), ((XYError*)lParam)->Y);
	SetDlgItemText(IDC_STAMAINYER2, StrBuff); 
    StrBuff.Format(_T("%f"), ((XYError*)lParam)->Angle);
	SetDlgItemText(IDC_STAMAINANGLE2, StrBuff);
	return LRESULT();
}
LRESULT CMain::OnSetText(WPARAM wParam, LPARAM lParam)
{
    SetDlgItemText(IDC_BTNMAINTIMEOUT, _T("暫停"));
    return LRESULT();
}
/*刷新XYZ座標*/
void CMain::OnTimer(UINT_PTR nIDEvent)
{
#ifdef MOVE
	SetDlgItemInt(IDC_STAMAINX2, MO_ReadLogicPosition(0));
	SetDlgItemInt(IDC_STAMAINY2, MO_ReadLogicPosition(1));
	SetDlgItemInt(IDC_STAMAINZ2, MO_ReadLogicPosition(2));
    if (g_pThreadRun != NULL)
    {
        GetDlgItem(IDC_BTNMAINSTART)->EnableWindow(FALSE);
        GetDlgItem(IDC_BTNMAINGOORIGIN)->EnableWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_BTNMAINSTART)->EnableWindow(TRUE);
        GetDlgItem(IDC_BTNMAINGOORIGIN)->EnableWindow(TRUE);
    }
#endif //MOVE
    UpdateData(TRUE);
	CPropertyPage::OnTimer(nIDEvent);
}
/*快捷鍵*/
BOOL CMain::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_F5)
	{
		OnBnClickedBtnmainstart();
	}
	if (pMsg->wParam == VK_F6)
	{
		OnBnClickedBtnmaingoorigin();
	}
	if (pMsg->wParam == VK_F7)
	{
		OnBnClickedBtnmaintimeout();
	}
	if (pMsg->wParam == VK_F8)
	{
		OnBnClickedBtnmainstop();
	}
	/*工具提示*/
	if (m_tooltip.m_hWnd != NULL)
	{
		m_tooltip.RelayEvent(pMsg);
        m_fasttooltip.RelayEvent(pMsg);
	}
	return CPropertyPage::PreTranslateMessage(pMsg);
}
