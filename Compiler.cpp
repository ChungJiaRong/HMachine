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
#include "Main.h"

// CCompiler 對話方塊
IMPLEMENT_DYNAMIC(CCompiler, CPropertyPage)

CCompiler::CCompiler()
	: CPropertyPage(IDD_COMPILER)
{
	m_ListWKCount = 0;
	m_ListPSCount = 0;
	m_WorkData.SetSize(201);//設定陣列大小201筆
	for (int i = 0; i < sizeof(m_WorkData); i++)//清空所有陣列 
	{
		m_WorkData[i].Empty();
	}
	for (int i = 0; i < 2; i++) 
	{
		m_PosData.Add(_T(""));
	}
}
CCompiler::~CCompiler()
{
}
void CCompiler::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_LISTCOMSTAND, m_ListCtrlPos);
	DDX_Control(pDX, IDC_LISTCOMWORK, m_ListCtrlWork);
	CPropertyPage::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CCompiler, CPropertyPage)
	ON_WM_SIZE()
    ON_WM_PAINT()

	ON_BN_CLICKED(IDC_BTNCOMFILENEW, &CCompiler::OnBnClickedFileNew)
	ON_BN_CLICKED(IDC_BTNCOMFILEOPEN, &CCompiler::OnBnClickedFileOpen)
	ON_BN_CLICKED(IDC_BTNCOMFILESAVE, &CCompiler::OnBnClickedFileSave)
	ON_BN_CLICKED(IDC_BTNCOMFILESAVEAS, &CCompiler::OnBnClickedFileSaveAs)

	ON_BN_CLICKED(IDC_BTNCOMWORKW, &CCompiler::OnBnClickedBtncomworkw)
	ON_BN_CLICKED(IDC_BTNCOMSTANDCHK1, &CCompiler::OnBnClickedBtncomstandchk1)
	ON_BN_CLICKED(IDC_BTNCOMSTANDCHK2, &CCompiler::OnBnClickedBtncomstandchk2)
	ON_BN_CLICKED(IDC_BTNCOMORIGINW, &CCompiler::OnBnClickedBtncomoriginw)
	ON_BN_CLICKED(IDC_BTNCOMYUP, &CCompiler::OnBnClickedBtncomyup)
	ON_BN_CLICKED(IDC_BTNCOMYDOWN, &CCompiler::OnBnClickedBtncomydown)
	ON_BN_CLICKED(IDC_BTNCOMXDOWN, &CCompiler::OnBnClickedBtncomxdown)
	ON_BN_CLICKED(IDC_BTNCOMXUP, &CCompiler::OnBnClickedBtncomxup)
    ON_BN_CLICKED(IDC_BTNCOMWORKFINISH, &CCompiler::OnBnClickedBtncomworkfinish)
	
	ON_NOTIFY(NM_RCLICK, IDC_LISTCOMWORK, &CCompiler::OnRclickListcomwork)
    ON_NOTIFY(NM_DBLCLK, IDC_LISTCOMWORK, &CCompiler::OnNMDblclkListcomwork)

	ON_COMMAND(IDM_LISTMODIFY, &CCompiler::OnListmodify)
	ON_COMMAND(IDM_LISTINSERT, &CCompiler::OnListinsert)
	ON_COMMAND(IDM_LISTDELETE, &CCompiler::OnListdelete)

    ON_EN_CHANGE(IDC_EDITCOMNAME, &CCompiler::OnEnChangeEditcomname)
    ON_CONTROL_RANGE(EN_CHANGE, IDC_EDITCOMSTANDY1, IDC_EDIT2, &CCompiler::OnEditChange)

