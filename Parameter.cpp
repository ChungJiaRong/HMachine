// Parameter.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Parameter.h"
#include "afxdialogex.h"


// CParameter 對話方塊

IMPLEMENT_DYNAMIC(CParameter, CPropertyPage)

CParameter::CParameter()
	: CPropertyPage(IDD_PARAMETER)
{
	m_ListCount = 11;
}
CParameter::~CParameter()
{
}
void CParameter::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITPARORIGINSPEED, OSpeed);
	DDX_Text(pDX, IDC_EDITPARLIMITSPEED, OLSpeed);
	DDX_Text(pDX, IDC_EDITPARHFSPEED, HSpeed.Init);
	DDX_Text(pDX, IDC_EDITPARHASPEED, HSpeed.Add);
	DDX_Text(pDX, IDC_EDITPARHENDSPEED, HSpeed.End);
	DDX_Text(pDX, IDC_EDITPARMFSPEED, MSpeed.Init);
	DDX_Text(pDX, IDC_EDITPARMASPEED, MSpeed.Add);
	DDX_Text(pDX, IDC_EDITPARMENDSPEED, MSpeed.End);
	DDX_Text(pDX, IDC_EDITPARLFSPEED, LSpeed.Init);
	DDX_Text(pDX, IDC_EDITPARLASPEED, LSpeed.Add);
	DDX_Text(pDX, IDC_EDITPARLENDSPEED, LSpeed.End);
	DDX_Text(pDX, IDC_EDITPARWFSPEED, WSpeed.Init);
	DDX_Text(pDX, IDC_EDITPARWASPEED, WSpeed.Add);
	DDX_Text(pDX, IDC_EDITPARWENDSPEED, WSpeed.End);
	DDX_Text(pDX, IDC_EDITPARRSPEED, RSpeed);
	DDX_Text(pDX, IDC_EDITPARRSPEED2, R2Speed);
	DDX_Text(pDX, IDC_EDITPARASPEED2, A2Speed);
	DDX_Text(pDX, IDC_EDITPARPOSLIMITY, Limit.Pos.x);
	DDX_Text(pDX, IDC_EDITPARPOSLIMITX, Limit.Pos.y);
	DDX_Text(pDX, IDC_EDITPARPOSLIMITZ, Limit.PosZ);
	DDX_Text(pDX, IDC_EDITPARNEDGLIMITX, Limit.Nedg.x);
	DDX_Text(pDX, IDC_EDITPARNEDGLIMITY, Limit.Nedg.y);
	DDX_Text(pDX, IDC_EDITPARNEDGLIMITZ, Limit.NedgZ);
    DDX_Text(pDX, IDC_EDITPARGLUEBEGIN, Glue.BeginWaitTime);
    DDX_Text(pDX, IDC_EDITPARGLUEEND, Glue.EndWaitTime);
    DDX_Text(pDX, IDC_EDITPARGLUEDISTANCE, Glue.StopGlueDistance);
    DDX_Text(pDX, IDC_EDITPARZUPSPEED, ZEndWay.FirstSpeed);
    DDX_Text(pDX, IDC_EDITPARZUPDISTANCE, ZEndWay.FirstUpDistance);
    DDX_Text(pDX, IDC_EDITPARGLUEZSPEED, ZEndWay.Speed);
    DDX_Text(pDX, IDC_EDITPARGLUEZHIGHT, ZEndWay.Hight);
    DDX_Text(pDX, IDC_EDITPARGLUEZWIDTH, ZEndWay.Width);
    DDX_CBIndex(pDX, IDC_CMBPARGLUEZTYPE, ZEndWay.Type);
	DDX_CBIndex(pDX, IDC_CMBPARTYPE, ARSpeedType);
	DDX_Control(pDX, IDC_LISTPAR, m_ListCtrlParame);
}
BEGIN_MESSAGE_MAP(CParameter, CPropertyPage)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTNPARSETFINISH, &CParameter::OnBnClickedBtnparsetfinish)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNPAREDITPAR, &CParameter::OnBnClickedBtnpareditpar)
	ON_BN_CLICKED(IDC_BTNPARINIT, &CParameter::OnBnClickedBtnparinit)
	ON_CBN_SELENDOK(IDC_CMBPARTYPE, &CParameter::OnSelendokCmbpartype)
	ON_STN_CLICKED(IDC_CHKPARHLIMIT, &CParameter::OnStnClickedChkparhlimit)
	ON_STN_CLICKED(IDC_CHKPARSLIMIT, &CParameter::OnStnClickedChkparslimit)
	ON_WM_TIMER()
    ON_CBN_SELENDOK(IDC_CMBPARGLUEZTYPE, &CParameter::OnCbnSelendokCmbparglueztype)
