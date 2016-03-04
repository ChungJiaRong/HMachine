// Administration.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Administration.h"
#include "afxdialogex.h"


// CAdministration 對話方塊

IMPLEMENT_DYNAMIC(CAdministration, CDialogEx)

CAdministration::CAdministration(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADMINISTRATION, pParent)
	,m_ActionChoose(0)
	,m_ListCount(0)
{
}
CAdministration::~CAdministration()
{
    m_UserData.FreeExtra();
    m_UserData.RemoveAll();
}
void CAdministration::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTADMINUSER, m_ListCtrlUser);
}
BEGIN_MESSAGE_MAP(CAdministration, CDialogEx)
	ON_BN_CLICKED(IDC_BTNADMINNEW, &CAdministration::OnBnClickedBtnadminnew)
	ON_BN_CLICKED(IDC_BTNADMINMODIFY, &CAdministration::OnBnClickedBtnadminmodify)
	ON_BN_CLICKED(IDC_BTNADMINDELETE, &CAdministration::OnBnClickedBtnadmindelete)
	ON_BN_CLICKED(IDC_BTNADMINCHECK, &CAdministration::OnBnClickedBtnadmincheck)
	ON_NOTIFY(NM_CLICK, IDC_LISTADMINUSER, &CAdministration::OnClickListadminuser)
END_MESSAGE_MAP()
// CAdministration 訊息處理常式
BOOL CAdministration::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此加入額外的初始化
	//((CButton*)GetDlgItem(IDC_RAINEWOPERATOR))->SetCheck(TRUE);
	CHeaderCtrl *pHeaderCtrl;
	pHeaderCtrl = (CHeaderCtrl*)m_ListCtrlUser.GetHeaderCtrl();//固定標題列寬
	pHeaderCtrl->EnableWindow(FALSE);
	m_ListCtrlUser.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ListCtrlUser.InsertColumn(0, _T("編號"), LVCFMT_CENTER, 45, -1);
	m_ListCtrlUser.InsertColumn(1, _T("帳號"), LVCFMT_CENTER, 118, -1);
	m_ListCtrlUser.InsertColumn(2, _T("密碼"), LVCFMT_CENTER, 118, -1);
	m_ListCtrlUser.InsertColumn(3, _T("職位稱"), LVCFMT_CENTER, 60, -1);
	GetDlgItem(IDC_BTNADMINMODIFY)->EnableWindow(FALSE);//關閉修改
	GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(FALSE);//關閉刪除
	ReadAccountData();
	AccountListRefresh();
    ((CEdit*)GetDlgItem(IDC_EDITNEWUSERID))->SetCueBanner(_T("注意帳號不可重複"), true);
    ((CEdit*)GetDlgItem(IDC_EDITNEWPASSWORD))->SetCueBanner(_T("密碼請輸入六位以上"), true);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
