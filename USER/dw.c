#include "include.h"

#define BackWaterAddr  0x01
#define MainTempAddr  0x02

#define OutWaterAddr  0x21

#define PowerLvel1	0x59
#define PowerLvel2	0x58
#define PowerLvel3	0x57
#define PowerLvel4	0x56

#define FaNum1					0x53
#define FaNum2					0x52
#define FaNum3					0x51
#define FaNum4					0x50

#define FaFunction1     0x68
#define FaFunction2     0x69
#define FaFunction3     0x6a
#define FaFunction4     0x6b

const unsigned char MsgCloseTouch[6]={0x5A,0xA5,0x03,0x80,0x0B,0x00};
const unsigned char MsgOpenTouch[6]={0x5A,0xA5,0x03,0x80,0x0B,0xff};
const unsigned char ItemTempSetAddr[4]={0x02,0x03,0x04,0x05};
const unsigned char ItemTimeSetAddr[8]={0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17};
const unsigned char MsgCloseLcd[7]={0x5A,0xA5,0x03,0x80,0x01,0x00};
const unsigned char MsgOpenLcd[7]={0x5A,0xA5,0x03,0x80,0x01,0x40};
const unsigned char MsgTimeRead[6]={0x5A,0xA5,0x03,0x81,0x20,0x07};
 unsigned char MsgTimeWrite[13]={0x5A,0xA5,0x0a,0x80,0x1f,0x5a,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //修改时间
const unsigned char MsgStartTimeRead[7]={0x5A,0xA5,0x04,0x83,0x00,0x03,0x01};
const unsigned char MsgEndTimeRead[7]=  {0x5A,0xA5,0x04,0x83,0x00,0x05,0x01};
const unsigned char MsgTimeSetTempRead[7]=  {0x5A,0xA5,0x04,0x83,0x00,0x04,0x01};
const unsigned char MsgMainSetTempRead[7]=  {0x5A,0xA5,0x04,0x83,0x00,0x02,0x01};
const unsigned char MsgOpenBeen10ms[6]={0x5A,0xA5,0x03,0x80,0x02,0x0A};
const unsigned char MsgShowMainPage[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x00};
const unsigned char MsgShowSetTempPageFireHigh[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x02};
const unsigned char MsgShowSetTempPageFireLow[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x03};
const unsigned char MsgShowSetTempPageWaterHigh[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x04};
const unsigned char MsgShowSetTempPageWaterLow[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x05};
const unsigned char MsgShowSetTimePageOneH[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x06};
const unsigned char MsgShowSetTimePageTwoH[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x08};
const unsigned char MsgShowSetTimePageThrH[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0A};
const unsigned char MsgShowSetTimePageForH[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0C};
const unsigned char MsgShowSetTimePageOneL[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x07};
const unsigned char MsgShowSetTimePageTwoL[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x09};
const unsigned char MsgShowSetTimePageThrL[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0B};
const unsigned char MsgShowSetTimePageForL[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0D};
const unsigned char MsgShowHandSetPage[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0E}; 
const unsigned char MsgShowWringSE[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x02}; //传感器异常
const unsigned char MsgShowWringTE[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x03}; //高温
const unsigned char MsgShowWringWA[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0e}; //加热异常
const unsigned char MsgShowWringTDV[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x0f}; //温差告警


const unsigned char MsgShowSRconfig[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x04}; //显示单屋配置界面
const unsigned char MsgShowMHconfig[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x07}; //显示多屋配置界面
const unsigned char MsgShowconfig[7]={0x5A,0xA5,0x04,0x80,0x03,0x00,0x08}; //显示配置界面
unsigned char MsgSetData[8]={0x5A,0xA5,0x05,0x82,0x00,0x01,0x00,0x25};

void CloseTouch(void)
{
	  UART2_SendString((unsigned char *)MsgCloseTouch,6);
}
void OpenTouch(void)
{
	  UART2_SendString((unsigned char *)MsgOpenTouch,6);
}


void CloseLcd(void)
{
  UART2_SendString((unsigned char *)MsgCloseLcd,6);
}
void OpenLcd(void)
{
  UART2_SendString((unsigned char *)MsgOpenLcd,6);
}
void ShowMainPage(void)
{
  UART2_SendString((unsigned char *)MsgShowMainPage,7);
}
void ShowTempSetPageFireHigh(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTempPageFireHigh,7);
}
void ShowTempSetPageFireLow(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTempPageFireLow,7);
}
void ShowTempSetPageWaterHigh(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTempPageWaterHigh,7);
}
void ShowTempSetPageWaterLow(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTempPageWaterLow,7);
}
void ShowTimeSetPageOneH(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageOneH,7);
}
void ShowTimeSetPageTwoH(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageTwoH,7);
}
void ShowTimeSetPageThrH(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageThrH,7);
}
void ShowTimeSetPageForH(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageForH,7);
}
void ShowTimeSetPageOneL(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageOneL,7);
}
void ShowTimeSetPageTwoL(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageTwoL,7);
}
void ShowTimeSetPageThrL(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageThrL,7);
}
void ShowTimeSetPageForL(void)
{
  UART2_SendString((unsigned char *)MsgShowSetTimePageForL,7);
}
void ShowHandSetPage(void)
{
  UART2_SendString((unsigned char *)MsgShowHandSetPage,7);
}


