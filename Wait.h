#pragma once


// CWait ��ܤ��

class CWait : public CDialogEx
{
	DECLARE_DYNAMIC(CWait)
public:
	CWait(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CWait();
// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAITING };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
};
