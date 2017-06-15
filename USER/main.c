#include "include.h"

unsigned char fireStatues=0;
unsigned char Power=0;
unsigned char level=0;
unsigned int SaveCount = 0;
unsigned char WaterPump = 0;
unsigned char FireBurner = 0;
unsigned char HandWaterPump = 0;
unsigned char HandFireBurner = 0;
unsigned char TempNow = 0;
unsigned char TempNowHigh = 0;
unsigned char TempSetContralHigh = 45;
unsigned char TempSetContralLow = 25;
unsigned char TempSetWaterHigh = 50;
unsigned char TempSetWaterLow = 30;
unsigned char TempSetMain = 30;
unsigned char TempSetUseIng =0;
unsigned char TempSetItemSelectIndex = 0;

unsigned char TimeSetBegain[4], TimeSetEnd[4],TimeTepSet[4];
unsigned char TimeSetItemSelectIndex = 0;
unsigned char ShowItemIndex = 0;
unsigned char HandMode = 0;

unsigned char FaFunctionSta[4];
//unsigned char SetItemSelectIndex=0;

unsigned char PowerFlag = 0;
unsigned char RunFlag = 0;

unsigned char ShowSetItemPageFlag = 0;
unsigned char TimerBuf[6] = {0x30, 0x31, ':', 0x31, 0x32, 0x00};

unsigned char ID[9] = {0x31, 0x36, 0x30, 0x38, 0x30, 0x32, 0x30, 0x32, 0x00};
unsigned char RegisteCode[4] = {0};
unsigned char RegisteFlag = 0;
unsigned char RegisterCount = 0,WifiSendCount=0;;
unsigned char IP[17];
unsigned char IPPORT[6];
unsigned char WifiName[32];
unsigned char WifiPass[32];
unsigned short WifiSendFlag=0;
unsigned char NetStatus = 0;

unsigned char WringFlag = 0;
unsigned char WringShowFlag = 0;
unsigned char LowTemp = 0;
unsigned char TimeContral = 0;
unsigned char TimeHourNow = 0;
unsigned char WIFIMODELChangle = 0;
unsigned char Wifi = 0;
unsigned char WifiCheckCount = 0;
unsigned char ControlModel = 0;//0->独立控制 1->分屋控制
void heapsort(unsigned short arr[], unsigned char N)
{
	unsigned int n = N, i = n / 2, parent, child;
	int t;

	for (;;) /* Loops until arr is sorted */
	{
		if (i > 0) /* First stage - Sorting the heap */
		{
			i--;		/* Save its index to i */
			t = arr[i]; /* Save parent value to t */
		}
		else /* Second stage - Extracting elements in-place */
		{
			n--; /* Make the new heap smaller */
			if (n == 0)
				return;		 /* When the heap is empty, we are done */
			t = arr[n];		 /* Save last value (it will be overwritten) */
			arr[n] = arr[0]; /* Save largest value at the end of arr */
		}

		parent = i;		   /* We will start pushing down t from parent */
		child = i * 2 + 1; /* parent's left child */

		/* Sift operation - pushing the value of t down the heap */
		while (child < n)
		{
			if (child + 1 < n && arr[child + 1] > arr[child])
			{
				child++; /* Choose the largest child */
			}
			if (arr[child] > t) /* If any child is bigger than the parent */
			{
				arr[parent] = arr[child]; /* Move the largest child up */
				parent = child;			  /* Move parent pointer to this child */
				//child = parent*2-1; /* Find the next child */
				child = parent * 2 + 1; /* the previous line is wrong*/
			}
			else
			{
				break; /* t's place is found */
			}
		}
		arr[parent] = t; /* We save t in the heap */
	}
}

