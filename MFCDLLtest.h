// MFCDLLtest.h : MFCDLLtest DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFCDLLtestApp
// �o�����O����@�аѾ\ MFCDLLtest.cpp
//

//__declspec(dllexport) bool Add(float a, float b, float& ans);
__declspec(dllexport) bool MO_Open();//OpenDriverCard id:0, IC_No:0
__declspec(dllexport) bool MO_Do2DLineMove(long lXTar, long lYTar, long lAcceleration, long lInitSpeed, long lSpeed);//
//__declspec(dllexport) bool MO_Do2DArcMove(long lXTra, long lYTra, long lXCenter, long lYCenter);
__declspec(dllexport) long MO_ReadPosition(int iAxis, long* p_lPosition);
//__declspec(dllexport) bool MO_SetInitSpeed(int iAxis, long lSpeed);
//__declspec(dllexport) bool MO_SetDriSpeed(int iAxis, long lSpeed);
//__declspec(dllexport) bool MO_SetAccStyle(int iStyle);
//__declspec(dllexport) bool MO_SetAccValue(int iAxis, long lAcceleration);
//__declspec(dllexport) bool MO_SetDecValue(int iAxis, long lDeceleration);
__declspec(dllexport) int MO_IsDriving(int iAxis);


class CMFCDLLtestApp : public CWinApp
{
public:
	CMFCDLLtestApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
