// Account.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Administration.h"


// CAccount 對話方塊

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLogin::~CLogin()
{
   /* m_UserData.FreeExtra();
    m_UserData.RemoveAll();*/
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

// CAccount 訊息處理常式
void CLogin::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	//SetWindowLong(this->m_hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW);//設置窗口在下面任務覽顯示
    ::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);//設置視窗永遠在最上層
	AfxGetMainWnd()->ShowWindow(SW_HIDE);//不能寫在Create，因為程式未創建完成就被隱藏會出錯
	CenterWindow();//顯示在螢幕中間                                                                    
}
/*登入*/
void CLogin::OnOK()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	CString UserID, UserPwd;
	GetDlgItemText(IDC_EDITACCOUNT, UserID);
	GetDlgItemText(IDC_EDITPASSWORD, UserPwd);
	CFile File;
	int UserCount = 0;
	if (File.Open(GetModulePath()+_T("Account.dat"), CFile::modeRead)) {//打開檔案
		CArchive ar(&File, CArchive::load);//讀取入檔案
		ar >> UserCount;
		m_UserData.SetSize(UserCount * 3);
		for (int i = 0; i < UserCount * 3; i++) {
			ar >> m_UserData[i];
			//m_UserData.SetAt(i,StrBuff);
		}
		File.Close();
	}
    if (UserID == _T("root") && UserPwd == _T("0000")) {//管理員帳密
        ((CHM_MachineApp*)AfxGetApp())->UserID = UserID;
        ((CHM_MachineApp*)AfxGetApp())->UserPwd = UserPwd;
        ((CHM_MachineApp*)AfxGetApp())->Post = _T("工程師");
        CDialogEx::OnOK();//關閉對話框返回ok
    }
	else if (UserID == _T("admin") && UserPwd == _T("123")) {//管理員帳密
		ShowWindow(SW_HIDE);
		CAdministration Dlg;
		Dlg.DoModal();
		SetDlgItemText(IDC_EDITACCOUNT,_T(""));
		SetDlgItemText(IDC_EDITPASSWORD,_T(""));
		GetDlgItem(IDC_EDITACCOUNT)->SetFocus();//焦點回到輸入帳號
		ShowWindow(SW_SHOW);
		//CDialogEx::OnOK();
	}
	else
	{
		BOOL Check = FALSE;
		for (int i = 0; i < UserCount; i++) {
			if (UserID == m_UserData[i * 3] && UserPwd == m_UserData[i * 3 + 1]) {
				((CHM_MachineApp*)AfxGetApp())->UserID = UserID;
				((CHM_MachineApp*)AfxGetApp())->UserPwd = UserPwd;
				((CHM_MachineApp*)AfxGetApp())->Post = m_UserData[i * 3 + 2];
				Check = TRUE;
				CDialogEx::OnOK();//關閉對話框返回ok
			}
		}
		if (!Check)
		{
			MessageBox(_T("你的帳密有誤!!"));
            SetDlgItemText(IDC_EDITACCOUNT, _T(""));
            SetDlgItemText(IDC_EDITPASSWORD, _T(""));
		}
	}
}
/*離開軟體*/
void CLogin::OnCancel()
{
	// TODO: 在此加入特定的程式碼和 (或) 呼叫基底類別
	if (MessageBox(_T("你確定要離開!"), _T("題示"), MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
	{
		CDialogEx::OnCancel();
	}
}

