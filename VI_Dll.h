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
//���model1���x�s�A�ǤJ��mmodel2�����APath����|(�ݥ�\\)�AName��W��
extern "C" _declspec(dllexport) void VI_GetModel(CWnd* IDC_ModelOneWindow,CString Path,CString Name);
//model���(Model��model,�p�����h��ϩ�i����pic);
extern "C" _declspec(dllexport) bool VI_SearchModel(CWnd* IDC_ShowWindow,void* Model,void* Pic);
//model2���(�ШϥΤW�����A����)
extern "C" _declspec(dllexport)void VI_FindModel1(double &OffSetX,double &OffSetY,double &Angle,void* Pic,void* Model);
//����
extern "C" _declspec(dllexport) void VI_FreeModel(void* Model);
//����
extern "C" _declspec(dllexport) void VI_FreePic(void* Pic);
//����
extern "C" _declspec(dllexport) void VI_FreeApp();
//��������
extern "C" _declspec(dllexport) void VI_ChangeWindow(CWnd* IDC_ShowWindow);
//����I��ϵ�����
extern "C" _declspec(dllexport) void VI_Getpicture(void* Model);
//������йϹ�(����)
extern "C" _declspec(dllexport) void VI_Showpicture(void* Pic);
//�������model
extern "C" _declspec(dllexport) void VI_Load(CString Path,CString Name,void* Model);
//�������йϹ����^�ǰ��t��
extern "C" _declspec(dllexport)  void VI_FindModel(void *PicTemp,void *PicTemp1,void* Model,void* Model1,double &OffSetX,double &OffSetY,double &Angle);
class CVI_DllApp : public CWinApp
{
public:
	CVI_DllApp();


// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