END_MESSAGE_MAP()
// CParameter 訊息處理常式
BOOL CParameter::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	// TODO:  在此加入額外的初始化
	/*載入圖片*/
	m_OnOffImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 1, 1);//創建圖標列表
	m_OnOffImageList.Add(AfxGetApp()->LoadIcon(IDI_OFF));
	m_OnOffImageList.Add(AfxGetApp()->LoadIcon(IDI_ON));
	/*設定Combox 速度類型*/
	((CComboBox*)GetDlgItem(IDC_CMBPARTYPE))->InsertString(0,_T("對稱梯形"));
	((CComboBox*)GetDlgItem(IDC_CMBPARTYPE))->InsertString(1,_T("對稱S形"));
	((CComboBox*)GetDlgItem(IDC_CMBPARTYPE))->InsertString(2,_T("不對稱梯形"));
	((CComboBox*)GetDlgItem(IDC_CMBPARTYPE))->InsertString(3,_T("不對稱S形"));
    /*設定Combox Z上升類型*/
    ((CComboBox*)GetDlgItem(IDC_CMBPARGLUEZTYPE))->InsertString(0, _T("正常"));
    ((CComboBox*)GetDlgItem(IDC_CMBPARGLUEZTYPE))->InsertString(1, _T("向後"));
    ((CComboBox*)GetDlgItem(IDC_CMBPARGLUEZTYPE))->InsertString(2, _T("直角向後"));
    ((CComboBox*)GetDlgItem(IDC_CMBPARGLUEZTYPE))->InsertString(3, _T("向前"));
    ((CComboBox*)GetDlgItem(IDC_CMBPARGLUEZTYPE))->InsertString(4, _T("直角向前"));
	/*初始列表*/
	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlParame.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlParame.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlParame.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 40, -1);
	m_ListCtrlParame.InsertColumn(1, _T("項目"), LVCFMT_CENTER, 100, -1);
	m_ListCtrlParame.InsertColumn(2, _T("狀態"), LVCFMT_CENTER, 160, -1);
	for (int i = 0; i < m_ListCount +13; i++)/*插入項目*/
	{
		CString StrBuff;
		StrBuff.Format(_T("%d"), i + 1);
		m_ListCtrlParame.InsertItem(i, (i<9) ? _T("00") + StrBuff : _T("0") + StrBuff);
	}
    /*工具提示*/
    m_tooltip.Create(this, TTS_ALWAYSTIP);  //  TTS_BALLOON | TTS_NOFADE | TTS_CLOSE
    m_tooltip.Activate(TRUE);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNPARSETFINISH), TT_BTNPARSETFINISH);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNPAREDITPAR), TT_BTNPAREDITPAR);
    m_tooltip.AddTool(GetDlgItem(IDC_BTNPARINIT), TT_BTNPARINIT);
    m_tooltip.AddTool(GetDlgItem(IDC_CHKPARHLIMIT), TT_CHKPARHLIMIT);
    m_tooltip.AddTool(GetDlgItem(IDC_CHKPARSLIMIT), TT_CHKPARSLIMIT);
    m_tooltip.SetDelayTime(TTDT_INITIAL, 1000);
    m_tooltip.SetDelayTime(TTDT_AUTOPOP, 10000);
    /*載入參數資料*/
    CFileStatus FileStatus;//檔案屬性
    CFile File;
    if (!File.GetStatus(GetModulePath()+ _T("Parameter.txt"), FileStatus)) {
        InitParameter();
        WriteParamData();
    }
    else {
        ReadParamData();
    }
	RefreshData();//刷新頁面資料
	SetParameter();//寫入軸卡參數
	SetTimer(1, 500, 0);//開啟刷新
   
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
void CParameter::OnPaint()
{
	CPaintDC dc(this);
	for (int i = IDC_EDITPARORIGINSPEED; i <= IDC_EDITPARGLUEZWIDTH; i++)
	{
		EditTextVertical((CEdit*)GetDlgItem(i));
	}
}
void CParameter::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	CWnd *pWnd;
	for (int i = IDC_LISTPAR; i <= IDC_BTNPARSETFINISH; i++)
	{
		pWnd = GetDlgItem(i);
		ChangeSize(pWnd, cx, cy);
	}
	GetClientRect(&m_InitRect);
}
/*改變控件大小*/
void CParameter::ChangeSize(CWnd* pWnd, int cx, int cy)
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
/*初始化參數*/
void CParameter::InitParameter() {
	Limit.Hard = TRUE;
	Limit.Soft = FALSE;
	Limit.Pos = Limit.Nedg = Limit.PosZ = Limit.NedgZ = 0;
	OSpeed = 20000;
	OLSpeed = 1000;
	HSpeed.Init = 15000;
	MSpeed.Init = 10000;
	LSpeed.Init = 1000;
	HSpeed.End = 40000;
	MSpeed.End = 25000;
	LSpeed.End = 5000;
	HSpeed.Add = MSpeed.Add = LSpeed.Add = 8000;
	WSpeed.Init = 10000;
	WSpeed.End = 30000;
	WSpeed.Add = 10000;
	ARSpeedType = 0;
	RSpeed = 0;
	R2Speed = 0;
	A2Speed = 0;
    Glue.BeginWaitTime = 0;
    Glue.EndWaitTime = 0;
    Glue.StopGlueDistance = 0;
    ZEndWay.FirstSpeed = 0;
    ZEndWay.FirstUpDistance = 0;
    ZEndWay.Type = 0;
    ZEndWay.Speed = 0;
    ZEndWay.Hight = 0;
    ZEndWay.Width = 0;
}
/*寫入檔案*/
void CParameter::WriteParamData() {
	CFile File;
	if (File.Open(GetModulePath()+_T("Parameter.txt"), CFile::modeCreate | CFile::modeWrite)) {
		CArchive ar(&File, CArchive::store);
        ar << OSpeed << OLSpeed
            << HSpeed.Init << HSpeed.Add << HSpeed.End
            << MSpeed.Init << MSpeed.Add << MSpeed.End
            << LSpeed.Init << LSpeed.Add << LSpeed.End
            << WSpeed.Init << WSpeed.Add << WSpeed.End
            << ARSpeedType << RSpeed << R2Speed << A2Speed
            << Limit.Hard << Limit.Soft << Limit.Pos << Limit.Nedg << Limit.PosZ << Limit.NedgZ
            << Glue.BeginWaitTime << Glue.EndWaitTime << Glue.StopGlueDistance
            << ZEndWay.FirstSpeed << ZEndWay.FirstUpDistance << ZEndWay.Type << ZEndWay.Speed << ZEndWay.Hight << ZEndWay.Width;
	}
	File.Close(); 
}
/*讀取檔案*/
void CParameter::ReadParamData() {
	CFile File;
	if (File.Open(GetModulePath()+_T("Parameter.txt"), CFile::modeRead)) {//打開檔案
		CArchive ar(&File, CArchive::load);//讀取入檔案
        ar >> OSpeed >> OLSpeed
            >> HSpeed.Init >> HSpeed.Add >> HSpeed.End
            >> MSpeed.Init >> MSpeed.Add >> MSpeed.End
            >> LSpeed.Init >> LSpeed.Add >> LSpeed.End
            >> WSpeed.Init >> WSpeed.Add >> WSpeed.End
            >> ARSpeedType >> RSpeed >> R2Speed >> A2Speed
            >> Limit.Hard >> Limit.Soft >> Limit.Pos >> Limit.Nedg >> Limit.PosZ >> Limit.NedgZ
            >> Glue.BeginWaitTime >> Glue.EndWaitTime >> Glue.StopGlueDistance
            >> ZEndWay.FirstSpeed >> ZEndWay.FirstUpDistance >> ZEndWay.Type >> ZEndWay.Speed >> ZEndWay.Hight >> ZEndWay.Width;
		File.Close();
	}
}
/*刷新數值*/
void CParameter::RefreshData() {
	CStringArray StrTable;
	StrTable.Add(_T("X軸硬體極限")); StrTable.Add(_T("Y軸硬體極限")); StrTable.Add(_T("Z軸硬體極限"));
	StrTable.Add(_T("X軸軟體極限")); StrTable.Add(_T("Y軸軟體極限")); StrTable.Add(_T("Z軸軟體極限"));
	StrTable.Add(_T("X軸硬體極限狀態")); StrTable.Add(_T("Y軸硬體極限狀態")); StrTable.Add(_T("Z軸硬體極限狀態"));
	StrTable.Add(_T("軸驅動速度"));  StrTable.Add(_T("軸加減速度"));
	UpdateData(FALSE);
	((CStatic*)GetDlgItem(IDC_CHKPARHLIMIT))->SetIcon(m_OnOffImageList.ExtractIcon(Limit.Hard));
	((CStatic*)GetDlgItem(IDC_CHKPARSLIMIT))->SetIcon(m_OnOffImageList.ExtractIcon(Limit.Soft));
	for (int i = 0; i < m_ListCount; i++)
	{
		SetListItemText(m_ListCtrlParame, i, 1, StrTable.GetAt(i));
	} 
}
/*EDIT控件文字垂直置中*/
void CParameter::EditTextVertical(CEdit *m_EditCtrl) {
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
/*編輯完成*/
void CParameter::OnBnClickedBtnparsetfinish()
{
	CString StrBuff;
	GetDlgItemText(IDC_BTNPAREDITPAR, StrBuff);
	if (StrBuff == _T("取消編輯"))
	{
		SetDlgItemText(IDC_BTNPAREDITPAR, _T("編輯參數"));
		for (int i = IDC_EDITPARORIGINSPEED; i <= IDC_EDITPARGLUEZWIDTH; i++)
		{
			GetDlgItem(i)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_CMBPARTYPE)->EnableWindow(FALSE);
        GetDlgItem(IDC_CMBPARGLUEZTYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHKPARHLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHKPARSLIMIT)->EnableWindow(FALSE);
		UpdateData(TRUE);
		WriteParamData();
		RefreshData();
		SetParameter();
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("參數設定"), _T("編輯完成"));
	}
}
/*編輯參數*/
void CParameter::OnBnClickedBtnpareditpar()
{
	CString StrBuff;
	GetDlgItemText(IDC_BTNPAREDITPAR, StrBuff);
	if (StrBuff == _T("編輯參數"))
	{
        GetDlgItem(IDC_EDITPARORIGINSPEED)->SetFocus();
		SetDlgItemText(IDC_BTNPAREDITPAR, _T("取消編輯"));
		for (int i = IDC_EDITPARORIGINSPEED; i <= IDC_EDITPARWENDSPEED; i++)
		{
			GetDlgItem(i)->EnableWindow(TRUE);
		}
        for (int i = IDC_EDITPARGLUEBEGIN; i <= IDC_EDITPARGLUEZHIGHT; i++)
        {
            GetDlgItem(i)->EnableWindow(TRUE);
        }
		GetDlgItem(IDC_CMBPARTYPE)->EnableWindow(TRUE);
        GetDlgItem(IDC_CMBPARGLUEZTYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHKPARHLIMIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHKPARSLIMIT)->EnableWindow(TRUE);
		OnSelendokCmbpartype();
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("參數設定"), _T("編輯參數"));
	}                                        
	else
	{
		SetDlgItemText(IDC_BTNPAREDITPAR, _T("編輯參數"));
		for (int i = IDC_EDITPARORIGINSPEED; i <= IDC_EDITPARGLUEZWIDTH; i++)
		{
			GetDlgItem(i)->EnableWindow(FALSE);
		}
        GetDlgItem(IDC_CMBPARTYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CMBPARGLUEZTYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHKPARHLIMIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHKPARSLIMIT)->EnableWindow(FALSE);
		RefreshData();
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("參數設定"), _T("取消編輯"));
	}
}
/*回歸初始設定*/
void CParameter::OnBnClickedBtnparinit()
{
	if (MessageBox(_T("你確定要回歸初始化?"), _T("題示"), MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
	{
		InitParameter();
		WriteParamData();
		RefreshData();
		WriteHistory(((CHM_MachineApp*)AfxGetApp())->HistoryFile, ((CHM_MachineApp*)AfxGetApp())->UserID, _T("參數設定"), _T("回歸初始設定"));
	}
}
/*選擇加減速型態*/
void CParameter::OnSelendokCmbpartype()
{
	UpdateData(TRUE);
	switch(ARSpeedType)
	{
	case 0:
		GetDlgItem(IDC_EDITPARRSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITPARRSPEED2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITPARASPEED2)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_EDITPARRSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITPARRSPEED2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITPARASPEED2)->EnableWindow(TRUE);
		break;
	case 2:
		GetDlgItem(IDC_EDITPARRSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITPARRSPEED2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDITPARASPEED2)->EnableWindow(FALSE);
		break;
	case 3:
		GetDlgItem(IDC_EDITPARRSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITPARRSPEED2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDITPARASPEED2)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
}
/*選擇Z上升形態*/
void CParameter::OnCbnSelendokCmbparglueztype()
{
    UpdateData(TRUE);
    switch (ZEndWay.Type)
    {
    case 1:
        GetDlgItem(IDC_EDITPARGLUEZWIDTH)->EnableWindow(TRUE);
        break;
    case 3:
        GetDlgItem(IDC_EDITPARGLUEZWIDTH)->EnableWindow(TRUE);
        break;
    default:
        GetDlgItem(IDC_EDITPARGLUEZWIDTH)->EnableWindow(FALSE);
        break;
    }
}
/*硬體極限開關*/
void CParameter::OnStnClickedChkparhlimit()
{
	if (Limit.Hard)
	{
		if (MessageBox(_T("你確定要關掉硬體極限?\n如造成嚴重損壞請自行負責!"), _T("題示"), MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
		{
			Limit.Hard = FALSE;
		}
	}
	else
	{
		Limit.Hard = TRUE;
	}
	((CStatic*)GetDlgItem(IDC_CHKPARHLIMIT))->SetIcon(m_OnOffImageList.ExtractIcon(Limit.Hard));
}
/*軟體極限開關*/
void CParameter::OnStnClickedChkparslimit()
{
	if (Limit.Soft)
	{
		Limit.Soft = FALSE;
		for (int i = IDC_EDITPARPOSLIMITY; i <= IDC_EDITPARNEDGLIMITZ; i++)
		{
			GetDlgItem(i)->EnableWindow(FALSE);
		}
	}
	else
	{
		Limit.Soft = TRUE;
		for (int i = IDC_EDITPARPOSLIMITY; i <= IDC_EDITPARNEDGLIMITZ; i++)
		{
			GetDlgItem(i)->EnableWindow(TRUE);
		}
	}
	((CStatic*)GetDlgItem(IDC_CHKPARSLIMIT))->SetIcon(m_OnOffImageList.ExtractIcon(Limit.Soft));
}
/*設定參數*/
void CParameter::SetParameter() {
#ifdef MOVE
	MO_SetHardLim(7,Limit.Hard);
	MO_SetSoftLim(7,Limit.Soft);
	if (Limit.Soft)
	{
		MO_SetCompSoft(0, Limit.Pos.x, Limit.Pos.y, Limit.PosZ);
		MO_SetCompSoft(1, Limit.Nedg.x, Limit.Nedg.y, Limit.NedgZ);
	}
	MO_SetAccType(ARSpeedType);
	MO_SetDeceleration(7, RSpeed);
	MO_SetJerk(7, A2Speed);
	MO_SetDJerk(7, R2Speed);
	MO_SetDecPation(0, 0, 0);
#endif //MOVE
}
/*設定列表文字*/
void CParameter::SetListItemText(CListCtrl &m_ListCtrl,UINT Item,UINT Count,...) {
	va_list ap = NULL;
	CString* Str;
	va_start(ap, Count);
	for (int i = 1; i <= Count; i++) {
		Str = va_arg(ap, CString*);
		m_ListCtrl.SetItemText(Item, i, (LPCTSTR)Str);
	}
	va_end(ap);
}
/*刷新速度*/
void CParameter::OnTimer(UINT_PTR nIDEvent)
{
	CString StrBuff;
	bool HardLimit[3];
	memset(HardLimit, FALSE, sizeof(HardLimit));
	bool SoftLimit[3];
	memset(SoftLimit, FALSE, sizeof(SoftLimit));
	bool HardLimitTF[3];
	memset(HardLimitTF, FALSE, sizeof(HardLimitTF));
	int  RunHardLimit[3];
	memset(RunHardLimit, NULL, sizeof(int));
#ifdef MOVE
	MO_ReadHardLim(HardLimit[0], HardLimit[1], HardLimit[2]);
	MO_ReadSoftLim(SoftLimit[0], SoftLimit[1], SoftLimit[2]);
	MO_ReadRunHardLim(RunHardLimit[0], HardLimitTF[0], RunHardLimit[1], HardLimitTF[1], RunHardLimit[2], HardLimitTF[2]);
	StrBuff.Format(_T("%d"), MO_ReadSpeed(0));
	m_ListCtrlParame.SetItemText(9, 2, StrBuff);
	StrBuff.Format(_T("%d"), MO_ReadAccDec(0));
	m_ListCtrlParame.SetItemText(10, 2, StrBuff);
    m_ListCtrlParame.SetItemText(11, 2, MO_StreamToUnit(MO_ReadReg(0, 0)));
    m_ListCtrlParame.SetItemText(12, 2, MO_StreamToUnit(MO_ReadReg(1, 0)));
    m_ListCtrlParame.SetItemText(13, 2, MO_StreamToUnit(MO_ReadReg(2, 0)));
    m_ListCtrlParame.SetItemText(14, 2, MO_StreamToUnit(MO_ReadReg(3, 0)));
    m_ListCtrlParame.SetItemText(15, 2, MO_StreamToUnit(MO_ReadReg(0, 1)));
    m_ListCtrlParame.SetItemText(16, 2, MO_StreamToUnit(MO_ReadReg(1, 1)));
    m_ListCtrlParame.SetItemText(17, 2, MO_StreamToUnit(MO_ReadReg(2, 1)));
    m_ListCtrlParame.SetItemText(18, 2, MO_StreamToUnit(MO_ReadReg(3, 1)));
    m_ListCtrlParame.SetItemText(19, 2, MO_StreamToUnit(MO_ReadReg(0, 2)));
    m_ListCtrlParame.SetItemText(20, 2, MO_StreamToUnit(MO_ReadReg(1, 2)));
    m_ListCtrlParame.SetItemText(21, 2, MO_StreamToUnit(MO_ReadReg(2, 2)));
    m_ListCtrlParame.SetItemText(22, 2, MO_StreamToUnit(MO_ReadReg(3, 2)));
#endif // MOVE
	for (int i = 0; i < 3; i++)
	{
		if (HardLimit[i])
		{
			m_ListCtrlParame.SetItemText(i, 2, _T("TRUE"));
		}
		else
		{
			m_ListCtrlParame.SetItemText(i, 2, _T("FALSE"));
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (SoftLimit[i])
		{
			m_ListCtrlParame.SetItemText(i + 3, 2, _T("TRUE"));
		}
		else
		{
			m_ListCtrlParame.SetItemText(i + 3, 2, _T("FALSE"));
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (HardLimitTF[i])
		{
			if (RunHardLimit[i] == -1)
				m_ListCtrlParame.SetItemText(i + 6, 2, _T("不在極限上"));
			else if(RunHardLimit[i] == 1)
				m_ListCtrlParame.SetItemText(i + 6, 2, _T("在正極限上"));
			else
				m_ListCtrlParame.SetItemText(i + 6, 2, _T("在負極限上"));
		}
		else
		{
			m_ListCtrlParame.SetItemText(i + 6, 2, _T("極限開關損壞"));
		}
	}
	CPropertyPage::OnTimer(nIDEvent);
}
/*快捷鍵*/
BOOL CParameter::PreTranslateMessage(MSG* pMsg)
{
    /*工具提示*/
    if (m_tooltip.m_hWnd != NULL)
    {
        m_tooltip.RelayEvent(pMsg);
    }
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
    {
        CWnd *mwnd = GetNextDlgTabItem(GetFocus());
        if (mwnd)
        {
            mwnd->SetFocus();
            ((CEdit*)GetDlgItem(mwnd->GetDlgCtrlID()))->SetSel(20, 0);
            return TRUE;

        }
    }
    return CPropertyPage::PreTranslateMessage(pMsg);
}



