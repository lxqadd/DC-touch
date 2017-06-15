#include "include.h"

u8 Getnowtimercount;

void TIM3_Int_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //?±??????

	TIM_TimeBaseStructure.TIM_Period = arr;						//?è???????????ü??????×°????????×?????×°???????÷????????	 ??????5000??500ms
	TIM_TimeBaseStructure.TIM_Prescaler = psc;					//?è??????×÷??TIMx?±?????????????¤·?????  10Khz??????????
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//?è???±??·???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM?ò??????????
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);				//?ù??TIM_TimeBaseInitStruct?????¨????????????TIMx???±???ù??????

	TIM_ITConfig( //?????ò???§?????¨??TIM????
		TIM3,	 //TIM2
		TIM_IT_Update,
		ENABLE //????
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;			  //TIM3????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //??????????0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //????????3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQ?¨??±?????
	NVIC_Init(&NVIC_InitStructure);							  //?ù??NVIC_InitStruct?????¨???????????????èNVIC?????÷

	TIM_Cmd(TIM3, ENABLE); //????TIMx???è
}
unsigned char TimeCount = 0;
unsigned int LcdReadTimeCount = 0;
unsigned int LcdOpenTouchtimer = 0;//打开触屏 延时时间  （上电触屏发生触发）
unsigned char LcdOpenTouchflg = 0;

u32 ReadCount=0;
void TIM3_IRQHandler(void) //TIM3????
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //?ì?é???¨??TIM????·??ú??·?:TIM ??????
	{
		unsigned char i;

		if(BEEPFLAG--==0)
		{
		  CloseBEEP();
		}
		if(LcdOpenTouchtimer > 0)
		{
			LcdOpenTouchtimer++;
			if(LcdOpenTouchtimer == 0x3e8)
			{
				LcdOpenTouchflg = 1;
				LcdOpenTouchtimer = 0;
			}	
		}
		if (TimeCount++ > 20)
		{
			TimeCount = 0;
		}
		if(WifiSendFlag>0)
		{
		  if(WifiSendFlag++>1000)
		    WifiSendFlag=0;
		}
//		if(LcdReadTimeCount ++ > 1200)
//		{
//			LcdReadTimeCount=0;
//		  LcdReadTime();
//		}
		
		if(Getnowtimercount++ > 200)		//1s读取1次时间
		{
			GetNowTimeFlag = 1;
			Getnowtimercount = 0;
		}
		
    if(SaveCount>0)		
		{
		 if(SaveCount++>200)
		 {
		 SaveCount=0;
		 SaveConfig();	
		 AutoFunctionNum = CheckFaFunctionNum(2);
		 }
	  }
		if(fireStatues == 1)
		{
			openfiretimer ++;
		}
		else 
			openfiretimer = 0;
		
		if(closefiredelaytimer > 0)
		{
			if(closefiredelaytimer++ > CLOSEFIRE_DT)
			{
				RunFlag = 0;		
				closefiredelaytimer = 0;
			}
		}
		
		if(closewaterpumptimer > 0)
		{
			if((closewaterpumptimer++) > CLOSEWATERPUMP_TIME)
			{
//				RunFlag = 0;		
				CloseWatePump();
				closewaterpumptimer = 0;
				closewaterpumptimerflg = 0;
			}		
		
		}
		
		if(Freeze_prooftimer > 0)
		{
		 if(Freeze_prooftimer++ > FREEZEPROOFTIMER)
		 {
				Freeze_prooftimer = 0;
		 }	
		}
		
		for (i = 0; i < 3; i++)
		{
			if (UartDataRev[i].RevCount++ > 2 && UartDataRev[i].RevLength > 0)
			{
				UartDataRev[i].RevBuffer[UartDataRev[i].RevLength] = 0;
				UartDataRev[i].RevHandler(UartDataRev[i].RevBuffer, UartDataRev[i].RevLength);
                                UartDataRev[i].RevLength=0;
			}
		}		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //????TIMx???????????í??:TIM ??????
	}
}
