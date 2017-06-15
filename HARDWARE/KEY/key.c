#include "include.h"

#define KEY_POWER GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)
#define KEY_OPEN GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)
#define KEY_SET GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)
#define KEY_TIME GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)
#define KEY_UP GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)
#define KEY_DOWN GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
#define changanjishi 10
unsigned char KeyLast = 0;
unsigned char KeyUP = 0;
unsigned char changan_key0 = 0;
unsigned char changan_key1 = 0;
unsigned char changan_key2 = 0;
unsigned char changan_key3 = 0;
unsigned char changan_key4 = 0;
unsigned char changan_key5 = 0;
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);														   //????GPIOA?¡À??
																												   //????1????????????????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //GPIOA9??GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;														   //????????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;															   //????50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);																		   //??????PA9??PA10
}
void POWERKeyDot()
{
	if (PowerFlag == 0)
	{
		ShowSetItemPageFlag = 2;
		PowerFlag = 1;
	}
	else
	{
		ShowSetItemPageFlag = 0;
		ShowItemIndex = 0;
		PowerFlag = 0;
		WringFlag = 0;
    WringShowNowNum=0;
		WringShowFlag = 0;
	}
}
void OPENKeyDot()
{
	if (PowerFlag == 1)
	{
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
	     	RunStatues(RunFlag);
      }
	}
}
void SETKeyDot()
{
	if (PowerFlag == 1)
	{
		ShowItemIndex++;
		if (ShowItemIndex == 4)
		{
			ShowItemIndex = 0;
		}
		if (ShowItemIndex == 1)
		{
			TempSetItemSelectIndex = 1;
		}
		else if (ShowItemIndex == 2)
		{
			TimeSetItemSelectIndex = 1;
		}
		if (ShowItemIndex != 3)
		{
			HandMode = 0;
		}
	}
}
void TIMEKeyDot()
{
	
}
void UPKeyDot()
{
	
}
void DOWNKeyDot()
{
	if (PowerFlag == 1)
	{
		if(ShowItemIndex==0)
		{
		      TempSetMain--;
			if (TempSetMain == 80)
					TempSetMain = 1;	
		}
		if (ShowItemIndex == 1)
		{
			if (TempSetItemSelectIndex == 1)
			{
				if (TempSetContralHigh == 0)
					TempSetContralHigh =  1;
				TempSetContralHigh--;
			}
			else if (TempSetItemSelectIndex == 2)
			{
				if (TempSetContralLow == 0)
					TempSetContralLow = 1;
				TempSetContralLow--;
			}
			else if (TempSetItemSelectIndex == 3)
			{
				if (TempSetWaterHigh == 0)
					TempSetWaterHigh = 1;
				TempSetWaterHigh--;
			}
			else if (TempSetItemSelectIndex == 4)
			{
				if (TempSetWaterLow == 0)
					TempSetWaterLow = 1;
				TempSetWaterLow--;
			}
		}
		else if (ShowItemIndex == 2)
		{
			if (TimeSetItemSelectIndex % 2 == 1)
			{
				if (TimeSetBegain[TimeSetItemSelectIndex / 2] == 0)
					TimeSetBegain[TimeSetItemSelectIndex / 2] = 24;
				TimeSetBegain[TimeSetItemSelectIndex / 2]--;
			}
			else if (TimeSetItemSelectIndex % 2 == 0)
			{
				if (TimeSetEnd[TimeSetItemSelectIndex / 2 - 1] <= TimeSetBegain[TimeSetItemSelectIndex / 2 - 1])
					TimeSetEnd[TimeSetItemSelectIndex / 2 - 1] = TimeSetBegain[TimeSetItemSelectIndex / 2 - 1] + 1;
				if (TimeSetEnd[TimeSetItemSelectIndex / 2 - 1] == 0)
					TimeSetEnd[TimeSetItemSelectIndex / 2 - 1] = 24;
				TimeSetEnd[TimeSetItemSelectIndex / 2 - 1]--;
			}
		}
		else if (ShowItemIndex == 3)
		{
			if (HandMode == 1)
			{
				if (HandWaterPump == 0)
				{
					HandWaterPump = 1;
				}
				else
				{
					HandWaterPump = 0;
				}
			}
		}
	}
}
void POWERKeyLongDot()
{
}
void OPENKeyLongDot()
{
}
void SETKeyLongDot()
{
		SaveConfig();
		ShowSetItemPageFlag = 2;
		ShowItemIndex = 0;	
}
void TIMEKeyLongDot()
{
}
void UPKeyLongDot()
{
	if (ShowItemIndex == 4)
	{
		WifiSendFlag = 1;
	}
}
void DOWNKeyLongDot()
{
}
void key_scan()
{
	if (KEY_POWER & KEY_OPEN & KEY_SET & KEY_TIME & KEY_UP & KEY_DOWN & KeyLast == 0)
	{
		KeyUP = 1;
	}
	else
	{
		if (KeyLast == 0)
		{
			if (!KEY_POWER)
			{
				KeyLast = 1;
				OpenBEEP();
			}
			else if (!KEY_OPEN)
			{
				KeyLast = 2;
				if (PowerFlag == 1)
					OpenBEEP();
			}
			else if (!KEY_SET)
			{
				KeyLast = 3;
				if (PowerFlag == 1)
					OpenBEEP();
			}
			else if (!KEY_TIME)
			{
				KeyLast = 4;
				if (PowerFlag == 1)
					OpenBEEP();
			}
			else if (!KEY_UP)
			{
				KeyLast = 5;
				if (PowerFlag == 1)
					OpenBEEP();
			}
			else if (!KEY_DOWN)
			{
				KeyLast = 6;
				if (PowerFlag == 1)
					OpenBEEP();
			}
		}
		else
		{
			switch (KeyLast)
			{
			case 1:
			{
				if (KEY_POWER == 1 && changan_key0 < changanjishi) //??¡ã??¨¹
				{
					KeyLast = 0;
					KeyUP = 0;
					changan_key0 = 0;
					POWERKeyDot();
				}
				else if (KEY_POWER == 1 && changan_key0 > changanjishi) //?¡è¡ã??¨¹
				{
					changan_key0 = 0;
					KeyLast = 0;
					KeyUP = 0;
					POWERKeyLongDot();
				}
				if (changan_key0++ > changanjishi) //&& wificonok != 2
				{
				}
				break;
			}
			case 2:
			{
				if (KEY_OPEN == 1 && changan_key1 < changanjishi)
				{
					changan_key1 = 0;
					KeyLast = 0;
					KeyUP = 0;
					OPENKeyDot();
				}
				else if (KEY_OPEN == 1 && changan_key1 > changanjishi)
				{
					changan_key1 = 0;
					KeyLast = 0;
					KeyUP = 0;
					OPENKeyLongDot();
				}
				if (changan_key1++ > changanjishi)
				{
					if (PowerFlag == 1)
						OpenBEEP();
				}
				break;
			}
			case 3:
			{
				if (KEY_SET == 1 && changan_key2 < changanjishi)
				{
					KeyLast = 0;
					KeyUP = 0;
					changan_key2 = 0;
					if (WringFlag == 0)
						SETKeyDot();
				}
				else if (KEY_SET == 1 && changan_key2 > changanjishi)
				{
					changan_key2 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						SETKeyLongDot();
				}
				if (changan_key2++ > changanjishi)
				{
					if (PowerFlag == 1)
						OpenBEEP();
				}
				break;
			}
			case 4:
			{
				if (KEY_TIME == 1 && changan_key3 < changanjishi)
				{
					changan_key3 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						TIMEKeyDot();
				}
				else if (KEY_TIME == 1 && changan_key3 > changanjishi)
				{
					changan_key3 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						TIMEKeyLongDot();
				}
				if (changan_key3++ > changanjishi)
				{
					if (PowerFlag == 1)
						OpenBEEP();
				}
				break;
			}
			case 5:
			{
				if (KEY_UP == 1 && changan_key4 < changanjishi)
				{
					changan_key4 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						UPKeyDot();
				}
				else if (KEY_UP == 1 && changan_key4 > changanjishi)
				{
					changan_key4 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						UPKeyLongDot();
				}
				if (changan_key4++ > changanjishi)
				{
					if (PowerFlag == 1)
						OpenBEEP();
				}
				break;
			}
			case 6:
			{
				if (KEY_DOWN == 1 && changan_key5 < changanjishi)
				{
					changan_key5 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						DOWNKeyDot();
				}
				else if (KEY_DOWN == 1 && changan_key5 > changanjishi)
				{
					changan_key5 = 0;
					KeyLast = 0;
					KeyUP = 0;
					if (WringFlag == 0)
						DOWNKeyLongDot();
				}
				if (changan_key5++ > changanjishi)
				{
					if (PowerFlag == 1)
						OpenBEEP();
				}
				break;
			}
			}
		}
	}
}

