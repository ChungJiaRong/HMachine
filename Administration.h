#pragma once
#include "afxcmn.h"


// CAdministration 對話方塊

class CAdministration : public CDialogEx
{
	DECLARE_DYNAMIC(CAdministration)

public:
	CAdministration(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CAdministration();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINISTRATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
//屬性
public:
	CListCtrl m_ListCtrlUser;
	UINT m_ActionChoose;
	int m_ListCount;
	CStringArray m_UserData;
//方法
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
