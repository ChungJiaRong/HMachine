#pragma once


// CMoveEdit

class CMoveEdit : public CEdit
{
	DECLARE_DYNAMIC(CMoveEdit)

public:
	CMoveEdit();
	virtual ~CMoveEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