extern float Get_PT100_tmp(float tmp);
extern vu16 AD_Value[200][4];
u32 val = 0;
float TmpNow[4];
void GetTmpVal()
{
	u8 j;
	for (j = 0; j < 4; j++)
	{

		u8 i;
		u16 tmpbuf[200];
		for (i = 0; i < 200; i++)
		{
			tmpbuf[i] = AD_Value[i][j];
		}
		heapsort(tmpbuf, 200);
		for (i = 50; i < 150; i++)
		{
			val += tmpbuf[i];
		}
		if (j == 3)
		{
			float v = ((float)val / 100 / 4096 * 3.3) * 10;
			TmpNow[j] = v;
		}
		else
			TmpNow[j] = Get_PT100_tmp((float)val / 100 / 4096 * 3.3);
		val = 0;
	}
}
void OutGpioInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);							 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);				
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_3; //GPIOB0,3,5,6,7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;								
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //？？？？GPIOB4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;								 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);//为什么没有 GPIOB3

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7 |GPIO_Pin_8| GPIO_Pin_11;		//GPIOA6,7,8,11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  
	GPIO_ResetBits(GPIOA, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
}
void InGpioInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);							
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);																
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;							 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								 
	GPIO_Init(GPIOB, &GPIO_InitStructure);											 
}
void SaveConfig()
{
	unsigned char Buffer[160], i, lenght = 0;
	Buffer[lenght++] = 0x55;
	Buffer[lenght++] = 0x55;
	memcpy(&Buffer[lenght], ID, 8);
	lenght += 8;
	Buffer[lenght++] =TempSetMain;
	for (i = 0; i < 4; i++)
	{
		Buffer[lenght++] = TimeSetBegain[i];
		Buffer[lenght++] = TimeTepSet[i];		
		Buffer[lenght++] = TimeSetEnd[i];
	}
	Buffer[lenght++]=Power ;
	Buffer[lenght++]=ControlModel;
	for (i = 0; i < 4; i++)
	{
	 Buffer[lenght++] = FaFunctionSta[i];
	}
	STMFLASH_Write(0x800ec00, (unsigned short *)Buffer, 80);
}
void ReadConfig()
{
	unsigned char Buffer[160], lenght = 0, i;
	STMFLASH_Read(0x800ec00, (unsigned short *)Buffer, 80);
	if (Buffer[lenght] != 0x55)
	{
		Buffer[lenght++] = 0x55;
	  Buffer[lenght++] = 0x55;
	  memcpy(&Buffer[lenght], ID, 8);
	  lenght += 8;
	  Buffer[lenght++] =TempSetMain;
	  for (i = 0; i < 4; i++)
	  {
		 Buffer[lenght++] = TimeSetBegain[i];
		 Buffer[lenght++] = 25;		
		 Buffer[lenght++] = TimeSetEnd[i];
	  }
		Buffer[lenght++] = 1;
		Buffer[lenght++]=0;
	  for (i = 0; i < 4; i++)
	  {
		 Buffer[lenght++] = FaFunctionSta[i];
	  }
		STMFLASH_Write(0x800ec00, (unsigned short *)Buffer, 80);
		STMFLASH_Read(0x800ec00, (unsigned short *)Buffer, 80);
	}
	lenght = 2;
	memcpy(ID, &Buffer[lenght], 8);
	lenght += 8;
	TempSetMain=Buffer[lenght++] ;
	for (i = 0; i < 4; i++)
	{
		TimeSetBegain[i] = Buffer[lenght++];
		TimeTepSet[i]= Buffer[lenght++];	
		TimeSetEnd[i] = Buffer[lenght++];
	}
	Power=Buffer[lenght++] ;
	ControlModel = Buffer[lenght++];
	for (i = 0; i < 4; i++)
	{
		FaFunctionSta[i] = Buffer[lenght++];
	}	
}

