#pragma once


// CComRound ��ܤ��

class CComRound : public CDialogEx
{
	DECLARE_DYNAMIC(CComRound)

public:
	CComRound(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CComRound();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMROUND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
    int ComboCheck;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
