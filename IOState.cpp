// IOState.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "IOState.h"
#include "afxdialogex.h"

// CIOState 對話方塊

IMPLEMENT_DYNAMIC(CIOState, CPropertyPage)

CIOState::CIOState()
	: CPropertyPage(IDD_IOSTATE)
{
	m_ConCtrlCount = 12;
	m_bBtnEnable = FALSE;
	memset(m_InputState, -1, sizeof(m_InputState));
	memset(m_OutputState, -1, sizeof(m_OutputState));
	m_EditInName.SetSize(12);
	m_EditOutName.SetSize(12);
	CreateB = new CButtonST[24];  
	CreateD = new CEdit[22];
    MyFont = new CFont;
}

CIOState::~CIOState()
{ 
    if (CreateB)
        delete[]CreateB;
    if (CreateD)
        delete[]CreateD;
    if (MyFont)
        delete MyFont;
}

void CIOState::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIOState, CPropertyPage)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNIOREFRESH, &CIOState::OnBnClickedBtniorefresh)
	ON_BN_CLICKED(IDC_BTNIOOPENREFRESH, &CIOState::OnBnClickedBtnioopenrefresh)
	ON_BN_CLICKED(IDC_BTNIOCOMPILER, &CIOState::OnBnClickedBtniocompiler)
	ON_BN_CLICKED(IDC_BTNSETFINISH, &CIOState::OnBnClickedBtnsetfinish)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTNIOSTATE,  951, &CIOState::OnStateClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTNIOONOFF, 966, &CIOState::OnOutputClick)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CIOState 訊息處理常式
