#pragma once


// CHistory ��ܤ��

class CHistory : public CDialogEx
{
	DECLARE_DYNAMIC(CHistory)

public:
	CHistory(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CHistory();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
};
