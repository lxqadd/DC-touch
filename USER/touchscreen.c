#include "include.h"
#include "string.h"
#include "touchscreen.h"
u8 Uart2RevBuf[20];
u8 TimeInterval=0;

Time NowTimer;
u8 GetNowTimeFlag = 0;
u8 WriteLcdTimeFlag = 0;
u8 mon_table[12]={0x31,0x28,0x31,0x30,0x31,0x30,0x31,0x31,0x30,0x31,0x30,0x31};
u8 OutsideFlg = 0;

//判断是否是闰年函数
//月份   1  2  3  4  5  6  7  8  9  10 11 12
//闰年   31 29 31 30 31 30 31 31 30 31 30 31
//非闰年 31 28 31 30 31 30 31 31 30 31 30 31
//输入:年份
//输出:该年份是不是闰年.1,是.0,不是
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	

void usart2_rev(unsigned char *str, unsigned short len)
{ unsigned char tmp;
	memset(Uart2RevBuf,0,20);
	memcpy(Uart2RevBuf,str,len);
 if(str[0]==0x5A&&str[1]==0xA5)
  {	
		  if((str[3]==0x81)&&(str[4]==0x20))
			{
				memcpy(&NowTimer, &str[6], 7);
			TimeHourNow=(NowTimer.hour>>4)*10+(NowTimer.hour&0x0f);
			return;
			}
      switch (str[5])
			{		
			case 0x02:
			{
        SaveCount=1;				
				TempSetMain=str[8];			
				break;
			}	
			case 0x03://启动时间
			{	
				TimeSetBegain[TimeInterval]=str[8];				
				break;
			}	
			case 0x04://设定温度
			{	
				TimeTepSet[TimeInterval]=str[8];				
				break;
			}	
			case 0x05://停止时间
			{			
				TimeSetEnd[TimeInterval]=str[8];					
				break;
			}

			case 0x10://控制显示是多屋单屋配置界面
			{
					if(ControlModel == 0)	
					{	
						ShowSRconfigPage();
					}
					else if(ControlModel == 1)
					{
						ShowMHconfigPage();
					}					
					else 	
					{
						ControlModel = 0;
						ShowSRconfigPage();
						SaveConfig();
					};						
				break;			
			}
			
			case 0x12:
			{	
//				if(HandMode==0)
//				{ 
						if (WringFlag)
					{
						WringFlag = 0;
						WringShowNowNum=0;			
						WringShowFlag = 0;
						RunFlag=0;
						HandMode=0;					
					}
					else
					{	
						if (RunFlag == 0)
						{
						 RunFlag = 1;
						}
						else
						{		
						 RunFlag = 0;		
						}
						CloseWatePump();
						CloseFireBurner();
						LowTemp = 0;
						RunStatues(RunFlag);
					}        
//				}					
				break;
			}		

			case 0x13://水泵
			{	
					HandMode=1;
				 if(str[8]==0x01)
				 {
				  HandWaterPump=1;
				 }
				 else
         {
				 HandWaterPump=0;
				 }		
				 break;
			}					

			case 0x15:
			{	
        TimeInterval=str[8];	
        SetStartTime(TimeSetBegain[TimeInterval]);
	      SetTempTime(TimeTepSet[TimeInterval]);
	      SetEndTime(TimeSetEnd[TimeInterval]);				
				break;
			}	
			case 0x17:
			{	
        SaveConfig();		
				break;
			}	
			case 0x18:
			case 0x19:
			case 0x1A:
			case 0x1B:
			{	
        if (WringFlag)
			 {
				WringFlag = 0;
        WringShowNowNum=0;			
				WringShowFlag = 0;
        RunFlag=0;
				HandMode=0;	
				ShowMainPage(); 
				RunStatues(RunFlag);
			 }
				break;
			}	
			
			case 0x20://修改屏时间 月
			{
				NowTimer.moon ++;
				if(!((NowTimer.moon&0x0f)-10))
				{
					NowTimer.moon += 6;
				}
				if(NowTimer.moon > 0x12)
					NowTimer.moon = 0x01;
				WriteLcdTimeFlag = 1;
				break;
			}
			case 0x21://修改屏时间 日
			{
				NowTimer.day ++;
				if(Is_Leap_Year(NowTimer.year +2000))
					mon_table[1] = 0x29;
				else
					mon_table[1] = 0x28;
				if(!((NowTimer.day&0x0f)-10))
				{
					NowTimer.day += 6;
				}
					
				if(NowTimer.day > mon_table[NowTimer.moon-1])
					NowTimer.day = 1;
				WriteLcdTimeFlag = 1;
				break;
			}
			case 0x22://修改屏时间 时
			{
				NowTimer.hour ++;
				if(!((NowTimer.hour&0x0f)-10))
				{
					NowTimer.hour += 6;
				}
				if(NowTimer.hour > 0x23)
					NowTimer.hour = 0;
				WriteLcdTimeFlag = 1;
				break;
			}
			case 0x23://修改屏时间 分
			{
				NowTimer.min++;
				if(!((NowTimer.min&0x0f)-10))
				{
					NowTimer.min += 6;
				}
				if(NowTimer.min > 0x59)
					NowTimer.min = 0;
				WriteLcdTimeFlag = 1;
				break;
			}			
			
			case 0x40:
			{
				if((str[7]==(unsigned char)(PASSWORD>>8))&&(str[8]==(((unsigned char)PASSWORD)&0xff)))//密码正确 进入不同的界面
				{//手动模式

					ShowconfigPage();
				}
				else
				{
					ShowMainPage();
				}
				break;
			}
	
			case 0x50:
			{
				HandMode = 1;		
				HandSetFa &= 0xf7;
				if(str[8] == 0)
					HandSetFa |= (0x01<<3);

				FaSta = HandSetFa;
				break;
			}
				case 0x51:
			{
				HandMode = 1;		
				HandSetFa &= 0xfb;
				if(str[8] == 0)
					HandSetFa |= (0x01<<2);
				FaSta = HandSetFa;
				break;
			}	
				case 0x52:
			{
				HandMode = 1;		
				HandSetFa &= 0xfd;
				if(str[8] == 0)
					HandSetFa |= (0x01<<1);			
				FaSta = HandSetFa;
				break;
			}		
				case 0x53:
			{
				HandMode = 1;		
				HandSetFa &= 0xfe;
				if(str[8] == 0)
					HandSetFa |= 0x01;
				FaSta = HandSetFa;
				break;
			}	

			
			case 0x56:
			{
				HandMode = 1;		
				HandFireBurner &= 0xf7;
				if(str[8] == 0)
					HandFireBurner |= (0x01<<3);
				break;
			}
				case 0x57:
			{
				HandMode = 1;		
				HandFireBurner &= 0xfb;
				if(str[8] == 0)
					HandFireBurner |= (0x01<<2);
				break;
			}	
				case 0x58:
			{
				HandMode = 1;		
				HandFireBurner &= 0xfd;
				if(str[8] == 0)
					HandFireBurner |= (0x01<<1);			
				break;
			}				
				case 0x59:
			{
				HandMode = 1;		
				HandFireBurner &= 0xfe;
				if(str[8] == 0)
					HandFireBurner |= 0x01;
				break;
			}	

			case 0x65:
			{
				 OutsideFlg = str[8];	
         if(OutsideFlg == 1)
				 {
				 		CloseWatePump();
						CloseFireBurner();
				 }	
					else if(OutsideFlg == 0)
					{
						OpenSetFa();	
					}
				 break;			
			}
      case 0x66://功率
			{	
          SaveCount=1;					
				 Power = str[8];
				 break;
			}	

			case 0x67://分屋
			{	
          SaveCount=1;					
				  ControlModel = str[8];
					OpenSetFa();	
				 break;
			}	
				case 0x68:
			{	
          SaveCount=1;					
				 FaFunctionSta[0] = str[8];
				 tmp=CheckFaFunctionNum(1);
					if(tmp == 4)
					{
						 FaFunctionSta[0] = 0;
					}
				
				 break;
			}		
				case 0x69:
			{		
          SaveCount=1;					
				 FaFunctionSta[1] = str[8];
				 tmp=CheckFaFunctionNum(1);
					if(tmp == 4)
					{
						 FaFunctionSta[1] = 0;
					}
				 break;
			}	
				case 0x6a:
			{		
          SaveCount=1;					
				 FaFunctionSta[2] = str[8];
				 tmp=CheckFaFunctionNum(1);
					if(tmp == 4)
					{
						 FaFunctionSta[2] = 0;
					}
				 break;
			}	
				case 0x6b:
			{		
          SaveCount=1;					
				 FaFunctionSta[3] = str[8];
				 tmp=CheckFaFunctionNum(1);
					if(tmp == 4)
					{
						 FaFunctionSta[3] = 0;
					}
				 break;
			}	
			
			case 0x90:
			case 0x91:
			{
					HandMode = 0;
					if(ControlModel == 0)	
					{	
						ShowSRconfigPage();
					}
					else if(ControlModel == 1)
					{
						ShowMHconfigPage();
//						RunFlag = 0;
//						RunStatues(RunFlag); 
//						HandFireBurner = 0;
//						HandMode = 0;	
						ChackAutoFa();						
						OpenSetFa();	
					}					
					else 	
					{
						ControlModel = 0;
						ShowSRconfigPage();
						SaveConfig();
					};		
				break;					
			}		
//			case 0x91:
//			{
//					if(ControlModel == 0)	
//					{	
//						ShowSRconfigPage();
//					}
//					else if(ControlModel == 1)
//					{
//						ShowMHconfigPage();
//					}					
//					else ;		
//				break;					
//			}
			case 0x92:
			{	
 				RunFlag = 0;
				RunStatues(RunFlag); 
				HandFireBurner = 0;
				HandMode = 0;		
				OpenSetFa();		
				break;
			}
/*
			case 0x11:
			{	
				RunFlag = 0;
				RunStatues(RunFlag);
				HandFireBurner = 0;
				HandWaterPump = 0;
				fireStatues=0;
        if(str[8]==0x01)//手动模式
				{
				HandMode = 1;				
				}
        else
				{
				HandMode = 0;
				}					
				break;
			}	

			case 0x13://水泵
			{	
				if(HandMode==1)
				{
				 if(str[8]==0x01)
				 {
				  HandWaterPump=1;
				 }
				 else
         {
				 HandWaterPump=0;
				 }		
				}
				 break;
			}		
			case 0x14://燃烧机
			{	 
				if(HandMode==1)
				{
         if(str[8]==0x01)
				 {
					fireStatues=1;
				  HandFireBurner=1;
				 }
				 else
         {
				  fireStatues=0;
				  HandFireBurner=0;
				 }
				}				        				
				 break;
			}
			*/
			

			default:
			break;
			}	
	}

}