BOOL CIOState::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// TODO:  在此加入額外的初始化
	CString StrBuff;
    /*新增控件*/
	AddControl();
	/*編號*/
	for (int i = 0; i < 12; i++) 
	{
		StrBuff.Format((i<9)?_T("00%d"):_T("0%d"), i+1);
		GetDlgItem(IDC_STAIOINUMBER_0 + i)->SetWindowText(StrBuff);
	}
	for (int i = 0; i < 12; i++)
	{
		StrBuff.Format((i<9) ? _T("00%d") : _T("0%d"), i + 1);
		GetDlgItem(IDC_STAIOOUTUMBER_0 + i)->SetWindowText(StrBuff);
	}
    CFileStatus FileStatus;//檔案屬性
    CFile File;
    if (!File.GetStatus(_T("IOData.txt"), FileStatus)) {
        WriteIOData();
    }
    else {
        ReadIOData();
    }
    MyUpdateData(TRUE, m_InputState, TRUE, m_OutputState, FALSE, TRUE);
	/*開啟刷新*/
	SetTimer(1, 500, NULL);
    /*設置字體*/
    MyFont->CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("標楷體"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CIOState::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此加入您的訊息處理常式程式碼
					   // 不要呼叫圖片訊息的 CPropertyPage::OnPaint()
	for (int i = 0; i < 22; i++)
	{
        EditTextVertical((CreateD + i));
	}
    EditTextVertical((CEdit*)GetDlgItem(IDC_EDITIOINAME));
    EditTextVertical((CEdit*)GetDlgItem(IDC_EDITIOONAME));
}
void CIOState::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼
	CWnd *pWnd;
	for (int i = IDC_STAIOINPUTER; i <= 1000; i++)
	{
		pWnd = GetDlgItem(i);
		ChangeSize(pWnd, cx, cy);
	}
	GetClientRect(&m_InitRect);
}
/*新增控件*/
void CIOState::AddControl()
{
	CRect rcButton, rcEdit;
	int Hight = 28;
	GetDlgItem(IDC_STAIOINPUTER)->GetWindowRect(&rcButton);
	ScreenToClient(rcButton);
	rcButton.right = 48;
	for (int i = 0; i < m_ConCtrlCount * 2; i++)
	{
		if (i == m_ConCtrlCount)
		{
			GetDlgItem(IDC_STAIOOUTPUTER)->GetWindowRect(&rcButton);
			ScreenToClient(rcButton); 
			rcButton.right = rcButton.left + 48;
		}
		if (i == 0 && i == m_ConCtrlCount)
		{
			rcButton.top = rcButton.bottom + 2;
			rcButton.bottom += Hight + 2;
		}
		else
		{
			rcButton.top = rcButton.bottom + 4;
			rcButton.bottom += Hight + 4;
		}   
		CreateB[i].Create(_T(""), WS_CHILD | WS_VISIBLE, rcButton, this, (i < m_ConCtrlCount) ? IDC_BTNIOSTATE + i : IDC_BTNIOONOFF + i - m_ConCtrlCount);
		CreateB[i].SetBitmaps(IDB_IOSLEEP,RGB(0,0,0));
	}
	GetDlgItem(IDC_EDITIOINAME)->GetWindowRect(&rcEdit);
	ScreenToClient(rcEdit);
	Hight = rcEdit.Height();
	for (int i = 0; i < (m_ConCtrlCount-1) * 2; i++)
	{
		if (i == (m_ConCtrlCount - 1))
		{
			GetDlgItem(IDC_EDITIOONAME)->GetWindowRect(&rcEdit);
			ScreenToClient(rcEdit);
		}
		rcEdit.top = rcEdit.bottom + 4;
		rcEdit.bottom += Hight + 4;
		CreateD[i].Create(WS_CHILD | WS_VISIBLE | ES_MULTILINE |WS_BORDER | WS_DISABLED, rcEdit, this, (i < (m_ConCtrlCount - 1)) ? IDC_EDITIOINAME + i + 1 : IDC_EDITIOONAME + i - (m_ConCtrlCount - 1) +1);
	} 
	/*修改初始編輯框風格*/
	((CEdit*)GetDlgItem(IDC_EDITIOINAME))->ModifyStyle(0, WS_BORDER );
	((CEdit*)GetDlgItem(IDC_EDITIOONAME))->ModifyStyle(0, WS_BORDER );
    /*刷新IO*/
    OnBnClickedBtniorefresh();
}
/*改變控件大小*/
void CIOState::ChangeSize(CWnd* pWnd, int cx, int cy)
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
/*EDIT控件文字垂直置中、字體*/
void CIOState::EditTextVertical(CEdit *m_EditCtrl) {
	/*改變字體*/
	m_EditCtrl->SetFont(MyFont,FALSE);
	TEXTMETRIC tm;//文字型態
	CRect rect;
	CDC *pEDC = m_EditCtrl->GetDC();//獲取控建DC
	pEDC->GetTextMetrics(&tm);//獲取DC字體高度
	int nFontHeight = 18/*tm.tmHeight*/ + tm.tmExternalLeading;//計算字體輸入的位置
	m_EditCtrl->GetClientRect(&rect);//獲取控建客戶區大小
	int offY = (rect.Height() - nFontHeight) / 2;//計算工作區域大小
	rect.OffsetRect(0, offY);//將工作區向下偏移
	m_EditCtrl->SetRectNP(&rect);//設置工作區
	ReleaseDC(pEDC);//釋放DC 
}
/*寫入檔案*/
void CIOState::WriteIOData() {
	CFile File;
	if (File.Open(GetModulePath()+_T("IOData.txt"), CFile::modeCreate | CFile::modeWrite)) {
		CArchive ar(&File, CArchive::store);
		for (int i = 0; i < 48; i++)
		{
			if (i < 12)
				ar << m_EditInName[i];
            else if (i < 24)
                ar << m_EditOutName[i - 12];
            else if (i < 36)
                ar << m_InputState[i - 24];
            else
				ar << m_OutputState[i - 36];
		}
	}
	File.Close();
}
/*讀取檔案*/
void CIOState::ReadIOData() {
	CFile File;
	if (File.Open(GetModulePath()+_T("IOData.txt"), CFile::modeRead)) {//打開檔案
		CArchive ar(&File, CArchive::load);//讀取入檔案
		for (int i = 0; i < 48; i++)
		{
			if (i < 12)
				ar >> m_EditInName[i];
			else if (i < 24)
				ar >> m_EditOutName[i - 12];
            else if (i < 36)
                ar >> m_InputState[i - 24];
			else
				ar >> m_OutputState[i - 36];
		}
		File.Close();
	}
}
/*立即刷新數值*/
void CIOState::OnBnClickedBtniorefresh()
{
	// TODO: 在此加入控制項告知處理常式程式碼
    if (m_bBtnEnable == FALSE){
#ifdef MOVE
        for (int i = 0; i < 12; i++)
        {
            
        }
	    for (int i = 0; i < 12; i++)
	    {
            if (m_InputState[i] != -1)
                m_InputState[i] = MO_ReadPIOInput(i);
	    }
	    for (int i = 0; i < 12; i++)
	    {
            if (m_OutputState[i] != -1)
		        MO_SetPIOOutput(i, m_OutputState[i]);
	    }
#endif //MOVE
        MyUpdateData(TRUE,m_InputState,FALSE,NULL);
    }
}
/*關閉刷新*/
void CIOState::OnBnClickedBtnioopenrefresh()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString StrBuff;
	GetDlgItem(IDC_BTNIOCLOSEREFRESH)->GetWindowText(StrBuff);
	if (StrBuff == _T("關閉刷新"))
	{
		KillTimer(1);
		SetDlgItemText(IDC_BTNIOCLOSEREFRESH,_T("開啟刷新"));
	}  
	else
	{
		SetTimer(1, 500, NULL);
		SetDlgItemText(IDC_BTNIOCLOSEREFRESH, _T("關閉刷新"));
	}
}
/*編輯資料*/
void CIOState::OnBnClickedBtniocompiler()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString StrBuff;
	GetDlgItemText(IDC_BTNIOCOMPILER, StrBuff);
	if (StrBuff == _T("編輯資料"))
	{
		SetDlgItemText(IDC_BTNIOCOMPILER, _T("取消編輯"));
		for (int i = IDC_EDITIOINAME; i <= IDC_EDITIOINAME + (m_ConCtrlCount -1) ; i++)
			GetDlgItem(i)->EnableWindow(TRUE);
		for (int i = IDC_EDITIOONAME; i <= IDC_EDITIOONAME + (m_ConCtrlCount - 1); i++)
			GetDlgItem(i)->EnableWindow(TRUE);
        m_bBtnEnable = TRUE;
        for (int i = 0; i < 12; i++)
        {
            m_OldIBuffer[i] = m_InputState[i];
        }
        for (int i = 0; i < 12; i++)
        {
            m_OldOBuffer[i] = m_OutputState[i];
        }
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("I/O設定"), _T("編輯I/O"));
	}
	else
	{
		SetDlgItemText(IDC_BTNIOCOMPILER, _T("編輯資料"));
		for (int i = IDC_EDITIOINAME; i <= IDC_EDITIOINAME + (m_ConCtrlCount - 1); i++)
			GetDlgItem(i)->EnableWindow(FALSE);
		for (int i = IDC_EDITIOONAME; i <= IDC_EDITIOONAME + (m_ConCtrlCount - 1); i++)
			GetDlgItem(i)->EnableWindow(FALSE);
        m_bBtnEnable = FALSE;
        for (int i = 0; i < 12; i++)
        {
            m_InputState[i] = m_OldIBuffer[i];
        }
        for (int i = 0; i < 12; i++)
        {
            m_OutputState[i] = m_OldOBuffer[i];
        }
        MyUpdateData(TRUE, m_InputState, TRUE, m_OutputState, FALSE, TRUE);
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("I/O設定"), _T("取消編輯"));
	}
}
/*設定完成*/
void CIOState::OnBnClickedBtnsetfinish()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString StrBuff;
	GetDlgItemText(IDC_BTNIOCOMPILER, StrBuff);
	if (StrBuff == _T("取消編輯"))
	{
		SetDlgItemText(IDC_BTNIOCOMPILER, _T("編輯資料"));
		for (int i = IDC_EDITIOINAME; i <= IDC_EDITIOINAME + (m_ConCtrlCount - 1); i++)
			GetDlgItem(i)->EnableWindow(FALSE);
		for (int i = IDC_EDITIOONAME; i <= IDC_EDITIOONAME + (m_ConCtrlCount - 1); i++)
			GetDlgItem(i)->EnableWindow(FALSE);
        m_bBtnEnable = FALSE;
        MyUpdateData(TRUE,m_InputState,TRUE,m_OutputState,TRUE,TRUE);
		WriteIOData();
        OnBnClickedBtniorefresh();
        WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("I/O設定"), _T("編輯完成"));
	}
}
/*Input開關*/
void CIOState::OnStateClick(UINT uId)
{
    if (m_bBtnEnable)
    {
        if (m_InputState[uId - 940] == -1)
        {
            m_InputState[uId - 940] = 1;
        }
        else
        {
            m_InputState[uId - 940] = -1;
        }   
        MyUpdateData(TRUE, m_InputState,FALSE,NULL);
    }
}
/*Output設定*/
void CIOState::OnOutputClick(UINT uId)
{
    if (m_bBtnEnable)
    {
        if (m_OutputState[uId - 955] == -1)
        {
            m_OutputState[uId - 955] = 1;
        }
        else if(m_OutputState[uId - 955] == 1)
        {
            m_OutputState[uId - 955] = 0;
        }
        else
        {
            m_OutputState[uId - 955] = -1;
        }
        MyUpdateData(FALSE,NULL,TRUE, m_OutputState);
    }
}
/*獲取和刷新控件*/
void CIOState::MyUpdateData(BOOL InputState, int* IStateData , BOOL OutputState , int* OStateData ,BOOL GetIOEditName , BOOL IOEditName) {
    /*刷新InputState*/
    if (InputState)
    {
        for (int i = 0; i < 12; i++)
        {
            if (IStateData[i] == -1)
            {
                CreateB[i].SetBitmaps(IDB_IOSLEEP, RGB(0, 0, 0));
            }
            if (IStateData[i] == 1)
            {
                CreateB[i].SetBitmaps(IDB_IOOPEN, RGB(0, 0, 0));
            }
            if (IStateData[i] == 0)
            {
                CreateB[i].SetBitmaps(IDB_IOCLOSE, RGB(0, 0, 0));
            }
        }
    }
    /*刷新OutputState*/
    if (OutputState)
    {
        for (int i = 0; i < 12; i++)
        {
            if (OStateData[i] == -1)
            {
                CreateB[i + 12].SetBitmaps(IDB_IOSLEEP, RGB(0, 0, 0));
            }
            if (OStateData[i] == 1)
            {
                CreateB[i + 12].SetBitmaps(IDB_IOOPEN, RGB(0, 0, 0));
            }
            if (OStateData[i] == 0)
            {
                CreateB[i + 12].SetBitmaps(IDB_IOCLOSE, RGB(0, 0, 0));
            }
        }
    }
    /*獲取IOEditName*/
    if (GetIOEditName)
    {
        for (int i = 0; i < 24; i++)
        {
            GetDlgItemText((i<12) ? IDC_EDITIOINAME + i : IDC_EDITIOONAME + i - 12, (i<12) ? m_EditInName[i] : m_EditOutName[i - 12]);
        }
    }
    /*刷新IOEditName*/
    if (IOEditName)
    {
        for (int i = 0; i < 24; i++)
        {
            SetDlgItemText((i<12) ? IDC_EDITIOINAME + i : IDC_EDITIOONAME + i - 12, (i<12) ? m_EditInName[i] : m_EditOutName[i - 12]);
        }
    }
    
}
/*刷新數值*/
void CIOState::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
#ifdef MOVE
	for (int i = 0; i < 12; i++)
	{
        if(m_InputState[i] != -1)
		    m_InputState[i] = MO_ReadPIOInput(i);
	}
#endif //MOVE
    if(!m_bBtnEnable)
        MyUpdateData(TRUE,m_InputState,FALSE,NULL,FALSE,FALSE);
	CPropertyPage::OnTimer(nIDEvent);
}
/*快捷鍵響應*/
BOOL CIOState::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->wParam == VK_F5)
    {
        OnBnClickedBtniorefresh();
    }
    if (pMsg->wParam == VK_F8)
    {
        OnBnClickedBtnsetfinish();
    }
    return CPropertyPage::PreTranslateMessage(pMsg);
}
