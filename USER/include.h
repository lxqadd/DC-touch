#ifndef _INCLUDE_H
#define _INCLUDE_H
#include "stm32f10x.h"
#include "usart1.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include "stmflash.h"
#include "wifi.h"
#include "sys.h"
#include "touchscreen.h"
#include <string.h>
#define BS_U16(_u16) ((unsigned short)((((unsigned short)(_u16)) >> 8) | (((unsigned short)(_u16)) << 8))) //?¨?????????
#define BS_ULONG(_u32) ((unsigned int)(BS_U16((_u32) >> 16) | (BS_U16(_u32 & 0xFFFF) << 16)))
#define FengMingQI_SET    GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define FengMingQI_RES    GPIO_ResetBits(GPIOB, GPIO_Pin_2)

////////////////////////////////////////////////////////////////////////////////

#define Dangwei_ONE_SET   GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define Dangwei_ONE_RES   GPIO_ResetBits(GPIOB, GPIO_Pin_4)

#define Dangwei_TWO_SET   GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define Dangwei_TWO_RES   GPIO_ResetBits(GPIOB, GPIO_Pin_5)

#define Dangwei_THREE_SET   GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define Dangwei_THREE_RES   GPIO_ResetBits(GPIOB, GPIO_Pin_6)

#define Dangwei_FOUR_SET   GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define Dangwei_FOUR_RES   GPIO_ResetBits(GPIOB, GPIO_Pin_7)

#define OpenFaOne		GPIO_SetBits(GPIOA, GPIO_Pin_6);// GPIO_ResetBits(GPIOA, GPIO_Pin_7|GPIO_Pin_11);GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define CloseFaOne	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
#define OpenFaTwo		GPIO_SetBits(GPIOA, GPIO_Pin_7);// GPIO_ResetBits(GPIOA, GPIO_Pin_6|GPIO_Pin_11);GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define CloseFaTwo	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
#define OpenFaThr		GPIO_SetBits(GPIOB, GPIO_Pin_0);// GPIO_ResetBits(GPIOA, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11);
#define CloseFaThr	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define OpenFaFou		GPIO_SetBits(GPIOA, GPIO_Pin_11);//GPIO_ResetBits(GPIOA, GPIO_Pin_6|GPIO_Pin_7);GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define CloseFaFou	GPIO_ResetBits(GPIOA, GPIO_Pin_11);

#define PASSWORD  1000


#define		HOUR12							8640000   //定时器为5ms  12H = 12 * 60 * 60 * 200
#define  	MIN10								120000
#define   MIN3								36000
#define		MIN1								12000	
#define 	MIN10								120000
#define  OPENFIRE_TIME				HOUR12	  //12h
#define  CLOSEFIRE_DT					MIN1			//1min
#define  CLOSEWATERPUMP_TIME 	MIN3 
#define  FREEZEPROOFTIMER 	  MIN10
////////////////////////////////////////////////////////////////////////////////

extern unsigned long openfiretimer;//加热计时
extern unsigned long closefiredelaytimer;
extern unsigned int  closewaterpumptimer;

extern unsigned char fireStatues;
extern unsigned char Power;
extern unsigned char level;
extern unsigned char OpenFunctionNum;
extern unsigned char CloseFunctionNum;
extern unsigned char AutoFunctionNum;
extern unsigned int SaveCount;
extern unsigned char ID[9];
extern unsigned char RegisteCode[4];
extern unsigned char WaterPump;
extern unsigned char FireBurner;
extern unsigned char HandWaterPump;
extern unsigned char HandFireBurner;
extern unsigned char TempNow;
extern unsigned char TempNowHigh;
extern unsigned char TempSet;
float Get_PT100_tmp(float fR);
extern unsigned char WaterPump;
extern unsigned char FireBurner;
extern unsigned char TempNow;
extern unsigned char BEEPFLAG;	
extern unsigned char TempSetContralHigh;
extern unsigned char TempSetContralLow;
extern unsigned char TempSetWaterHigh;
extern unsigned char TempSetWaterLow;
extern unsigned char  TempSetMain;
extern unsigned char TempSetUseIng;
extern unsigned char TempSetItemSelectIndex;

