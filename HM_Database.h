#pragma once
class CHM_Database :public CObject
{
    DECLARE_SERIAL(CHM_Database)
//ÄÝ©Ê
public:
    CString m_ptOrigin;
    CString m_ptEnd;
    CString m_Action;
    CString m_MoveType;
    CString m_ThreePoint;
    CString m_Stand;
//¤èªk
public:
    CHM_Database();
    ~CHM_Database();
    CHM_Database(CString m_ptOrigin , CString m_ptEnd, CString m_Action , CString m_MoveType, CString m_ThreePoint);
    CHM_Database(CString m_Stand);
    void Serialize(CArchive& ar);
    void WKArrayCopy(std::vector<CString>
        *pCStrA,UINT Count);
};

