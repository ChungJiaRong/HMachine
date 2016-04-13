#pragma once
#include "afxcmn.h"
#include "afxwin.h"
struct Speed {
	LONG Init;
	LONG Add;
	LONG End;
};
struct Limit {
	BOOL Hard;
	BOOL Soft;
	CPoint Pos;
	CPoint Nedg;
	LONG PosZ, NedgZ;
};
struct Glue {
	LONG BeginWaitTime;
	LONG EndWaitTime;
	LONG StopGlueDistance;
};
struct ZEndWay
{
	LONG FirstSpeed;
	LONG FirstUpDistance;
	int Type;
	LONG Speed;
	LONG Hight;
	LONG Width;
};
// CParameter ��ܤ��

class CParameter : public CPropertyPage
{
	DECLARE_DYNAMIC(CParameter)

public:
	CParameter();   // �зǫغc�禡
	virtual ~CParameter();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
//�ݩ�
public:
	CRect m_InitRect;
	CImageList m_OnOffImageList;
	LONG OSpeed, OLSpeed, RSpeed ,R2Speed,A2Speed;
	int ARSpeedType;
	Limit Limit;
	Speed HSpeed, MSpeed, LSpeed , WSpeed;
	Glue Glue;
	ZEndWay ZEndWay;
	CListCtrl m_ListCtrlParame;
	int m_ListCount;
	CToolTipCtrl m_tooltip;
//��k
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnparsetfinish();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnpareditpar();
	afx_msg void OnBnClickedBtnparinit();
	afx_msg void OnSelendokCmbpartype();
	afx_msg void OnStnClickedChkparhlimit();
	afx_msg void OnStnClickedChkparslimit();
	void ChangeSize(CWnd * pWnd, int cx, int cy);
	void InitParameter();
	void WriteParamData();
	void ReadParamData();
	void RefreshData();
	void SetParameter();
	void SetListItemText(CListCtrl &m_ListCtrl, UINT Item, UINT Count, ...);
	void EditTextVertical(CEdit * m_EditCtrl);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelendokCmbparglueztype();
};