void SetFaFunctionTemp(void)
{
			
		MsgSetData[7]=FaFunctionSta[0];
		MsgSetData[5]=FaFunction1;		
		UART2_SendString((unsigned char *)MsgSetData,8);

		MsgSetData[7]=FaFunctionSta[1];
		MsgSetData[5]=FaFunction2;		
		UART2_SendString((unsigned char *)MsgSetData,8);

		MsgSetData[7]=FaFunctionSta[2];
		MsgSetData[5]=FaFunction3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	
		MsgSetData[7]=FaFunctionSta[3];
		MsgSetData[5]=FaFunction4;		
		UART2_SendString((unsigned char *)MsgSetData,8);

}
void SetFaStaTemp(unsigned char num)
{
//  MsgSetData[7]=num;
//  MsgSetData[5]=BackWaterAddr;
//  UART2_SendString((unsigned char *)MsgSetData,8);
	if(num & 0x01)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=FaNum1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=FaNum1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}		
	if(num & 0x02)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=FaNum2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=FaNum2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	if(num & 0x04 )
	{
		MsgSetData[7]=0;
		MsgSetData[5]=FaNum3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=FaNum3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	if(num & 0x08)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=FaNum4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=FaNum4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}	
}

void SetHandFireBurnerTemp(unsigned char num)
{
//  MsgSetData[7]=num;
//  MsgSetData[5]=BackWaterAddr;
//  UART2_SendString((unsigned char *)MsgSetData,8);
	if(num & 0x01)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}		
	if(num & 0x02)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	if(num & 0x04 )
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	if(num & 0x08)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}	
}

