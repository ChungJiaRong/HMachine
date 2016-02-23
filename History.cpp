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
    DDX_Control(pDX, IDC_DATEHISSTART, m_DateTimeStart);
    DDX_Control(pDX, IDC_DATEHISEND, m_DateTimeEnd);
}


BEGIN_MESSAGE_MAP(CHistory, CDialogEx)
    ON_CBN_SELCHANGE(IDC_CMBHISACCOUNT, &CHistory::OnSelchangeComboBox)
    ON_CBN_SELCHANGE(IDC_CMBHISACTION, &CHistory::OnSelchangeComboBox)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATEHISSTART, &CHistory::OnDatetimechangeDate)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATEHISEND, &CHistory::OnDatetimechangeDate)
    ON_BN_CLICKED(IDC_BTNHISCSEARCHALL, &CHistory::OnBnClickedBtnhiscsearchall)
END_MESSAGE_MAP()


// CHistory 訊息處理常式
BOOL CHistory::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    // TODO:  在此加入額外的初始化
    /*設定列表*/
    m_HistoryList.InsertColumn(0, _T("備註"), LVCFMT_FIXED_WIDTH, 220);
    m_HistoryList.InsertColumn(0, _T("Action"), LVCFMT_FIXED_WIDTH, 150);
    m_HistoryList.InsertColumn(0, _T("Account"), LVCFMT_FIXED_WIDTH, 150);
    m_HistoryList.InsertColumn(0, _T("Time"), LVCFMT_FIXED_WIDTH, 100);
    m_HistoryList.InsertColumn(0, _T("Date"), LVCFMT_FIXED_WIDTH, 100);
    /*設定帳號Combox*/
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(0, _T("ALL"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(1, _T("admin"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(2, _T("root"));
    ReadAccountData();//讀取使用者帳戶
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->SetCurSel(0);
    /*設定動作Combox*/
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(0, _T("ALL"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(1, _T("料件加工"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(2, _T("料件編輯"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(3, _T("參數修改"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(4, _T("I/O設定"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(5, _T("帳戶資訊"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->SetCurSel(0);
    /*設定DateTime*/
    CTime TimeTemp = TimeTemp.GetCurrentTime();
    m_DateTimeStart.SetTime(&TimeTemp);
    m_DateTimeEnd.SetTime(&TimeTemp);
    /*讀取資料顯示列表*/
    CString Account, Action;
    CTime Begin, End;
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->GetLBText(0, Account);
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->GetLBText(0, Action);
    m_DateTimeStart.GetTime(Begin);
    m_DateTimeEnd.GetTime(End);
    SearchReadHistoty(&((CHM_MachineApp*)AfxGetApp())->HistoryFile, _T("History.txt"), &m_HistoryList, 
        Begin, End, Account, Action);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}
/*讀出使用者資料*/
void CHistory::ReadAccountData() {
    CFile File;
    int ListCount = 0, UserCount = 3;
    CString StrBuff;
    if (File.Open(_T("Account.dat"), CFile::modeRead)) {//打開檔案
        CArchive ar(&File, CArchive::load);//讀取入檔案
        ar >> ListCount;//讀出使用者總數
        for (int i = 0; i < ListCount * 3; i++) {
            ar >> StrBuff;//讀出資料
            if (!(i % 3))
            {
                ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(UserCount, StrBuff);
                UserCount++;
            }
        }
        File.Close();
    }
}
/*搜尋刷新List*/
void CHistory::SearchReadHistoty(CFile *read_file, CString myfilepath, CListCtrl *setlist, CTime Begin, CTime End, CString read_account, CString read_action) {
    {
        CString indata[5];  //判斷與儲存各個欄位資料
        CString str_begin,StrBuff;
        BOOL findnow = FALSE;
        int findnum = -1, nYear = 0, nMonth = 0, nDate = 0;  //計算找到幾筆資料
        CArchive ar(read_file, CArchive::load);

        StrBuff = Begin.Format("%Y/%m/%d");
        swscanf(StrBuff, _T("%d/%d/%d"), &nYear, &nMonth, &nDate);
        CTime BeginBuff(nYear, nMonth, nDate, 0, 0, 0);

        StrBuff = End.Format("%Y/%m/%d");
        swscanf(StrBuff, _T("%d/%d/%d"), &nYear, &nMonth, &nDate);
        CTime EndBuff(nYear, nMonth, nDate, 0, 0, 0);

        if (Begin > End)
        {
            Begin = EndBuff;
            End = BeginBuff;
        } 
        else
        {
            Begin = BeginBuff;
            End = EndBuff;
        }

        str_begin = Begin.Format("%Y/%m/%d");
        //開始讀取
        if (read_file->Open(myfilepath, CFile::modeCreate | CFile::modeNoTruncate
            | CFile::modeRead | CFile::typeUnicode | CFile::shareDenyNone) == 0)
            return;
        else
        {
            setlist->DeleteAllItems();//刪除所有列表項目
            while (1)
            {
                for (int j = 0; j < 5; j++)
                {
                    ar >> indata[j];  
                    if (ar.IsBufferEmpty() == TRUE)
                        break;
                }
                if (findnum == -1)
                {
                    StrBuff = indata[0];
                    findnum = 0;
                }     
                swscanf(indata[0], _T("%d/%d/%d"), &nYear, &nMonth, &nDate);
                CTime tmfirst(nYear, nMonth, nDate, 0, 0, 0);
                if (tmfirst >= Begin && tmfirst <= End) //如果日期對
                {
                    if (read_account == indata[2] || read_account == _T("ALL"))
                    {
                        if (read_action == indata[3] || read_action == _T("ALL"))
                        {
                            findnow = TRUE;
                        }
                    }
                }
                if (findnow == TRUE)
                {
                    findnum++;
                    setlist->InsertItem(findnum - 1, indata[0]);
                    setlist->SetItemText(findnum - 1, 1, indata[1]);
                    setlist->SetItemText(findnum - 1, 2, indata[2]);
                    setlist->SetItemText(findnum - 1, 3, indata[3]);
                    setlist->SetItemText(findnum - 1, 4, indata[4]);
                    findnow = FALSE;
                }
                if (ar.IsBufferEmpty() == TRUE)
                    break;
            }
        }
        /*設定日期控件*/
        swscanf(StrBuff.GetBuffer(StrBuff.GetLength()), _T("%d/%d/%d"), &nYear, &nMonth, &nDate); //掃描格式化
        CTime Begin(nYear, nMonth, nDate, 0, 0, 0);
        CTime End(CTime::GetCurrentTime());
        m_DateTimeStart.SetRange(&Begin, &End);
        m_DateTimeEnd.SetRange(&Begin, &End);
        ar.Close();
        read_file->Close();
    }
}
/*所有歷史檔案刷新List*/
void CHistory::ReadAllHistory(CListCtrl &setlist, CFile &read_file, CString myfilepath)
{
    CString indata;  //儲存個別欄位資料
    CArchive ar(&read_file, CArchive::load);
    CString StrBuff;
    int year, month, date;
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
                if (i == 0 && j == 0) 
                {
                    StrBuff = indata;
                }
                setlist.SetItemText(i, j, indata);
                if (ar.IsBufferEmpty() == TRUE)
                    break;
            }
            count++;
            if (ar.IsBufferEmpty() == TRUE)
                break;
        }
    }
    /*設定日期控件*/
    swscanf(StrBuff.GetBuffer(StrBuff.GetLength()), _T("%d/%d/%d"), &year, &month, &date); //掃描格式化
    CTime Begin(year, month, date, 0, 0, 0);
    CTime End(CTime::GetCurrentTime());
    m_DateTimeStart.SetRange(&Begin,&End);
    m_DateTimeEnd.SetRange(&Begin,&End);
    ar.Close();
    read_file.Close();
}
/*帳號、動作發生改變*/
void CHistory::OnSelchangeComboBox()
{
    CString Account, Action;
    CTime Begin, End;
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->GetLBText(((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->GetCurSel(), Account);
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->GetLBText(((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->GetCurSel(), Action);
    m_DateTimeStart.GetTime(Begin);
    m_DateTimeEnd.GetTime(End);
    SearchReadHistoty(&((CHM_MachineApp*)AfxGetApp())->HistoryFile, _T("History.txt"), &m_HistoryList,
        Begin, End, Account, Action);
}
/*日期發生改變*/
void CHistory::OnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    // TODO: 在此加入控制項告知處理常式程式碼
    CString Account, Action;
    CTime Begin, End;
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->GetLBText(((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->GetCurSel(), Account);
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->GetLBText(((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->GetCurSel(), Action);
    m_DateTimeStart.GetTime(Begin);
    m_DateTimeEnd.GetTime(End);
    SearchReadHistoty(&((CHM_MachineApp*)AfxGetApp())->HistoryFile, _T("History.txt"), &m_HistoryList,
        Begin, End, Account, Action);
    *pResult = 0;
}
/*搜尋所有歷史*/
void CHistory::OnBnClickedBtnhiscsearchall()
{
    // TODO: 在此加入控制項告知處理常式程式碼
    ReadAllHistory(m_HistoryList, ((CHM_MachineApp*)AfxGetApp())->HistoryFile, _T("History.txt"));
}

