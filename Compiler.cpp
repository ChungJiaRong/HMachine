// Compiler.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Compiler.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "HM_MachineDoc.h"
#include "HM_MachineView.h"
#include "HM_Database.h"



#define IDC_BRIEFCONTROL 10000

// CCompiler 對話方塊
IMPLEMENT_DYNAMIC(CCompiler, CPropertyPage)

CCompiler::CCompiler()
	: CPropertyPage(IDD_COMPILER)
{
}
CCompiler::~CCompiler()
{
}
void CCompiler::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LISTCOMSTAND, m_ListCtrlPos);
	DDX_Control(pDX, IDC_LISTCOMWORK, m_ListCtrlWork);
	DDX_Control(pDX, IDC_BTNCOMXUP, m_Xup);
	DDX_Control(pDX, IDC_BTNCOMXDOWN, m_Xdown);
	DDX_Control(pDX, IDC_BTNCOMYUP, m_Yup);
	DDX_Control(pDX, IDC_BTNCOMYDOWN, m_Ydown);
	DDX_Control(pDX, IDC_BTNCOMZUP, m_Zup);
	DDX_Control(pDX, IDC_BTNCOMZDOWN, m_Zdown);
    DDX_Control(pDX, IDC_EDITCOMABSVX, m_MoveX);
    DDX_Control(pDX, IDC_EDITCOMABSVY, m_MoveY);
    DDX_Control(pDX, IDC_EDITCOMABSVZ, m_MoveZ);
	CPropertyPage::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CCompiler, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BTNCOMFILENEW, &CCompiler::OnBnClickedFileNew)
	ON_BN_CLICKED(IDC_BTNCOMFILEOPEN, &CCompiler::OnBnClickedFileOpen)
	ON_BN_CLICKED(IDC_BTNCOMFILESAVE, &CCompiler::OnBnClickedFileSave)
	ON_BN_CLICKED(IDC_BTNCOMFILESAVEAS, &CCompiler::OnBnClickedFileSaveAs)

	ON_BN_CLICKED(IDC_BTNCOMWAIT, &CCompiler::OnBnClickedBtncomwait)
	ON_BN_CLICKED(IDC_BTNCOMORIGINW, &CCompiler::OnBnClickedBtncomoriginw)
    ON_BN_CLICKED(IDC_BTNCOMBETWEEN, &CCompiler::OnBnClickedBtncombetween)
	ON_BN_CLICKED(IDC_BTNCOMEND, &CCompiler::OnBnClickedBtncomend)

	ON_BN_CLICKED(IDC_BTNCOMSTANDCHK1, &CCompiler::OnBnClickedBtncomstandchk1)
	ON_BN_CLICKED(IDC_BTNCOMSTANDCHK2, &CCompiler::OnBnClickedBtncomstandchk2)
	ON_BN_CLICKED(IDC_BTNCOMPICKUP, &CCompiler::OnBnClickedBtncompickup)
	ON_BN_CLICKED(IDC_BTNCOMMOVEXYZ, &CCompiler::OnBnClickedBtncommovexyz)
	ON_BN_CLICKED(IDC_BTNCOMDISPENSING, &CCompiler::OnBnClickedBtncomdispensing)
	ON_BN_CLICKED(IDC_BTNCOMWORKFINISH, &CCompiler::OnBnClickedBtncomworkfinish)
    ON_BN_CLICKED(IDC_BTNCOMGUI, &CCompiler::OnBnClickedBtncomgui)
	
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCOMWORK, &CCompiler::OnNMDblclkListcomwork)
	ON_COMMAND(IDM_LISTMODIFY, &CCompiler::OnListmodify)
	ON_COMMAND(IDM_LISTINSERT, &CCompiler::OnListinsert)
	ON_COMMAND(IDM_LISTDELETE, &CCompiler::OnListdelete)

	ON_EN_CHANGE(IDC_EDITCOMNAME, &CCompiler::OnEnChangeEditcomname)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_EDITCOMABSVX, IDC_EDITCOMABSVZ, &CCompiler::OnEditChange)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RADCOMSPOT, IDC_RADCOMNONE, &CCompiler::OnZActionChange)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RADCOMLINE, IDC_RADCOMROUND, &CCompiler::OnMoveTypeChange)

    ON_CBN_SELENDOK(IDC_BRIEFCONTROL, &CCompiler::OnSelendokCmbcombrief)
    ON_NOTIFY(NM_CLICK, IDC_LISTCOMWORK, &CCompiler::OnNMClickListcomwork)
    ON_BN_CLICKED(IDC_BTNCOMCCDCHECK, &CCompiler::OnBnClickedBtncomccdcheck)
    ON_BN_CLICKED(IDC_BTNCOMCCDMODIFY, &CCompiler::OnBnClickedBtncomccdmodify)
    
    ON_BN_CLICKED(IDC_BTNCOMPRANT, &CCompiler::OnBnClickedBtncomprant)
    
    ON_BN_CLICKED(IDC_BTNCOMMOVERXYZ, &CCompiler::OnBnClickedBtncommoverxyz)
