// VI_Dll.h : VI_Dll DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CVI_DllApp
// �o�����O����@�аѾ\ VI_Dll.cpp
//

//�Y�ɼv���A�ǤJ��mmodel1����(Ex:GetDlgItem(IDC_STATIC1))
extern "C" _declspec(dllexport) void VI_ModelDefine(CWnd* IDC_ModelOneWindow);
//���خ�
extern "C" _declspec(dllexport) void VI_ChangeRec(CWnd* IDC_ModelOneWindow,int x,int y);
//���model1���x�s�A�ǤJ��mmodel2����
extern "C" _declspec(dllexport) void VI_GetModel1(CWnd* IDC_ModelOneWindow);
//���model2���x�s
extern "C" _declspec(dllexport) void VI_GetModel2(CWnd* IDC_ModelTwoWindow);
//model1���
extern "C" _declspec(dllexport) void VI_FindModel1(double &OffSetX,double &OffSetY,double &Angle,CWnd* IDC_ShowWindow);
//model2���
extern "C" _declspec(dllexport) void VI_FindModel2(double &OffSetX2,double &OffSetY2,double &Angle2,CWnd* IDC_ShowWindow);
//����
extern "C" _declspec(dllexport) void VI_Free();
//��������
extern "C" _declspec(dllexport) void VI_ChangeWindow(CWnd* IDC_ShowWindow);

class CVI_DllApp : public CWinApp
{
public:
	CVI_DllApp();


// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