void SetPowerTemp(unsigned char num)
{
//  MsgSetData[7]=num;
//  MsgSetData[5]=BackWaterAddr;
//  UART2_SendString((unsigned char *)MsgSetData,8);
	if(num == 0)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}		
	else if(num == 1)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else if(num == 2)
	{
		
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else if(num == 3)
	{
		MsgSetData[7]=0;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
	else
	{
		MsgSetData[7]=1;
		MsgSetData[5]=PowerLvel1;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel2;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel3;		
		UART2_SendString((unsigned char *)MsgSetData,8);
		MsgSetData[5]=PowerLvel4;		
		UART2_SendString((unsigned char *)MsgSetData,8);
	}
}

void SetBackWaterTemp(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=BackWaterAddr;
  UART2_SendString((unsigned char *)MsgSetData,8);
}

void SetOutWaterTemp(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=OutWaterAddr;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetSetTemp(unsigned char index,unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=ItemTempSetAddr[index];
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetSetTime(unsigned char index,unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=ItemTimeSetAddr[index];
  UART2_SendString((unsigned char *)MsgSetData,8);
  delay_ms(100);
}
void SetMainStatus(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0000;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetHandStatus(unsigned char num)
{
 // MsgSetData[7]=num;
 // MsgSetData[5]=0x0020;
 // UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetWIFIStatus(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0009;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetWaterStatus(unsigned char num)
{
  //MsgSetData[7]=num;
  //MsgSetData[5]=0x0023;
  //UART2_SendString((unsigned char *)MsgSetData,8);
}
unsigned char FireFunFlag=0;
void SetFireRun(void)
{
	#ifdef MODE_Bouch 
  MsgSetData[7]=Power;
  MsgSetData[5]=0x0066;	
  #endif	
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetContralRun(void)
{
	#ifdef MODE_Bouch 
  MsgSetData[7]=ControlModel;
  MsgSetData[5]=0x0067;	
  #endif	
  UART2_SendString((unsigned char *)MsgSetData,8);
}
unsigned char WaterFunFlag=0;
void SetWaterRun(void)
{
	#ifndef MODE_Bouch   
  if(WaterFunFlag==0)
  {
    WaterFunFlag=1;    
  }
  else
  {
    WaterFunFlag=0;
  }
  MsgSetData[7]=WaterFunFlag;
  MsgSetData[5]=0x0022;
	#endif	
	#ifdef MODE_Bouch 
  MsgSetData[7]=WaterPump;
  MsgSetData[5]=0x0013;	
  #endif		
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetTimeHour(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0030;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetTimeMin(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0031;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void ShowWringPageSE(void)
{
  UART2_SendString((unsigned char *)MsgShowWringSE,7);
}
void ShowWringPageWA(void)
{
  UART2_SendString((unsigned char *)MsgShowWringWA,7);
}
void ShowWringPageTDV(void)
{
  UART2_SendString((unsigned char *)MsgShowWringTDV,7);
}

void ShowMHconfigPage(void)
{
  UART2_SendString((unsigned char *)MsgShowMHconfig,7);
}

void ShowSRconfigPage(void)
{
  UART2_SendString((unsigned char *)MsgShowSRconfig,7);
}

void ShowconfigPage(void)
{
  UART2_SendString((unsigned char *)MsgShowconfig,7);
}

void ShowWringPageTE(void)
{
  UART2_SendString((unsigned char *)MsgShowWringTE,7);
}
void LcdReadTime(void)
{
  UART2_SendString((unsigned char *)MsgTimeRead,6);
}

void LcdWriteTime(void)
{
	memcpy(&MsgTimeWrite[6],&NowTimer,7);
	UART2_SendString((unsigned char *)MsgTimeWrite,13);
}
void LcdReadStartTime(void)
{
  UART2_SendString((unsigned char *)MsgStartTimeRead,7);
}
void  LcdReadEndTime(void)
{
  UART2_SendString((unsigned char *)MsgEndTimeRead,7);
}
void LcdReadTimeSetTemp(void)
{
  UART2_SendString((unsigned char *)MsgTimeSetTempRead,7);
}
void RunStatues(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0012;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void FireStatues(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0041;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetStartTime(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0003;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetTempTime(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0004;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void SetEndTime(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=0x0005;
  UART2_SendString((unsigned char *)MsgSetData,8);
}

void LcdReadMainSetTemp(void)
{
  UART2_SendString((unsigned char *)MsgMainSetTempRead,7);
}
void SetMainTemp(unsigned char num)
{
  MsgSetData[7]=num;
  MsgSetData[5]=MainTempAddr;
  UART2_SendString((unsigned char *)MsgSetData,8);
}
void LcdOpenBEEP(void)
{
  UART2_SendString((unsigned char *)MsgOpenBeen10ms,6);
}