/*新增*/
void CAdministration::OnBnClickedBtnadminnew()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString StrBuff;
	GetDlgItem(IDC_BTNADMINNEW)->GetWindowText(StrBuff);
	((CButton*)GetDlgItem(IDC_RADNEWENGINEER))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(FALSE);
	if (StrBuff == _T("新增"))
	{
		GetDlgItem(IDC_BTNADMINNEW)->SetWindowText(_T("取消新增"));//設置按紐文字
		GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(FALSE);//關閉刪除
		GetDlgItem(IDC_BTNADMINMODIFY)->EnableWindow(FALSE);//關閉修改
		GetDlgItem(IDC_LISTADMINUSER)->EnableWindow(FALSE);//關閉使用者列表
		for (int i = 511; i <= IDC_BTNADMINCHECK; i++)//開啟編輯
		{
			GetDlgItem(i)->EnableWindow(TRUE);
		}
		GetDlgItem(IDC_EDITNEWUSERID)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDITNEWPASSWORD)->SetWindowText(_T(""));
		((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(TRUE);
		m_ActionChoose = 1;
	}
	else 
	{  
		GetDlgItem(IDC_BTNADMINNEW)->SetWindowText(_T("新增"));//設置按紐文字
		GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(TRUE);//開啟刪除
		GetDlgItem(IDC_BTNADMINMODIFY)->EnableWindow(TRUE);//開啟修改
		GetDlgItem(IDC_LISTADMINUSER)->EnableWindow(TRUE);//開啟使用者列表
		for (int i = 511; i <= IDC_BTNADMINCHECK; i++)//關閉編輯控件
		{
			GetDlgItem(i)->EnableWindow(FALSE);
		}
        SetDlgItemText(IDC_EDITNEWUSERID, _T(""));
        SetDlgItemText(IDC_EDITNEWPASSWORD, _T(""));	
		if (!m_ActionChoose)//新增成功
		{
			m_ListCtrlUser.SetItemState(m_ListCount, LVIS_SELECTED, LVIS_SELECTED);
			m_ListCtrlUser.SetSelectionMark(m_ListCount);
		}
        int istat = m_ListCtrlUser.GetSelectionMark();
		if (istat != -1)
		{
			GetDlgItem(IDC_EDITNEWUSERID)->SetWindowText(m_UserData[(m_ActionChoose ? istat : m_ListCount) * 3]);
			GetDlgItem(IDC_EDITNEWPASSWORD)->SetWindowText(m_UserData[(m_ActionChoose ? istat : m_ListCount) * 3 + 1]);
			if (m_UserData[(m_ActionChoose ? istat : m_ListCount) * 3 + 2] == _T("工程師"))
			{
				((CButton*)GetDlgItem(IDC_RADNEWENGINEER))->SetCheck(TRUE);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(TRUE);
			}
		}
	} 
}
/*修改*/
void CAdministration::OnBnClickedBtnadminmodify()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString StrBuff;
	GetDlgItem(IDC_BTNADMINMODIFY)->GetWindowText(StrBuff);
	int istat = m_ListCtrlUser.GetSelectionMark();
	if (StrBuff == _T("修改"))
	{
		GetDlgItem(IDC_BTNADMINMODIFY)->SetWindowText(_T("取消修改"));
		for (int i = 512; i <= IDC_BTNADMINCHECK; i++)//開啟編輯
		{
			GetDlgItem(i)->EnableWindow(TRUE);
		}
		GetDlgItem(IDC_BTNADMINNEW)->EnableWindow(FALSE);//關閉新增
		GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(FALSE);//關閉刪除
		GetDlgItem(IDC_LISTADMINUSER)->EnableWindow(FALSE);//關閉使用者列表
		m_ActionChoose = 2;
	}
	else
	{
		GetDlgItem(IDC_BTNADMINMODIFY)->SetWindowText(_T("修改"));
		for (int i = 512; i <= IDC_BTNADMINCHECK; i++)//關閉編輯
		{
			GetDlgItem(i)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_BTNADMINNEW)->EnableWindow(TRUE);//開啟新增
		GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(TRUE);//開啟刪除
		GetDlgItem(IDC_LISTADMINUSER)->EnableWindow(TRUE);//關閉使用者列表
		if (m_ActionChoose)//未修改成功
		{
			((CButton*)GetDlgItem(IDC_RADNEWENGINEER))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(FALSE);
			GetDlgItem(IDC_EDITNEWPASSWORD)->SetWindowText(m_UserData[istat * 3 + 1]);
			if (m_UserData[istat * 3 + 2] == _T("工程師"))
			{
				((CButton*)GetDlgItem(IDC_RADNEWENGINEER))->SetCheck(TRUE);
			}
			else
			{
				((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(TRUE);
			}
		}
	}
}
/*刪除*/
void CAdministration::OnBnClickedBtnadmindelete()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	int istat = m_ListCtrlUser.GetSelectionMark();
	m_UserData.RemoveAt(istat * 3);
	m_UserData.RemoveAt(istat * 3);
	m_UserData.RemoveAt(istat * 3);
	m_ListCtrlUser.DeleteItem(istat);//刪除List項目
	m_ListCount--;
	SetDlgItemText(IDC_EDITNEWUSERID, _T(""));
	SetDlgItemText(IDC_EDITNEWPASSWORD, _T(""));
    GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(FALSE);//關閉刪除
    GetDlgItem(IDC_BTNADMINMODIFY)->EnableWindow(FALSE);//關閉修改
	AccountListRefresh();//帳戶列表刷新
	WriteAccountData();
    MessageBox(_T("刪除成功!"));
}
/*確認*/
void CAdministration::OnBnClickedBtnadmincheck()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString UserID, UserPwd,StrBuff;
	switch (m_ActionChoose)
	{
	case 1:
        GetDlgItemText(IDC_EDITNEWUSERID, UserID);
        GetDlgItemText(IDC_EDITNEWPASSWORD, UserPwd);
        if (!CheckUserID(UserID))
        {
            break;
        }
        if (!CheckUserPassWord(UserPwd))
        {
            break;
        }
        m_ListCtrlUser.InsertItem(m_ListCount, _T(""));
		m_UserData.Add(UserID);
		m_UserData.Add(UserPwd);
		switch (GetCheckedRadioButton(IDC_RADNEWENGINEER, IDC_RADNEWOPERATOR))
		{
		case IDC_RADNEWENGINEER:
			m_UserData.Add(_T("工程師"));
			break;
		case IDC_RADNEWOPERATOR:
			m_UserData.Add(_T("操作員"));
			break;
		default:
			MessageBox(_T("程式出現錯誤!"));
            return;
		}
		m_ActionChoose = 0;
		OnBnClickedBtnadminnew();
		m_ListCount++;
		AccountListRefresh();//帳戶列表刷新
		WriteAccountData();
        MessageBox(_T("新增成功!"));
		break;
	case 2: 
		int istat = m_ListCtrlUser.GetSelectionMark();
        GetDlgItemText(IDC_EDITNEWPASSWORD, UserPwd);
        if (!CheckUserPassWord(UserPwd))
        {
            break;
        }
		m_UserData.SetAt(istat * 3 + 1, UserPwd);
		switch (GetCheckedRadioButton(IDC_RADNEWENGINEER, IDC_RADNEWOPERATOR))
		{
		case IDC_RADNEWENGINEER:
			m_UserData.SetAt(istat * 3 + 2, _T("工程師"));
			break;
		case IDC_RADNEWOPERATOR:
			m_UserData.SetAt(istat * 3 + 2, _T("操作員"));
			break;
		default:
			MessageBox(_T("程式出現錯誤!"));
            return;
		} 
		m_ActionChoose = 0;
		OnBnClickedBtnadminmodify();
		AccountListRefresh();//帳戶列表刷新
		WriteAccountData();
        MessageBox(_T("修改成功!"));
		break;
	}
}
/*顯示選取列表中的項*/
void CAdministration::OnClickListadminuser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此加入控制項告知處理常式程式碼
	int istat = m_ListCtrlUser.GetSelectionMark();//獲取選擇的項
	if (istat >= 0)
	{
		GetDlgItem(IDC_BTNADMINMODIFY)->EnableWindow(TRUE);//開啟修改
		GetDlgItem(IDC_BTNADMINDELETE)->EnableWindow(TRUE);//開啟刪除
		((CButton*)GetDlgItem(IDC_RADNEWENGINEER))->SetCheck(FALSE);//清除選取
		((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(FALSE);
		GetDlgItem(IDC_EDITNEWUSERID)->SetWindowText(m_ListCtrlUser.GetItemText(istat, 1));
		GetDlgItem(IDC_EDITNEWPASSWORD)->SetWindowText(m_ListCtrlUser.GetItemText(istat, 2));
		if (m_ListCtrlUser.GetItemText(istat, 3) == _T("工程師"))
		{
			((CButton*)GetDlgItem(IDC_RADNEWENGINEER))->SetCheck(TRUE);
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADNEWOPERATOR))->SetCheck(TRUE);
		}
	}
	*pResult = 0;
}
/*帳戶列表刷新*/
void CAdministration::AccountListRefresh() {
	CString StrBuff;
	if (m_ListCount > 0)
	{
		for (int i = 0; i < m_ListCount; i++)
		{
			StrBuff.Format(_T("%d"), i+1);
			m_ListCtrlUser.SetItemText(i, 0, StrBuff);
			m_ListCtrlUser.SetItemText(i, 1, m_UserData[i * 3]);
			m_ListCtrlUser.SetItemText(i, 2, m_UserData[i * 3+1]);
			m_ListCtrlUser.SetItemText(i, 3, m_UserData[i * 3+2]);
		}
	}
}
/*讀出使用者資料*/
void CAdministration::ReadAccountData() {
	m_ListCtrlUser.DeleteAllItems();//清空列表
	CFile File;
	CString StrBuff;
	if (File.Open(GetModulePath()+_T("Account.dat"), CFile::modeRead)) {//打開檔案
		CArchive ar(&File, CArchive::load);//讀取入檔案
		ar >> m_ListCount;//讀出使用者總數
		m_UserData.SetSize(m_ListCount*3);
		for (int i = 0; i < m_ListCount * 3; i++) {
			ar >> m_UserData[i];//讀出資料
			if (!(i % 3))
			{
				m_ListCtrlUser.InsertItem(i,_T(""));//增加項目
			}
		}
		File.Close();
	}
}
/*寫入使用者資料*/
void CAdministration::WriteAccountData() {
	CFile File;
	if (File.Open(GetModulePath()+_T("Account.dat"), CFile::modeCreate | CFile::modeWrite)) {
		CArchive ar(&File, CArchive::store);
		ar << m_ListCount;//寫入使用者總數
		for (int i = 0; i < m_ListCount * 3; i++) {
			ar << m_UserData[i];//寫入使用者資料
		}     
	}
	File.Close();//要寫在if外
}
//檢查帳號是否重復
BOOL CAdministration::CheckUserID(CString UserID) {
    for (int i = 0; i < m_ListCount; i++)
    {
        if (UserID == m_UserData[i*3]) {
            MessageBox(_T("帳號已存在!"));
            return FALSE;
        }
    }
    return TRUE;
}
//檢查密碼是否符合規範(長度不得小於6位元、密碼須包含大小寫字母、數字及特殊符號)
BOOL CAdministration::CheckUserPassWord(CString UserPwd){
    int iLength = UserPwd.GetLength();
    if (iLength < 6)
    {
        MessageBox(_T("密碼長度至少6位"), NULL, MB_OK | MB_ICONERROR);
        return FALSE;
    }
    for (int i = 0; i<iLength; i++)
    {
        int iCharacter = (int)UserPwd.GetAt(i);
        if (!(iCharacter >= 0x30 && iCharacter <= 0x39    //數位集合[0x30, 0x39](ASCII碼字元對應的十六進位值)
            || iCharacter >= 0x61 && iCharacter <= 0x7a   //小寫字母集合[0x61, 0x7a]
            || iCharacter >= 0x41 && iCharacter <= 0x5a)) //大寫字母集合[0x41, 0x5a]
        {
            MessageBox(_T("密碼只允許大小寫字母、數字!"), NULL, MB_OK | MB_ICONERROR);
            return FALSE;
        }
    }
    return TRUE;
}
/*屏蔽Enter鍵*/
void CAdministration::OnOK()
{
    // TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
    //CDialogEx::OnOK();
}