END_MESSAGE_MAP()
// CCompiler 訊息處理常式
BOOL CCompiler::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	CHeaderCtrl* pHeaderCtrl;
	//對位點欄初始化設定
	pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlPos.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlPos.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    m_ListCtrlPos.InsertColumn(0, _T("1"), LVCFMT_CENTER, 2, -1);
	m_ListCtrlPos.InsertColumn(1, _T("待命點(x,y,z)"), LVCFMT_CENTER, 156, -1);
    m_ListCtrlPos.InsertColumn(2, _T("對位點[1](x,y)"), LVCFMT_CENTER, 108, -1);
    m_ListCtrlPos.InsertColumn(3, _T("對位點[2](x,y)"), LVCFMT_CENTER, 108, -1);
    m_ListCtrlPos.InsertColumn(4, _T("Z軸回升點"), LVCFMT_CENTER, 68, -1);
    m_ListCtrlPos.InsertColumn(5, _T("出膠時間(𝜇s)"), LVCFMT_CENTER, 92, -1);
	//工作點欄初始化設定
	pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlWork.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlWork.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlWork.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 38, -1);
	m_ListCtrlWork.InsertColumn(1, _T("起始點(x,y)"), LVCFMT_CENTER, 108, -1);
	m_ListCtrlWork.InsertColumn(2, _T("結束點(x,y,z)"), LVCFMT_CENTER, 156, -1);
    m_ListCtrlWork.InsertColumn(3, _T("中間點(x,y)"), LVCFMT_CENTER, 108, -1);
	m_ListCtrlWork.InsertColumn(4, _T("動作"), LVCFMT_CENTER, 40, -1);
    m_ListCtrlWork.InsertColumn(5, _T("移動型態"), LVCFMT_CENTER, 60, -1); 
	//Radio初始選擇
    ((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);//選直線
	((CButton *)GetDlgItem(IDC_RADCOMSPOT))->SetCheck(TRUE);//選點膠
	((CButton *)GetDlgItem(IDC_RADCOMLS))->SetCheck(TRUE);//選低速
	/*初始化按鈕移動*/
	m_Xup.MoveX = 5000;
	m_Xdown.MoveX = -5000;
	m_Yup.MoveY = -5000;
	m_Ydown.MoveY = 5000;   
	m_Zup.MoveZ = -5000;
	m_Zdown.MoveZ = 5000;
	/*Timer刷新座標*/
	SetTimer(1, 100, 0);
    /*初始化數值*/
    InitVariable();
    /*工具提示*/
    m_tooltip.Create(this, TTS_ALWAYSTIP);  //  TTS_BALLOON | TTS_NOFADE | TTS_CLOSE
    m_tooltip.Activate(TRUE);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMFILENEW), TT_BTNCOMFILENEW);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMFILEOPEN), TT_BTNCOMFILEOPEN);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMFILESAVE), TT_BTNCOMFILESAVE);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMFILESAVEAS), TT_BTNCOMFILESAVEAS);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMMOVEXYZ), TT_BTNCOMMOVEXYZ);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMSTANDCHK1), TT_BTNCOMSTANDCHK1);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMSTANDCHK2), TT_BTNCOMSTANDCHK2);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMWAIT), TT_BTNCOMWAIT);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMPICKUP), TT_BTNBTNCOMPICKUP);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMEND), TT_BTNCOMWORKW);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMWORKFINISH), TT_BTNCOMWORKFINISH);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNCOMDISPENSING), TT_BTNCOMDISPENSING);
    m_tooltip.SetDelayTime(TTDT_INITIAL, 1000);
    m_tooltip.SetDelayTime(TTDT_AUTOPOP, 10000);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CCompiler::OnPaint()
{
	CPaintDC dc(this);
	//EDIT控件文字垂直置中
	for (int i = IDC_EDITCOMNAME; i <= IDC_EDITCOMABSVZ; i++)
	{
		EditTextVertical((CEdit*)GetDlgItem(i));
	}
#ifdef VI
	VI_ChangeWindow(GetDlgItem(IDC_PICCOMALIGNMENT));//切換顯示視窗
#endif // VI
}
void CCompiler::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	CWnd* pWnd;
	for (int i = IDC_LISTCOMWORK; i <= IDC_PICCOMALIGNMENT; i++)
	{
		pWnd = GetDlgItem(i);
		ChangeSize(pWnd, cx, cy);
	} 
	GetClientRect(&m_InitRect);
}
/*改變控件大小*/
void CCompiler::ChangeSize(CWnd* pWnd, int cx, int cy)
{
	if (pWnd)  //判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建   
	{
		CRect Rect;   //获取控件变化前的大小    
		pWnd->GetWindowRect(&Rect);
		ScreenToClient(&Rect);//将控件大小转换为在对话框中的区域坐标 
							  /*控件隨著視窗變大而變大-缺點位置會改變*/
		Rect.left = Rect.left*cx / m_InitRect.Width();//调整控件大小  
		Rect.right = Rect.right*cx / m_InitRect.Width();
		Rect.top = Rect.top*cy / m_InitRect.Height();
		Rect.bottom = Rect.bottom*cy / m_InitRect.Height();
		pWnd->MoveWindow(Rect);//设置控件大小
	}
}
/*初始數值*/
void CCompiler::InitVariable() {
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	m_ListCtrlWork.DeleteAllItems();//清除工作點列表
    m_ListCtrlPos.DeleteAllItems();//清除其他資訊列表
    m_ListCtrlPos.InsertItem(0, _T(""));//增加一行
    pView->GetDocument()->DeleteContents();//清除所有資料

    CHM_Database *pHM_Database = new CHM_Database(_T("0"));//回升點預設為0
    pView->GetDocument()->m_OtherArray.Add(pHM_Database);
    pHM_Database = new CHM_Database(_T("0"));//出膠時間預設為0
    pView->GetDocument()->m_OtherArray.Add(pHM_Database);
    pHM_Database = new CHM_Database(_T("0，0，0"), _T("0，0，0"), _T("無"), _T("直線"), _T(""));//待命點預設為0,0,0
    pView->GetDocument()->m_WorkArray.Add(pHM_Database);

    //m_ModifyRound = FALSE;//修改狀態為圓清除
    m_ModifyLock = FALSE;//修改狀態清除
    m_InsterLock = FALSE;//插入狀態清除
    m_ListWKInster = 0;//插入點計數清零
	m_ListWKCount = 1;//工作點計數清零  1是因為待命點預設0,0,0
	m_ListPSCount = 0;//對位點計數清零

    //m_DxfRate = 1;//Dxf倍率清零
    //m_DxfZdown = _T("0");//Dxf下降高度清零
    //m_RADIUS = 0;//半徑清零
    //m_SizeChoose = TRUE;//大小弧
    //m_InverseChoose = TRUE;//正反轉

	for (int i = IDC_EDITCOMNAME; i <= IDC_EDITCOMABSVZ; i++)
	{
		SetDlgItemText(i, _T(""));//清空編輯框文字
	}
}
/*料件名稱修改*/
void CCompiler::OnEnChangeEditcomname()
{
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	CString StrBuff;
	GetDlgItemText(IDC_EDITCOMNAME, StrBuff);
	pView->GetDocument()->SetTitle(StrBuff); //設置檔案標頭   
}
/*EDIT控件文字垂直置中*/
void CCompiler::EditTextVertical(CEdit *m_EditCtrl) {
	TEXTMETRIC tm;//文字型態
	CRect rect;
	CDC *pEDC = m_EditCtrl->GetDC();//獲取控建DC
	pEDC->GetTextMetrics(&tm);//獲取DC字體高度
	int nFontHeight = tm.tmHeight + tm.tmExternalLeading;//計算字體輸入的位置
	m_EditCtrl->GetClientRect(&rect);//獲取控建客戶區大小
	int offY = (rect.Height() - nFontHeight) / 2;//計算工作區域大小
	rect.OffsetRect(0, offY);//將工作區向下偏移
	m_EditCtrl->SetRectNP(&rect);//設置工作區
	ReleaseDC(pEDC);//釋放DC
}
/*Edit限制輸入*/
void CCompiler::OnEditChange(UINT uId)
{
	if (uId == IDC_EDITCOMABSVZ)
	{
		if (GetDlgItemInt(uId) >= 80000 && GetDlgItemInt(uId) <= -80000) {
			SetDlgItemInt(uId, 80000);
			((CEdit*)GetDlgItem(uId))->SetSel(5, 0);
		}
	}
	else 
    {
		if (GetDlgItemInt(uId) >= 200000 && GetDlgItemInt(uId) <= -200000) {
			SetDlgItemInt(uId, 200000);
			((CEdit*)GetDlgItem(uId))->SetSel(6, 0);
		}
	}
}
/*檔案按鈕*/
void CCompiler::OnBnClickedFileNew()
{
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_NEW, 0);
	GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(TRUE);//開啟料件名稱EDIT
	InitVariable();//變數初始化	 
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("開啟新檔"));
}
void CCompiler::OnBnClickedFileOpen()
{
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	CString StrBuff,FilePathName;

	TCHAR szFilters[] = _T("HMF Type Files (*.hmf)|*.hmf|All Files (*.*)|*.*||");
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilters);
	FileDlg.m_ofn.lpstrTitle = _T("打開我的料件"); 
	if (FileDlg.DoModal() == IDOK)
	{
        ::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_NEW, 0);
        InitVariable();//變數初始化
		FilePathName = FileDlg.GetPathName();
		AfxGetApp()->OpenDocumentFile(FilePathName);
		m_ListWKCount = pView->GetDocument()->m_WorkArray.GetSize();
		m_ListPSCount = pView->GetDocument()->m_StandArray.GetSize();
		WorkListRefresh(TRUE);//刷新列表+工作點載入m_WorkData 
		/*對位讀取*/
		for (int i = 0; i < m_ListPSCount; i++) {
            m_ListCtrlPos.SetItemText(0, i + 2, ((CHM_Database*)pView->GetDocument()->m_StandArray.GetAt(i))->m_Stand);
            m_ListCtrlPos.SetItemText(0, i + 4, ((CHM_Database*)pView->GetDocument()->m_OtherArray.GetAt(i))->m_Stand);
		}
		StrBuff = pView->GetDocument()->GetTitle();
		SetDlgItemText(IDC_EDITCOMNAME, StrBuff);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(FALSE);//關閉料件名稱EDIT
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("開啟舊檔"));
	}
	else
	{
	}
}
void CCompiler::OnBnClickedFileSave()
{
	CString oldName,newName;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
	oldName = pView->GetDocument()->GetTitle();
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_SAVE, 0);
	newName = pView->GetDocument()->GetTitle();
	if (oldName != newName) {
		SetDlgItemText(IDC_EDITCOMNAME, newName);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(FALSE);//關閉料件名稱EDIT
	}  
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("儲存檔案"));
}
void CCompiler::OnBnClickedFileSaveAs()
{
	CString oldName, newName;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
	oldName = pView->GetDocument()->GetTitle();
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_SAVE_AS, 0);
	newName = pView->GetDocument()->GetTitle();
	if (oldName != newName) {
		SetDlgItemText(IDC_EDITCOMNAME,newName);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(FALSE);//關閉料件名稱EDIT
	}
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("另存新檔"));
}
/*等待點儲存*/
void CCompiler::OnBnClickedBtncomwait()
{
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CString X, Y, Z;
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYX));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYY));
    Z.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYZ));
    CHM_Database *pHM_Database = new CHM_Database(_T("0，0，0"), X + _T("，") + Y + _T("，") + Z, _T("無"), _T("直線"),_T(""));
	/*if (!m_ListWKCount) {
		m_ListWKCount++;
		pView->GetDocument()->m_WorkArray.Add(pHM_Database);
	}
	else {
		pView->GetDocument()->m_WorkArray.SetAt(0, pHM_Database);
	}*/ //舊版待命點鎖起來
    pView->GetDocument()->m_WorkArray.SetAt(0, pHM_Database);
    WorkListRefresh(TRUE);
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("待命點寫入"));
}
/*對位點[1]儲存*/
void CCompiler::OnBnClickedBtncomstandchk1()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	CString X, Y;
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYX));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYY));
	m_ListCtrlPos.SetItemText(0, 2, X + _T("，") + Y);
    CHM_Database *pHM_Database = new CHM_Database(X + _T("，") + Y);
	if (!m_ListPSCount) {
		pView->GetDocument()->m_StandArray.Add(pHM_Database);
		m_ListPSCount++;
	}
	else {
		pView->GetDocument()->m_StandArray.SetAt(0, pHM_Database);
	}