void ShowTempSet(unsigned char SetItemIndex)//设定燃机温度上下限 水泵温度上下限
{
	switch (SetItemIndex)
	{
	case 1:
		ShowTempSetPageFireHigh();
		SetSetTemp(SetItemIndex - 1, TempSetContralHigh);
		break;
	case 2:
		ShowTempSetPageFireLow();
		SetSetTemp(SetItemIndex - 1, TempSetContralLow);
		break;
	case 3:
		ShowTempSetPageWaterHigh();
		SetSetTemp(SetItemIndex - 1, TempSetWaterHigh);
		break;
	case 4:
		ShowTempSetPageWaterLow();
		SetSetTemp(SetItemIndex - 1, TempSetWaterLow);
		break;
	}
}
void ShowTimeSet(unsigned char SetItemIndex)//设置时段
{
	switch (SetItemIndex)
	{
	case 1:
		ShowTimeSetPageOneH();
		SetSetTime(0, TimeSetBegain[0]);
		SetSetTime(1, TimeSetEnd[0]);
		break;
	case 2:
		ShowTimeSetPageOneL();
		SetSetTime(0, TimeSetBegain[0]);
		SetSetTime(1, TimeSetEnd[0]);
		break;
	case 3:
		ShowTimeSetPageTwoH();
		SetSetTime(2, TimeSetBegain[1]);
		SetSetTime(3, TimeSetEnd[1]);
		break;
	case 4:
		ShowTimeSetPageTwoL();
		SetSetTime(2, TimeSetBegain[1]);
		SetSetTime(3, TimeSetEnd[1]);
		break;
	case 5:
		ShowTimeSetPageThrH();
		SetSetTime(4, TimeSetBegain[2]);
		SetSetTime(5, TimeSetEnd[2]);
		break;
	case 6:
		ShowTimeSetPageThrL();
		SetSetTime(4, TimeSetBegain[2]);
		SetSetTime(5, TimeSetEnd[2]);
		break;
	case 7:
		ShowTimeSetPageForH();
		SetSetTime(6, TimeSetBegain[3]);
		SetSetTime(7, TimeSetEnd[3]);
		break;
	case 8:
		ShowTimeSetPageForL();
		SetSetTime(6, TimeSetBegain[3]);
		SetSetTime(7, TimeSetEnd[3]);
		break;
	}
}
unsigned char WringPageChangeCount = 10;
unsigned char WringShowNowNum = 0;
void ShowWring()
{
	unsigned char i;
	if (WringPageChangeCount++ > 10)
	{
		WringPageChangeCount = 0;
		for (i = WringShowNowNum; i < 4; i++)
		{
			if (WringFlag >> i & 0x01)
			{
				switch (i)
				{
				case 0:
					ShowWringPageSE();//传感器异常
					WringShowNowNum = 1;
					return;
				case 1:
					ShowWringPageWA();//传感器异常
					WringShowNowNum = 2;
					return;
				case 2:
					ShowWringPageTDV();//传感器异常
					WringShowNowNum = 3;
					return;
					
				case 3://高温
					ShowWringPageTE();
					WringShowNowNum = 0;
					return;
				}
			}
		}
		if (WringShowNowNum == 4)
			WringShowNowNum = 0;
	}
}
static char WIFI_StrEqual(unsigned char *src, unsigned char* dst)
{
	unsigned char len, i;
	u8 startEquai[4]={0};
	u8 OverEquai[4]={0};
	memcpy(startEquai,src,4);
	memcpy(OverEquai,dst,4);
//	len = strlen((const char *)startEquai);
//	if (strlen(startEquai) > 4)
//		return 0;
//	if (strlen(OverEquai) > 4)
//		return 0;
	for (i = 0; i < 4; i++)
	{
		if (startEquai[i] != OverEquai[i])
			return 0;
	}
	return 1;
}
void usart1_rev(unsigned char *str, unsigned short len)//wifi 通讯
{
	
	unsigned char check = 0;
	unsigned short i;
	if (strstr((const char *)str, "STA:OK") != NULL)
	{
		Wifi = 1;
	}
	if (strstr((const char *)str, "STA:DOWN") != NULL)
	{
		Wifi = 0;
	}
	check = 0;
	for (i = 1; i < len - 2; i++)
	{
		check ^= str[i];
	}
	if (check == str[len-2])
	{
		WifiSendFlag=0;
		if (str[1] == 0x72)
		{
			Server *SerResponse = (Server *)str;
			if (SerResponse->result == 1)
			{
				//OK
			}
			else if (SerResponse->result == 2)
			{
				//ERR RESEND
        WifiSendRealTimeData();
				if (WifiSendCount++ > 2)
				{
					WifiSendCount = 0;
					RegisteFlag = 0;
				}
			}
		}
		else if (str[1]== 0x71)
		{
			Rev_Register *REV=(Rev_Register*)str;
//			if (REV->result == 1)
//			{
				memcpy(RegisteCode, REV->registration_key, 4);
				RegisteFlag = 1;
//			}
//			else
//			{
//				WifiSendRegister();
//				if (RegisterCount++ > 2)
//				{
//					RegisterCount = 0;
//					WifiReStart();
//				}
//			}
		} 
		else if(str[1]==0x73)
		{
			WifiCon_Get *rev=(WifiCon_Get*)str;
		  if (WIFI_StrEqual(RegisteCode,rev->Secret_Key)) //RegisterKey==rev->Secret_Key
		  {
			unsigned char temp,tempc;
			temp=rev->setaddr;
			switch(temp)
			{
				case 0x01:									//后台传输设置温度 为ASC码   其它传输为  16进制	
				{
					TempSetMain = ((str[8]&0x0f)*10+(str[9]&0x0f));
					if(TempSetMain>60)
					{
						TempSetMain=60;
					}				
					SaveConfig();
					SetMainTemp(TempSetMain);
					break;
				} 
				case 0x02:
				{
					Power = rev->data;
					if(Power > 0x04)
						Power =0x01;
					SaveConfig();
					break;
				}
				case 0x03:
				{
					RunFlag=rev->data; 				
						break;
				 }
				case 0x04:
				{
				  ControlModel = rev->data;
					SaveConfig();
					OpenSetFa();	
					break;					
				}
				default:
					break;						
			}
//			  TempSetMain = temp;
//        SaveConfig();
//			if(TempSetMain>40)
//			{
//			      TempSetMain=40;
//			}
//			SetMainTemp(TempSetMain);
//			FirstRun=0;
//			RunFlag=rev->work; 	
//			if(RunFlag==0)
//			 {
//				WringFlag=0;
//			 }
			WifiClientDeal(1);					
		  }

		}
	}
}
//#ifndef MODE_Bouch   
//void usart2_rev(unsigned char *str, unsigned short len)
//{
//	 if(str[0]==0x5A&&str[1]==0xA5)
//  {
//		 switch (str[4])
//			{
//			case 0x24:
//			{					
//			  TimeHourNow=(str[6]>>4)*10+(str[6]&0x0f);	
//				break;
//			}			
//			case 0x25:
//			{			
//				 break;
//			}		
//			default:
//			break;
//			}	
//  }
//}
//	#endif

