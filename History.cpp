// History.cpp : 實作檔
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "History.h"
#include "afxdialogex.h"


// CHistory 對話方塊

IMPLEMENT_DYNAMIC(CHistory, CDialogEx)

CHistory::CHistory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HISTORY, pParent)
{

}

CHistory::~CHistory()
{
}

void CHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LISTHIS, m_HistoryList);
}


BEGIN_MESSAGE_MAP(CHistory, CDialogEx)
END_MESSAGE_MAP()


// CHistory 訊息處理常式
BOOL CHistory::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此加入額外的初始化
    ReadAccountData();//讀取使用者帳戶
    /*設定列表*/
    m_HistoryList.InsertColumn(0, _T("備註"), LVCFMT_FIXED_WIDTH, 220);
    m_HistoryList.InsertColumn(0, _T("Action"), LVCFMT_FIXED_WIDTH, 150);
    m_HistoryList.InsertColumn(0, _T("Account"), LVCFMT_FIXED_WIDTH, 150);
    m_HistoryList.InsertColumn(0, _T("Time"), LVCFMT_FIXED_WIDTH, 100);
    m_HistoryList.InsertColumn(0, _T("Date"), LVCFMT_FIXED_WIDTH, 100);
    /*設定帳號Combox*/
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(0, _T("ALL"));
    for (int i = 0; i < m_AccoutName.GetCount(); i++) {
        ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(i + 1, m_AccoutName.GetAt(i));
    }
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->SetCurSel(0);
    /*設定動作Combox*/
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(0, _T("ALL"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(1, _T("料件加工"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(2, _T("料件編輯"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(3, _T("參數修改"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(4, _T("I/O設定"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(5, _T("帳戶資訊"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->SetCurSel(0);
    /*讀取資料顯示列表*/
    ReadHistory(m_HistoryList, ((CHM_MachineApp*)AfxGetApp())->HistoryFile, _T("History.txt"));
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
/*讀出使用者資料*/
void CHistory::ReadAccountData() {
    CFile File;
    int m_ListCount = 0;
    CString StrBuff;
    if (File.Open(_T("Account.dat"), CFile::modeRead)) {//打開檔案
        CArchive ar(&File, CArchive::load);//讀取入檔案
        ar >> m_ListCount;//讀出使用者總數
        m_AccoutName.Add(_T("admin"));
        m_AccoutName.Add(_T("root"));
        for (int i = 0; i < m_ListCount * 3; i++) {
            ar >> StrBuff;//讀出資料
            if (!(i % 3))
            {
                m_AccoutName.Add(StrBuff);//增加項目
            }
        }
        File.Close();
    }
}
/*刷新List*/
void CHistory::ReadHistory(CListCtrl &setlist, CFile &read_file, CString myfilepath)
{
    CString indata;  //儲存個別欄位資料
    CArchive ar(&read_file, CArchive::load);
    int count = 1;
    //讀取資料
    if (read_file.Open(myfilepath, CFile::modeCreate | CFile::modeNoTruncate
        | CFile::modeRead | CFile::typeUnicode | CFile::shareDenyNone) == 0)
        return;
    else
    {
        setlist.DeleteAllItems();
        for (int i = 0; i < count; i++)
        {
            setlist.InsertItem(i, _T(""));
            for (int j = 0; j < 5; j++)
            {
                ar >> indata;
                setlist.SetItemText(i, j, indata);
                if (ar.IsBufferEmpty() == TRUE)
                    break;
            }
            count++;
            if (ar.IsBufferEmpty() == TRUE)
                break;
        }
    }
    //MessageBox(_T("讀取完畢"));
    ar.Close();
    read_file.Close();
}