#ifdef VI
	VI_GetModel(GetDlgItem(IDC_PICCOMALIGNMENT), GetModulePath(), _T("Model1"));
#endif //VI
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("對位點1寫入"));
}
/*對位點[2]儲存*/
void CCompiler::OnBnClickedBtncomstandchk2()
{
	CString X, Y;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	if (!m_ListPSCount) {
		MessageBox(_T("請先設定第一個對位點!"));
	}
	else {
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYX));
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYY));
		m_ListCtrlPos.SetItemText(0, 3, X + _T("，") + Y);
        CHM_Database *pHM_Database = new CHM_Database(X + _T("，") + Y);
        if (m_ListPSCount == 1)
        {
            pView->GetDocument()->m_StandArray.Add(pHM_Database);
            m_ListPSCount++;
        }
        else
        {
            pView->GetDocument()->m_StandArray.SetAt(1, pHM_Database);
        }	
#ifdef VI
		VI_GetModel(GetDlgItem(IDC_PICCOMALIGNMENT), GetModulePath(), _T("Model2"));
#endif // VI 
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("對位點2寫入"));
	}
}
/*起始點儲存or確認修改*/
void CCompiler::OnBnClickedBtncomoriginw()
{
    CString X, Y, Z, MoveType,StrBuff;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYX));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYY));
    Z.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYZ));
    if (m_ModifyLock)
    {
        if (m_OldListColumn == 1)
        {
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin = X + _T("，") + Y + _T("，") + Z;
        }
        else if (m_OldListColumn == 2)
        {
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd = X + _T("，") + Y + _T("，") + Z;
        }
        else
        {
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint = X + _T("，") + Y + _T("，") + Z;
        }
        /*半徑的可修改直線圓弧部分*/
        //if (m_ModifyRound)
        //{
        //    m_RADIUS = CStringToXYZ(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Right(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.GetLength() - 2), 0) -
        //        CStringToXYZ(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin,0);
        //    CString StrBuff = RoundDataCheck(X + _T("，") + Y + _T("，") + Z);
        //    if (StrBuff == _T("F"))
        //    {
        //        return;
        //    }
        //    MoveType = _T("圓，") + X + _T("，") + Y + _T("，1");
        //    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin = StrBuff;
        //    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd = StrBuff;
        //    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = MoveType;
        //}
        //else { //圓弧 起始結束修改 改變圓心
        //    if (ModifyArc)
        //    {
        //        CString StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd, X + _T("，") + Y + _T("，") + Z);
        //        if (StrBuff == _T("F"))
        //        {
        //            return;
        //        }
        //        MoveType = _T("圓弧，") + StrBuff;
        //        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = MoveType;
        //        ModifyArc = FALSE;
        //    }
        //    else
        //    {
        //        (m_OldListColumn == 1) ?  :
        //            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd = X + _T("，") + Y + _T("，") + Z;
        //       /* if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Find(_T("圓弧，")) + 1)
        //        {
        //            CString StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd, X + _T("，") + Y + _T("，") + Z);
        //            if (StrBuff == _T("F"))
        //            {
        //                return;
        //            }
        //            MoveType = _T("圓弧，") + StrBuff;
        //            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = MoveType;
        //        }*/
        //    }  
        //}
        /*三點可修改直線圓弧部分*/
        if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType != _T("直線"))
        {
            StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin,
                ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd,
                ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint);
            if (StrBuff == _T("F"))
            {
                return;
            }
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType
                = ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Left(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Find(_T('，')) + 1)
                + StrBuff;
        }
        MoreEnableWindows(IDC_BTNCOMFILENEW, IDC_BTNCOMWAIT, TRUE);
        MoreEnableWindows(IDC_RADCOMSPOT, IDC_RADCOMROUND, TRUE);
        ((CButton *)GetDlgItem(IDC_RADCOMSPOT))->SetCheck(TRUE);
        ((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);
        SetDlgItemText(IDC_BTNCOMORIGINW, _T("起始點"));
        SetDlgItemText(IDC_BTNCOMEND, _T("結束點"));
        m_Static.DestroyWindow();
        m_ModifyLock = FALSE;
        WorkListRefresh(FALSE);
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("修改完成"));
    }
    else
    {
        if (m_ListWKCount && m_ListWKCount < 100000) {
            if (m_InsterLock)   //插入
            {
                ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin = X + _T("，") + Y + _T("，") + Z;
            }
            else  //新增
            {
                CHM_Database *pHM_Database = new CHM_Database(X + _T("，") + Y + _T("，") + Z, _T(""), _T(""), _T(""),_T(""));
                if (pView->GetDocument()->m_WorkArray.GetCount() != m_ListWKCount + 1)
                {
                    pView->GetDocument()->m_WorkArray.Add(pHM_Database);
                }
                else {
                    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin = X + _T("，") + Y + _T("，") + Z;
                }
            }
            WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("起始點寫入"));
        }
        else {
            if (m_ListWKCount == 100000)
                MessageBox(_T("工作點已滿!"));
            else
                MessageBox(_T("請先設定待命點!"));
        }
        WorkListRefresh(TRUE);
    }  
}
/*圓/圓弧中間點*/
void CCompiler::OnBnClickedBtncombetween()
{
    CString X, Y, Z, MoveType, ZAction, StrBuff;
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    //獲取XY座標
    X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYX));
    Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYY));
    Z.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYZ));
    if (m_ListWKCount && m_ListWKCount < 100000) {
        if (m_InsterLock) //插入
        {
            if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin == _T(""))//判斷插入的原點是否有設
            {
                ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin
                    = ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster - 1))->m_ptOrigin;
            }
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint = X + _T("，") + Y + _T("，") + Z;
            WorkListRefresh(FALSE);
        }
        else //新增
        {
            if (pView->GetDocument()->m_WorkArray.GetCount() == m_ListWKCount)//沒有按起始儲存
            {
                CHM_Database *pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount - 1))->m_ptEnd, _T(""), _T(""), _T(""), X + _T("，") + Y + _T("，") + Z);
                pView->GetDocument()->m_WorkArray.Add(pHM_Database);
            }
            else
            {
                ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint = X + _T("，") + Y + _T("，") + Z;
            }
            WorkListRefresh(TRUE);
        }
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("中間點寫入"));
    }
    else {
        if (m_ListWKCount == 100000)
            MessageBox(_T("工作點已滿!"));
        else
            MessageBox(_T("請先設定待命點!"));
    }
    
}
/*結束點儲存or取消修改*/
void CCompiler::OnBnClickedBtncomend()
{
    CString X, Y, Z, MoveType, ZAction, StrBuff;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CHM_Database *pHM_Database;
	//獲取XY座標
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYX));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYY));
    Z.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYZ));
    if (m_ModifyLock)//修改
    {
        /*可修改直線圓弧部分*/
        /*if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType == _T(""))
        {
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = _T("直線");
            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint = _T("");
        }*/
        MoreEnableWindows(IDC_BTNCOMFILENEW, IDC_BTNCOMWAIT, TRUE);
        MoreEnableWindows(IDC_RADCOMSPOT, IDC_RADCOMROUND, TRUE);
        ((CButton *)GetDlgItem(IDC_RADCOMSPOT))->SetCheck(TRUE);
        ((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);
        SetDlgItemText(IDC_BTNCOMORIGINW, _T("起始點"));
        SetDlgItemText(IDC_BTNCOMEND, _T("結束點"));
        m_Static.DestroyWindow();
        m_ModifyLock = FALSE;
        WorkListRefresh(FALSE);
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("修改取消"));
    }
    else
    {
        if (m_ListWKCount && m_ListWKCount < 100000) {
            switch (GetCheckedRadioButton(IDC_RADCOMSPOT, IDC_RADCOMNONE)) {
            case IDC_RADCOMSPOT:
                ZAction = _T("點膠");
                break;
            case IDC_RADCOMAPPLY:
                ZAction = _T("塗膠");
                break;
            case IDC_RADCOMNONE:
                ZAction = _T("無");
                break;
            default://防呆用
                MessageBox(_T("程式出現錯誤"));
                ((CButton *)GetDlgItem(IDC_RADCOMSPOT))->SetCheck(TRUE);
                break;
            }
            switch (GetCheckedRadioButton(IDC_RADCOMLINE, IDC_RADCOMROUND))
            {
            case IDC_RADCOMLINE:
                MoveType = _T("直線");
                break;
            case IDC_RADCOMARC:
                /*兩點加半徑*/
                /*if (pView->GetDocument()->m_WorkArray.GetCount() == m_ListWKCount)
                {
                StrBuff = ArcDataCheck(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount - 1))->m_ptEnd, X + _T("，") + Y + _T("，") + Z);//
                }
                else
                {
                StrBuff = ArcDataCheck(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin, X + _T("，") + Y + _T("，") + Z);
                }*/
                /*三點*/
                if (m_InsterLock)//在插入狀態中
                {
                    if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint == _T(""))//沒按中間點
                    {
                        MessageBox(_T("請先設定中間點"));
                        return;
                    }
                    StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin,
                        X + _T("，") + Y + _T("，") + Z, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint);
                }
                else //在新增狀態
                {
                    if (pView->GetDocument()->m_WorkArray.GetCount() == m_ListWKCount || 
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint == _T(""))  //沒設中間點
                    {
                        MessageBox(_T("請先設定中間點"));
                        return;
                    }
                    StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin, X + _T("，") + Y + _T("，") + Z,
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint); 
                }
                if (StrBuff == _T("F"))
                {
                    return;
                }
                MoveType = _T("圓弧，") + StrBuff;
                break;
            case IDC_RADCOMROUND:
                /*圓心加半徑*/
                //StrBuff = RoundDataCheck(X + _T("，") + Y + _T("，") + Z);
                /*三點*/ 
                if (m_InsterLock)
                {
                    if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint == _T("")) //沒按中間點也沒按起始點
                    {
                        MessageBox(_T("請先設定中間點"));
                        return;
                    }
                    StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin,
                        X + _T("，") + Y + _T("，") + Z, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint);
                }
                else
                {
                    if (pView->GetDocument()->m_WorkArray.GetCount() == m_ListWKCount ||
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint == _T("")) //沒按中間點也沒按起始點
                    {
                        MessageBox(_T("請先設定中間點"));
                        return;
                    }
                    StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin, X + _T("，") + Y + _T("，") + Z,
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint);
                }
                if (StrBuff == _T("F"))
                {
                    return;
                }
                MoveType = _T("圓，") + StrBuff;
                break;
            default: //防呆用
                MessageBox(_T("程式出現錯誤"));
                ((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);
                break;
            }
            int iLength = MoveType.Find(_T('，'));//用來判斷圓弧或圓
            if (m_InsterLock)
            {
                if (MoveType.Left(iLength) == _T("圓"))//判斷如果是存圓
                {             
                    pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin
                        , ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin, ZAction, MoveType,
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint);
                    pView->GetDocument()->m_WorkArray.SetAt(m_ListWKInster, pHM_Database);         
                }
                else if(MoveType.Left(iLength) == _T("圓弧"))
                {
                    pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin
                        , X + _T("，") + Y + _T("，") + Z, ZAction, MoveType,
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ThreePoint);
                    pView->GetDocument()->m_WorkArray.SetAt(m_ListWKInster, pHM_Database);
                }
                else  //直線
                {
                    if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin != _T(""))
                    {
                        pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster))->m_ptOrigin,
                            X + _T("，") + Y + _T("，") + Z, ZAction, MoveType,_T(""));
                    }
                    else
                    {
                        pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKInster - 1))->m_ptEnd,
                            X + _T("，") + Y + _T("，") + Z, ZAction, MoveType,_T(""));
                    }
                    pView->GetDocument()->m_WorkArray.SetAt(m_ListWKInster,pHM_Database);
                }
                m_ListWKInster = 0;
                m_InsterLock = FALSE;
                MoreEnableWindows(IDC_BTNCOMFILENEW, IDC_BTNCOMWAIT, TRUE);//新增到等待點的按鈕都打開
                WorkListRefresh(FALSE);
                WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("新增成功"));
            }
            else
            {
                if (MoveType.Left(iLength) == _T("圓"))
                {
                    pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin
                        , ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin, ZAction, MoveType,
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint);
                    pView->GetDocument()->m_WorkArray.SetAt(m_ListWKCount, pHM_Database);
                }
                else if (MoveType.Left(iLength) == _T("圓弧"))
                {
                    pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin
                        , X + _T("，") + Y + _T("，") + Z, ZAction, MoveType,
                        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ThreePoint);
                    pView->GetDocument()->m_WorkArray.SetAt(m_ListWKCount, pHM_Database);
                }
                else
                {
                    if (pView->GetDocument()->m_WorkArray.GetCount() != m_ListWKCount) //成立代表已經新增
                    {
                        pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount))->m_ptOrigin,
                            X + _T("，") + Y + _T("，") + Z, ZAction, MoveType, _T(""));
                        pView->GetDocument()->m_WorkArray.SetAt(m_ListWKCount,pHM_Database);
                    }
                    else
                    {
                        pHM_Database = new CHM_Database(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_ListWKCount - 1))->m_ptEnd,
                            X + _T("，") + Y + _T("，") + Z, ZAction, MoveType, _T(""));
                        pView->GetDocument()->m_WorkArray.Add(pHM_Database);
                    }
                }
                WorkListRefresh(TRUE);
                WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("結束點寫入"));
            }
            m_ListWKCount++;// 插入完畢工作點也要加1
        }
        else {
            if (m_ListWKCount == 100000)
                MessageBox(_T("工作點已滿!"));
            else
                MessageBox(_T("請先設定待命點!"));
        }
    }
}
/*Z軸回升點儲存*/
void CCompiler::OnBnClickedBtncompickup()
{
    CString Z;
    Z.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMCURRENTLYZ));
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CHM_Database *pHM_Database = new CHM_Database(Z);
    pView->GetDocument()->m_OtherArray.SetAt(0, pHM_Database);
    m_ListCtrlPos.SetItemText(0, 4, Z);
}
/*絕對位置移動(XYZ軸移動)*/
void CCompiler::OnBnClickedBtncommovexyz()
{      
    CString StrBuff;
    for (int i = IDC_EDITCOMABSVX; i <= IDC_EDITCOMABSVZ; i++)
    {
        GetDlgItemText(i, StrBuff);
        if (StrBuff.Find(L'-') + 1) {
            MessageBox(L"絕對座標沒有負值");
            return;
        }
    }
#ifdef MOVE
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
	switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
	{
	case IDC_RADCOMHS:
		MO_Do3DLineMove(GetDlgItemInt(IDC_EDITCOMABSVX) - MO_ReadLogicPosition(0),
			GetDlgItemInt(IDC_EDITCOMABSVY) - MO_ReadLogicPosition(1), 0,
			pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
		Sleep(1);//防止軸卡出錯
		MO_Do3DLineMove(0,0,GetDlgItemInt(IDC_EDITCOMABSVZ) - MO_ReadLogicPosition(2),
			pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
		break;
	case IDC_RADCOMMS:
		MO_Do3DLineMove(GetDlgItemInt(IDC_EDITCOMABSVX) - MO_ReadLogicPosition(0),
			GetDlgItemInt(IDC_EDITCOMABSVY) - MO_ReadLogicPosition(1),0,
			pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
		Sleep(1);//防止軸卡出錯
		MO_Do3DLineMove(0,0,GetDlgItemInt(IDC_EDITCOMABSVZ) - MO_ReadLogicPosition(2),
			pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
		break;
	case IDC_RADCOMLS:
		MO_Do3DLineMove(GetDlgItemInt(IDC_EDITCOMABSVX) - MO_ReadLogicPosition(0),
			GetDlgItemInt(IDC_EDITCOMABSVY) - MO_ReadLogicPosition(1),0,
			pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
		Sleep(1);//防止軸卡出錯
		MO_Do3DLineMove(0,0,GetDlgItemInt(IDC_EDITCOMABSVZ) - MO_ReadLogicPosition(2),
			pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
#endif // MOVE
#ifndef MOVE
	SetDlgItemInt(IDC_EDITCOMCURRENTLYX, GetDlgItemInt(IDC_EDITCOMABSVX));
	SetDlgItemInt(IDC_EDITCOMCURRENTLYY, GetDlgItemInt(IDC_EDITCOMABSVY));
	SetDlgItemInt(IDC_EDITCOMCURRENTLYZ, GetDlgItemInt(IDC_EDITCOMABSVZ));
#endif //NOMOVE
	StrBuff.Format(_T("絕對位置移動至(%d,%d,%d)"), GetDlgItemInt(IDC_EDITCOMABSVX), GetDlgItemInt(IDC_EDITCOMABSVY), GetDlgItemInt(IDC_EDITCOMABSVZ));
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), StrBuff);
}
/*相對位置移動(XYZ軸移動)*/
void CCompiler::OnBnClickedBtncommoverxyz()
{
#ifdef MOVE
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
    CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
    switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
    {
    case IDC_RADCOMHS:
        MO_Do3DLineMove(GetDlgItemInt(IDC_EDITCOMABSVX),
            GetDlgItemInt(IDC_EDITCOMABSVY), 0,
            pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
        Sleep(1);//防止軸卡出錯
        MO_Do3DLineMove(0, 0, GetDlgItemInt(IDC_EDITCOMABSVZ),
            pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
        break;
    case IDC_RADCOMMS:
        MO_Do3DLineMove(GetDlgItemInt(IDC_EDITCOMABSVX),
            GetDlgItemInt(IDC_EDITCOMABSVY), 0,
            pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
        Sleep(1);//防止軸卡出錯
        MO_Do3DLineMove(0, 0, GetDlgItemInt(IDC_EDITCOMABSVZ),
            pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
        break;
    case IDC_RADCOMLS:
        MO_Do3DLineMove(GetDlgItemInt(IDC_EDITCOMABSVX),
            GetDlgItemInt(IDC_EDITCOMABSVY), 0,
            pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
        Sleep(1);//防止軸卡出錯
        MO_Do3DLineMove(0, 0, GetDlgItemInt(IDC_EDITCOMABSVZ),
            pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
        break;
    default:
        MessageBox(_T("程式出現錯誤!"));
        break;
    }
#endif // MOVE 
    CString StrBuff;
    StrBuff.Format(_T("相對位置移動至(%d,%d,%d)"), GetDlgItemInt(IDC_EDITCOMABSVX), GetDlgItemInt(IDC_EDITCOMABSVY), GetDlgItemInt(IDC_EDITCOMABSVZ));
    WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), StrBuff);
}
/*工作列表刷新*/
void CCompiler::WorkListRefresh(BOOL ScrollBarRefresh) {
	CString StrBuff;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	m_ListCtrlWork.DeleteAllItems();
    int nCount = pView->GetDocument()->m_WorkArray.GetSize();
    if (nCount)
    {
        m_ListCtrlPos.SetItemText(0, 1, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(0))->m_ptEnd);
    }
	for (int i = 1; i < nCount; i++) {
		m_ListCtrlWork.InsertItem(i, NULL);
		(i>9)?StrBuff.Format(_T("0%d"), i):StrBuff.Format(_T("00%d"), i);
		m_ListCtrlWork.SetItemText(i-1, 0, StrBuff);
        m_ListCtrlWork.SetItemText(i - 1, 1, CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptOrigin,3));
        m_ListCtrlWork.SetItemText(i - 1, 2, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptEnd);
        m_ListCtrlWork.SetItemText(i - 1, 3, CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ThreePoint,3));
        m_ListCtrlWork.SetItemText(i - 1, 4, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_Action);
        int iLength = ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_MoveType.Find(_T('，'));
        if (iLength == -1)
            iLength = 2;
        m_ListCtrlWork.SetItemText(i - 1, 5, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_MoveType.Left(iLength));
		/*刷新ScrollBar*/
		int nMin, nMax;
		if (ScrollBarRefresh)
		{   
			m_ListCtrlWork.GetScrollRange(SB_VERT, &nMin, &nMax);
			m_ListCtrlWork.SetScrollPos(SB_VERT, nMax);
			m_ListCtrlWork.EnsureVisible(m_ListCtrlWork.GetItemCount() - 1, FALSE);//使List中一項可見(如滾動條向下滾)
		}    
	}
}
/*0.1秒刷新XYZ*/
void CCompiler::OnTimer(UINT_PTR nIDEvent)
{
#ifdef MOVE
    SetDlgItemInt(IDC_EDITCOMCURRENTLYX, MO_ReadLogicPosition(0));
    SetDlgItemInt(IDC_EDITCOMCURRENTLYY, MO_ReadLogicPosition(1));
    SetDlgItemInt(IDC_EDITCOMCURRENTLYZ, MO_ReadLogicPosition(2));
#endif // MOVE
	CPropertyPage::OnTimer(nIDEvent);
}

/*左鍵點兩下出現菜單*/
void CCompiler::OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	CListCtrl *CList = (CListCtrl *)GetDlgItem(IDC_LISTCOMWORK);
	CMenu menu, *pSubMenu;
	CPoint CurPnt;
	int ItemCount = m_ListCtrlWork.GetItemCount();//獲取項目總數
    NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
    if (pEditCtrl->iItem == -1 || pEditCtrl->iSubItem == 0 || m_ModifyLock || m_InsterLock || pView->GetDocument()->m_WorkArray.GetCount() != m_ListWKCount || pEditCtrl->iSubItem == 5)  //不在表單上或新增修改中
    {
        if (m_Combobox.GetSafeHwnd())
        {
            m_Combobox.DestroyWindow(); 
        }
    }
    else //在表單上
    {
        if (pEditCtrl->iSubItem != 4)
        { 
            if (m_Combobox.GetSafeHwnd())  //如果combobox已創建，創建
            {
                m_Combobox.DestroyWindow();
            }
            m_OldListRow = pEditCtrl->iItem;
            m_OldListColumn = pEditCtrl->iSubItem;
            int iLength = ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Find(_T("，"));
            menu.LoadMenu(IDR_LISTPOPMENU);//加入菜單
            pSubMenu = menu.GetSubMenu(0);
            if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Left(2) == _T("直線") && pEditCtrl->iSubItem == 3)
            {
                pSubMenu->EnableMenuItem(IDM_LISTMODIFY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//直線不能修改第三點
            }
            else if(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Left(iLength) == _T("圓"))
            {
                pSubMenu->EnableMenuItem(IDM_LISTMODIFY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//直線不能修改第三點
            }
            GetCursorPos(&CurPnt);
            pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, CurPnt.x, CurPnt.y, this);//點右鍵出現的菜單位置

   
            //if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(pEditCtrl->iItem + 1))->m_MoveType.Left(2) == _T("圓，"))
            //{
            //    pSubMenu->ModifyMenu(0, MF_BYPOSITION, IDM_LISTMODIFY, _T("修改圓心"));
            //    m_OldListColumn = 2;
            //    //m_ModifyRound = TRUE;
            //}
            //if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(pEditCtrl->iItem + 1))->m_MoveType.Left(3) == _T("圓弧，"))
            //{
            //    pSubMenu->EnableMenuItem(IDM_LISTMODIFY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//圓弧不能修改
            //    //(ItemCount>1) ? pSubMenu->EnableMenuItem(IDM_LISTDELETE, MF_BYCOMMAND | MF_ENABLED)
            //    //    : pSubMenu->EnableMenuItem(IDM_LISTDELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);//第一筆不能刪
            //}  
        }
        else //代表選到"工作方式"
        {
            if (m_Combobox.GetSafeHwnd()) //條件二:是否創建combobox
            {
                if (!(m_OldListRow == pEditCtrl->iItem && m_OldListColumn == pEditCtrl->iSubItem)) //條件三:是否按的為同一格
                {
                    m_Combobox.DestroyWindow();
                    CreateCombo(pEditCtrl, &m_Combobox);
                }
                else//點選之前創建好的  
                {
                    m_Combobox.SetFocus();//設置為焦點   
                }
            }
            else //還沒創建combobox
            {
                CreateCombo(pEditCtrl, &m_Combobox);
            }
        }
    }
	*pResult = 0;
}
/*列表點左鍵一次*/
void CCompiler::OnNMClickListcomwork(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    // TODO: 在此加入控制項告知處理常式程式碼
    NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
    if (m_Combobox.GetSafeHwnd())
    {
        if (!(m_OldListRow == pEditCtrl->iItem && m_OldListColumn == pEditCtrl->iSubItem)) //條件三:是否按的為同一格
        {
            m_Combobox.DestroyWindow();
        }
    }
    *pResult = 0;
}
/*菜單修改*/
void CCompiler::OnListmodify()
{
    MoreEnableWindows(IDC_BTNCOMFILENEW, IDC_BTNCOMWAIT, FALSE);//關閉按鈕
    GetDlgItem(IDC_BTNCOMBETWEEN)->EnableWindow(FALSE);//關閉中間點按鈕
    for (int i = IDC_RADCOMSPOT; i <= IDC_RADCOMROUND; i++)
    {
        GetDlgItem(i)->EnableWindow(FALSE);
        ((CButton *)GetDlgItem(i))->SetCheck(FALSE);     
    }
    SetDlgItemText(IDC_BTNCOMORIGINW, _T("確認修改"));
    SetDlgItemText(IDC_BTNCOMEND, _T("取消修改"));
    CreateStatic(&m_Static);
    m_ModifyLock = TRUE;
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("修改工作點"));
}
/*菜單插入*/
void CCompiler::OnListinsert()
{
	int istat = m_ListCtrlWork.GetSelectionMark() + 1;//獲取選擇的項
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	if (m_ListWKCount < 100000)//避免沒有工作點和大於100000點時
	{
        CHM_Database *pHM_Database = new CHM_Database(_T(""),_T(""),_T(""),_T(""),_T(""));
        pView->GetDocument()->m_WorkArray.InsertAt(istat,pHM_Database);//List插入項目
        m_ListWKInster = istat;
        m_InsterLock = TRUE;
        MoreEnableWindows(IDC_BTNCOMFILENEW, IDC_BTNCOMWAIT, FALSE);//關閉按鈕
		WorkListRefresh(FALSE);
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("插入工作點"));
	}
	else
	{   
	    MessageBox(_T("工作點已滿!"));
	}
}
/*菜單刪除*/
void CCompiler::OnListdelete()
{
	int istat = m_ListCtrlWork.GetSelectionMark()+1;//獲取選擇的項
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	pView->GetDocument()->m_WorkArray.RemoveAt(istat);//從資料庫中移除
	m_ListCtrlWork.DeleteItem(istat);//刪除List項目
	m_ListWKCount--;
	WorkListRefresh(FALSE);
	WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("刪除工作點"));
}
/*創建ComboBox*/
void CCompiler::CreateCombo(NM_LISTVIEW  *pEditCtrl, CComboBox *m_Combobox1)
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
    //點處理
    m_OldListRow = pEditCtrl->iItem;
    m_OldListColumn = pEditCtrl->iSubItem;
    //創建ComboBox
    m_Combobox1->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_BRIEFCONTROL);
    m_Combobox1->SetParent(&m_ListCtrlWork); //設定父視窗  
    m_Combobox1->SetFont(this->GetFont(), FALSE);  //字體 
    CRect  EditRect; //宣告框框
    m_ListCtrlWork.GetSubItemRect(m_OldListRow, m_OldListColumn, LVIR_LABEL, EditRect);
    EditRect.SetRect(EditRect.left, EditRect.top - 1, EditRect.left + m_ListCtrlWork.GetColumnWidth(m_OldListColumn), EditRect.bottom - 1); //調整格子大小
    m_Combobox1->MoveWindow(&EditRect); //將編輯框放在滑鼠點擊位置上
    CString strItem = m_ListCtrlWork.GetItemText(m_OldListRow, m_OldListColumn);  //獲得格子上資訊
    m_Combobox1->SetWindowText(strItem); //print在格子上 
    m_Combobox1->AddString(L"點膠");
    m_Combobox1->AddString(L"塗膠");
    m_Combobox1->AddString(L"無");
    /*可修改直線圓弧部分*/
    //if (m_OldListColumn = 4)
    //{   
    //    /*int iLength = ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Find(_T("，"));
    //    if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Left(iLength) == _T("圓"))
    //    {
    //        m_Combobox1->AddString(L"圓");
    //    }
    //    else
    //    {
    //        m_Combobox1->AddString(L"直線");
    //        m_Combobox1->AddString(L"圓弧");
    //    }*/
    //    m_Combobox1->AddString(L"直線");
    //    m_Combobox1->AddString(L"圓弧");
    //    m_Combobox1->AddString(L"圓");
    //}
    //else
    //{
    //    m_Combobox1->AddString(L"點膠");
    //    m_Combobox1->AddString(L"塗膠");
    //    m_Combobox1->AddString(L"無");
    //}  
    m_Combobox1->ShowDropDown();
    m_Combobox1->ShowWindow(SW_SHOW); //顯示編輯框
}
/*Combobox選擇*/
void CCompiler::OnSelendokCmbcombrief() {
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
    CString StrBuff,RoundC;
    m_Combobox.GetLBText(m_Combobox.GetCurSel(),StrBuff);
    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_Action = StrBuff;
    /*可修改直線圓弧部分*/
    //if (StrBuff == _T("直線"))
    //{
    //    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = StrBuff;
    //    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint = _T("");
    //}
    //else if (StrBuff == _T("圓弧"))
    //{
    //    /*兩點加半徑*/
    //    /*CComRound Open;
    //    if (Open.DoModal() == IDOK)
    //    {
    //       
    //        StrBuff = ArcDataCheck(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin, ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd);
    //        if (StrBuff == _T("F"))
    //        {
    //            m_Combobox.DestroyWindow();
    //            return;
    //        }
    //        else
    //        {
    //            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = _T("圓弧，") + StrBuff;
    //        } 
    //    } */ 
    //    /*三點*/
    //    if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint == _T(""))
    //    {
    //        m_ListCtrlWork.SetItemText(m_OldListRow, m_OldListColumn, _T("圓弧，"));
    //        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = _T("圓弧，");
    //        m_OldListColumn = 3;
    //        OnListmodify();     
    //    }
    //    else
    //    {
    //        StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin
    //            , ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd
    //            ,((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint);
    //        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = _T("圓弧，") + StrBuff;
    //    }
    //}
    //else if (StrBuff == _T("圓"))
    //{
    //    /*兩點加半徑*/
    //    /*
    //    CComRound Open;
    //    if (Open.DoModal() == IDOK)
    //    {
    //        RoundC.Format(_T("%d，%d，%d"),
    //            CStringToXYZ(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Right(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.GetLength() - 2), 0),
    //            CStringToXYZ(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.Right(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType.GetLength() - 2), 1),
    //            CStringToXYZ(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd, 2));
    //        StrBuff = RoundDataCheck(RoundC);
    //        if (StrBuff == _T("F"))
    //        {
    //            m_Combobox.DestroyWindow();
    //            WorkListRefresh(FALSE);
    //            return;
    //        }
    //        else
    //        {
    //            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin = StrBuff;
    //            ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd = StrBuff;
    //        }
    //    } */
    //    /*三點*/
    //    if (((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint == _T(""))
    //    {
    //        m_ListCtrlWork.SetItemText(m_OldListRow, m_OldListColumn, _T("圓，"));
    //        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = _T("圓，");
    //        OnListmodify();
    //    }
    //    else
    //    {
    //        StrBuff = TRoundCCalculation(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin
    //            , ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd
    //            , ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ThreePoint);
    //        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_MoveType = _T("圓，") + StrBuff;
    //        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptEnd
    //            = ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_ptOrigin;
    //    }
    //}
    //else
    //{
    //    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(m_OldListRow + 1))->m_Action = StrBuff;
    //}
    m_Combobox.DestroyWindow();
    WorkListRefresh(FALSE);
}
/*創建Static、並修改編輯框文字*/
void CCompiler::CreateStatic(CStatic *m_Static)
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
    m_Static->Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE | SS_SUNKEN , CRect(0, 0, 0, 0), this, IDC_BRIEFCONTROL);
    m_Static->SetParent(&m_ListCtrlWork); //設定父視窗  
    m_Static->SetFont(this->GetFont(), FALSE);  //字體
    CRect  EditRect; //宣告框框
    m_ListCtrlWork.GetSubItemRect(m_OldListRow, m_OldListColumn, LVIR_LABEL, EditRect);
    EditRect.SetRect(EditRect.left, EditRect.top - 1, EditRect.left + m_ListCtrlWork.GetColumnWidth(m_OldListColumn), EditRect.bottom - 1); //調整格子大小
    m_Static->MoveWindow(&EditRect); //將編輯框放在滑鼠點擊位置上
    CString strItem = m_ListCtrlWork.GetItemText(m_OldListRow, m_OldListColumn);  //獲得格子上資訊
    m_Static->SetWindowText(strItem);
    strItem = strItem + _T("，");
    SetDlgItemInt(IDC_EDITCOMABSVX, CStringToXYZ(strItem, 0));
    SetDlgItemInt(IDC_EDITCOMABSVY, CStringToXYZ(strItem, 1));
    SetDlgItemInt(IDC_EDITCOMABSVZ, CStringToXYZ(strItem, 2));
}

