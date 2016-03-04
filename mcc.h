// mcc.h : mcc DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�
#ifndef MO_DLL
#define MO_DLL __declspec(dllimport)
#endif
int g_iId = 0;//�b�d�}���s��0
MO_DLL bool MO_Open(int interrupt);//�}�Ҷb�d�ñN�޿��m�k�s
MO_DLL void MO_Close();//�����b�d
MO_DLL void MO_STOP();//�����X��
MO_DLL void MO_DecSTOP();//��t����
MO_DLL void MO_MoveToHome(long lSpeed1, long lSpeed2, int iAxis, long lMove);//���I�_�k
MO_DLL void MO_Do2DLineMove(long lXTar, long lYTar, long lSpeed, long lAcceleration, long lInitSpeed);//XY��b���u�ɶ�����
MO_DLL void MO_DoZLineMove(long lZTar, long lSpeed, long lAcceleration, long lInitSpeed);//Z�b���u�ɶ�����
MO_DLL void MO_Do2DArcMove(long lXTar, long lYTar, long XCenter, long YCenter, long lInitSpeed, long lSpeed, bool bRevolve);//XY��b�꩷�ɶ�����
MO_DLL void MO_Do3DLineMove(long lXTar, long lYTar, long lZTar, long lSpeed, long lAcceleration, long lInitSpeed);//�T�b���u����
MO_DLL void MO_SetHardLim(int iAxis, bool bSet);//�]�m�w�鷥���}������
MO_DLL void MO_SetSoftLim(int iAxis, bool bSet);//�]�m�n�鷥���}������
MO_DLL void MO_SetCompSoft(bool bPM, long lCompX, long lCompY, long lCompZ); //�]�m�n�鷥���d��
MO_DLL void MO_SetDeceleration(int iAxis, long lDeceleration);//�]�m��t��
MO_DLL void MO_SetAccType(int iType);//�]�m�[��t���A(�諬��S��)
MO_DLL long MO_ReadLogicPosition(int iAxis);//Ū���޿��m
MO_DLL long MO_ReadRealPosition(int iAxis);//Ū����ڦ�m(encoder�M��)
MO_DLL long MO_ReadSpeed(int iAxis);//Ū���b�X�ʳt��
MO_DLL long MO_ReadAccDec(int iAxis);//Ū���b�[��t��
MO_DLL bool MO_ReadIsDriving(int iAxis);//�T�{�O�_���b�X�ʤ�
MO_DLL void MO_ReadHardLim(bool &bHardX, bool &bHardY, bool &bHardZ);//Ū���w�鷥���}���]�w���A
MO_DLL void MO_ReadSoftLim(bool &bSoftX, bool &bSoftY, bool &bSoftZ);//Ū���n�鷥���}���]�w���A
MO_DLL void MO_ReadRunHardLim(int &iPMLimX, bool &bIsOkLimX, int &iPMLimY, bool &bIsOkLimY, int &iPMLimZ, bool &bIsOkLimZ);//Ū���O�_�b�w�鷥���}���W�H�ιB�檬�A
MO_DLL void MO_ReadMotoAlarm(bool &bMotoSignalX,bool &bMotoSignalY,bool &bMotoSignalZ);//���A���F��J�T�����`(���A���F�M��)
MO_DLL void MO_ReadEMG(bool &bEMGX,bool &bEMGY,bool &bEMGZ);//Ū���X�ʤ���氱��A
MO_DLL void MO_ReadSoftLimError(bool bPM, bool &bSoftX, bool &bSoftY, bool &bSoftZ);//Ū���n�鷥���}�����檬�A
MO_DLL void MO_ReadHomeError(bool &bHomeErrorX,bool &bHomeErrorY,bool &bHomeErrorZ);//Ū���U�b���I�_�k���~���A
MO_DLL void MO_ReadIP(bool &bIPX,bool &bIPY,bool &bIPZ);//Ū���U�b���ɿ��~���A
MO_DLL void MO_AlarmCClean();//���~���A�M��
MO_DLL bool MO_ReadPIOInput(int iBit);//Ū���q�μȦs��PIO��J
MO_DLL void MO_SetPIOOutput(int iBit, bool bData); //�]�m�q�μȦs��PIO��X
MO_DLL bool MO_ReadStartBtn();//Ū�����xStart���s���A
MO_DLL void MO_SetJerk(int iAxis, long lSpeed);//�]�m�[�t�׼W�[�v(�Ω�S�����u)
MO_DLL void MO_SetDJerk(int iAxis, long lSpeed); //�]�m��t�׼W�[�v(�Ω�D���S�����u)
MO_DLL void MO_SetDecPation(ULONG ulPationX, ULONG ulPationY, ULONG ulPationZ);//�]�m��t���I(�Ω�D���S�����u)
MO_DLL void MO_SetDecOK(bool bData);//�]�m���ɴ�t����L��
MO_DLL long MO_Timer(int iMode, int iTimerNo, long lData);//�p�ɾ�
MO_DLL bool MO_ReadGumming();//Ū���X������A
MO_DLL void MO_GummingSet(long lMicroSecond, LPTHREAD_START_ROUTINE GummingTimeOutThread);//�]�m�X����ơA���[us]
MO_DLL void MO_FinishGumming();//�X������
MO_DLL void MO_StopGumming();//����X��
<<<<<<< HEAD
MO_DLL void MO_Do3DLineMove(long lXTar, long lYTar, long lZTar, long lSpeed, long lAcceleration, long lInitSpeed);
=======
>>>>>>> compiler
MO_DLL long MO_ReadReg(int iRegSelect, int iAxis);//Ū���Ȧs��RR0~RR3
MO_DLL CString MO_StreamToUnit(int iValue);//�Ʀr�ഫ��CString 16-bit binary
// CmccApp
// �o�����O����@�аѾ\ mcc.cpp
//

class CmccApp : public CWinApp
{
public:
	CmccApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
