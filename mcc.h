// mcc.h : mcc DLL 的主要標頭檔
//

#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"		// 主要符號
#ifndef MO_DLL
#define MO_DLL __declspec(dllimport)
#endif
int g_iId = 0;//軸卡開關編號0
MO_DLL bool MO_Open(int interrupt);//開啟軸卡並將邏輯位置歸零
MO_DLL void MO_Close();//關閉軸卡
MO_DLL void MO_STOP();//停止驅動
MO_DLL void MO_DecSTOP();//減速停止
MO_DLL void MO_MoveToHome(long lSpeed1, long lSpeed2, int iAxis, long lMove);//原點復歸
MO_DLL void MO_Do2DLineMove(long lXTar, long lYTar, long lSpeed, long lAcceleration, long lInitSpeed);//XY兩軸直線補間移動
MO_DLL void MO_DoZLineMove(long lZTar, long lSpeed, long lAcceleration, long lInitSpeed);//Z軸直線補間移動
MO_DLL void MO_Do2DArcMove(long lXTar, long lYTar, long XCenter, long YCenter, long lInitSpeed, long lSpeed, bool bRevolve);//XY兩軸圓弧補間移動
MO_DLL void MO_Do3DLineMove(long lXTar, long lYTar, long lZTar, long lSpeed, long lAcceleration, long lInitSpeed);//三軸直線插補
MO_DLL void MO_SetHardLim(int iAxis, bool bSet);//設置硬體極限開關有效
MO_DLL void MO_SetSoftLim(int iAxis, bool bSet);//設置軟體極限開關有效
MO_DLL void MO_SetCompSoft(bool bPM, long lCompX, long lCompY, long lCompZ); //設置軟體極限範圍
MO_DLL void MO_SetDeceleration(int iAxis, long lDeceleration);//設置減速度
MO_DLL void MO_SetAccType(int iType);//設置加減速型態(梯型或S型)
MO_DLL long MO_ReadLogicPosition(int iAxis);//讀取邏輯位置
MO_DLL long MO_ReadRealPosition(int iAxis);//讀取實際位置(encoder專用)
MO_DLL long MO_ReadSpeed(int iAxis);//讀取軸驅動速度
MO_DLL long MO_ReadAccDec(int iAxis);//讀取軸加減速度
MO_DLL bool MO_ReadIsDriving(int iAxis);//確認是否正在驅動中
MO_DLL void MO_ReadHardLim(bool &bHardX, bool &bHardY, bool &bHardZ);//讀取硬體極限開關設定狀態
MO_DLL void MO_ReadSoftLim(bool &bSoftX, bool &bSoftY, bool &bSoftZ);//讀取軟體極限開關設定狀態
MO_DLL void MO_ReadRunHardLim(int &iPMLimX, bool &bIsOkLimX, int &iPMLimY, bool &bIsOkLimY, int &iPMLimZ, bool &bIsOkLimZ);//讀取是否在硬體極限開關上以及運行狀態
MO_DLL void MO_ReadMotoAlarm(bool &bMotoSignalX,bool &bMotoSignalY,bool &bMotoSignalZ);//伺服馬達輸入訊號異常(伺服馬達專用)
MO_DLL void MO_ReadEMG(bool &bEMGX,bool &bEMGY,bool &bEMGZ);//讀取驅動中緊急停止狀態
MO_DLL void MO_ReadSoftLimError(bool bPM, bool &bSoftX, bool &bSoftY, bool &bSoftZ);//讀取軟體極限開關執行狀態
MO_DLL void MO_ReadHomeError(bool &bHomeErrorX,bool &bHomeErrorY,bool &bHomeErrorZ);//讀取各軸原點復歸錯誤狀態
MO_DLL void MO_ReadIP(bool &bIPX,bool &bIPY,bool &bIPZ);//讀取各軸插補錯誤狀態
MO_DLL void MO_AlarmCClean();//錯誤狀態清除
MO_DLL bool MO_ReadPIOInput(int iBit);//讀取通用暫存器PIO輸入
MO_DLL void MO_SetPIOOutput(int iBit, bool bData); //設置通用暫存器PIO輸出
MO_DLL bool MO_ReadStartBtn();//讀取機台Start按鈕狀態
MO_DLL void MO_SetJerk(int iAxis, long lSpeed);//設置加速度增加率(用於S型曲線)
MO_DLL void MO_SetDJerk(int iAxis, long lSpeed); //設置減速度增加率(用於非對稱S型曲線)
MO_DLL void MO_SetDecPation(ULONG ulPationX, ULONG ulPationY, ULONG ulPationZ);//設置減速度點(用於非對稱S型曲線)
MO_DLL void MO_SetDecOK(bool bData);//設置插補減速停止有無效
MO_DLL long MO_Timer(int iMode, int iTimerNo, long lData);//計時器
MO_DLL bool MO_ReadGumming();//讀取出膠控制狀態
MO_DLL void MO_GummingSet(long lMicroSecond, LPTHREAD_START_ROUTINE GummingTimeOutThread);//設置出膠秒數，單位[us]
MO_DLL void MO_FinishGumming();//出膠完成
MO_DLL void MO_StopGumming();//停止出膠
<<<<<<< HEAD
MO_DLL void MO_Do3DLineMove(long lXTar, long lYTar, long lZTar, long lSpeed, long lAcceleration, long lInitSpeed);
=======
>>>>>>> compiler
MO_DLL long MO_ReadReg(int iRegSelect, int iAxis);//讀取暫存器RR0~RR3
MO_DLL CString MO_StreamToUnit(int iValue);//數字轉換成CString 16-bit binary
// CmccApp
// 這個類別的實作請參閱 mcc.cpp
//

class CmccApp : public CWinApp
{
public:
	CmccApp();

// 覆寫
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