/*鍵盤響應事件*/
BOOL CCompiler::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_LEFT) {
			MoveXYZ(-5000, 0, 0);
		}
		if (pMsg->wParam == VK_RIGHT) {
			MoveXYZ(5000, 0, 0);
		}
		if (pMsg->wParam == VK_UP) {
			MoveXYZ(0, -5000, 0);
		}
		if (pMsg->wParam == VK_DOWN) {
			MoveXYZ(0, 5000, 0);
		}
		if (pMsg->wParam == VK_HOME) {
			MoveXYZ(0, 0, -5000);
		}
		if (pMsg->wParam == VK_END) {
			MoveXYZ(0, 0, 5000);
		}
		if (pMsg->wParam == VK_TAB) {
			CWnd *mwnd = GetNextDlgTabItem(GetFocus());//取得当前焦点控件的下一个控件的句柄
			if (mwnd)
			{
				mwnd->SetFocus();        //设置下一件控件得到输入焦点
				return TRUE;
			}
		}
		if (pMsg->wParam == VK_RETURN) {
			return TRUE;
		}
	}
	if (pMsg->message == WM_KEYUP) {
		if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT
			|| pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN
			|| pMsg->wParam == VK_HOME || pMsg->wParam == VK_END) {
#ifdef MOVE
			MO_DecSTOP();
#endif // MOVE
		}
	}
    /*工具提示*/
    if (m_tooltip.m_hWnd != NULL)
    {
        m_tooltip.RelayEvent(pMsg);
    }
	return CPropertyPage::PreTranslateMessage(pMsg);
}
/*XYZ鍵盤移動*/
void CCompiler::MoveXYZ(int MoveX,int MoveY,int MoveZ) {	
#ifdef MOVE
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	CParameter* pParameter = (CParameter*)pView->m_DlgArray.GetAt(2);
	switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
	{
	case IDC_RADCOMHS:
		MO_Do3DLineMove(MoveX, MoveY, MoveZ, pParameter->HSpeed.End, pParameter->HSpeed.Add, pParameter->HSpeed.Init);
		break;
	case IDC_RADCOMMS:
		MO_Do3DLineMove(MoveX, MoveY, MoveZ, pParameter->MSpeed.End, pParameter->MSpeed.Add, pParameter->MSpeed.Init);
		break;
	case IDC_RADCOMLS:
		MO_Do3DLineMove(MoveX, MoveY, MoveZ, pParameter->LSpeed.End, pParameter->LSpeed.Add, pParameter->LSpeed.Init);
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
#endif // MOVE
}

/*出膠系統*/
void CCompiler::OnBnClickedBtncomdispensing()
{
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
	CGlueEdit gluedit;
    gluedit.SetBackgroundColor(RGB(255, 255, 0));
	if (gluedit.DoModal() == IDOK)
	{
        m_ListCtrlPos.SetItemText(0, 5, ((CHM_Database*)pView->GetDocument()->m_OtherArray.GetAt(1))->m_Stand);
	}
}
/*編輯完成載入料件*/
void CCompiler::OnBnClickedBtncomworkfinish()
{
	if (m_ListPSCount <= 1 || m_ListWKCount < 1)
	{
		MessageBox(_T("請設定對位點和工作點!"));
	}
	else
	{
		if (MessageBox(_T("你確定要載入料件?"), _T("詢問"), MB_ICONINFORMATION | MB_OKCANCEL) == IDOK) {
			CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
			CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
            int WorkCount = DataToWorkData();//工作點修正
			CFile File;
			if (File.Open(GetModulePath()+_T("Inprocess.txt"), CFile::modeCreate | CFile::modeWrite)) {
				CArchive ar(&File, CArchive::store);
                ar << ((CHM_Database*)pView->GetDocument()->m_StandArray.GetAt(0))->m_Stand //對位點1
                    << ((CHM_Database*)pView->GetDocument()->m_StandArray.GetAt(1))->m_Stand //對位點2
                    << ((CHM_Database*)pView->GetDocument()->m_OtherArray.GetAt(0))->m_Stand //回升高度
                    << ((CHM_Database*)pView->GetDocument()->m_OtherArray.GetAt(1))->m_Stand //出膠時間
                    << WorkCount;//工作數量
				for (int i = 0; i < WorkCount * 3; i++) {
					ar << m_WorkData.at(i);
				}
			}
			File.Close();
			pView->m_MainDataUP = TRUE;//刷新MainWorkList
			pView->m_DlgArray[pView->m_TabCtrl->GetCurSel()]->ShowWindow(SW_HIDE);//隱藏此頁面
			CRect TabClientR;
			pView->m_TabCtrl->GetClientRect(&TabClientR);//獲取tabctrl客戶區大小
			pView->m_DlgArray[0]->SetWindowPos(
				NULL,
				TabClientR.left + 1, TabClientR.top + 25, TabClientR.right - 1, TabClientR.bottom - 25,
				SWP_SHOWWINDOW);//顯示主頁
			pView->m_TabCtrl->SetCurSel(0);//設置索引
			pView->m_DlgArray[0]->SetFocus();//設置焦點
			WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("料件編輯"), _T("載入料件"));
		}
	}
}
/*圖形化編輯*/
void CCompiler::OnBnClickedBtncomgui()
{
}
/*示意圖*/
void CCompiler::OnBnClickedBtncomprant()
{
    CPrint Print;
    if (Print.DoModal())
    {
        MessageBox(_T("示意圖已關閉"));
    }
}
/*CCD校正和確定移入區域一*/
void CCompiler::OnBnClickedBtncomccdmodify()
{
    CString StrBuff;
    GetDlgItemText(IDC_BTNCOMCCDMODIFY, StrBuff);
    if (StrBuff == _T("CCD校正"))
    {
        #ifdef VI
        ModeChange(GetDlgItem(IDC_PICCOMALIGNMENT));
        #endif // VI
        SetDlgItemText(IDC_BTNCOMCCDMODIFY,_T("確定移入區域一"));
    }
    else
    { 
        #ifdef VI
        ConversionModel1 = malloc(2 * sizeof(void*));
        LocateDefine(GetDlgItem(IDC_PICCOMALIGNMENT), ConversionModel1);
        ConversionModel1X = MO_ReadLogicPosition(0);
        ConversionModel1Y = MO_ReadLogicPosition(1);
        #endif // VI
        GetDlgItem(IDC_BTNCOMCCDCHECK)->EnableWindow(TRUE);
    }
}
/*確定移入區域二*/
void CCompiler::OnBnClickedBtncomccdcheck()
{
    #ifdef VI
    GetRelation(GetDlgItem(IDC_PICCOMALIGNMENT), ConversionModel1, ConversionModel1X, ConversionModel1Y,
        MO_ReadLogicPosition(0), MO_ReadLogicPosition(1), ConversionX, ConversionY);
    VI_FreeModel(ConversionModel1);
    #endif // VI
    GetDlgItem(IDC_BTNCOMCCDCHECK)->EnableWindow(FALSE);
    SetDlgItemText(IDC_BTNCOMCCDMODIFY, _T("CCD校正")); 
    CString StrBuff;
    StrBuff.Format(_T("pix:um=1:%.3f"), ConversionX);
    SetDlgItemText(IDC_STACOMSCALE, StrBuff);
}


