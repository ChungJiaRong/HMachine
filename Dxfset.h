#pragma once


// CDxfset ��ܤ��

class CDxfset : public CDialogEx
{
	DECLARE_DYNAMIC(CDxfset)

public:
	CDxfset(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CDxfset();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DXFSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
    virtual void OnOK();
public:
    virtual BOOL OnInitDialog();
};
