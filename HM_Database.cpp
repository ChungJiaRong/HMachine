#include "stdafx.h"
#include "HM_Database.h"
//添加檔案版本號
IMPLEMENT_SERIAL(CHM_Database, CObject, 1)

CHM_Database::CHM_Database()
{
}
CHM_Database::CHM_Database(CString m_ptOrigin, CString m_ptEnd, CString m_Action , CString m_MoveType, CString m_ThreePoint) {
    this->m_ptOrigin = m_ptOrigin;
    this->m_ptEnd = m_ptEnd;
    this->m_Action = m_Action;
    this->m_MoveType = m_MoveType;
    this->m_ThreePoint = m_ThreePoint;
}

CHM_Database::CHM_Database(CString m_Stand) {
    this->m_Stand = m_Stand;
}
CHM_Database::~CHM_Database()
{
}
void CHM_Database::Serialize(CArchive& ar) {
    if (ar.IsStoring()) {
        ar << m_ptOrigin << m_ptEnd<< m_Action << m_MoveType << m_ThreePoint << m_Stand;
    }
    else {
        ar >> m_ptOrigin >> m_ptEnd>> m_Action >> m_MoveType >> m_ThreePoint >> m_Stand;
    }
}
void CHM_Database::WKArrayCopy(std::vector<CString>
    *pCStrA, UINT Count)
{
    pCStrA->insert(pCStrA->begin() + Count * 3, m_ptEnd);
    pCStrA->insert(pCStrA->begin() + Count * 3 + 1, m_Action);
    pCStrA->insert(pCStrA->begin() + Count * 3 + 2, m_MoveType);
}