/*Z軸動作選擇*/
void CCompiler::OnZActionChange(UINT uId)
{
    //if (uId == IDC_RADCOMSPOT)
    //{
    //    SetDlgItemText(IDC_BTNCOMWORKW, _T("點膠點"));
    //}
    //else if (uId == IDC_RADCOMAPPLY)
    //{
    //    SetDlgItemText(IDC_BTNCOMWORKW, _T("塗膠點"));
    //}
    //else
    //{
    //    SetDlgItemText(IDC_BTNCOMWORKW, _T("移動點"));
    //}
}
/*移動方式選擇*/
void CCompiler::OnMoveTypeChange(UINT uId)
{
    if (uId == IDC_RADCOMLINE)
    {
        GetDlgItem(IDC_BTNCOMBETWEEN)->EnableWindow(FALSE);
    }
    else if (uId == IDC_RADCOMARC)
    {
        /*兩點半徑圓弧*/
        /*CComRound Open;
        if (Open.DoModal() == IDCANCEL) 
        {
            ((CButton *)GetDlgItem(IDC_RADCOMARC))->SetCheck(FALSE);
            ((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);
        }*/
        GetDlgItem(IDC_BTNCOMBETWEEN)->EnableWindow(TRUE);
    }
    else
    {
        /*GetDlgItem(IDC_BTNCOMORIGINW)->EnableWindow(TRUE);
        CComRound Open;
        if (Open.DoModal() == IDCANCEL)
        {
            ((CButton *)GetDlgItem(IDC_RADCOMROUND))->SetCheck(FALSE);
            ((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);
        }*/
        GetDlgItem(IDC_BTNCOMBETWEEN)->EnableWindow(TRUE);
    }
}

