// History.cpp : ��@��
//

#include "stdafx.h"
#include "HM_Machine.h"
#include "History.h"
#include "afxdialogex.h"


// CHistory ��ܤ��

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


// CHistory �T���B�z�`��
BOOL CHistory::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  �b���[�J�B�~����l��
    ReadAccountData();//Ū���ϥΪ̱b��
    /*�]�w�C��*/
    m_HistoryList.InsertColumn(0, _T("�Ƶ�"), LVCFMT_FIXED_WIDTH, 220);
    m_HistoryList.InsertColumn(0, _T("Action"), LVCFMT_FIXED_WIDTH, 150);
    m_HistoryList.InsertColumn(0, _T("Account"), LVCFMT_FIXED_WIDTH, 150);
    m_HistoryList.InsertColumn(0, _T("Time"), LVCFMT_FIXED_WIDTH, 100);
    m_HistoryList.InsertColumn(0, _T("Date"), LVCFMT_FIXED_WIDTH, 100);
    /*�]�w�b��Combox*/
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(0, _T("ALL"));
    for (int i = 0; i < m_AccoutName.GetCount(); i++) {
        ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->InsertString(i + 1, m_AccoutName.GetAt(i));
    }
    ((CComboBox*)GetDlgItem(IDC_CMBHISACCOUNT))->SetCurSel(0);
    /*�]�w�ʧ@Combox*/
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(0, _T("ALL"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(1, _T("�ƥ�[�u"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(2, _T("�ƥ�s��"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(3, _T("�Ѽƭק�"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(4, _T("I/O�]�w"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->InsertString(5, _T("�b���T"));
    ((CComboBox*)GetDlgItem(IDC_CMBHISACTION))->SetCurSel(0);
    /*Ū�������ܦC��*/
    ReadHistory(m_HistoryList, ((CHM_MachineApp*)AfxGetApp())->HistoryFile, _T("History.txt"));
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX �ݩʭ����Ǧ^ FALSE
}
/*Ū�X�ϥΪ̸��*/
void CHistory::ReadAccountData() {
    CFile File;
    int m_ListCount = 0;
    CString StrBuff;
    if (File.Open(_T("Account.dat"), CFile::modeRead)) {//���}�ɮ�
        CArchive ar(&File, CArchive::load);//Ū���J�ɮ�
        ar >> m_ListCount;//Ū�X�ϥΪ��`��
        m_AccoutName.Add(_T("admin"));
        m_AccoutName.Add(_T("root"));
        for (int i = 0; i < m_ListCount * 3; i++) {
            ar >> StrBuff;//Ū�X���
            if (!(i % 3))
            {
                m_AccoutName.Add(StrBuff);//�W�[����
            }
        }
        File.Close();
    }
}
/*��sList*/
void CHistory::ReadHistory(CListCtrl &setlist, CFile &read_file, CString myfilepath)
{
    CString indata;  //�x�s�ӧO�����
    CArchive ar(&read_file, CArchive::load);
    int count = 1;
    //Ū�����
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
    //MessageBox(_T("Ū������"));
    ar.Close();
    read_file.Close();
}