END_MESSAGE_MAP()
// CCompiler 訊息處理常式
BOOL CCompiler::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// TODO:  在此加入額外的初始化
	CHeaderCtrl* pHeaderCtrl;
	//對位點欄初始化設定
	pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlPos.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlPos.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlPos.InsertColumn(0, _T("對位點"), LVCFMT_LEFT, 111, -1);
	m_ListCtrlPos.InsertColumn(1, _T("座標點"), LVCFMT_LEFT, 111, -1);
	for (int i = 0; i < 2; i++) {
		i ? m_ListCtrlPos.InsertItem(i, _T("第二個點")) : m_ListCtrlPos.InsertItem(i, _T("第一個點"));
	}
	//工作點欄初始化設定
	pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlWork.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlWork.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlWork.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 38, -1);
	m_ListCtrlWork.InsertColumn(1, _T("起始點"), LVCFMT_CENTER, 115, -1);
	m_ListCtrlWork.InsertColumn(2, _T("結束點"), LVCFMT_CENTER, 115, -1);
	m_ListCtrlWork.InsertColumn(3, _T("動作"), LVCFMT_CENTER, 38, -1);
	//Radio初始選擇
	((CButton *)GetDlgItem(IDC_RADCOMLINE))->SetCheck(TRUE);//選上直線
	((CButton *)GetDlgItem(IDC_RADCOMLS))->SetCheck(TRUE);//選上低速
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CCompiler::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此加入您的訊息處理常式程式碼
					   // 不要呼叫圖片訊息的 CPropertyPage::OnPaint()
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	//EDIT控件文字垂直置中
	for (int i = 1118; i < 1125; i++)
	{
		EditTextVertical((CEdit*)GetDlgItem(i));
	}
}
void CCompiler::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	CWnd* pWnd;
	for (int i = 1100; i < 1133; i++)
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
	m_ListCtrlWork.DeleteAllItems();//清除工作點列表
	m_WorkData.RemoveAll();//刪除所有陣列
	m_PosData.RemoveAll();//刪除對位點陣列
	m_ListWKCount = 0;//工作點計數清零
	m_ListPSCount = 0;//對位點計數清零
	m_WorkData.SetSize(201);//設定陣列大小201筆
	for (int i = 0; i < sizeof(m_WorkData); i++)//清空工作點陣列 
	{
		m_WorkData[i].Empty();
	}
	for (int i = 0; i < 2; i++) 
	{
		m_PosData.Add(_T(""));//清空對位陣列
		m_ListCtrlPos.SetItemText(i, 1, _T(""));//清空對位點列表
	}
	for (int i = 1118; i < 1125; i++)
	{
		GetDlgItem(i)->SetWindowText(_T(""));//清空編輯框文字
	}
}
/*檔案按鈕*/
void CCompiler::OnBnClickedFileNew()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//if (MessageBox(_T("資料尚未儲存!\n確定要開啟新檔?"), _T("題示"), MB_ICONINFORMATION | MB_OKCANCEL) == IDOK) {
		::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_NEW, 0);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(TRUE);//開啟料件名稱EDIT
		InitVariable();//變數初始化	 
	//}
}
void CCompiler::OnBnClickedFileOpen()
{
	// TODO: 在此加入控制項告知處理常式程式碼 
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	CString StrBuff,FilePathName;
	TCHAR szFilters[] = _T("HMF Type Files (*.hmf)|*.hmf|All Files (*.*)|*.*||");
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilters);
	FileDlg.m_ofn.lpstrTitle = _T("打開我的料件"); 
	if (FileDlg.DoModal() == IDOK)
	{
		FilePathName = FileDlg.GetPathName();
		AfxGetApp()->OpenDocumentFile(FilePathName);
		InitVariable();//變數初始化 
		m_ListWKCount = pView->GetDocument()->m_objArray.GetSize();
		m_ListPSCount = pView->GetDocument()->m_standArray.GetSize();
		for (int i = 0; i < m_ListWKCount; i++) {
			StrBuff.Format(_T("%d"), i+1);
			m_ListCtrlWork.InsertItem(i, StrBuff);
		}
		WorkListRefresh(TRUE); 
		m_ListWKCount++;//讓下一點工作點寫入
		for (int i = 0; i < m_ListPSCount; i++) {
			((CHM_Database*)pView->GetDocument()->m_standArray.GetAt(i))->PSArrayCopy(&m_PosData,i);
			m_ListCtrlPos.SetItemText(i, 1, m_PosData[i]);
		}
		StrBuff = pView->GetDocument()->GetTitle();
		GetDlgItem(IDC_EDITCOMNAME)->SetWindowText(StrBuff);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(FALSE);//關閉料件名稱EDIT
	}
	else
	{

	}
}
void CCompiler::OnBnClickedFileSave()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString oldName,newName;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
	oldName = pView->GetDocument()->GetTitle();
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_SAVE, 0);
	newName = pView->GetDocument()->GetTitle();
	if (oldName != newName) {
		GetDlgItem(IDC_EDITCOMNAME)->SetWindowText(newName);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(FALSE);//關閉料件名稱EDIT
	}
	else{
	}   
}
void CCompiler::OnBnClickedFileSaveAs()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString oldName, newName;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
	oldName = pView->GetDocument()->GetTitle();
	::SendMessage(AfxGetMainWnd()->m_hWnd, WM_COMMAND, ID_FILE_SAVE_AS, 0);
	newName = pView->GetDocument()->GetTitle();
	if (oldName != newName) {
		GetDlgItem(IDC_EDITCOMNAME)->SetWindowText(newName);
		GetDlgItem(IDC_EDITCOMNAME)->EnableWindow(FALSE);//關閉料件名稱EDIT
	}
	else {
	}
}
/*起始點設定*/
void CCompiler::OnBnClickedBtncomoriginw()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	CString X, Y;
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2));
	if (!m_ListWKCount) {
		m_WorkData.SetAt(0, X + _T("，") + Y);
		m_ListWKCount++;
		m_ListCtrlWork.InsertItem(m_ListWKCount, _T("001"));//插入的索引只在插入時有用 並不關聯內建索引值
		CHM_Database *pHM_Database = new CHM_Database(m_WorkData[0], _T(""), _T(""));
		pView->GetDocument()->m_objArray.Add(pHM_Database);
	}
	else {
		m_WorkData.SetAt(0, X + _T("，") + Y);
		if (m_WorkData[1] == _T(""))
		{
			CHM_Database *pHM_Database = new CHM_Database(m_WorkData[0], _T(""), _T(""));
			pView->GetDocument()->m_objArray.SetAt(0, pHM_Database);
		}
		else
		{
			CHM_Database *pHM_Database = new CHM_Database(m_WorkData[0], m_WorkData[1], m_WorkData[2]);
			pView->GetDocument()->m_objArray.SetAt(0, pHM_Database);
		}
		m_ListCtrlWork.EnsureVisible(0, FALSE);//使List中一項可見(如滾動條向下滾)
	}
	m_ListCtrlWork.SetItemText(0, 1, X + _T("，") + Y);//設置第一個為索引值，關連到現有列表中的索引值所以很重要
}
/*工作點設定*/
void CCompiler::OnBnClickedBtncomworkw()
{
	//// TODO: 在此加入控制項告知處理常式程式碼
	CString X, Y, StrBuff;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	if (m_ListWKCount && m_ListWKCount < 100) {
		//獲取XY座標
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1));
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2));
		m_WorkData.SetAt(m_ListWKCount * 2 - 1, X + _T("，") + Y);
		//WorkData.Add(X + _T("，") + Y);
		//獲取 動作指令
		switch (GetCheckedRadioButton(IDC_RADCOMLINE, IDC_RADCOMARC))
		{
		case IDC_RADCOMLINE:
			m_WorkData.SetAt(m_ListWKCount * 2,_T("直線"));
			//WorkData.Add(_T("直線"));
			break;
		case IDC_RADCOMARC:
			m_WorkData.SetAt(m_ListWKCount * 2, _T("圓弧"));
			//WorkData.Add(_T("圓弧"));
			break;
		default:
			MessageBox(_T("程式出現錯誤!"));
			break;
		}
		if (m_ListWKCount == 1) {
			CHM_Database *pHM_Database = new CHM_Database(m_WorkData[0], m_WorkData[m_ListWKCount*2-1], m_WorkData[m_ListWKCount*2]);
			pView->GetDocument()->m_objArray.SetAt(0,pHM_Database);
		}
		else {
			StrBuff.Format(_T("%d"), m_ListWKCount);
			m_ListCtrlWork.InsertItem(m_ListWKCount, StrBuff);
			CHM_Database *pHM_Database = new CHM_Database(m_WorkData[m_ListWKCount*2-3], m_WorkData[m_ListWKCount*2-1], m_WorkData[m_ListWKCount*2]);
			pView->GetDocument()->m_objArray.Add(pHM_Database);
		}
		m_ListWKCount++;
	}
	else {
		if(m_ListWKCount == 100)
			MessageBox(_T("工作點已滿!"));
		else
			MessageBox(_T("請先設定起始點!"));
	}
	WorkListRefresh(TRUE);
}
/*對位點1設定*/
void CCompiler::OnBnClickedBtncomstandchk1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString X, Y;
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMSTANDX1));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMSTANDY1));
	m_PosData.SetAt(0, X + _T("，") + Y);
	m_ListCtrlPos.SetItemText(0, 1, X + _T("，") + Y);
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	if (!m_ListPSCount) {
		CHM_Database *pHM_Database = new CHM_Database(m_PosData[0]);
		pView->GetDocument()->m_standArray.Add(pHM_Database);
		pHM_Database = new CHM_Database(_T(""));
		pView->GetDocument()->m_standArray.Add(pHM_Database);
		m_ListPSCount++;
	}
	else {
		CHM_Database *pHM_Database = new CHM_Database(m_PosData[0]);
		pView->GetDocument()->m_standArray.SetAt(0, pHM_Database);
	} 
}
/*對位點2設定*/
void CCompiler::OnBnClickedBtncomstandchk2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString X, Y;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	if (!m_ListPSCount) {
		MessageBox(_T("請先設定第一個對位點!"));
	}
	else {
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMSTANDX2));
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDITCOMSTANDY2));
		m_PosData.SetAt(1, X + _T("，") + Y);
		m_ListCtrlPos.SetItemText(1, 1, X + _T("，") + Y);
		CHM_Database *pHM_Database = new CHM_Database(m_PosData[1]);
		pView->GetDocument()->m_standArray.SetAt(1, pHM_Database);
	}
}
/*Y上移*/
void CCompiler::OnBnClickedBtncomyup()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString Y;
	switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
	{
	case IDC_RADCOMHS:
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2) + 100);
		break;
	case IDC_RADCOMMS:
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2) + 10);
		break;
	case IDC_RADCOMLS:
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2) + 1);
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
	GetDlgItem(IDC_EDIT2)->SetWindowText(Y);
	
}
/*Y下移*/
void CCompiler::OnBnClickedBtncomydown()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString Y;
	switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
	{
	case IDC_RADCOMHS:
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2) - 100);
		break;
	case IDC_RADCOMMS:
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2) - 10);
		break;
	case IDC_RADCOMLS:
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2) - 1);
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
	GetDlgItem(IDC_EDIT2)->SetWindowText(Y);
	
}
/*X左移*/
void CCompiler::OnBnClickedBtncomxdown()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString X;
	switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
	{
	case IDC_RADCOMHS:
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1) - 100);
		break;
	case IDC_RADCOMMS:
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1) - 10);
		break;
	case IDC_RADCOMLS:
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1) - 1);
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(X);
}
/*X右移*/
void CCompiler::OnBnClickedBtncomxup()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString X;
	switch (GetCheckedRadioButton(IDC_RADCOMHS, IDC_RADCOMLS))
	{
	case IDC_RADCOMHS:
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1) + 100);
		break;
	case IDC_RADCOMMS:
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1) + 10);
		break;
	case IDC_RADCOMLS:
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1) + 1);
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
	GetDlgItem(IDC_EDIT1)->SetWindowText(X);
}
/*鍵盤響應事件*/
BOOL CCompiler::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_LEFT) {
			OnBnClickedBtncomxdown();
			return TRUE;
		}   
		if (pMsg->wParam == VK_RIGHT) {
			OnBnClickedBtncomxup();
			return TRUE;
		}
		if (pMsg->wParam == VK_UP) {
			OnBnClickedBtncomyup();
			return TRUE;
		}
		if (pMsg->wParam == VK_DOWN) {
			OnBnClickedBtncomydown();
			return TRUE;
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
			OnBnClickedBtncomworkw();
		}
	}
	return CPropertyPage::PreTranslateMessage(pMsg);
}
/*料件名稱修改*/
void CCompiler::OnEnChangeEditcomname()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CPropertyPage::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。
	// TODO:  在此加入控制項告知處理常式程式碼
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	CString str;
	GetDlgItem(IDC_EDITCOMNAME)->GetWindowText(str);
	pView->GetDocument()->SetTitle(str); //設置檔案標頭   
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
/*工作列表刷新*/
void CCompiler::WorkListRefresh(BOOL ScrollBarRefresh) {
	CString StrBuff;
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動的View指針
	int nCount = pView->GetDocument()->m_objArray.GetSize();
	for (int i = 0; i < nCount; i++) {
		((CHM_Database*)pView->GetDocument()->m_objArray.GetAt(i))->WKArrayCopy(&m_WorkData, i);
		if (i == 0)
		{
			m_ListCtrlWork.SetItemText(i, 0, _T("001"));
			m_ListCtrlWork.SetItemText(i, 1, m_WorkData[0]);
		}
		else
		{  
			(i+1>9)?StrBuff.Format(_T("0%d"), i+1):StrBuff.Format(_T("00%d"), i + 1);
			m_ListCtrlWork.SetItemText(i, 0, StrBuff);
			m_ListCtrlWork.SetItemText(i, 1, m_WorkData[i * 2 - 1]);
		}
		m_ListCtrlWork.SetItemText(i, 2, m_WorkData[i * 2 + 1]);
		m_ListCtrlWork.SetItemText(i, 3, m_WorkData[i * 2 + 2]);
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
/*編輯完成載入料件*/
void CCompiler::OnBnClickedBtncomworkfinish()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (m_PosData[0] == _T("") || m_PosData[1] == _T("") || m_ListWKCount < 1) 
	{
		MessageBox(_T("請設定對位點和工作點!"));
	}
	else
	{
		if (MessageBox(_T("你確定要載入料件?"), _T("詢問"), MB_ICONINFORMATION | MB_OKCANCEL) == IDOK) {
			CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;//獲取已建立的View指針
			CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();//獲取活動中的view指針
			CFile File; 
			if (File.Open(_T("Inprocess.txt"), CFile::modeCreate | CFile::modeWrite)) {
				CArchive ar(&File, CArchive::store);
				ar << m_PosData[0] << m_PosData[1] << m_ListWKCount-1;
				for (int i = 0; i < m_ListWKCount * 2 - 1; i++) {
					ar << m_WorkData[i];
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
		}  
	} 
}
/*列表右鍵菜單*/
void CCompiler::OnRclickListcomwork(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	//CListCtrl *CList = (CListCtrl *)GetDlgItem(IDC_LISTCOMWORK);
	//CMenu menu, *pSubMenu;
	//CPoint CurPnt;
	//int  istat = m_ListCtrlWork.GetSelectionMark();//獲取選擇的項
	//if (istat >= 0)//沒有資料時禁止使用
	//{
	//    menu.LoadMenu(IDR_LISTPOPMENU);//加入菜單
	//    pSubMenu = menu.GetSubMenu(0);
	//    GetCursorPos(&CurPnt);
	//    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, CurPnt.x, CurPnt.y, this);//點右鍵出現的菜單位置
	//}
	*pResult = 0;
}
/*右鍵菜單修改*/
void CCompiler::OnListmodify()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CString X, Y;
	int  istat = m_ListCtrlWork.GetSelectionMark();//獲取選擇的項
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	//獲取XY座標
	X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1));
	Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2));
	m_WorkData.SetAt(istat * 2 + 1, X + _T("，") + Y);
	//獲取 動作指令
	switch (GetCheckedRadioButton(IDC_RADCOMLINE, IDC_RADCOMARC))
	{
	case IDC_RADCOMLINE:
		m_WorkData.SetAt(istat * 2 + 2, _T("直線"));
		break;
	case IDC_RADCOMARC:
		m_WorkData.SetAt(istat * 2 + 2, _T("圓弧"));
		break;
	default:
		MessageBox(_T("程式出現錯誤!"));
		break;
	}
	CHM_Database *pHM_Database = new CHM_Database(istat ? m_WorkData[istat * 2 - 1] : m_WorkData[0], m_WorkData[istat * 2 + 1], m_WorkData[istat * 2 + 2]);
	pView->GetDocument()->m_objArray.SetAt(istat, pHM_Database);//修改資料庫數值
	WorkListRefresh(FALSE);
}
/*右鍵菜單插入*/
void CCompiler::OnListinsert()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CString X, Y, StrBuff;
	int istat = m_ListCtrlWork.GetSelectionMark();//獲取選擇的項
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	if (m_WorkData[1] != _T(""))//避免沒有工作點時
	{
		//獲取XY座標
		X.Format(_T("%d"), GetDlgItemInt(IDC_EDIT1));
		Y.Format(_T("%d"), GetDlgItemInt(IDC_EDIT2));
		m_WorkData.InsertAt(istat * 2 + 1, X + _T("，") + Y);//插入資料陣列
		//獲取 動作指令
		switch (GetCheckedRadioButton(IDC_RADCOMLINE, IDC_RADCOMARC))
		{
		case IDC_RADCOMLINE:
			m_WorkData.InsertAt(istat * 2+2 , _T("直線"));
			break;
		case IDC_RADCOMARC:
			m_WorkData.InsertAt(istat * 2+2, _T("圓弧"));
			break;
		default:
			MessageBox(_T("程式出現錯誤!"));
			break;
		}
		StrBuff.Format(_T("%d"), istat + 1);
		m_ListCtrlWork.InsertItem(istat + 1, StrBuff);//List插入項目
		CHM_Database *pHM_Database = new CHM_Database(istat ? m_WorkData[istat * 2 - 1] : m_WorkData[0], m_WorkData[istat * 2 + 1], m_WorkData[istat * 2 + 2]);
		pView->GetDocument()->m_objArray.InsertAt(istat, pHM_Database);//插入資料庫
		m_ListWKCount++;
		WorkListRefresh(FALSE);
	}
	else
	{   
		MessageBox(_T("請先設定第一個工作點!"));
	}
}
/*右鍵菜單刪除*/
void CCompiler::OnListdelete()
{
	// TODO: 在此加入您的命令處理常式程式碼
	int istat = m_ListCtrlWork.GetSelectionMark();//獲取選擇的項
	CMainFrame *pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CHM_MachineView *pView = (CHM_MachineView *)pMain->GetActiveView();
	m_WorkData.RemoveAt(istat * 2 + 1);
	m_WorkData.RemoveAt(istat * 2 + 1);
	pView->GetDocument()->m_objArray.RemoveAt(istat);//從資料庫中移除
	m_ListCtrlWork.DeleteItem(istat);//刪除List項目
	m_ListWKCount--;
	WorkListRefresh(FALSE);
}
/*左鍵點兩下出現菜單*/
void CCompiler::OnNMDblclkListcomwork(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	CListCtrl *CList = (CListCtrl *)GetDlgItem(IDC_LISTCOMWORK);
	CMenu menu,*pSubMenu;
	CPoint CurPnt;
	int istat = m_ListCtrlWork.GetSelectionMark();//獲取選擇的項
	int ItemCount = m_ListCtrlWork.GetItemCount();//獲取項目總數
	if (istat >= 0)//沒有資料時禁止使用
	{
		menu.LoadMenu(IDR_LISTPOPMENU);//加入菜單
		pSubMenu = menu.GetSubMenu(0);
		(ItemCount>1) ? pSubMenu->EnableMenuItem(IDM_LISTDELETE, MF_BYCOMMAND | MF_ENABLED)
			: pSubMenu->EnableMenuItem(IDM_LISTDELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		GetCursorPos(&CurPnt);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, CurPnt.x, CurPnt.y, this);//點右鍵出現的菜單位置
	}
	*pResult = 0;
}
/*Edit限制輸入*/
void CCompiler::OnEditChange(UINT uId)
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CPropertyPage::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。
	// TODO:  在此加入控制項告知處理常式程式碼
	if (GetDlgItemInt(uId) >= 200000) {
		SetDlgItemInt(uId, 200000);
		((CEdit*)GetDlgItem(uId))->SetSel(6,0);
	}
}