/*資料轉工作路徑*/
int CCompiler::DataToWorkData() {
    CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
    CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
    m_WorkData.clear();
    int nCount = pView->GetDocument()->m_WorkArray.GetSize();
    int DataCount = 0;
    ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(0))->WKArrayCopy(&m_WorkData, DataCount);
    DataCount++;
    for (int i = 1; i < nCount; i++)
    {
        if (CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptOrigin,3)
            != CStringToXY(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i - 1))->m_ptEnd,3))
        {
            m_WorkData.push_back(((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->m_ptOrigin);
            m_WorkData.push_back(_T("無"));
            m_WorkData.push_back(_T("直線"));
            DataCount++;    
        }
        ((CHM_Database*)pView->GetDocument()->m_WorkArray.GetAt(i))->WKArrayCopy(&m_WorkData, DataCount);
        DataCount++;
    }
    return DataCount;  
}
/*字串轉長整數*/
LONG CCompiler::CStringToXYZ(CString Data, int Choose) {
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
/*三點計算圓心*/ 
CString CCompiler::TRoundCCalculation(CString Origin, CString End, CString Between) {
    if (Origin == End || End == Between || Origin == Between)
    {
        MessageBox(_T("What the fucking you type in my system."));
        return _T("F");
    }
    CString Ans;
    double x1 = double(CStringToXYZ(Origin,0)); double y1 = double(CStringToXYZ(Origin, 1));
    double x2 = double(CStringToXYZ(End, 0)); double y2 = double(CStringToXYZ(End, 1));
    double x3 = double(CStringToXYZ(Between, 0)); double y3 = double(CStringToXYZ(Between, 1));
    
    double tan13 = (y3 - y1) / (x3 - x1);
    if ((tan13) >= 200) tan13 = 200;
    else if ((tan13) <= -200) tan13 = -200;
    double tan12 = (y2 - y1) / (x2 - x1);
    if ((tan12) >= 200) tan12 = 200;
    else if ((tan12) <= -200) tan13 = -200;

    double a = 2 * (x1 - x2);
    double b = 2 * (y1 - y2);
    double c = y1*y1 + x1*x1 - x2*x2 - y2*y2;
    double d = 2 * (x1 - x3);
    double e = 2 * (y1 - y3);
    double f = y1*y1 + x1*x1 - x3*x3 - y3*y3;
    int h = round((e*c - b*f) / (a*e - b*d));
    int k = round((a*f - d*c) / (a*e - b*d));
    Ans.Format(_T("%d，%d，"), h, k);
    if ((x2 - x1) > 0)
    {
        if ((y3 - tan12*x3) > (y1 - tan12*x1))
        {
            Ans = Ans + _T("0");
        }
        else if ((y3 - tan12*x3) < (y1 - tan12*x1))
        {
            Ans = Ans + _T("1");
        }
        else
        {
            Ans = _T("F");
            MessageBox(_T("三點共線"));
        }
    }
    else if ((x2 - x1) < 0)
    {
        if ((y3 - tan12*x3) > (y1 - tan12*x1))
        {
            Ans = Ans + _T("1");
        }
        else if ((y3 - tan12*x3) < (y1 - tan12*x1))
        {
            Ans = Ans + _T("0");
        }
        else
        {
            Ans = _T("F");
            MessageBox(_T("三點共線"));
        }
    }
    else
    {
        if ((x3 > x1))
        {
            Ans = Ans + _T("1");
        }
        else if ((x3 < x1))
        {
            Ans = Ans + _T("0");
        }
        else
        {
            Ans = _T("F");
            MessageBox(_T("三點共線"));
        }
    }
    return Ans;
}
/*關閉控件API*/
void CCompiler::MoreEnableWindows(int BeginID, int EndID, BOOL Enable)
{
    for (int i = BeginID; i <= EndID; i++) {
        GetDlgItem(i)->EnableWindow(Enable);
    }
}
/*字串分離(x,y)*/
CString CCompiler::CStringToXY(CString Data, int Choose) {
    int iLength = Data.Find(_T('，'));
    int iLength2 = Data.Right(Data.GetLength() - iLength - 1).Find(_T('，'));
    if (Choose == 0)
    {
        return Data.Left(iLength);
    }
    else if (Choose == 1)
    {
        return Data.Right(Data.GetLength() - iLength - 1).Left(iLength2);
    }
    else if (Choose == 2)
    {
        return Data.Right(Data.GetLength() - iLength - 1).Right((Data.Right(Data.GetLength() - iLength - 1)).GetLength() - iLength2 - 1);//從右讀回來Data.GetLength()-iLength-1多個字元
    }
    else 
    {
        return Data.Left(iLength + iLength2 + 1);
    }
}


/*兩點+半徑*/
/*兩點距離計算判斷半徑最小值*/
LONG CCompiler::RoundRCalculation(CString Data1, CString Data2) {
    return round(sqrt(((CStringToXYZ(Data1, 0) - CStringToXYZ(Data2, 0))) / 10.0 *
        ((CStringToXYZ(Data1, 0) - CStringToXYZ(Data2, 0))) / 10.0 +
        ((CStringToXYZ(Data1, 1) - CStringToXYZ(Data2, 1))) / 10.0 *
        ((CStringToXYZ(Data1, 1) - CStringToXYZ(Data2, 1))) / 10.0) * 5);
}
/*圓心計算*/
CPoint CCompiler::RoundCCalculation(int RADIUS, CPoint Origin, CPoint End, BOOL SizeChoose, BOOL InverseChoose) {
    double N1X, N1Y, N2X, N2Y, N, Buff, Buff1;
    CPoint Round1, Round2;
    N = sqrt((Origin.x - End.x) / 10.0 *
        (Origin.x - End.x) / 10.0 +
        (Origin.y - End.y) / 10.0 *
        (Origin.y - End.y) / 10.0) * 10;
    N1X = -((End.y - Origin.y) / N);
    N1Y = ((End.x - Origin.x) / N);
    N2X = ((End.y - Origin.y) / N);
    N2Y = -((End.x - Origin.x) / N);
    Buff = sqrt((RADIUS / 1000.0)*(RADIUS / 1000.0) - ((int(N / 2) / 1000.0)*(int(N / 2) / 1000.0))) * 1000;
    /*SizeChoose = 1 大弧 0 小弧*/
    /*InverseChoose = 1 順時針 0 逆時針*/
    if (SizeChoose)
    {
        if (InverseChoose)
        {
            CPoint Round2(round((Origin.x + End.x) / 2 + (Buff*N2X)), round((Origin.y + End.y) / 2 + (Buff*N2Y)));
            return Round2;
        }
        else
        {
            CPoint Round1(round((Origin.x + End.x) / 2 + (Buff*N1X)), round((Origin.y + End.y) / 2 + (Buff*N1Y)));
            return Round1;
        }
    }
    else
    {
        if (InverseChoose)
        {
            CPoint Round1(round((Origin.x + End.x) / 2 + (Buff*N1X)), round((Origin.y + End.y) / 2 + (Buff*N1Y)));
            return Round1;
        }
        else
        {
            CPoint Round2(round((Origin.x + End.x) / 2 + (Buff*N2X)), round((Origin.y + End.y) / 2 + (Buff*N2Y)));
            return Round2;
        }
    }
}
/*圓弧資料判斷*/
CString CCompiler::ArcDataCheck(CString strOrigin, CString strEnd) {
    CString StrBuff;
    if (strOrigin == strEnd)
    {
        MessageBox(_T("起始點不可以等於結束點!"));
        return _T("F");
    }
    if (m_RADIUS >= RoundRCalculation(strOrigin, strEnd))
    {
        CPoint Origin(CStringToXYZ(strOrigin, 0), CStringToXYZ(strOrigin, 1));
        CPoint End(CStringToXYZ(strEnd, 0), CStringToXYZ(strEnd, 1));
        CPoint Ans = RoundCCalculation(m_RADIUS, Origin, End, m_SizeChoose, m_InverseChoose);
        if (m_InverseChoose)
        {
            StrBuff.Format(_T("%d，%d"), Ans.x, Ans.y);
            StrBuff = StrBuff + _T("，1");
        }
        else
        {
            StrBuff.Format(_T("%d，%d"), Ans.x, Ans.y);
            StrBuff = StrBuff + _T("，0");
        }
        return StrBuff;
    }
    else
    {
        StrBuff.Format(_T("請再次設置 \r半徑請大於:%d"), RoundRCalculation(strOrigin, strEnd));
        MessageBox(StrBuff);
        return _T("F");
    }
}
/*圓半徑大小判斷*/
CString CCompiler::RoundDataCheck(CString RoundC)
{
    CString StrBuff;
    if ((CStringToXYZ(RoundC, 0) - m_RADIUS) >= 0 &&
        (CStringToXYZ(RoundC, 1) - m_RADIUS) >= 0 &&
        (CStringToXYZ(RoundC, 0) + m_RADIUS) <= 200000 &&
        (CStringToXYZ(RoundC, 1) + m_RADIUS) <= 200000)
    {
        StrBuff.Format(_T("%d，%d，%d"), (CStringToXYZ(RoundC, 0) - m_RADIUS), CStringToXYZ(RoundC, 1), CStringToXYZ(RoundC, 2));
        return StrBuff;
    }
    MessageBox(_T("此圓半徑太大\r超過加工範圍!"));
    return _T("F");
}





