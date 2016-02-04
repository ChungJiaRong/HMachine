#pragma once
#include "afxcmn.h"


// CAdministration ��ܤ��

class CAdministration : public CDialogEx
{
	DECLARE_DYNAMIC(CAdministration)

public:
	CAdministration(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CAdministration();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINISTRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
//�ݩ�
public:
	CListCtrl m_ListCtrlUser;
	UINT m_ActionChoose;
	int m_ListCount;
	CStringArray m_UserData;
//��k
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnadminnew();
	afx_msg void OnBnClickedBtnadminmodify();
	afx_msg void OnBnClickedBtnadmindelete();
	afx_msg void OnBnClickedBtnadmincheck();
	afx_msg void OnClickListadminuser(NMHDR *pNMHDR, LRESULT *pResult);
	void AccountListRefresh();
	void ReadAccountData();
	void WriteAccountData();
	BOOL CheckUserPassWord(CString PassWord);
	BOOL CheckUserID(CString UserID);
    virtual void OnOK();
};