static char RevBack(unsigned char OlderBuf,unsigned char *output)
{       
				u8 len=0,i,check=0;
			  output[len++]=0xAA;
				output[len++]=OlderBuf;
				output[len++]=0x01;
				for(i=1;i<len;i++)
				{
				check+=output[i];
				}
				output[len++]=check;
				output[len++]=0x55;
				return len;
}
void usart3_rev(unsigned char *str, unsigned short len)
{
  if(str[0]==0xaa&&str[len-1]==0x55)
  {
		  u8 check=0;
      u32 i;
      for(i=1;i<len-2;i++)	
     {	
			 check+=str[i];
		 }
     if(check==str[len-2])	
		 {
        u8 BufBack[20]={0};
				u8 LenBack=0;	
        LenBack=RevBack(str[1],BufBack);
				switch(str[1])
				{
//					if(str[1]==0x01)
//					{
//						memset(ID,0,9);
//						memcpy(ID,&str[2],8);
//						UART3_SendString(ID,strlen(ID));
//						SaveConfig();
//					}
					case 0x11:
					{
						memset(ID,0,9);
						memcpy(ID, &str[2],8); 
						SaveConfig();
						UART3_SendString(BufBack,LenBack);			
						break;
					}
						
				}
			}
	}
}
int main(void)
{
 	SystemInit();   //??????RCC ?????ì?????ì??????????????72MHZ
	delay_init(72); //??????????? 

	USART1_Config();
	UartDataRev[0].RevHandler = usart1_rev;//WIFI
	USART2_Config();
	UartDataRev[1].RevHandler = usart2_rev;//LCD
	USART3_Config();
	UartDataRev[2].RevHandler = usart3_rev;//串口写ID

  delay_ms(300);	

	
	ReadConfig();
// delay_ms(1000); //等待系统稳定        
	ADC1_Init();

	GetTmpVal();
	OutGpioInit();
	InGpioInit();
  BEEPFLAG=30;
  OpenBEEP();
	OpenBEEP();
	CloseTouch();//关闭触屏的触摸功能 (发现初始化后触屏有数据发出)


  SetStartTime(TimeSetBegain[0]);
	delay_ms(10);
	SetTempTime(TimeTepSet[0]);
	delay_ms(10);
	SetEndTime(TimeSetEnd[0]);
	delay_ms(10);
	SetMainTemp(TempSetMain);
	delay_ms(10);

  delay_ms(5000); //未起作用
	MainrunTmp = 0;
  PowerFlag=1;	
	ShowMainPage();

	OpenSetFa();
	ChackAutoFa();
  AutoFunctionNum = CheckFaFunctionNum(2);
  LcdReadTime();
	TIM3_Int_Init(49, 7199);	//5ms
	LcdOpenTouchtimer = 1;
	while (1)
	{
		GetTmpVal();
		TempNow = TmpNow[0];
	  TempNowHigh = TmpNow[1];
		delay_ms(200);	
		if(LcdOpenTouchflg == 1)
		{
			OpenTouch();
			LcdOpenTouchflg = 0;
		}
		#ifdef MODE_Bouch 
		switch (WifiCheckCount++)
			{
			case 20:
				UART1_SendString("AT+STASTATUS", 12);
				break;
			case 30:
				if(RegisteFlag==1&&WifiSendFlag==0)
				{
				  WifiSendFlag=1;
				  WifiSendRealTimeData();
				}

				break;
			case 40:
				WifiCheckCount = 0;
				break;
			}
			if(Wifi==1&&RegisteFlag==0&&WifiSendFlag==0)
			{
			  WifiSendFlag=1;
			  WifiSendRegister();
			}
			if (Wifi == 1)//WIFI图标
			{
				SetWIFIStatus(1);
			}
			else
			{
				SetWIFIStatus(0);
			}
			
			if(GetNowTimeFlag)
			{
				LcdReadTime();
				GetNowTimeFlag = 0;
			}				
    MainRun();	
    RunStatues(RunFlag);
			//		delay_ms(1000);	
    FireStatues(fireStatues);		
			//		delay_ms(1000);				
		SetBackWaterTemp(TempNow);
			//		delay_ms(1000);	
		SetOutWaterTemp(TempNowHigh);
			//		delay_ms(1000);	
		if(WriteLcdTimeFlag == 1)
		{
			WriteLcdTimeFlag = 0;
			LcdWriteTime();
		}
				if(fireStatues == 1)
		{
			SetPowerTemp(Power);
		}
		else
		{
			SetPowerTemp(4);//关闭所有的加热状态显示
		}
		if(HandMode == 1)
		{
			SetHandFireBurnerTemp(HandFireBurner);
		}
		SetFaStaTemp(FaSta);
		//					delay_ms(1000);	
		SetWaterRun();
		//					delay_ms(1000);	
		SetFireRun();
		//					delay_ms(1000);	
		SetContralRun();
		//					delay_ms(1000);	
		SetFaFunctionTemp();
		//		      delay_ms(1000);			
		if (WringFlag != 0)
		{
				ShowWring();
		}
		#endif	

	}

}
void KeyScreen()
{

}

