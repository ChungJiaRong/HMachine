#pragma once


// CAccount ��ܤ��

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CLogin();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
//�ݩ�
public:
    CStringArray m_UserData;
//��k
public:
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
