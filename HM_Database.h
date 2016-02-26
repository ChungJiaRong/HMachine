#pragma once
class CHM_Database :public CObject
{
    DECLARE_SERIAL(CHM_Database)
//ÄÝ©Ê
public:
    CString m_ptOrigin;
    CString m_ptEnd;
    CString m_Action;
    CString m_Stand;
//¤èªk
public:
    CHM_Database();
    ~CHM_Database();
    CHM_Database(CString m_ptOrigin , CString m_ptEnd, CString m_Action);
    CHM_Database(CString m_Stand);
    void Serialize(CArchive& ar);
    void WKArrayCopy(CStringArray* pCStrA,UINT Count);
    void PSArrayCopy(CStringArray * pCStrA, UINT Count);
};