extern unsigned char TimeSetBegain[4],TimeSetEnd[4],TimeTepSet[4];
extern unsigned char FaFunctionSta[4];
extern unsigned char TimeSetItemSelectIndex;
extern unsigned char ShowItemIndex;
extern unsigned char SetItemSelectIndex;
extern unsigned char PowerFlag;
extern unsigned char RunFlag;
extern unsigned char ShowSetItemPageFlag;
extern unsigned char WringFlag;
extern unsigned char WringShowNowNum;
extern unsigned char WringShowFlag;
extern unsigned char LowTemp;
extern unsigned char TimeContral;
extern unsigned char TimeHourNow;
extern unsigned short WifiSendFlag;
extern unsigned char HandMode;
extern unsigned char FirstRun;
extern unsigned char ControlModel;
extern unsigned char MainrunTmp;

extern unsigned char FaSta;

extern unsigned char  HandSetFa;


extern Time NowTimer;
extern u8 GetNowTimeFlag;
extern u8 WriteLcdTimeFlag;
extern unsigned int 	Freeze_prooftimer;
extern unsigned char closewaterpumptimerflg;
extern unsigned char closefiredelayflg;
extern unsigned int LcdOpenTouchtimer;
extern unsigned char LcdOpenTouchflg;

extern u8 OutsideFlg;

#define Wring_SensorErr	1<<0			//传感器报警
#define Wring_WarmAbnormal	1<<1	//疲劳告警//加热异常报警  
#define Wring_TempDValue	1<<2		//温差报警
#define Wring_HighTemp	1<<3 		 	//高温报警

extern void MainRun(void);
extern void OpenBEEP(void);
extern void CloseBEEP(void);
extern void SaveConfig(void);
#define MODE_Boiler 1
#define MODE_Bouch 1
void SaveWifiConfig(void);
void RevWifiData(unsigned char *str,unsigned short len);

void CloseLcd(void);
void OpenLcd(void);
void ShowMainPage(void);
void ShowTempSetPageFireHigh(void);
void ShowTempSetPageFireLow(void);
void ShowTempSetPageWaterHigh(void);
void ShowTempSetPageWaterLow(void);
void ShowTimeSetPageOne(void);
void ShowTimeSetPageTwo(void);
void ShowTimeSetPageThr(void);
void ShowTimeSetPageFor(void);
void ShowHandSetPage(void);
void LcdReadTime(void);
void SetMainTemp(unsigned char num);


void SetSetTemp(unsigned char index,unsigned char num);
void SetMainStatus(unsigned char num);
void SetSetTime(unsigned char index,unsigned char num);
void SetFireRun(void);
void SetWaterRun(void);
void ShowWringPageSE(void);
void ShowWringPageWA(void);
void ShowWringPageTDV(void);
void ShowWringPageTE(void);
void ShowMHconfigPage(void);
void ShowSRconfigPage(void);
void ShowconfigPage(void);
void ChackAutoFa(void);
void OpenSetFa(void);
void SetWIFIStatus(unsigned char num);
void SetHandStatus(unsigned char num);
void SetWaterStatus(unsigned char num);
void SetFaFunctionTemp(void);
void SetHandFireBurnerTemp(unsigned char num);
void SetTimeHour(unsigned char num);
void SetTimeMin(unsigned char num);

unsigned char CheckFaFunctionNum(unsigned char code);//code 为功能码 0：打开1：关闭2：自动

void WifiSendRegister(void);
void WifiClientDeal(unsigned char str);
void WifiSendRealTimeData(void);
void WifiReStart(void);
void SetContralRun(void);
void KeyScreen(void);
void OPENKeyDot(void);
void RunStatues(unsigned char num);
void LcdReadStartTime(void);
void LcdReadEndTime(void);
void LcdReadTimeSetTemp(void);	
void SetStartTime(unsigned char num);
void SetTempTime(unsigned char num);
void SetEndTime(unsigned char num);
void SetBackWaterTemp(unsigned char num);
void SetOutWaterTemp(unsigned char num);
void SetPowerTemp(unsigned char num);
void SetFaStaTemp(unsigned char num);
void LcdOpenBEEP(void);
void starthot(u8 level);
void FireStatues(unsigned char num);
void CloseWatePump(void);
void CloseFireBurner(void);

/*
时间：2017年2月24日15:11:49
操作：添加dw.c文件的对外函数
*/
void ShowTimeSetPageOneH(void);
void ShowTimeSetPageOneL(void);
void ShowTimeSetPageTwoH(void);
void ShowTimeSetPageTwoL(void);
void ShowTimeSetPageThrH(void);
void ShowTimeSetPageThrL(void);
void ShowTimeSetPageForH(void);
void ShowTimeSetPageForL(void);
void CloseTouch(void);
void OpenTouch(void);

void LcdWriteTime(void);

void UART3_SendString(unsigned char *s, unsigned char len);

#endif
